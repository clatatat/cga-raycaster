/* RCMENU.C - Options menu and controls submenu                    */
/* Renders to CGA VRAM page 0, navigated with arrow keys + Enter  */

#include <stdio.h>
#include "raycast.h"

/* Menu item indices */
#define MI_RESUME    0
#define MI_LCD       1
#define MI_COLUMNS   2
#define MI_RDIST     3
#define MI_FARSHADE  4
#define MI_ENHPREC   5
#define MI_FLRCEIL   6
#define MI_CONTROLS  7
#define MI_QUIT      8
#define MENU_ITEMS   9

/* Row on screen for each menu item */
static const int menu_rows[MENU_ITEMS] = { 3, 5, 6, 7, 8, 9, 10, 11, 13 };

/* Render distance cycling values */
static const unsigned char rdist_vals[] = { 0, 8, 12, 16, 24 };
static const char *rdist_names[] = {
    "Infinite", "8 tiles ", "12 tiles", "16 tiles", "24 tiles"
};
#define RDIST_COUNT 5

/* Attribute constants */
#define AT_TITLE  0x0F   /* bright white */
#define AT_LABEL  0x07   /* light gray   */
#define AT_VALUE  0x0E   /* yellow       */
#define AT_DIM    0x08   /* dark gray    */
#define AT_CURSOR 0x0F   /* bright white */

/* Number of control bindings */
#define CTRL_ITEMS  10

/*-----------------------------------------------------------------
  VRAM text helpers
-----------------------------------------------------------------*/
static void v_clear(VIDMEM scr, int cols)
{
    int i;
    int total = cols * SCREEN_H;
    for (i = 0; i < total; i++)
        scr[i] = TC(' ', 0x00);
}

static void v_puts(VIDMEM scr, int cols, int row, int col,
                   const char *str, unsigned char attr)
{
    VIDMEM p = scr + (unsigned)row * cols + col;
    while (*str)
        *p++ = TC((unsigned char)*str++, attr);
}

static void v_putch(VIDMEM scr, int cols, int row, int col,
                    unsigned char ch, unsigned char attr)
{
    scr[(unsigned)row * cols + col] = TC(ch, attr);
}

/*-----------------------------------------------------------------
  Debounced key waiting for menu navigation
-----------------------------------------------------------------*/
static unsigned char menu_wait_key(void)
{
    /* Wait for all nav keys released */
    while (key_state[SC_UP] || key_state[SC_DOWN] ||
           key_state[SC_ESC] || key_state[SC_ENTER])
        ;
    /* Wait for one to be pressed */
    for (;;) {
        if (key_state[SC_UP])    return SC_UP;
        if (key_state[SC_DOWN])  return SC_DOWN;
        if (key_state[SC_ESC])   return SC_ESC;
        if (key_state[SC_ENTER]) return SC_ENTER;
    }
}

/* Wait for all keys released, then return first pressed scan code */
static unsigned char wait_any_key(void)
{
    unsigned char i;
    int any;
    do {
        any = 0;
        for (i = 1; i < 128; i++) {
            if (key_state[i]) { any = 1; break; }
        }
    } while (any);
    for (;;) {
        for (i = 1; i < 128; i++) {
            if (key_state[i]) return i;
        }
    }
}

/*-----------------------------------------------------------------
  Convert scan code to display name
-----------------------------------------------------------------*/
static const char *key_name(unsigned char sc)
{
    static char buf[8];
    switch (sc) {
    case 0x01: return "ESC";
    case 0x02: return "1";    case 0x03: return "2";
    case 0x04: return "3";    case 0x05: return "4";
    case 0x06: return "5";    case 0x07: return "6";
    case 0x08: return "7";    case 0x09: return "8";
    case 0x0A: return "9";    case 0x0B: return "0";
    case 0x0E: return "BKSP";  case 0x0F: return "TAB";
    case 0x10: return "Q";    case 0x11: return "W";
    case 0x12: return "E";    case 0x13: return "R";
    case 0x14: return "T";    case 0x15: return "Y";
    case 0x16: return "U";    case 0x17: return "I";
    case 0x18: return "O";    case 0x19: return "P";
    case 0x1C: return "ENTER";
    case 0x1E: return "A";    case 0x1F: return "S";
    case 0x20: return "D";    case 0x21: return "F";
    case 0x22: return "G";    case 0x23: return "H";
    case 0x24: return "J";    case 0x25: return "K";
    case 0x26: return "L";
    case 0x2C: return "Z";    case 0x2D: return "X";
    case 0x2E: return "C";    case 0x2F: return "V";
    case 0x30: return "B";    case 0x31: return "N";
    case 0x32: return "M";
    case 0x39: return "SPACE";
    case 0x48: return "UP";    case 0x4B: return "LEFT";
    case 0x4D: return "RIGHT"; case 0x50: return "DOWN";
    }
    buf[0] = '0'; buf[1] = 'x';
    buf[2] = "0123456789ABCDEF"[(sc >> 4) & 0xF];
    buf[3] = "0123456789ABCDEF"[sc & 0xF];
    buf[4] = '\0';
    return buf;
}

/*-----------------------------------------------------------------
  Get index into rdist_vals for current setting
-----------------------------------------------------------------*/
static int get_rdist_idx(void)
{
    int i;
    for (i = 0; i < RDIST_COUNT; i++) {
        if (rdist_vals[i] == settings.render_dist) return i;
    }
    return 0;
}

/*-----------------------------------------------------------------
  Draw the main options menu
-----------------------------------------------------------------*/
static void draw_menu(VIDMEM scr, int cols, int sel)
{
    int c;
    int vcol;
    int ccol;
    const char *val;

    vcol = (cols == 80) ? 38 : 22;
    ccol = cols - 2;

    v_clear(scr, cols);

    /* Title */
    c = (cols - 15) / 2;
    v_puts(scr, cols, 1, c, "=== Options ===", AT_TITLE);

    /* Resume */
    v_puts(scr, cols, 3, 2, "Resume Game", AT_LABEL);

    /* LCD Palette */
    v_puts(scr, cols, 5, 2, "LCD Palette:", AT_LABEL);
    val = settings.lcd_palette ? "ON " : "OFF";
    v_puts(scr, cols, 5, vcol, val, AT_VALUE);

    /* Columns */
    v_puts(scr, cols, 6, 2, "Columns:", AT_LABEL);
    val = (settings.columns == 80) ? "80" : "40";
    v_puts(scr, cols, 6, vcol, val, AT_VALUE);

    /* Render Distance */
    v_puts(scr, cols, 7, 2, "Render Distance:", AT_LABEL);
    v_puts(scr, cols, 7, vcol, rdist_names[get_rdist_idx()], AT_VALUE);

    /* Far Shade */
    v_puts(scr, cols, 8, 2, "Far Shade:", AT_LABEL);
    val = settings.far_shade ? "ON " : "OFF";
    v_puts(scr, cols, 8, vcol, val, AT_VALUE);

    /* Enhanced Precision */
    v_puts(scr, cols, 9, 2, "Enhanced Precision:", AT_LABEL);
    val = settings.enhanced_prec ? "ON " : "OFF";
    v_puts(scr, cols, 9, vcol, val, AT_VALUE);

    /* Floor/Ceiling */
    v_puts(scr, cols, 10, 2, "Floor/Ceiling:", AT_LABEL);
    val = settings.draw_floorceil ? "ON " : "OFF";
    v_puts(scr, cols, 10, vcol, val, AT_VALUE);

    /* Controls */
    v_puts(scr, cols, 11, 2, "Controls...", AT_LABEL);

    /* Quit */
    v_puts(scr, cols, 13, 2, "Quit Game", AT_LABEL);

    /* Cursor block on selected row */
    v_putch(scr, cols, menu_rows[sel], ccol, 0xDB, AT_CURSOR);
}

/*-----------------------------------------------------------------
  Controls sub-menu: display and rebind keys
-----------------------------------------------------------------*/
static void show_controls(VIDMEM scr, int cols)
{
    static const char *action_names[CTRL_ITEMS] = {
        "Forward:",      "Backward:",
        "Turn Left:",    "Turn Right:",
        "Strafe Left:",  "Strafe Right:",
        "Primary:",      "Secondary:",
        "Tertiary:",     "Quaternary:"
    };
    int sel = 0;

    for (;;) {
        unsigned char key;
        unsigned char *bindings[CTRL_ITEMS];
        int vcol;
        int ccol;
        int i, row;

        bindings[0] = &controls.sc_forward;
        bindings[1] = &controls.sc_backward;
        bindings[2] = &controls.sc_turn_left;
        bindings[3] = &controls.sc_turn_right;
        bindings[4] = &controls.sc_strafe_left;
        bindings[5] = &controls.sc_strafe_right;
        bindings[6] = &controls.sc_primary;
        bindings[7] = &controls.sc_secondary;
        bindings[8] = &controls.sc_tertiary;
        bindings[9] = &controls.sc_quaternary;

        vcol = (cols == 80) ? 36 : 20;
        ccol = cols - 2;

        v_clear(scr, cols);
        i = (cols - 16) / 2;
        v_puts(scr, cols, 1, i, "=== Controls ===", AT_TITLE);

        for (i = 0; i < CTRL_ITEMS; i++) {
            row = 3 + i;
            v_puts(scr, cols, row, 2, action_names[i], AT_LABEL);
            v_puts(scr, cols, row, vcol, key_name(*bindings[i]), AT_VALUE);
        }

        v_putch(scr, cols, 3 + sel, ccol, 0xDB, AT_CURSOR);
        v_puts(scr, cols, 14, 2, "ENTER=rebind  ESC=back", AT_DIM);

        key = menu_wait_key();

        if (key == SC_ESC) return;
        if (key == SC_UP && sel > 0) sel--;
        if (key == SC_DOWN && sel < CTRL_ITEMS - 1) sel++;
        if (key == SC_ENTER) {
            /* Prompt for new key */
            v_puts(scr, cols, 3 + sel, vcol, "...   ", AT_VALUE);
            key = wait_any_key();
            if (key != SC_ESC)
                *bindings[sel] = key;
        }
    }
}

/*-----------------------------------------------------------------
  save_options - Write current settings and controls to OPTIONS.TXT
-----------------------------------------------------------------*/
void save_options(void)
{
    FILE *f = fopen("OPTIONS.TXT", "w");
    if (!f) return;
    fprintf(f, "%d\n", (int)settings.lcd_palette);
    fprintf(f, "%d\n", (int)settings.columns);
    fprintf(f, "%d\n", (int)settings.render_dist);
    fprintf(f, "%d\n", (int)settings.far_shade);
    fprintf(f, "%d\n", (int)controls.sc_forward);
    fprintf(f, "%d\n", (int)controls.sc_backward);
    fprintf(f, "%d\n", (int)controls.sc_turn_left);
    fprintf(f, "%d\n", (int)controls.sc_turn_right);
    fprintf(f, "%d\n", (int)controls.sc_strafe_left);
    fprintf(f, "%d\n", (int)controls.sc_strafe_right);
    fprintf(f, "%d\n", (int)controls.sc_primary);
    fprintf(f, "%d\n", (int)controls.sc_secondary);
    fprintf(f, "%d\n", (int)controls.sc_tertiary);
    fprintf(f, "%d\n", (int)controls.sc_quaternary);
    fprintf(f, "%d\n", (int)settings.enhanced_prec);
    fprintf(f, "%d\n", (int)settings.draw_floorceil);
    if (eng_80colperf)
        fprintf(f, "ENG-80COLPERF=1\n");
    if (eng_debug)
        fprintf(f, "ENG-DEBUG=1\n");
    fclose(f);
}

/*-----------------------------------------------------------------
  load_options - Read settings and controls from OPTIONS.TXT.
  Silently ignored if the file does not exist (uses defaults).
-----------------------------------------------------------------*/
void load_options(void)
{
    int v;
    FILE *f = fopen("OPTIONS.TXT", "r");
    if (!f) return;

    if (fscanf(f, "%d", &v) == 1) settings.lcd_palette     = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) settings.columns         = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) settings.render_dist     = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) settings.far_shade       = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) controls.sc_forward      = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) controls.sc_backward     = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) controls.sc_turn_left    = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) controls.sc_turn_right   = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) controls.sc_strafe_left  = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) controls.sc_strafe_right = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) controls.sc_primary      = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) controls.sc_secondary    = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) controls.sc_tertiary     = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) controls.sc_quaternary   = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) settings.enhanced_prec   = (unsigned char)v;
    if (fscanf(f, "%d", &v) == 1) settings.draw_floorceil   = (unsigned char)v;

    fclose(f);

    /* Sanitize loaded values */
    if (settings.columns != 40 && settings.columns != 80)
        settings.columns = 40;
    settings.lcd_palette    = settings.lcd_palette    ? 1 : 0;
    settings.far_shade      = settings.far_shade      ? 1 : 0;
    settings.enhanced_prec  = settings.enhanced_prec  ? 1 : 0;
    settings.draw_floorceil = settings.draw_floorceil ? 1 : 0;
}

/*-----------------------------------------------------------------
  show_menu - Display options menu, handle input.
  Returns: 1 = resume game, 0 = quit game.
-----------------------------------------------------------------*/
int show_menu(void)
{
    VIDMEM scr = VMEM_PAGE0;
    int sel = MI_RESUME;
    int cols = settings.columns;
    union REGS r;

    /* Show page 0 */
    r.h.ah = BIOS_SETPAGE;
    r.h.al = 0;
    int86(VIDEO_INT, &r, &r);

    draw_menu(scr, cols, sel);

    for (;;) {
        unsigned char key = menu_wait_key();

        if (key == SC_ESC) { save_options(); return 1; }  /* resume */

        if (key == SC_UP && sel > 0) {
            sel--;
            draw_menu(scr, cols, sel);
        }
        if (key == SC_DOWN && sel < MENU_ITEMS - 1) {
            sel++;
            draw_menu(scr, cols, sel);
        }
        if (key == SC_ENTER) {
            switch (sel) {
            case MI_RESUME:
                save_options();
                return 1;
            case MI_LCD:
                settings.lcd_palette = !settings.lcd_palette;
                break;
            case MI_COLUMNS:
                settings.columns = (settings.columns == 40) ? 80 : 40;
                cols = settings.columns;
                set_columns(cols);
                scr = VMEM_PAGE0;
                /* Re-show page 0 after mode switch */
                r.h.ah = BIOS_SETPAGE;
                r.h.al = 0;
                int86(VIDEO_INT, &r, &r);
                break;
            case MI_RDIST: {
                int idx = get_rdist_idx();
                idx = (idx + 1) % RDIST_COUNT;
                settings.render_dist = rdist_vals[idx];
                break;
            }
            case MI_FARSHADE:
                settings.far_shade = !settings.far_shade;
                break;
            case MI_ENHPREC:
                settings.enhanced_prec = !settings.enhanced_prec;
                break;
            case MI_FLRCEIL:
                settings.draw_floorceil = !settings.draw_floorceil;
                break;
            case MI_CONTROLS:
                show_controls(scr, cols);
                break;
            case MI_QUIT:
                save_options();
                return 0;
            }
            draw_menu(scr, cols, sel);
        }
    }
}

/*-----------------------------------------------------------------
  Debug menu - hex input helpers
-----------------------------------------------------------------*/

/* Convert hex char to nibble value, -1 if invalid */
static int hex_val(unsigned char sc)
{
    if (sc >= 0x02 && sc <= 0x0A) return sc - 1;  /* 1-9 */
    if (sc == 0x0B) return 0;                       /* 0 key */
    if (sc == 0x1E) return 0xA;  /* A */
    if (sc == 0x30) return 0xB;  /* B */
    if (sc == 0x2E) return 0xC;  /* C */
    if (sc == 0x20) return 0xD;  /* D */
    if (sc == 0x12) return 0xE;  /* E */
    if (sc == 0x21) return 0xF;  /* F */
    return -1;
}

static const char hex_chars[] = "0123456789ABCDEF";

/* Format a byte as 0xNN into buf (must be 5+ chars) */
static void fmt_hex(char *buf, unsigned char val)
{
    buf[0] = '0'; buf[1] = 'x';
    buf[2] = hex_chars[(val >> 4) & 0xF];
    buf[3] = hex_chars[val & 0xF];
    buf[4] = '\0';
}

/* Read a 2-digit hex value from keyboard. Shows "0x__" at (row,col).
   Returns the byte value entered. ESC cancels (returns old value). */
static unsigned char input_hex(VIDMEM scr, int cols,
                               int row, int col, unsigned char old)
{
    unsigned char hi, lo, sc;
    int v;

    v_puts(scr, cols, row, col, "0x__", AT_VALUE);

    /* High nibble */
    for (;;) {
        sc = wait_any_key();
        if (sc == SC_ESC) return old;
        v = hex_val(sc);
        if (v >= 0) { hi = (unsigned char)v; break; }
    }
    v_putch(scr, cols, row, col + 2, hex_chars[hi], AT_VALUE);

    /* Wait for release */
    while (key_state[sc]) ;

    /* Low nibble */
    for (;;) {
        sc = wait_any_key();
        if (sc == SC_ESC) return old;
        v = hex_val(sc);
        if (v >= 0) { lo = (unsigned char)v; break; }
    }
    v_putch(scr, cols, row, col + 3, hex_chars[lo], AT_VALUE);

    while (key_state[sc]) ;

    return (hi << 4) | lo;
}

/*-----------------------------------------------------------------
  show_debug_menu - Debug tools menu (Z key, requires ENG-DEBUG=1)
  Currently: edit floor/ceiling char and color attribute.
  Returns 1 always (resume game).
-----------------------------------------------------------------*/
#define DM_CEIL_CHAR  0
#define DM_CEIL_ATTR  1
#define DM_FLOOR_CHAR 2
#define DM_FLOOR_ATTR 3
#define DM_BACK       4
#define DM_ITEMS      5

int show_debug_menu(void)
{
    static const int dm_rows[DM_ITEMS] = { 5, 6, 8, 9, 11 };
    VIDMEM scr = VMEM_PAGE0;
    int cols = settings.columns;
    int sel = 0;
    int vcol;
    union REGS r;

    unsigned char cc, ca, fc, fa;  /* ceil char/attr, floor char/attr */

    /* Decompose current VRAM words */
    cc = (unsigned char)(dbg_ceil_cell & 0xFF);
    ca = (unsigned char)(dbg_ceil_cell >> 8);
    fc = (unsigned char)(dbg_floor_cell & 0xFF);
    fa = (unsigned char)(dbg_floor_cell >> 8);

    vcol = (cols == 80) ? 36 : 20;

    /* Show page 0 */
    r.h.ah = BIOS_SETPAGE;
    r.h.al = 0;
    int86(VIDEO_INT, &r, &r);

    for (;;) {
        unsigned char key;
        char hbuf[6];
        int ccol = cols - 2;

        v_clear(scr, cols);

        { int c = (cols - 19) / 2;
          v_puts(scr, cols, 1, c, "=== Debug Tools ===", AT_TITLE); }

        v_puts(scr, cols, 3, 2, "-- Ceiling --", AT_DIM);

        v_puts(scr, cols, 5, 2, "Char:", AT_LABEL);
        fmt_hex(hbuf, cc);
        v_puts(scr, cols, 5, vcol, hbuf, AT_VALUE);
        v_putch(scr, cols, 5, vcol + 5, cc, ca);  /* preview */

        v_puts(scr, cols, 6, 2, "Color:", AT_LABEL);
        fmt_hex(hbuf, ca);
        v_puts(scr, cols, 6, vcol, hbuf, AT_VALUE);

        v_puts(scr, cols, 7, 2, "-- Floor --", AT_DIM);

        v_puts(scr, cols, 8, 2, "Char:", AT_LABEL);
        fmt_hex(hbuf, fc);
        v_puts(scr, cols, 8, vcol, hbuf, AT_VALUE);
        v_putch(scr, cols, 8, vcol + 5, fc, fa);  /* preview */

        v_puts(scr, cols, 9, 2, "Color:", AT_LABEL);
        fmt_hex(hbuf, fa);
        v_puts(scr, cols, 9, vcol, hbuf, AT_VALUE);

        v_puts(scr, cols, 11, 2, "Back", AT_LABEL);

        /* Cursor */
        v_putch(scr, cols, dm_rows[sel], ccol, 0xDB, AT_CURSOR);

        v_puts(scr, cols, 13, 2, "ENTER=edit hex  ESC=back", AT_DIM);

        key = menu_wait_key();

        if (key == SC_ESC) break;
        if (key == SC_UP && sel > 0) sel--;
        if (key == SC_DOWN && sel < DM_ITEMS - 1) sel++;

        if (key == SC_ENTER) {
            switch (sel) {
            case DM_CEIL_CHAR:
                cc = input_hex(scr, cols, 5, vcol, cc);
                break;
            case DM_CEIL_ATTR:
                ca = input_hex(scr, cols, 6, vcol, ca);
                break;
            case DM_FLOOR_CHAR:
                fc = input_hex(scr, cols, 8, vcol, fc);
                break;
            case DM_FLOOR_ATTR:
                fa = input_hex(scr, cols, 9, vcol, fa);
                break;
            case DM_BACK:
                goto done;
            }
        }
    }
done:
    /* Pack back into VRAM words */
    dbg_ceil_cell  = TC(cc, ca);
    dbg_floor_cell = TC(fc, fa);
    return 1;
}

/*-----------------------------------------------------------------
  show_tile_menu - Tile picker for debug placement (O key).
  Sets dbg_place_tile. Returns 1 always.
-----------------------------------------------------------------*/
int show_tile_menu(void)
{
    static const char *tile_names[NUM_TILES] = {
        "Air (empty)", "Stone", "Brick", "Wood", "Log",
        "Tree", "Dirt", "Grass", "Sand", "Rocks", "Glass"
    };
    VIDMEM scr = VMEM_PAGE0;
    int cols = settings.columns;
    int sel = (int)dbg_place_tile;
    union REGS r;

    r.h.ah = BIOS_SETPAGE;
    r.h.al = 0;
    int86(VIDEO_INT, &r, &r);

    for (;;) {
        unsigned char key;
        int i, ccol = cols - 2;
        int c;

        v_clear(scr, cols);
        c = (cols - 20) / 2;
        v_puts(scr, cols, 1, c, "=== Tile Picker ===", AT_TITLE);

        for (i = 0; i < NUM_TILES; i++) {
            v_puts(scr, cols, 3 + i, 2, tile_names[i], AT_LABEL);
            if (i == (int)dbg_place_tile)
                v_puts(scr, cols, 3 + i, 16, "<cur>", AT_DIM);
        }

        v_putch(scr, cols, 3 + sel, ccol, 0xDB, AT_CURSOR);
        v_puts(scr, cols, 3 + NUM_TILES + 1, 2, "ENTER=select  ESC=back", AT_DIM);

        key = menu_wait_key();

        if (key == SC_ESC) return 1;
        if (key == SC_UP && sel > 0) sel--;
        if (key == SC_DOWN && sel < NUM_TILES - 1) sel++;
        if (key == SC_ENTER) {
            dbg_place_tile = (unsigned char)sel;
            return 1;
        }
    }
}

/*-----------------------------------------------------------------
  CGA mode 4 graphics helpers for minimap
-----------------------------------------------------------------*/

/* Write a single pixel in CGA mode 4 (320x200, 2bpp) */
static void gfx_pixel(int x, int y, unsigned char color)
{
    unsigned char far *base;
    unsigned int offset;
    int shift;

    if ((unsigned)x >= 320 || (unsigned)y >= 200) return;

    base = (y & 1) ? (unsigned char far *)((0xB800L << 16) | 0x2000L)
                    : (unsigned char far *)(0xB800L << 16);
    offset = (unsigned)(y >> 1) * 80 + (unsigned)(x >> 2);
    shift = 6 - ((x & 3) << 1);
    base[offset] = (base[offset] & ~(3 << shift))
                 | (unsigned char)(color << shift);
}

/* Fill a rectangle in CGA mode 4 */
static void gfx_rect(int x0, int y0, int w, int h, unsigned char color)
{
    int x, y;
    for (y = y0; y < y0 + h; y++) {
        unsigned char far *base;
        unsigned int row_off;
        if ((unsigned)y >= 200) continue;
        base = (y & 1) ? (unsigned char far *)((0xB800L << 16) | 0x2000L)
                       : (unsigned char far *)(0xB800L << 16);
        row_off = (unsigned)(y >> 1) * 80;
        for (x = x0; x < x0 + w; x++) {
            unsigned int off;
            int shift;
            if ((unsigned)x >= 320) continue;
            off = row_off + (unsigned)(x >> 2);
            shift = 6 - ((x & 3) << 1);
            base[off] = (base[off] & ~(3 << shift))
                      | (unsigned char)(color << shift);
        }
    }
}

/* Map tile type to CGA 4-color index (palette 1) */
static unsigned char tile_to_color(unsigned char t)
{
    switch (t) {
    case TILE_EMPTY: return 0;  /* black          */
    case TILE_STONE: return 3;  /* white          */
    case TILE_BRICK: return 2;  /* magenta        */
    case TILE_WOOD:  return 1;  /* cyan           */
    case TILE_LOG:   return 1;
    case TILE_TREE:  return 1;
    case TILE_DIRT:  return 2;
    case TILE_GRASS: return 1;
    case TILE_SAND:  return 2;
    case TILE_ROCKS: return 3;
    case TILE_GLASS: return 1;
    default:         return 0;
    }
}

/*-----------------------------------------------------------------
  show_minimap - Render top-down map in CGA mode 4 (320x200, 4-color).
  Switches video mode, draws map + player, waits for key.
  Caller is responsible for restoring text mode via set_columns().
-----------------------------------------------------------------*/
void show_minimap(Player *p, Map *m)
{
    union REGS r;
    int mx, my, ox, oy, px, py;
    int scale;
    int mw = (int)m->w;
    int mh = (int)m->h;

    /* Compute scale: largest square that fits 320x200 */
    scale = 200 / mh;
    if ((320 / mw) < scale) scale = 320 / mw;
    if (scale < 1) scale = 1;

    ox = (320 - mw * scale) / 2;
    oy = (200 - mh * scale) / 2;

    /* Switch to CGA mode 4 (320x200, 4-color) */
    r.h.ah = BIOS_SETMODE;
    r.h.al = 0x04;
    int86(VIDEO_INT, &r, &r);

    /* Select palette 1: cyan / magenta / white */
    r.h.ah = 0x0B;
    r.h.bh = 1;
    r.h.bl = 1;
    int86(VIDEO_INT, &r, &r);

    /* Draw map tiles */
    for (my = 0; my < mh; my++) {
        for (mx = 0; mx < mw; mx++) {
            unsigned char tile = m->data[(unsigned)my * m->w + (unsigned)mx];
            unsigned char color = tile_to_color(tile);
            gfx_rect(ox + mx * scale, oy + my * scale,
                      scale, scale, color);
        }
    }

    /* Draw player position as white cross */
    px = ox + FIX2INT(p->px) * scale + scale / 2;
    py = oy + FIX2INT(p->py) * scale + scale / 2;
    gfx_pixel(px, py, 3);
    gfx_pixel(px - 1, py, 3);
    gfx_pixel(px + 1, py, 3);
    gfx_pixel(px, py - 1, 3);
    gfx_pixel(px, py + 1, 3);

    /* Draw facing direction: 3-pixel line from player center */
    {
        int dx = cos_tab[p->angle];
        int dy = sin_tab[p->angle];
        int i;
        for (i = 2; i <= 4; i++) {
            int fx = px + (int)((long)dx * i / 256);
            int fy = py + (int)((long)dy * i / 256);
            gfx_pixel(fx, fy, 2);  /* magenta direction indicator */
        }
    }

    /* Wait for any key to return */
    wait_any_key();
}
