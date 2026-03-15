/* RCMENU.C - Options menu and controls submenu                    */
/* Renders to CGA VRAM page 0, navigated with arrow keys + Enter  */

#include <stdio.h>
#include "raycast.h"

/* Menu item indices */
#define MI_RESUME    0
#define MI_LCD       1
#define MI_16X16     2
#define MI_COLUMNS   3
#define MI_RDIST     4
#define MI_FARSHADE  5
#define MI_ENHPREC   6
#define MI_FLRCEIL   7
#define MI_CONTROLS  8
#define MI_QUIT      9
#define MENU_ITEMS   10

/* Row on screen for each menu item */
static const int menu_rows[MENU_ITEMS] = { 3, 5, 6, 7, 8, 9, 10, 11, 12, 14 };

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

    /* 16x16 Textures */
    v_puts(scr, cols, 6, 2, "16x16 Textures:", AT_LABEL);
    if (settings.lcd_palette)
        v_puts(scr, cols, 6, vcol, "N/A", AT_DIM);
    else {
        val = settings.use_16x16 ? "ON " : "OFF";
        v_puts(scr, cols, 6, vcol, val, AT_VALUE);
    }

    /* Columns */
    v_puts(scr, cols, 7, 2, "Columns:", AT_LABEL);
    val = (settings.columns == 80) ? "80" : "40";
    v_puts(scr, cols, 7, vcol, val, AT_VALUE);

    /* Render Distance */
    v_puts(scr, cols, 8, 2, "Render Distance:", AT_LABEL);
    v_puts(scr, cols, 8, vcol, rdist_names[get_rdist_idx()], AT_VALUE);

    /* Far Shade */
    v_puts(scr, cols, 9, 2, "Far Shade:", AT_LABEL);
    val = settings.far_shade ? "ON " : "OFF";
    v_puts(scr, cols, 9, vcol, val, AT_VALUE);

    /* Enhanced Precision */
    v_puts(scr, cols, 10, 2, "Enhanced Precision:", AT_LABEL);
    val = settings.enhanced_prec ? "ON " : "OFF";
    v_puts(scr, cols, 10, vcol, val, AT_VALUE);

    /* Floor/Ceiling */
    v_puts(scr, cols, 11, 2, "Floor/Ceiling:", AT_LABEL);
    val = settings.draw_floorceil ? "ON " : "OFF";
    v_puts(scr, cols, 11, vcol, val, AT_VALUE);

    /* Controls */
    v_puts(scr, cols, 12, 2, "Controls...", AT_LABEL);

    /* Quit */
    v_puts(scr, cols, 14, 2, "Quit Game", AT_LABEL);

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
    fprintf(f, "%d\n", (int)settings.use_16x16);
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
    if (fscanf(f, "%d", &v) == 1) settings.use_16x16       = (unsigned char)v;
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
    if (settings.lcd_palette) settings.use_16x16 = 0;
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
                settings.lcd_palette ^= 1;
                if (settings.lcd_palette)
                    settings.use_16x16 = 0;
                break;
            case MI_16X16:
                if (!settings.lcd_palette)
                    settings.use_16x16 ^= 1;
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
                settings.far_shade ^= 1;
                break;
            case MI_ENHPREC:
                settings.enhanced_prec ^= 1;
                break;
            case MI_FLRCEIL:
                settings.draw_floorceil ^= 1;
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
