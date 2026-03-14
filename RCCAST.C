/* RCCAST.C - DDA raycasting engine for 40-column text mode       */
/* Vector-based approach (Wolfenstein-style camera plane)          */
/* Fisheye prevention is inherent: uses perpendicular distance    */

#include "raycast.h"

/* Precomputed camera-space X offsets for each screen column.     */
/* cameraX = 2*x/SCREEN_W - 1, in 8.8 fixed-point.               */
/* Maps column 0 -> -256 (left), column 19/20 -> ~0, column 39 -> +243 */
static const short cam_off[SCREEN_W] = {
    -256,-243,-230,-218,-205,-192,-179,-167,
    -154,-141,-128,-115,-103, -90, -77, -64,
     -51, -39, -26, -13,   0,  13,  26,  39,
      51,  64,  77,  90, 103, 115, 128, 141,
     154, 167, 179, 192, 205, 218, 230, 243
};

/* Absolute value for fix8 */
#define FIX_ABS(x)  ((x) < 0 ? -(x) : (x))

/*-----------------------------------------------------------------
  safe_div - Overflow-safe wrapper for fix_div.
  Returns 0x7FFF when the result would overflow a signed 16-bit
  (i.e. when |a/b| >= 128, since 128.0 can't be represented in 8.8).
  This prevents the 8086 #DE (divide error) interrupt that crashes
  the program when turning at angles that make ray components tiny.
-----------------------------------------------------------------*/
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
  cast_rays - cast 40 rays and fill the hits[] array
  
  Uses vector-based DDA (Digital Differential Analyzer):
  1. Compute player direction vector (dirX, dirY) from angle
  2. Compute camera plane perpendicular to direction, scaled by FOV
  3. For each column, compute ray direction = dir + plane * cameraX
  4. DDA: step through grid lines until a wall tile is hit
  5. Record perpendicular distance, tile type, texture X coordinate
  
  Perpendicular distance (not Euclidean) prevents fisheye distortion.
-----------------------------------------------------------------*/
void cast_rays(Player *p, Map *m, RayHit hits[])
{
    short dirX, dirY;       /* player direction vector (8.8 FP)   */
    short planeX, planeY;   /* camera plane vector (8.8 FP)       */
    int x;

    /* Direction from angle lookup */
    dirX = cos_tab[p->angle];
    dirY = sin_tab[p->angle];

    /* Camera plane = perpendicular to dir, scaled by FOV_PLANE    */
    /* Perpendicular to (dirX, dirY) is (-dirY, dirX)              */
    /* Scale by FOV_PLANE/FIX_ONE = 169/256 ~ 0.66                */
    planeX = -fix_mul(dirY, FOV_PLANE);
    planeY =  fix_mul(dirX, FOV_PLANE);

    for (x = 0; x < SCREEN_W; x++)
    {
        short rayDirX, rayDirY;     /* ray direction (8.8 FP)     */
        short deltaDistX, deltaDistY; /* distance between grid lines */
        short sideDistX, sideDistY; /* distance to next grid line */
        int mapX, mapY;             /* current map tile coords    */
        int stepX, stepY;           /* +1 or -1 step direction    */
        int side;                   /* 0=vertical, 1=horizontal   */
        unsigned char tile;
        short camX;

        /* Ray direction = dir + plane * cameraX */
        camX = cam_off[x];
        rayDirX = dirX + fix_mul(planeX, camX);
        rayDirY = dirY + fix_mul(planeY, camX);

        /* Player map cell */
        mapX = FIX2INT(p->px);
        mapY = FIX2INT(p->py);

        /* deltaDist = abs(FIX_ONE / rayDir component)             */
        /* This is the distance the ray travels to cross one full  */
        /* grid line in X or Y. We use fix_div for precision.      */
        /* Guard against zero ray direction components.            */
        deltaDistX = FIX_ABS(safe_div(FIX_ONE, rayDirX));
        deltaDistY = FIX_ABS(safe_div(FIX_ONE, rayDirY));

        /* Cap deltaDist to prevent signed overflow in DDA accum */
        if (deltaDistX > 0x1000) deltaDistX = 0x1000;
        if (deltaDistY > 0x1000) deltaDistY = 0x1000;

        /* Determine step direction and initial sideDist            */
        /* sideDist = distance from player to next grid boundary    */
        /* along the ray, measured in ray-length units              */
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = fix_mul((short)(p->px - INT2FIX(mapX)), deltaDistX);
        } else {
            stepX = 1;
            sideDistX = fix_mul((short)(INT2FIX(mapX + 1) - p->px), deltaDistX);
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = fix_mul((short)(p->py - INT2FIX(mapY)), deltaDistY);
        } else {
            stepY = 1;
            sideDistY = fix_mul((short)(INT2FIX(mapY + 1) - p->py), deltaDistY);
        }

        /* DDA loop - step through grid lines until we hit a wall  */
        tile = TILE_EMPTY;
        while (tile == TILE_EMPTY)
        {
            /* Jump to next map square in X or Y direction */
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;   /* vertical wall (perpendicular to X) */
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;   /* horizontal wall (perpendicular to Y) */
            }

            /* Check if ray is out of bounds (safety) */
            if (mapX < 0 || mapX >= (int)m->w ||
                mapY < 0 || mapY >= (int)m->h) {
                tile = TILE_STONE;  /* treat OOB as stone wall */
                break;
            }

            tile = m->data[(unsigned)mapY * m->w + (unsigned)mapX];
        }

        /* Calculate perpendicular distance (prevents fisheye)     */
        /* perpDist = (mapCoord - playerPos + (1-step)/2) / rayDir  */
        if (side == 0) {
            /* Vertical wall: distance along X axis */
            short num = INT2FIX(mapX) - p->px;
            if (stepX == -1) num += FIX_ONE;
            hits[x].dist = safe_div(num, rayDirX);
        } else {
            /* Horizontal wall: distance along Y axis */
            short num = INT2FIX(mapY) - p->py;
            if (stepY == -1) num += FIX_ONE;
            hits[x].dist = safe_div(num, rayDirY);
        }

        /* Ensure distance is positive */
        if (hits[x].dist < 1) hits[x].dist = 1;

        /* Calculate texture X coordinate                          */
        /* Where exactly on the wall face did the ray hit?         */
        {
            short wallHitFrac;  /* fractional part of hit position */

            if (side == 0) {
                /* Hit a vertical wall: texture X from Y position */
                wallHitFrac = p->py + fix_mul(hits[x].dist, rayDirY);
            } else {
                /* Hit a horizontal wall: texture X from X position */
                wallHitFrac = p->px + fix_mul(hits[x].dist, rayDirX);
            }
            /* Keep only fractional part (0-255), scale to 0-7 */
            wallHitFrac = FIX_FRAC(wallHitFrac);
            hits[x].texX = (unsigned char)(wallHitFrac >> (8 - TEX_SHIFT));
        }

        hits[x].tile = tile;
        hits[x].side = (unsigned char)side;
    }
}
