/* RAYCAST.C - Main entry point for CGA text-mode raycaster       */
/* Target: Microsoft QuickC 2.5, CGA mode 1 (40x25), 8086/8088   */

#include <stdio.h>
#include <stdlib.h>
#include "raycast.h"

/* Ray hit buffer - one result per screen column */
static RayHit hits[SCREEN_W];

/* Game state */
static Player player;
static Map    level;

/*-----------------------------------------------------------------
  cleanup - Called via atexit() to ensure safe shutdown even if
  the program terminates unexpectedly (e.g. division by zero).
-----------------------------------------------------------------*/
static void cleanup(void)
{
    remove_keyboard();
    restore_video();
}

/*-----------------------------------------------------------------
  main - Initialize engine, run game loop, shut down
-----------------------------------------------------------------*/
int main(void)
{
    int running = 1;

    /* Set up the map and player start position */
    map_init(&level);
    player.px = INT2FIX(3) + FIX_HALF;   /* center of tile (3,3) */
    player.py = INT2FIX(3) + FIX_HALF;
    player.angle = 0;                     /* facing east          */

    /* Register cleanup for abnormal exits */
    atexit(cleanup);

    /* Switch to CGA 40x25 text mode and install keyboard ISR */
    init_video();
    install_keyboard();

    /* === Main loop ============================================= */
    while (running) {
        /* Handle player movement and turning; returns 0 on ESC */
        running = process_input(&player, &level);

        /* Cast all 40 rays */
        cast_rays(&player, &level, hits);

        /* Draw the frame to the hidden page */
        render_frame(hits);

        /* Swap visible/draw pages */
        flip_page();
    }

    /* cleanup() handles restore_video and remove_keyboard via atexit */
    return 0;
}
