/* RAYCAST.C - Main entry point for CGA text-mode raycaster       */
/* Target: Microsoft QuickC 2.5, CGA text mode, 8086/8088         */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raycast.h"

/* Global settings and controls with defaults */
Settings settings  = { 0, 40, 0, 1, 0, 1 };   /* LCD=OFF, 40 cols, Infinite, FarShade=ON, EnhPrec=OFF, FloorCeil=ON */
Controls controls  = { SC_W, SC_S, SC_A, SC_D, SC_LEFT, SC_RIGHT,
                       SC_I, SC_O, SC_P, SC_SPACE };

/* Key-action flags (updated each frame by process_input) */
unsigned char keyflag1 = 0;
unsigned char keyflag2 = 0;
unsigned char keyflag3 = 0;
unsigned char keyflag4 = 0;

/* Debug mode globals */
unsigned char eng_debug = 0;
unsigned short dbg_ceil_cell  = 0x0000;  /* TC(' ', 0x00) */
unsigned short dbg_floor_cell = 0x08B0;  /* TC(0xB0, 0x08) */
unsigned char  dbg_place_tile = TILE_ROCKS;
unsigned char  eng_80colperf = 0;

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

    /* Load saved options if OPTIONS.TXT exists */
    load_options();

    /* Check for ENG-DEBUG=1 and ENG-80COLPERF=1 in OPTIONS.TXT */
    {
        FILE *f = fopen("OPTIONS.TXT", "r");
        if (f) {
            char line[32];
            char prev[32];
            char last[32];
            prev[0] = '\0';
            last[0] = '\0';
            while (fgets(line, sizeof(line), f)) {
                strcpy(prev, last);
                strcpy(last, line);
            }
            fclose(f);
            if (strncmp(last, "ENG-DEBUG=1", 11) == 0)
                eng_debug = 1;
            if (strncmp(prev, "ENG-80COLPERF=1", 15) == 0)
                eng_80colperf = 1;
        }
    }

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

        /* Z = debug menu (only if ENG-DEBUG=1) */
        if (eng_debug && key_state[SC_Z]) {
            show_debug_menu();
            set_columns(settings.columns);
            continue;
        }

        /* O = tile picker (debug) */
        if (eng_debug && key_state[controls.sc_secondary]) {
            show_tile_menu();
            set_columns(settings.columns);
            continue;
        }

        /* P = place selected tile in front of player (debug) */
        if (eng_debug && key_state[controls.sc_tertiary]) {
            int tx = FIX2INT(player.px + cos_tab[player.angle]);
            int ty = FIX2INT(player.py + sin_tab[player.angle]);
            map_set(&level, tx, ty, dbg_place_tile);
            while (key_state[controls.sc_tertiary]) ;
        }

        /* \ = minimap (debug) */
        if (eng_debug && key_state[SC_BACKSLASH]) {
            show_minimap(&player, &level);
            set_columns(settings.columns);
            continue;
        }

        /* J = spawn test entity (debug) */
        if (eng_debug && key_state[SC_J]) {
            spawn_entity(&test_entity, &player);
            while (key_state[SC_J]) ;
        }

        update_entity(&test_entity, &player, &level);

        cast_rays(&player, &level, hits);
        render_frame(hits);
        render_sprites(&player, &level, hits);
        render_entity(&test_entity, &player, hits);
        flip_page();
    }

    /* cleanup() handles restore_video and remove_keyboard via atexit */
    return 0;
}
