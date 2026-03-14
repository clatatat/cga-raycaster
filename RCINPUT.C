/* RCINPUT.C - INT 9h keyboard ISR for real-time key state         */
/* Installs a custom hardware keyboard interrupt handler that     */
/* tracks make/break codes for smooth held-key input.             */
/* CRITICAL: remove_keyboard() MUST be called before program exit */

#include "raycast.h"
#include <conio.h>

/* Key state array: 1 = pressed, 0 = released, indexed by scan code */
unsigned char key_state[128];

/* Saved original INT 9h vector */
static void (interrupt far *old_isr)(void);

/*-----------------------------------------------------------------
  new_kb_isr - Custom INT 9h keyboard interrupt service routine
  
  Reads the raw scan code from keyboard port 0x60.
  Make codes (bit 7 clear) set key_state[code] = 1.
  Break codes (bit 7 set) clear key_state[code & 0x7F] = 0.
  Acknowledges the keystroke and sends EOI to the PIC.
-----------------------------------------------------------------*/
static void interrupt far new_kb_isr(void)
{
    unsigned char scan;
    unsigned char ctrl;

    /* Read scan code from keyboard data port */
    scan = inp(0x60);

    /* Update key state */
    if (scan & 0x80) {
        /* Break code (key released) */
        key_state[scan & 0x7F] = 0;
    } else {
        /* Make code (key pressed) */
        key_state[scan] = 1;
    }

    /* Acknowledge keystroke to keyboard controller */
    ctrl = inp(0x61);
    outp(0x61, ctrl | 0x80);    /* set bit 7 to acknowledge */
    outp(0x61, ctrl & 0x7F);    /* clear bit 7 to re-enable */

    /* Send End-Of-Interrupt to PIC (8259A) */
    outp(0x20, 0x20);
}

/*-----------------------------------------------------------------
  install_keyboard - Save original INT 9h and install our ISR
-----------------------------------------------------------------*/
void install_keyboard(void)
{
    int i;

    /* Clear all key states */
    for (i = 0; i < 128; i++)
        key_state[i] = 0;

    /* Save original ISR and install ours */
    old_isr = _dos_getvect(9);
    _dos_setvect(9, new_kb_isr);
}

/*-----------------------------------------------------------------
  remove_keyboard - Restore original INT 9h handler
  MUST be called before program exit or the system will crash.
-----------------------------------------------------------------*/
void remove_keyboard(void)
{
    if (old_isr != (void (interrupt far *)(void))0)
        _dos_setvect(9, old_isr);
}

/*-----------------------------------------------------------------
  process_input - Read key states and update player position/angle
  
  Controls:
    W / Up Arrow    = move forward
    S / Down Arrow  = move backward
    A               = turn left
    D               = turn right
    Left Arrow      = strafe left
    Right Arrow     = strafe right
    ESC             = quit
  
  Returns 1 to continue, 0 if ESC was pressed.
-----------------------------------------------------------------*/
int process_input(Player *p, Map *m)
{
    short moveX, moveY;
    short strafeX, strafeY;
    fix8 newX, newY;

    /* ESC = quit */
    if (key_state[SC_ESC])
        return 0;

    /* Turn left/right (A/D keys) */
    if (key_state[SC_A])
        p->angle -= TURN_SPEED;     /* wraps naturally (unsigned char) */

    if (key_state[SC_D])
        p->angle += TURN_SPEED;

    /* Movement direction from angle */
    moveX = cos_tab[p->angle];
    moveY = sin_tab[p->angle];

    /* Strafe direction (perpendicular to movement) */
    strafeX = -sin_tab[p->angle];
    strafeY =  cos_tab[p->angle];

    /* Forward / backward (W/S or Up/Down) */
    if (key_state[SC_W] || key_state[SC_UP]) {
        newX = p->px + fix_mul(MOVE_SPEED, moveX);
        newY = p->py + fix_mul(MOVE_SPEED, moveY);
        /* Collision: check X and Y independently for wall sliding */
        if (map_get(m, FIX2INT(newX), FIX2INT(p->py)) == TILE_EMPTY)
            p->px = newX;
        if (map_get(m, FIX2INT(p->px), FIX2INT(newY)) == TILE_EMPTY)
            p->py = newY;
    }

    if (key_state[SC_S] || key_state[SC_DOWN]) {
        newX = p->px - fix_mul(MOVE_SPEED, moveX);
        newY = p->py - fix_mul(MOVE_SPEED, moveY);
        if (map_get(m, FIX2INT(newX), FIX2INT(p->py)) == TILE_EMPTY)
            p->px = newX;
        if (map_get(m, FIX2INT(p->px), FIX2INT(newY)) == TILE_EMPTY)
            p->py = newY;
    }

    /* Strafe left/right (arrow keys) */
    if (key_state[SC_LEFT]) {
        newX = p->px - fix_mul(STRAFE_SPEED, strafeX);
        newY = p->py - fix_mul(STRAFE_SPEED, strafeY);
        if (map_get(m, FIX2INT(newX), FIX2INT(p->py)) == TILE_EMPTY)
            p->px = newX;
        if (map_get(m, FIX2INT(p->px), FIX2INT(newY)) == TILE_EMPTY)
            p->py = newY;
    }

    if (key_state[SC_RIGHT]) {
        newX = p->px + fix_mul(STRAFE_SPEED, strafeX);
        newY = p->py + fix_mul(STRAFE_SPEED, strafeY);
        if (map_get(m, FIX2INT(newX), FIX2INT(p->py)) == TILE_EMPTY)
            p->px = newX;
        if (map_get(m, FIX2INT(p->px), FIX2INT(newY)) == TILE_EMPTY)
            p->py = newY;
    }

    return 1;
}
