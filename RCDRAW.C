/* RCDRAW.C - Text-mode rendering engine with page flipping       */
/* Supports 40-col (mode 1) and 80-col (mode 3) via settings     */

#include "raycast.h"

/* Current video state */
static unsigned char orig_mode;     /* saved video mode for restore */
static int draw_page;               /* 0 or 1: which page we draw to */
static VIDMEM pages[2];             /* far pointers to page 0 and 1 */

/* Ceiling and floor VRAM words */
#define CEIL_CELL   TC(' ', 0x00)           /* black space */
#define FLOOR_CELL  TC(0xB0, 0x08)          /* dark floor pattern */
#define BLANK_CELL  TC(' ', 0x00)            /* empty cell */
#define WALL_CONST_2X (WALL_CONST * 2)      /* double-height for half-block precision */

#define FIX_ABS(x)  ((x) < 0 ? -(x) : (x))

/* Overflow-safe division for wall height calculation */
static short safe_div(short a, short b)
{
    short aa, ab;
    if (b == 0) return 0x7FFF;
    aa = FIX_ABS(a);
    ab = FIX_ABS(b);
    if ((aa >> 7) >= ab)
        return 0x7FFF;
    return fix_div(a, b);
}

/*-----------------------------------------------------------------
  set_columns - Switch video mode for the given column count.
  40 = CGA mode 1 (40x25), 80 = CGA mode 3 (80x25).
  Clears screen, hides cursor, resets page pointers.
-----------------------------------------------------------------*/
void set_columns(unsigned char cols)
{
    union REGS r;

    r.h.ah = BIOS_SETMODE;
    r.h.al = (cols == 80) ? 0x03 : CGA_MODE1;
    int86(VIDEO_INT, &r, &r);

    /* Hide cursor */
    r.h.ah = BIOS_SETCUR;
    r.h.ch = 0x20;
    r.h.cl = 0x00;
    int86(VIDEO_INT, &r, &r);

    /* Page pointers: page size differs by mode */
    pages[0] = VMEM_PAGE0;
    if (cols == 80)
        pages[1] = (VIDMEM)((CGA_SEG << 16) | 0x1000L);
    else
        pages[1] = VMEM_PAGE1;

    draw_page = 1;

    r.h.ah = BIOS_SETPAGE;
    r.h.al = 0;
    int86(VIDEO_INT, &r, &r);
}

/*-----------------------------------------------------------------
  init_video - Save original mode, then set game video mode
-----------------------------------------------------------------*/
void init_video(void)
{
    union REGS r;

    /* Save current video mode */
    r.h.ah = BIOS_GETMODE;
    int86(VIDEO_INT, &r, &r);
    orig_mode = r.h.al;

    set_columns(settings.columns);
}

/*-----------------------------------------------------------------
  restore_video - Restore original video mode
-----------------------------------------------------------------*/
void restore_video(void)
{
    union REGS r;

    r.h.ah = BIOS_SETMODE;
    r.h.al = orig_mode;
    int86(VIDEO_INT, &r, &r);
}

/*-----------------------------------------------------------------
  flip_page - Swap display/draw pages
  Shows the page we just drew to, switches draw target to other.
-----------------------------------------------------------------*/
void flip_page(void)
{
    union REGS r;

    /* Display the page we just finished drawing */
    r.h.ah = BIOS_SETPAGE;
    r.h.al = (unsigned char)draw_page;
    int86(VIDEO_INT, &r, &r);

    /* Next frame, draw to the other page */
    draw_page ^= 1;
}

/*-----------------------------------------------------------------
  render_frame - Draw a full 40x25 frame to the off-screen page
  
  For each column:
  1. Compute wall height from perpendicular distance
  2. Draw ceiling (black), wall (textured), floor (dark pattern)
  3. Apply distance shading: clear intensity bit for far walls
  
  Texture sampling:
  - texX comes from cast_rays (horizontal position on wall face)
  - texY is computed per-row by stepping through the texture column
-----------------------------------------------------------------*/
void render_frame(RayHit hits[])
{
    VIDMEM scr;
    unsigned short far **active_tex;
    int x, y;
    int cols = settings.columns;

    active_tex = settings.lcd_palette ? lcd_tex_table : tex_table;
    scr = pages[draw_page];
    {
        unsigned short *active_far;
        unsigned char *active_half;
        unsigned short ceil_cell, floor_cell;
        active_far = settings.lcd_palette ? lcd_far_table : far_table;
        active_half = settings.lcd_palette ? lcd_half_table : half_table;
        ceil_cell  = CEIL_CELL;
        floor_cell = settings.draw_floorceil ? FLOOR_CELL : BLANK_CELL;

    for (x = 0; x < cols; x++)
    {
        int wallHeight;
        int drawStart, drawEnd;
        short texStep, texPos;
        unsigned short far *tex;
        unsigned char texX;

        /* Ray hit nothing (render distance limit) */
        if (hits[x].dist == 0) {
            int mid = SCREEN_H / 2;
            for (y = 0; y < mid; y++)
                *(scr + y * cols + x) = ceil_cell;
            for (y = mid; y < SCREEN_H; y++)
                *(scr + y * cols + x) = floor_cell;
            continue;
        }

        /* Wall height in screen rows = WALL_CONST / perpDist */
        if (hits[x].dist > 0)
            wallHeight = safe_div(WALL_CONST, hits[x].dist) >> 8;
        else
            wallHeight = SCREEN_H;

        if (wallHeight > SCREEN_H) wallHeight = SCREEN_H;
        if (wallHeight < 1) wallHeight = 1;

        /* Vertical centering */
        drawStart = (SCREEN_H - wallHeight) >> 1;
        drawEnd = drawStart + wallHeight;

        /* Far distance: render as a single flat cell, skip texture */
        if (hits[x].dist > INT2FIX(8) && settings.far_shade) {
            unsigned short far_cell = active_far[hits[x].tile];
            for (y = 0; y < drawStart; y++)
                *(scr + y * cols + x) = ceil_cell;
            for (y = drawStart; y < drawEnd; y++)
                *(scr + y * cols + x) = far_cell;
            for (y = drawEnd; y < SCREEN_H; y++)
                *(scr + y * cols + x) = floor_cell;
            continue;
        }

        /* Enhanced precision: half-block characters at wall edges */
        if (settings.enhanced_prec) {
            int wallHalf, halfSU, halfS, halfE;
            int fS, fE, hoff;
            short tSH, tSF, tPos;
            unsigned char hAttr;

            hAttr = active_half[hits[x].tile];
            wallHalf = safe_div(WALL_CONST_2X, hits[x].dist) >> 8;
            if (wallHalf < 1) wallHalf = 1;

            halfSU = (SCREEN_H * 2 - wallHalf) / 2;
            halfS = halfSU < 0 ? 0 : halfSU;
            halfE = halfSU + wallHalf;
            if (halfE > SCREEN_H * 2) halfE = SCREEN_H * 2;

            fS = (halfS + 1) / 2;
            fE = halfE / 2;

            /* Ceiling */
            for (y = 0; y < halfS / 2; y++)
                *(scr + y * cols + x) = ceil_cell;

            /* Top edge: bottom-half block */
            if (halfS & 1)
                *(scr + (halfS / 2) * cols + x) = TC(0xDC, hAttr);

            /* Full-wall rows with texture */
            tex = active_tex[hits[x].tile];
            texX = hits[x].texX;
            tSH = (short)((TEX_SIZE << 8) / wallHalf);
            tSF = tSH * 2;
            hoff = fS * 2 - halfSU;
            tPos = (short)(hoff * tSH);

            for (y = fS; y < fE; y++) {
                int texY = (tPos >> 8) & TEX_MASK;
                *(scr + y * cols + x) = tex[texY * TEX_SIZE + texX];
                tPos += tSF;
            }

            /* Bottom edge: top-half block */
            if (halfE & 1)
                *(scr + (halfE / 2) * cols + x) = TC(0xDF, hAttr);

            /* Floor */
            for (y = (halfE + 1) / 2; y < SCREEN_H; y++)
                *(scr + y * cols + x) = floor_cell;

            continue;
        }

        /* Get texture pointer for this tile */
        tex = active_tex[hits[x].tile];
        texX = hits[x].texX;

        /* Texture Y stepping: map wallHeight rows to TEX_SIZE texels */
        /* texStep = (TEX_SIZE << 8) / wallHeight  (8.8 FP)           */
        texStep = (short)((TEX_SIZE << 8) / wallHeight);
        texPos = 0;

        /* If wall is taller than screen, skip off-screen top portion */
        if (wallHeight > SCREEN_H) {
            texPos = (short)(((wallHeight - SCREEN_H) >> 1) * texStep);
        }

        /* --- Draw the column --- */

        /* Ceiling */
        for (y = 0; y < drawStart; y++)
            *(scr + y * cols + x) = ceil_cell;

        /* Wall */
        for (y = drawStart; y < drawEnd; y++)
        {
            unsigned short texel;
            int texY;

            texY = (texPos >> 8) & TEX_MASK;
            texel = tex[texY * TEX_SIZE + texX];

            *(scr + y * cols + x) = texel;
            texPos += texStep;
        }

        /* Floor */
        for (y = drawEnd; y < SCREEN_H; y++)
            *(scr + y * cols + x) = floor_cell;
    }

    /* Second pass: overlay glass tiles on top of rendered walls.
       Texels with value 0 are transparent (show what is behind). */
    for (x = 0; x < cols; x++) {
        int gH, gS, gE;
        short gStep, gPos;
        unsigned short far *gTex;
        unsigned short texel;
        int texY;
        if (hits[x].glass_dist == 0) continue;
        gH = safe_div(WALL_CONST, hits[x].glass_dist) >> 8;
        if (gH > SCREEN_H) gH = SCREEN_H;
        if (gH < 1) gH = 1;
        gS = (SCREEN_H - gH) >> 1;
        gE = gS + gH;
        gTex = active_tex[hits[x].glass_tile];
        gStep = (short)((TEX_SIZE << 8) / gH);
        gPos = 0;
        for (y = gS; y < gE; y++) {
            texY = (gPos >> 8) & TEX_MASK;
            texel = gTex[texY * TEX_SIZE + hits[x].glass_texX];
            if (texel != 0)
                *(scr + y * cols + x) = texel;
            gPos += gStep;
        }
    }
    }
}

/*-----------------------------------------------------------------
  render_sprites - Draw billboard sprite tiles on top of the
  already-rendered wall frame. Uses painter's algorithm
  (back to front) with per-column z-testing against wall distances.

  Sprites always face the player and use the same 8x8 texture
  format as walls. Texels with value 0 are transparent.
  Does not render sprites more than 8 tiles away.
  Unaffected by enhanced precision setting.
-----------------------------------------------------------------*/
void render_sprites(Player *p, Map *m, RayHit hits[])
{
    struct vis_sprite {
        short depth;
        short screenX;
        short size;
        unsigned char tile;
    } sprites[MAX_SPRITES];
    int count = 0;
    int cols = settings.columns;
    VIDMEM scr = pages[draw_page];
    unsigned short far **active_tex;
    short dirX, dirY, planeX, planeY;
    int px, py, minX, maxX, minY, maxY;
    int mx, my, i, j;

    active_tex = settings.lcd_palette ? lcd_tex_table : tex_table;

    dirX = cos_tab[p->angle];
    dirY = sin_tab[p->angle];
    planeX = -fix_mul(dirY, FOV_PLANE);
    planeY =  fix_mul(dirX, FOV_PLANE);

    /* Player tile position */
    px = FIX2INT(p->px);
    py = FIX2INT(p->py);

    /* Scan +/-8 tiles around player for sprite tiles */
    minX = px - 8; if (minX < 0) minX = 0;
    maxX = px + 8; if (maxX >= (int)m->w) maxX = (int)m->w - 1;
    minY = py - 8; if (minY < 0) minY = 0;
    maxY = py + 8; if (maxY >= (int)m->h) maxY = (int)m->h - 1;

    for (my = minY; my <= maxY && count < MAX_SPRITES; my++) {
        for (mx = minX; mx <= maxX && count < MAX_SPRITES; mx++) {
            unsigned char tile = m->data[(unsigned)my * m->w + (unsigned)mx];
            if (TILE_IS_SPRITE(tile)) {
                short sx, sy, temp1, temp2, depth, scrX;
                int sprSize;

                /* Vector from player to sprite center */
                sx = (short)(INT2FIX(mx) + FIX_HALF - p->px);
                sy = (short)(INT2FIX(my) + FIX_HALF - p->py);

                /* Camera-space depth via inverse camera matrix.
                   det = dirX*planeY - planeX*dirY = FOV_PLANE (constant).
                   depth = (planeY*sx - planeX*sy) / FOV_PLANE */
                temp1 = (short)(fix_mul(planeY, sx) - fix_mul(planeX, sy));
                depth = safe_div(temp1, FOV_PLANE);

                if (depth <= 0 || depth > SPRITE_MAX_DIST)
                    continue;

                /* Lateral component (det cancels):
                   camX = (-dirY*sx + dirX*sy) / (planeY*sx - planeX*sy)
                   screenX = cols/2 + camX * (cols/2) */
                temp2 = (short)(-fix_mul(dirY, sx) + fix_mul(dirX, sy));
                scrX = (short)(cols / 2 +
                    (int)(((long)safe_div(temp2, temp1) * (cols / 2)) >> 8));

                /* Sprite size = same formula as wall height */
                sprSize = safe_div(WALL_CONST, depth) >> 8;
                if (sprSize < 1) sprSize = 1;
                if (sprSize > SCREEN_H * 2) sprSize = SCREEN_H * 2;

                sprites[count].depth = depth;
                sprites[count].screenX = scrX;
                sprites[count].size = (short)sprSize;
                sprites[count].tile = tile;
                count++;
            }
        }
    }

    if (count == 0) return;

    /* Insertion sort by depth descending (back to front) */
    for (i = 1; i < count; i++) {
        struct vis_sprite tmp = sprites[i];
        j = i - 1;
        while (j >= 0 && sprites[j].depth < tmp.depth) {
            sprites[j + 1] = sprites[j];
            j--;
        }
        sprites[j + 1] = tmp;
    }

    /* Render each sprite */
    for (i = 0; i < count; i++) {
        int sprH = sprites[i].size;
        int sprW = sprH;    /* square sprites */
        int scx = sprites[i].screenX;
        int dStartX = scx - sprW / 2;
        int dEndX = dStartX + sprW;
        int dStartY = (SCREEN_H - sprH) / 2;
        int dEndY = dStartY + sprH;
        unsigned short far *tex = active_tex[sprites[i].tile];
        short texStepY;
        int startX, endX, x, y;

        if (sprH < 1) continue;
        texStepY = (short)((TEX_SIZE << 8) / sprH);

        startX = dStartX < 0 ? 0 : dStartX;
        endX = dEndX > cols ? cols : dEndX;

        for (x = startX; x < endX; x++) {
            int texX;
            short texPosY;
            int startY, endY;

            /* Z-test: skip column if wall is closer */
            if (hits[x].dist != 0 && sprites[i].depth >= hits[x].dist)
                continue;

            texX = ((x - dStartX) * TEX_SIZE) / sprW;
            if (texX >= TEX_SIZE) texX = TEX_SIZE - 1;

            texPosY = 0;
            startY = dStartY;
            if (startY < 0) {
                texPosY = (short)((-startY) * texStepY);
                startY = 0;
            }
            endY = dEndY > SCREEN_H ? SCREEN_H : dEndY;

            for (y = startY; y < endY; y++) {
                int texY = (texPosY >> 8) & TEX_MASK;
                unsigned short texel = tex[texY * TEX_SIZE + texX];
                if (texel != 0)     /* 0 = transparent */
                    *(scr + y * cols + x) = texel;
                texPosY += texStepY;
            }
        }
    }
}
