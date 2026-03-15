/* RAYCAST.H - Master header for CGA text-mode raycaster engine  */
/* Target: Microsoft QuickC 2.5, small model, CGA mode 1 (40x25) */
/* Assemble helpers: MASM 5.1 (/Mx for case-sensitive publics)    */

#ifndef RAYCAST_H
#define RAYCAST_H

#include <dos.h>

/* ================================================================
   Fixed-point 8.8 signed arithmetic
   Range: -128.0 to +127.996  (0x8000 .. 0x7FFF)
   Resolution: 1/256 = 0.00390625
   ================================================================ */
typedef short fix8;

#define FIX_ONE     256
#define FIX_HALF    128
#define INT2FIX(n)  ((fix8)((n) << 8))
#define FIX2INT(n)  ((short)(n) >> 8)
#define FIX_FRAC(n) ((n) & 0xFF)

/* Provided by RCMATH.ASM (MASM 5.1, .MODEL SMALL, C) */
extern short cdecl fix_mul(short a, short b);
extern short cdecl fix_div(short a, short b);

/* ================================================================
   Screen constants - CGA text mode 1 (40x25 color)
   ================================================================ */
#define SCREEN_W     40
#define SCREEN_H     25
#define MAX_COLS     80        /* max supported columns (80-col mode) */
#define SCREEN_CELLS 1000   /* SCREEN_W * SCREEN_H */

/* ================================================================
   Video memory - CGA direct memory access via far pointers
   Each cell = 2 bytes: low byte = ASCII char, high byte = attribute
   40x25 mode: page size = 2048 bytes (2000 used + 48 padding)
   ================================================================ */
typedef unsigned short far *VIDMEM;

#define CGA_SEG      0xB800L
#define PAGE0_OFF    0x0000L
#define PAGE1_OFF    0x0800L   /* 2048 bytes per page in 40x25 */
#define VMEM_PAGE0   ((VIDMEM)((CGA_SEG << 16) | PAGE0_OFF))
#define VMEM_PAGE1   ((VIDMEM)((CGA_SEG << 16) | PAGE1_OFF))

/* ================================================================
   BIOS INT 10h video services
   ================================================================ */
#define VIDEO_INT    0x10
#define BIOS_SETMODE 0x00
#define BIOS_SETPAGE 0x05
#define BIOS_SETCUR  0x01
#define BIOS_GETMODE 0x0F
#define CGA_MODE1    0x01     /* 40x25 color text */

/* ================================================================
   Textures - 8x8 character cells, compiled-in as C arrays
   Each texel = packed VRAM word: (attr << 8) | char
   ================================================================ */
#define TEX_SIZE     8
#define TEX_SHIFT    3        /* log2(TEX_SIZE) */
#define TEX_MASK     7        /* TEX_SIZE - 1   */

/* Pack a character + attribute into a CGA VRAM word */
#define TC(ch, at)   ((unsigned short)(((unsigned char)(at) << 8) \
                     | (unsigned char)(ch)))

/* ================================================================
   Tile types - index into tex_table[]
   ================================================================ */
#define TILE_EMPTY   0
#define TILE_STONE   1
#define TILE_BRICK   2
#define TILE_WOOD    3
#define TILE_LOG     4
#define TILE_TREE    5
#define NUM_TILES    6

/* Sprite tile helpers */
#define TILE_IS_SPRITE(t) ((t) == TILE_TREE)
#define MAX_SPRITES  16     /* max visible sprites per frame */
#define SPRITE_MAX_DIST  INT2FIX(8)  /* sprites vanish beyond 8 tiles */

/* ================================================================
   Map structure - supports 16x16 up to 256x256
   data[] is row-major: data[y * w + x]
   ================================================================ */
#define MAX_MAP_DIM  256

typedef struct {
    unsigned short w;
    unsigned short h;
    unsigned char far *data;
} Map;

/* ================================================================
   Player state
   ================================================================ */
typedef struct {
    fix8 px, py;            /* position in map units (8.8 FP)    */
    unsigned char angle;    /* 0-255: 0=east, 64=north, 128=west */
} Player;

/* ================================================================
   Ray hit result - one per screen column
   ================================================================ */
typedef struct {
    fix8 dist;              /* perpendicular distance (8.8 FP)   */
    unsigned char tile;     /* tile type that was hit             */
    unsigned char texX;     /* texture X column (0 .. TEX_SIZE-1) */
    unsigned char side;     /* 0 = vertical wall, 1 = horizontal */
} RayHit;

/* ================================================================
   Rendering constants
   ================================================================ */
/* Wall height at distance 1.0 fills the screen (25 rows) */
#define WALL_CONST   INT2FIX(SCREEN_H)   /* 6400 = 25 << 8 */

/* Camera plane magnitude: tan(FOV/2) where FOV ~60 degrees */
/* tan(30) = 0.577; using 0.66 for Wolfenstein-style wider FOV */
#define FOV_PLANE    169     /* ~0.66 in 8.8 FP */

/* ================================================================
   Movement tuning
   ================================================================ */
#define MOVE_SPEED   24      /* ~0.094 map units/frame */
#define STRAFE_SPEED 20      /* slightly slower strafe */
#define TURN_SPEED   3       /* ~4.2 degrees/frame     */

/* ================================================================
   Keyboard scan codes (AT/XT make codes)
   ================================================================ */
#define SC_ESC       0x01
#define SC_ENTER     0x1C
#define SC_W         0x11
#define SC_A         0x1E
#define SC_S         0x1F
#define SC_D         0x20
#define SC_UP        0x48
#define SC_DOWN      0x50
#define SC_LEFT      0x4B
#define SC_RIGHT     0x4D
#define SC_I         0x17
#define SC_O         0x18
#define SC_P         0x19
#define SC_SPACE     0x39

/* ================================================================
   Extern declarations - trig tables (RCMATH.C)
   ================================================================ */
extern const short sin_tab[256];
extern const short cos_tab[256];

/* ================================================================
   Settings - run-time options changeable from the menu
   ================================================================ */
typedef struct {
    unsigned char lcd_palette;   /* 0=OFF, 1=ON */
    unsigned char columns;       /* 40 or 80 */
    unsigned char render_dist;   /* 0=Infinite, 8, 16, or 24 tiles */
    unsigned char far_shade;     /* 0=OFF, 1=ON: flat cell beyond 8 tiles */
    unsigned char enhanced_prec; /* 0=OFF, 1=ON: half-block edge precision */
    unsigned char draw_floorceil;/* 0=OFF, 1=ON: render floor/ceiling chars */
} Settings;

extern Settings settings;

/* ================================================================
   Controls - rebindable key scan codes
   ================================================================ */
typedef struct {
    unsigned char sc_forward;
    unsigned char sc_backward;
    unsigned char sc_turn_left;
    unsigned char sc_turn_right;
    unsigned char sc_strafe_left;
    unsigned char sc_strafe_right;
    unsigned char sc_primary;
    unsigned char sc_secondary;
    unsigned char sc_tertiary;
    unsigned char sc_quaternary;
} Controls;

extern Controls controls;

/* Key-action flags: set each frame by process_input() */
extern unsigned char keyflag1;   /* Primary action   */
extern unsigned char keyflag2;   /* Secondary action */
extern unsigned char keyflag3;   /* Tertiary action  */
extern unsigned char keyflag4;   /* Quaternary action*/

/* ================================================================
   Function prototypes
   ================================================================ */

/* RCCAST.C - raycasting engine */
void cast_rays(Player *p, Map *m, RayHit hits[]);

/* RCDRAW.C - video init, rendering, page flipping */
void init_video(void);
void restore_video(void);
void set_columns(unsigned char cols);
void render_frame(RayHit hits[]);
void render_sprites(Player *p, Map *m, RayHit hits[]);
void flip_page(void);

/* RCTEX.C - texture data */
extern unsigned short far *tex_table[];
extern unsigned short far_table[];
extern unsigned char half_table[];     /* attribute for half-block edges */

/* RCLCD.C - LCD-optimised texture data */
extern unsigned short far *lcd_tex_table[];
extern unsigned short lcd_far_table[];
extern unsigned char lcd_half_table[]; /* attribute for half-block edges */

/* RCINPUT.C - keyboard ISR and input processing */
void install_keyboard(void);
void remove_keyboard(void);
int  process_input(Player *p, Map *m);
extern unsigned char key_state[];

/* RCMAP.C - map data and access */
void map_init(Map *m);
unsigned char map_get(Map *m, int x, int y);

/* RCMENU.C - options menu */
int show_menu(void);
void save_options(void);
void load_options(void);

#endif /* RAYCAST_H */
