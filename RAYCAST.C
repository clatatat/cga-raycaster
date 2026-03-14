/* RAYCAST.C - Main entry point for CGA text-mode raycaster       */
/* Target: Microsoft QuickC 2.5, CGA text mode, 8086/8088         */

#include <stdio.h>
#include <stdlib.h>
#include "raycast.h"

/* Global settings and controls with defaults */
Settings settings  = { 0, 0, 40, 0 };   /* LCD=OFF, 16x16=OFF, 40 cols, Infinite */
Controls controls  = { SC_W, SC_S, SC_A, SC_D, SC_LEFT, SC_RIGHT };

/* Ray hit buffer - sized for max columns */
static RayHit hits[MAX_COLS];

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
    int result;

    /* Set up the map and player start position */
    map_init(&level);
    player.px = INT2FIX(3) + FIX_HALF;   /* center of tile (3,3) */
    player.py = INT2FIX(3) + FIX_HALF;
    player.angle = 0;                     /* facing east          */

    /* Register cleanup for abnormal exits */
    atexit(cleanup);

    /* Switch to CGA text mode and install keyboard ISR */
    init_video();
    install_keyboard();

    /* === Main loop ============================================= */
    for (;;) {
        result = process_input(&player, &level);

        if (result == 2) {
            /* ESC pressed: show menu */
            result = show_menu();
            if (result == 0) break;     /* quit selected */
            /* Resume: reinit video (clears menu, resets pages) */
            set_columns(settings.columns);
            continue;
        }

        cast_rays(&player, &level, hits);
        render_frame(hits);
        flip_page();
    }

    /* cleanup() handles restore_video and remove_keyboard via atexit */
    return 0;
}
