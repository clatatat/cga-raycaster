/* RCENT.C - Entity system: textures, AI, spawning                */
/* Test entity follows the player with line-of-sight checking     */

#include "raycast.h"

/* ================================================================
   Entity textures - 8x8, 3 frames
   Frame 0: Idle  (bright green solid block)
   Frame 1: Walk0 (bright red solid block)
   Frame 2: Walk1 (bright blue solid block)
   ================================================================ */
#define GREEN_CELL  TC(0xDB, 0x0A)
#define RED_CELL    TC(0xDB, 0x0C)
#define BLUE_CELL   TC(0xDB, 0x09)

static const unsigned short ent_tex_idle[TEX_SIZE][TEX_SIZE] = {
    { GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL },
    { GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL },
    { GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL },
    { GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL },
    { GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL },
    { GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL },
    { GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL },
    { GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL, GREEN_CELL }
};

static const unsigned short ent_tex_walk0[TEX_SIZE][TEX_SIZE] = {
    { RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL },
    { RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL },
    { RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL },
    { RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL },
    { RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL },
    { RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL },
    { RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL },
    { RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL, RED_CELL }
};

static const unsigned short ent_tex_walk1[TEX_SIZE][TEX_SIZE] = {
    { BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL },
    { BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL },
    { BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL },
    { BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL },
    { BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL },
    { BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL },
    { BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL },
    { BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL, BLUE_CELL }
};

/* Frame pointer table: [0]=idle, [1]=walk0, [2]=walk1 */
unsigned short far *ent_frames[3] = {
    (unsigned short far *)ent_tex_idle,
    (unsigned short far *)ent_tex_walk0,
    (unsigned short far *)ent_tex_walk1
};

/* Global test entity instance */
Entity test_entity = { 0, 0, 0, 0, 0, 0, 0 };

/* ================================================================
   atan2_fix - Compute angle (0-255) from dy, dx (8.8 fixed-point)
   Returns unsigned char angle matching cos_tab/sin_tab convention.
   ================================================================ */
static unsigned char atan2_fix(short dy, short dx)
{
    unsigned char angle;
    short ax, ay;

    ax = dx < 0 ? -dx : dx;
    ay = dy < 0 ? -dy : dy;

    if (ax == 0 && ay == 0) return 0;

    if (ax >= ay) {
        angle = (unsigned char)(((long)ay << 5) / ax);
    } else {
        angle = 64 - (unsigned char)(((long)ax << 5) / ay);
    }

    /* Map to correct quadrant (0=east, 64=south, 128=west, 192=north) */
    if (dx >= 0 && dy >= 0) return angle;           /* Q1: 0-63    */
    if (dx <  0 && dy >= 0) return 128 - angle;     /* Q2: 65-128  */
    if (dx <  0 && dy <  0) return 128 + angle;     /* Q3: 129-192 */
    return (unsigned char)(256 - angle);             /* Q4: 193-255 */
}

/* ================================================================
   turn_toward - Smoothly step entity angle toward target angle
   Takes shortest path around the 0-255 circle.
   ================================================================ */
static void turn_toward(Entity *e, unsigned char target)
{
    unsigned char diff = target - e->angle;

    if (diff == 0) return;

    if (diff <= 128) {
        /* Shorter to turn clockwise (increase) */
        if (diff > ENT_TURN_SPEED)
            e->angle += ENT_TURN_SPEED;
        else
            e->angle = target;
    } else {
        /* Shorter to turn counter-clockwise (decrease) */
        if ((unsigned char)(0 - diff) > ENT_TURN_SPEED)
            e->angle -= ENT_TURN_SPEED;
        else
            e->angle = target;
    }
}

/* ================================================================
   entity_can_see - Bresenham line-of-sight from entity to player.
   Returns 1 if no solid wall blocks the path, 0 otherwise.
   Glass tiles do NOT block line-of-sight.
   ================================================================ */
static int entity_can_see(Entity *e, Player *p, Map *m)
{
    int x0 = FIX2INT(e->x);
    int y0 = FIX2INT(e->y);
    int x1 = FIX2INT(p->px);
    int y1 = FIX2INT(p->py);
    int dx, dy, sx, sy, err, err2;

    dx = x1 - x0; if (dx < 0) dx = -dx;
    dy = y1 - y0; if (dy < 0) dy = -dy;
    sx = x0 < x1 ? 1 : -1;
    sy = y0 < y1 ? 1 : -1;
    err = dx - dy;

    for (;;) {
        if (x0 == x1 && y0 == y1) return 1;
        err2 = err * 2;
        if (err2 > -dy) { err -= dy; x0 += sx; }
        if (err2 <  dx) { err += dx; y0 += sy; }
        if (x0 == x1 && y0 == y1) return 1;
        {
            unsigned char t = map_get(m, x0, y0);
            if (t != TILE_EMPTY && t != TILE_GLASS && !TILE_IS_SPRITE(t))
                return 0;
        }
    }
}

/* ================================================================
   spawn_entity - Place entity in the tile directly in front of
   the player, centered in that tile.
   ================================================================ */
void spawn_entity(Entity *e, Player *p)
{
    int tx = FIX2INT(p->px + cos_tab[p->angle]);
    int ty = FIX2INT(p->py + sin_tab[p->angle]);

    e->x = INT2FIX(tx) + FIX_HALF;
    e->y = INT2FIX(ty) + FIX_HALF;
    e->angle = 0;
    e->active = 1;
    e->state = ENT_IDLE;
    e->frame = 0;
    e->timer = ENT_ANIM_RATE;
}

/* ================================================================
   update_entity - Per-frame AI update.
   If line-of-sight to player is clear, face player and walk toward.
   Otherwise idle. Collision against walls same as player.
   ================================================================ */
void update_entity(Entity *e, Player *p, Map *m)
{
    unsigned char target;
    short dx, dy, ax, ay;
    short moveX, moveY;
    fix8 newX, newY;

    if (!e->active) return;

    dx = (short)(p->px - e->x);
    dy = (short)(p->py - e->y);

    /* Check line of sight */
    if (!entity_can_see(e, p, m)) {
        e->state = ENT_IDLE;
        e->frame = 0;
        e->timer = ENT_ANIM_RATE;
        return;
    }

    /* Calculate angle toward player */
    target = atan2_fix(dy, dx);
    turn_toward(e, target);

    /* If close enough, stop walking */
    ax = dx < 0 ? -dx : dx;
    ay = dy < 0 ? -dy : dy;
    if (ax < FIX_HALF && ay < FIX_HALF) {
        e->state = ENT_IDLE;
        e->frame = 0;
        e->timer = ENT_ANIM_RATE;
        return;
    }

    /* Walk toward player using entity's facing direction */
    e->state = ENT_WALK;
    moveX = cos_tab[e->angle];
    moveY = sin_tab[e->angle];

    {
        short spd = ENT_MOVE_SPEED;
        if (eng_80colperf && settings.columns == 80)
            spd = ENT_MOVE_SPEED * 2;
        newX = e->x + fix_mul(spd, moveX);
        newY = e->y + fix_mul(spd, moveY);
    }
    if (map_get(m, FIX2INT(newX), FIX2INT(e->y)) == TILE_EMPTY)
        e->x = newX;
    if (map_get(m, FIX2INT(e->x), FIX2INT(newY)) == TILE_EMPTY)
        e->y = newY;

    /* Animate walk: alternate between frame 0 and 1 */
    if (e->timer == 0) {
        e->frame ^= 1;
        e->timer = ENT_ANIM_RATE;
    } else {
        e->timer--;
    }
}
