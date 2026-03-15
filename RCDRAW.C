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
    }
}
