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
    int x, y;
    int cols = settings.columns;

    scr = pages[draw_page];

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
                *(scr + y * cols + x) = CEIL_CELL;
            for (y = mid; y < SCREEN_H; y++)
                *(scr + y * cols + x) = FLOOR_CELL;
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

        /* Get texture pointer for this tile */
        tex = tex_table[hits[x].tile];
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
            *(scr + y * cols + x) = CEIL_CELL;

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
            *(scr + y * cols + x) = FLOOR_CELL;
    }
}
