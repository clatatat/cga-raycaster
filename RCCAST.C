/* RCCAST.C - DDA raycasting engine for text-mode renderer         */
/* Vector-based approach (Wolfenstein-style camera plane)          */
/* Fisheye prevention is inherent: uses perpendicular distance    */
/* Supports variable column count (40 or 80) and render distance  */

#include "raycast.h"

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
    int cols = settings.columns;
    int rdist = (int)settings.render_dist;

    /* Direction from angle lookup */
    dirX = cos_tab[p->angle];
    dirY = sin_tab[p->angle];

    /* Camera plane = perpendicular to dir, scaled by FOV_PLANE    */
    planeX = -fix_mul(dirY, FOV_PLANE);
    planeY =  fix_mul(dirX, FOV_PLANE);

    for (x = 0; x < cols; x++)
    {
        short rayDirX, rayDirY;
        short deltaDistX, deltaDistY;
        short sideDistX, sideDistY;
        int mapX, mapY;
        int startMapX, startMapY;
        int stepX, stepY;
        int side;
        int glass_mapX, glass_mapY, glass_side;
        unsigned char tile;
        short camX;

        /* cameraX = (2*x/cols - 1) in 8.8 fixed-point */
        camX = (short)(((long)(2 * x - cols) << 8) / cols);
        rayDirX = dirX + fix_mul(planeX, camX);
        rayDirY = dirY + fix_mul(planeY, camX);

        /* Player map cell */
        mapX = FIX2INT(p->px);
        mapY = FIX2INT(p->py);
        startMapX = mapX;
        startMapY = mapY;

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
        glass_mapX = -1; glass_mapY = -1; glass_side = -1;
        hits[x].glass_dist = 0; hits[x].glass_tile = 0; hits[x].glass_texX = 0;
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

            /* Render distance limit: stop if ray traveled too far */
            if (rdist > 0) {
                int dx = mapX - startMapX;
                int dy = mapY - startMapY;
                if (dx < 0) dx = -dx;
                if (dy < 0) dy = -dy;
                if (dx > rdist || dy > rdist)
                    break;  /* tile stays TILE_EMPTY = no hit */
            }

            /* Check if ray is out of bounds (safety) */
            if (mapX < 0 || mapX >= (int)m->w ||
                mapY < 0 || mapY >= (int)m->h) {
                tile = TILE_STONE;  /* treat OOB as stone wall */
                break;
            }

            tile = m->data[(unsigned)mapY * m->w + (unsigned)mapX];

            /* Rays pass through sprite tiles (rendered separately) */
            if (TILE_IS_SPRITE(tile))
                tile = TILE_EMPTY;
            /* Record first glass hit, then let ray continue through */
            else if (TILE_IS_GLASS(tile) && glass_mapX < 0) {
                glass_mapX = mapX; glass_mapY = mapY; glass_side = side;
                hits[x].glass_tile = tile;
                tile = TILE_EMPTY;
            }
        }

        /* Compute glass hit depth and texture X if glass was encountered */
        if (glass_mapX >= 0) {
            fix8 gdist;
            short wallHitFrac;
            if (glass_side == 0) {
                short num = INT2FIX(glass_mapX) - p->px;
                if (stepX == -1) num += FIX_ONE;
                gdist = safe_div(num, rayDirX);
            } else {
                short num = INT2FIX(glass_mapY) - p->py;
                if (stepY == -1) num += FIX_ONE;
                gdist = safe_div(num, rayDirY);
            }
            if (gdist < 1) gdist = 1;
            if (glass_side == 0)
                wallHitFrac = p->py + fix_mul(gdist, rayDirY);
            else
                wallHitFrac = p->px + fix_mul(gdist, rayDirX);
            wallHitFrac = FIX_FRAC(wallHitFrac);
            hits[x].glass_dist = gdist;
            hits[x].glass_texX = (unsigned char)(wallHitFrac >> (8 - TEX_SHIFT));
        }

        /* No wall hit within render distance */
        if (tile == TILE_EMPTY) {
            hits[x].dist = 0;
            hits[x].tile = TILE_EMPTY;
            hits[x].texX = 0;
            hits[x].side = 0;
            continue;
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
