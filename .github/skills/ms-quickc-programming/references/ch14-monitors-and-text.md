Chapter 14  Monitors and Text Modes

    Professional application programs, including QuickC itself, use a much
    fancier screen interface than we have used in our programs. In this
    chapter we produce some of those screen features in QuickC. First we must
    overcome the problem posed by the variety of different display systems.
    IBM supports several monitor-video controller systems: monochrome, CGA,
    EGA, MCGA, and VGA. In general, these systems use different hardware, and
    different memory and port addresses. They also provide different colors,
    resolutions, and graphics capabilities.

    Writing programs that run on a range of video controller systems can be
    troublesome, especially if you want something fancier or faster than the
    teletype-like output produced by standard C Library functions. This
    chapter concentrates on solving these problems for text-mode programs. We
    continue using BIOS calls, and we introduce direct memory access and
    ports. We also look at the IBM "graphics character" set, which lets you
    create screen graphics without leaving text mode.


Monitors and Controllers

    IBM has developed several different video standards, each involving its
    own hardware video controller and corresponding monitors. In the PC
    series, the hardware controllers are on add-on cards called "adapters." In
    the new PS/2 series, however, the circuitry for controlling the monitor is
    built into the motherboard. We use the term "video controller" in this
    book to encompass both the adapter cards and the built-in control
    circuitry.

    The most widely used video controller is the Monochrome Display Adapter,
    or MDA. When coupled with a monitor called the Monochrome Display, it
    produces a high-resolution, text-only display consisting of 25 rows of 80
    characters each.

    The next most commonly used controller is the Color Graphics Adapter, or
    CGA. It can be used with color or B/W monitors capable of either 40-by-25
    or 80-by-25 text displays (but not the Monochrome Display). It has seven
    separate modes of operation. Although the 80-by-25 display shows as many
    characters as the Monochrome Display, its lower resolution creates coarser
    text characters.

    Recently, the Enhanced Graphics Adapter, or EGA, has become popular. It is
    compatible with the Monochrome Display, with normal CGA displays, and with
    a high-resolution monitor called the Enhanced Display (ED). Used with a
    Monochrome Display, it provides a graphics mode in addition to the text
    mode. Used with CGA-style monitors, it provides more colors than the CGA
    board does. Used with the Enhanced Display (or equivalent), it emulates
    the CGA modes with increased text resolution, and it provides three
    additional graphics modes.

    The newest controllers are the Multi-Color Graphics Array (MCGA), found on
    the PS/2 Model 30, and the Video Graphics Array (VGA), found on the PS/2
    Models 50, 60, 70, and 80. The MCGA matches CGA resolution but offers an
    enormously greater range of colors. The VGA emulates the EGA modes, adds
    three new graphics modes, offers higher resolution for all text modes, and
    provides more colors.

    Table 14-1 summarizes some of the differences in features offered by the
    various video controllers we have introduced. Resolution is given in
    pixels, or picture elements, the elementary display elements from which
    characters and images are built. The size of a pixel depends on the
    controller and the mode. A pixel in mode 0, for example, is twice as wide
    as a pixel in mode 2. However, the VGA controller produces smaller pixels
    than the CGA controller, even when both are in mode 0. Also, not all
    monitors have sufficient resolution to support a controller's use of
    pixels. A CGA monitor, for example, is physically incapable of generating
    the higher resolution (smaller pixel) modes of the EGA and VGA. In
    general, all modes cannot produce the maximum number of colors, and only a
    subset of available colors can be shown at any one time.

    Table 14-1 Video Controllers
    Name    Horizontal       Vertical        Colors  Modes    Monitors
            Resolution       Resolution
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    MDA     720              350             2       1        MDâ˜¼
    CGA     640/320          200             16      7        Colorâ˜¼, B/Wâ˜¼
    EGA     640/320          350/200         64      12       EDâ˜¼, MDâ˜¼,
                                                            Colorâ˜¼, B/Wâ˜¼
    MCGA    720/360/640/320  400/480/200     262,    11       PSMâ˜¼, EDâ˜¼, MDâ˜¼,
                                            144              Colorâ˜¼, B/Wâ˜¼
    VGA     720/360/640/320  400/480/350/200 262,    15       PSMâ˜¼, EDâ˜¼, MDâ˜¼,
                                            144              Colorâ˜¼, B/Wâ˜¼
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€


Text Modes and Portability

    Fortunately, all these video controllers support an 80-by-25 text mode,
    and that simplifies the task of writing programs to run with all
    combinations.

Controller Similarities

    A comparison of 80-by-25 text modes for different hardware combinations
    shows both similarities and differences. In all cases, the screen is
    treated as an array of characters rather than as an array of pixels. That
    is, you can only display or alter entire characters, not the individual
    pixels that comprise the characters.

    All controllers use two bytes of memory to represent each text-mode
    character. One byte holds the character's ASCII code, and the other byte
    holds the character's display attribute. All video controllers also
    contain random access memory (video RAM) in which character data is mapped
    to the display. That is, the controller periodically scans the video RAM
    to determine which characters it should display. Therefore, to change the
    screen display, you must change the appropriate bytes in the video RAM.
    Note that text-mode video RAM always consists of 4000 bytes: One screen
    holds 80 x 25, or 2000, characters, each represented by two bytes.

    All controllers also maintain a table of character fonts called a
    "character generator." The controller uses these pixel patterns to
    physically represent characters on the screen. For example, ASCII code 72
    in the video RAM tells the controller to put an H at a screen location,
    and the character font table specifies the particular "H" pixel pattern to
    use. (See Figure 14-1 on the following page.)

    These similarities ease the task of writing text programs that are
    compatible with the various displays.

        Video RAM                       Font ROM
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”           â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ 072 (ASCII code)â”‚           â”‚ H (Font info)   â”‚
    â”‚  â–’              â”‚           â”‚ â–’               â”‚
    â””â”€â”€â–’â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜           â””â”€â–’â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
        â–’                            â–’
        â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’
                â–’
            â•”â•â•â•â•â•â–’â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•—
            â•‘  â”Œâ”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”  â•‘
            â•‘  â”‚  H                  â”‚  â•‘
            â•‘  â”‚                     â”‚  â•‘
            â•‘  â”‚                     â”‚  â•‘
            â•‘  â”‚                     â”‚  â•‘
            â•‘  â”‚                     â”‚  â•‘
            â•‘  â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜  â•‘
            â•šâ•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
                    Display

    Figure 14-1. Producing characters with the MDA.

    Differences between displays complicate the programming process. For
    example, one powerful video technique called "direct memory access" uses
    pointers to video RAM to directly alter RAM contents. However, the MDA
    uses a different video RAM address than other controllers, so your program
    must always test for its use. Another programming technique uses "ports"
    to access registers on the controllers. However, the various controllers
    have different numbers of registers, and each register has a different
    port address and performs a different function. This makes for very
    involved hardware programming.

    Video controllers also contain differing amounts of video RAM. The MDA has
    only enough memory to hold one screenful, or page, of characters. The
    other controllers hold enough memory to hold four or more pages of text.

    Most controllers offer different screen resolutions. Although all the
    controllers display a maximum of 2000 characters on the screen, some can
    generate more pixels than others. For example, the CGA screen consists of
    a matrix of 640 horizontal pixels (for 80 characters) by 200 vertical
    pixels (for 25 display lines). The net result is that each character is
    represented by an 8-by-8-pixel grid, or "character box." The MDA, on the
    other hand, generates 720 horizontal pixels and 350 lines, providing a
    9-by-14-pixel character box. Thus, MDA characters look better than their
    CGA counterparts because each character is drawn with more detail, as
    shown in Figure 14-2.

    Finally, the color displays can use the attribute byte to specify
    foreground and background colors for each character. Table 14-2 provides
    a summary of the different characteristics of video controllers operating
    in text mode.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 14-2 can be found on p.453 of the printed version of the book.  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 14-2. Character boxes.

    Table 14-2 Summary of Text-Mode Differences
    Controller           Video RAM Starting   Pages      Character Color
                        Address                         Box Size
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    MDA                  0xB8000              1          9 x 14    No
    CGA                  0xB0000              4          8 x 8     Yes
    EGA (mode 7)         0xB8000              4/8â˜¼       9 x 14    No
    EGA (modes 2, 3)     0xB0000              4/8â˜¼       8 x 14    Yes
    MCGA                 0xB0000              8          9 x 16    Yes
    VGA                  0xB0000              8          9 x 16    Yes
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€


Device-independent Programming

    When programming for the PC, you have the choice of programming for
    specific hardware or ignoring the hardware altogether. The direct memory
    access method discussed later in this chapter uses hardware information
    explicitly. To write device-independent programs that don't require
    explicit hardware information, use one or more of the following methods:

    1.  Program with the standard C Library output functions such as printf()
        and putchar(). This results in portable code, but it limits the
        positioning of text and doesn't permit the use of color.

    2.  Use the ANSI.SYS escape sequences, as described in Chapter 13.
        However, if your program utilizes the cursor-control keys, for
        example, you must use console I/O functions, which restrict
        portability. Also, using ANSI.SYS inhibits some special features of
        the EGA, such as the 43-line display. The ANSI approach works on all
        systems that recognize the standard ANSI codes; IBM PCs and clones
        must have the ANSI.SYS driver installed.

    3.  Use IBM PC BIOS calls, as described in Chapter 13. The BIOS includes
        programs for all PC video controllers, and it selects the appropriate
        code for the display and controller you are using. That's why our
        examples in Chapter 13 didn't specify a monitor or controller. BIOS
        calls also support using more than one page of screen memory; but
        because the MDA has only one page, we suggest you restrict
        applications to page 0.

    We thoroughly covered the first two choices in the last chapter. Although
    we also discussed BIOS calls, we skipped some of the detail until you
    understood more about the hardware. In the next section we will discuss
    BIOS calls in greater detail.

Working with BIOS Again: Attributes

    In Chapter 13, we built a small library (SCRFUN.LIB) of BIOS-based C
    functions that are hardware-independent. In fact, insulating the user from
    the hardware is one of the primary reasons for having a BIOS. For
    instance, we can use the same BIOS calls to control the way in which
    characters are displayed on an MDA, CGA, EGA, or VGA monitor. The
    attribute of a character controls its appearance. Let's see how we can use
    the BIOS to investigate and control attributes.

    An attribute is a 1-byte value in which the individual bits have
    particular meanings that affect the appearance of the associated
    character. For example, with the Monochrome Display Adapter, bit 7 of the
    attribute controls the blink function, bits 6â”€4 control the background,
    bit 3 controls the intensify foreground function, and bits 2â”€0 control the
    foregroundâ”€â”€that is, the pixels constituting the character. (See Figure
    14-3.) Table 14-3 lists the standard attribute values used by the MDA.

    Bit numbers â”€â”€â”€â”€â”€7     6     5     4     3     2     1    0
                â”Œâ”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”
                â”‚     â”‚     â”‚     â”‚     â”‚     â”‚     â”‚     â”‚     â”‚
                â””â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”˜
                    â”‚  â””â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”˜  â”‚  â””â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                    â”‚       Background      â”‚       Foreground
                Blink bit             Intensity bit

    Figure 14-3. Monochrome attribute bits.

    Table 14-3 Monochrome Attributes
    Bit Pattern        Hex Value         Meaning
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    0000 0000          0x00              No display
    0000 0111          0x07              Normal display
    0111 0000          0x70              Reverse video
    0000 0001          0x01              Underline
    0111 0111          0x77              Whiteout
    1xxx xxxx          0x80              Blink mode
    xxxx 1xxx          0x08              Intensified foreground
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Note: The last two entries are used with different modes. For example,
    10000111 (0x87) is normal display with blinking, while 11110000 (0xF0) is
    reverse video with blinking. The x's indicate that those values don't
    affect blinking or intensity.

    The other video controllers use bits 6â”€4 to control the color of the
    background and bits 2â”€0 to control the color of the foreground. Bits 7 and
    3 serve the same function as they do for the MDA. Figure 14-4 shows the
    color that each bit controls.

    Bit numbers â”€â”€â”€â”€â”€7     6     5     4     3     2     1    0
                â”Œâ”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”
                â”‚ BL  â”‚  R  â”‚  G  â”‚  B  â”‚  I  â”‚  R  â”‚  G  â”‚  B  â”‚
                â””â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”˜
                    â”‚  â”‚ Red  Green Blue â”‚  â”‚  â”‚ Red  Green Blue â”‚
                    â”‚  â””â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”˜  â”‚  â””â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                    â”‚       Background      â”‚       Foreground
                    Blink                 Intensify
                                        foreground

    Figure 14-4. Color attribute bits.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    The EGA BIOS
    The IBM BIOS was created long before the inception of the EGA. How, then,
    can you use BIOS routines to control the EGA? The EGA card comes with a
    set of BIOS interrupt 0x10 video I/O routines in its own ROM. Recall that
    the address of each interrupt routine is stored in the interrupt vector
    table. When you boot an EGA system, the entry for video interrupt 0x10 is
    loaded with the EGA BIOS address instead of the motherboard BIOS address.
    Thus, the old BIOS routines are bypassed and the new EGA-supplied ones are
    used.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    To produce a blue character on a red screen, use an attribute of 01000001.
    This turns on the red background bit and the blue foreground bit. To make
    the foreground a bright blue, turn on the intensity bit with 01001001.

    If you set both the blue and green foreground bits, the blue and the green
    phosphors on the display screen are simultaneously turned on, producing a
    color called cyan. Setting all three foreground bits turns on all three
    colors, which, by the laws of video color mixing, produces white.
    Similarly, clearing all three bits causes no pixels to be turned on,
    producing black. Therefore, the "normal" monochrome attribute of 00000111
    also produces white-on-black characters for the CGA, EGA, and VGA. Table
    14-4 shows the colors generated by the various 3-bit combinations.

    Table 14-4 Text Color Values
    Bit Pattern        Hex Foreground    Hex Background     Color
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    000                0x0               0x00               Black
    001                0x1               0x10               Blue
    010                0x2               0x20               Green
    011                0x3               0x30               Cyan
    100                0x4               0x40               Red
    101                0x5               0x50               Magenta
    110                0x6               0x60               Dark yellow
                                                            (brown)
    111                0x7               0x70               White (light gray)
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Note: The hex value 0x8 intensifies the foreground color, and 0x80 makes
    the character blink. Also, all attributes can be combined using logical
    operators.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Colors
    All colors can be produced by combining three primary colors together in
    varying proportions. The three "additive" primary colors are red, green,
    and blue. For example, when you direct a beam of green light and a beam of
    red light toward a piece of white paper, the area where the beams overlap
    (or are "added") appears yellow.

    A color video screen also creates colors by combining the additive
    primaries. Each pixel on a color screen contains individual red, green,
    and blue dots. Turning a pixel blue amounts to turning on the blue dots in
    the pixel. To produce yellow, you turn on the green and the red dots in a
    pixelâ”€â”€the eye perceives only the combined light, which is yellow.

    The PC's system of using numbers to represent color imitates the physical
    color-mixing process. For example, in binary notation, the color number
    for red is 100 and the color number for green is 010. Turning on both the
    red and the green bits corresponds to specifying the binary number 110,
    which is the code for yellow.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Suppose you want a yellow character on a blue background. Because yellow
    is produced by combining red and green light (bits 2 and 1), and
    background blue is bit 4, the corresponding attribute is 00010110, or
    0x16. (The actual colors you see depend on your monitor and its
    adjustments.)

    It's more interesting to display the attributes on the screen than it is
    to read about them, so let's develop a program that changes the attribute
    bits to demonstrate how the colors change. First we must write a function
    that prints a string using a given attribute. Using the functions from our
    SCRFUN.LIB library, we produce the following Print_attr() function
    (Listing 14-1).

    Print_attr() writes a character-attribute pair and moves the cursor one
    position to the right. Print_attr() has its limitations. First, it doesn't
    recognize the end of a line. Second, it doesn't have all the fancy
    formatting that printf() has. (You can modify the function to handle the
    end-of-line problem and use the sprintf() function to do the formatting.)

    Now let's use the Print_attr() string-displaying function in a program to
    display the various attributes. To demonstrate the role of each attribute
    bit, the program has you type the attribute byte as a binary number. The
    comments in the ATTRIB.C program (Listing 14-2 on the following page)
    explain the workings of the various functions. Before you run the ATTRIB.C
    program, pull down the Debug menu: Screen Swapping On should be active
    (indicated by a check to the left of the option). If it is not active,
    choose it from the menu to activate it.

    This program works with any of the previously mentioned standard video
    controllers. If you have a monochrome monitor, check to see what
    nonstandard combinations such as 00000100 produce. If you have a color
    monitor, enjoy the many color combinations.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* Print_attr() -- prints the string str using */
    /* attribute attr on the indicated page        */
    /* It uses functions from the scrfun.c file.   */

    void Print_attr(str, attr, page)
    char *str;
    unsigned char attr, page;
    {
        while (*str != '\0')
            {
            Write_ch_atr(*str++, attr, page, 1);
            Cursrt();
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-1.  The Print_attr() function.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* attrib.c -- this program illustrates attributes */
    /* program list: attrib.c, scrfun.lib              */
    /* user include files: scrn.h                      */
    /* Note: activate Screen Swapping On in Debug menu */
    #include <stdio.h>
    #include <conio.h>
    #include "scrn.h"
    #define PAGE 0
    #define ESC '\033'
    char *Format = "This message is displayed using an "
                    "attribute value of %2X hex (%s).";
    int Get_attrib(char *);
    void Print_attr(char *, unsigned char, unsigned char);

    main()
    {

        int attribute;       /* value of attribute   */
        char attr_str[9];    /* attr. in string form */
        char mesg[80];

        Clearscr();
        Home();
        printf("Enter an attribute as an 8-digit binary "
                "number, such as 00000111, and see a\n"
                "message displayed using that attribute."
                "Hit <Esc> to quit.\n"
                "Attribute = ");
        while ((attribute = Get_attrib(attr_str)) != -1)
            {
            Setcurs(10,0,PAGE);
            sprintf(mesg, Format, attribute, attr_str);
            Print_attr(mesg, attribute, PAGE);
            Setcurs(2, 12, PAGE);
            printf("         ");  /* clear old display */
            Setcurs(2, 12, PAGE);
            }
        Clearscr();
    }

    /* The following function reads in a binary number    */
    /* as a sequence of 1s and 0s. It places the 1 and 0  */
    /* characters in a string whose address is passed as  */
    /* an argument. It returns the numeric value of the   */
    /* binary number. Bad input is summarily rejected.    */
    /* The function returns -1 when you press Esc.        */
    int Get_attrib(a_str)
    char a_str[];     /* attribute as binary string */
    {
        int attrib[8];
        int index = 7;
        int ch;
        int attribute = 0; /* attrib. as numeric value */
        int pow;

        a_str[8] = '\0';  /* terminate string */
        while ((index >= 0) && (ch = getch()) != ESC)
            {
            if (ch != '0' && ch != '1')  /* bad input */
                putch('\a');
            else
                {
                putch(ch);
                a_str[index] = ch;      /* string form */
                attrib[index--] = ch - '0'; /* numeric */
                }
            }
        if (ch == ESC)
            return (-1);
        else            /* convert numeric array to a number */
            {
            for(index = 0, pow = 1; index < 8;
                                    index++, pow *= 2)
                attribute += attrib[index] * pow;
            return attribute;
            }
    }

    /* The following function prints the string str using */
    /* attribute attr on the indicated page.              */
    /* It uses functions from the scrfun.c file.          */

    void Print_attr(str, attr, page)
    char *str;
    unsigned char attr, page;
    {
        while (*str != '\0')
            {
            Write_ch_atr(*str++, attr, page, 1);
            Cursrt();
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-2.  The ATTRIB.C program.

Attributes and Bitwise Operators

    You can also manipulate attributes with the C bitwise operators that we
    discussed in Chapter 7. Suppose, for example, a program uses the
    following definitions:

    #define NORMAL 0x07
    #define VIDREV 0x70
    #define BLINK  0x80
    #define INTENSE 0x08

    To set mode to an intense, normal attribute, we can use the bitwise
    logical OR operator, as follows:

    mode = NORMAL | INTENSE;

    Because 1 OR anything is 1, all bits set to 1 are left on. Now, suppose
    mode has already gone through several changes. At this point it might be
    normal, reverse video, or have blinking on or off, etc. To turn on the
    intensify mode regardless of the current state, use an instruction like
    the following:

    mode = mode | INTENSE;

    The only bit this instruction can change is bit 3, the intensity bit,
    because all the other bits of INTENSE are 0, and 0 OR any bit is merely
    that bit. (That is, 0 | 0 is 0, and 1 | 0 is 1.) Furthermore, this
    instruction always sets bit 3 to 1, regardless of its previous value. (0 |
    1 is 1, and 1 | 1 is 1.) Incidentally, you can also use a combination
    assignment operator to rewrite the last C statement as follows:

    mode |= INTENSE;  /*unconditionally turns INTENSE on */

    Sometimes an instruction must "toggle" a bit. That is, the instruction
    turns on an off bit or turns off an on bit. For this, we use the EXCLUSIVE
    OR operator (^). Recall that this operator produces a "true" value (1) if
    one operand or the other is "true" but not if both are "true." The
    following expression toggles the intensity bit:

    mode = mode ^ INTENSE;

    If the intensity bit in mode is initially off, the expression becomes 0 ^
    1, which is 1, or on. If the intensity bit in mode is initially on, the
    expression is 1 ^ 1, which is 0, or off. Again, we can simplify the
    statement with the following combination assignment operator:

    mode ^= INTENSE;  /* toggles the intensity bit */

Compatible "Graphics"

    A system with true graphics capability lets you individually control each
    pixel on the screen. By its very makeup, the MDA lacks that ability. The
    CGA provides graphics modes, and the EGA and VGA have additional graphics
    abilities. Therefore, to produce true graphics, a program must address
    specific hardware.

    However, IBM has given the PC a limited but more universal graphics
    capability by extending the character set. The ASCII character set uses
    the values 0 through 127. But because a byte can store any value through
    255, IBM added 128 additional characters to the set and assigned them code
    values 128 through 255. These constitute the IBM Extended Character Set.
    Many of these characters are mathematical symbols, foreign-language
    characters, and so on. However, 48 of the characters (codes 176 through
    223) constitute the "graphics characters," which are useful for drawing
    and filling rectangular forms.

    With these characters, you can do a limited amount of hardware-independent
    graphics. The QuickC screen, for example, uses these characters to draw
    its boxes and borders. In fact, you can use QuickC to examine the extended
    ASCII set. Pull down the general Help menu and browse through it until you
    reach the screen that displays the extended set.

    You can also display the extended set of characters from the keyboard. To
    see what character 206 looks like, first press Num Lock; then, at your
    system prompt, hold down the Alt key and type 206 using the keys in the
    numeric keypad. When you release Alt, the character appears on the
    display.

Programming with the Graphics Character Set

    Let's develop a QuickC program to help us investigate the extended
    character set. Below are some of the features we need to develop in a
    program that draws with the graphics characters.

    â–   Key-mapping so that a single keystroke generates a graphics character

    â–   Cursor control for drawing at different screen locations

    â–   An erasing feature

    â–   An auto-drawing feature that generates strings of characters across the
        screen

    â–   An attribute manipulator for highlighting text or turning on blinking

    Many of these goals resemble problems we solved in Chapter 13; therefore,
    we can put our previously developed tools to good use now. For example, we
    can use the getch() function and scan codes to use the function keys and
    the cursor-control keys. We can call the BIOS to clear the screen and to
    provide cursor-movement functions. And by using the method developed for
    REKEY.C (Listing 13-7 on p. 411), we can map the keys. In short, we have
    the tools; now we have to organize them into a workable QuickC program.

    The User Interface

    Today it is not enough to design a program that works. Interactive
    programs require that the programmer think about the user's point of view.
    In our case, for example, we need to plan how to best use the keyboard to
    control the graphics characters.

    For example, which key represents which character? With 48 graphics
    characters, there is no obvious mnemonic method for assigning keys. And it
    is unreasonable to expect a user to remember 48 random assignments. To
    help the user, we display the graphics characters and key assignments at
    the bottom of the screen. We also list other important keys.

    Next, we must plan how to manage the drawing process. Drawing with
    graphics characters often involves repeatedly using the same character.
    Merely mapping a graphics character to a key is acceptable only for
    repeating the character left to right because that's the way keyboard
    input normally works. But drawing characters vertically or from right to
    left is more difficult. Cursor control helps, but drawing a vertical line
    would entail pressing the character key, using the Down Arrow key to move
    down a line, using the Left Arrow key to move under the first character,
    and then pressing the character key again. Therefore, we must use a
    different technique.

    In our solution to the problem, the character keys select, but do not
    display, a graphics character. To actually display the character, the user
    must press one of the arrow keys. This places the character at the current
    position of the cursor, then shifts the cursor in the direction of the
    arrow key. Until the user selects another character key, the current
    graphics character remains active. Therefore, repeatedly pressing an arrow
    key moves the cursor and leaves a display trail of the current graphics
    character. This simplifies drawing horizontal and vertical lines.

    Now let's add some refinements. The PgUp key disenables drawing so that
    the user can move the cursor without displaying characters. The PgDn key
    restores the drawing mode. The Spacebar represents the program's "eraser."
    The user can select the Spacebar as the current graphics character and use
    the cursor keys to delete unwanted characters. Our last refinement lets
    the user select character attributes with the function keys.

    We take advantage of QuickC's program list feature to split the program
    into three file modules. Note that two of the modules use SCRFUN.LIB and
    scrn.h and one uses keys.h, all developed in Chapter 13. We also collect
    the define statements for the three modules in an include file called
    grafchar.h.

    First, look at the main program, GRAFCHAR.C (Listing 14-3). To run this
    program within the QuickC environment, be sure that Screen Swapping On is
    active (on the Debug menu).

    GRAFCHAR.C is a simple programâ”€â”€it merely calls the other two files in the
    program list: initstuf.c and drawchar.c. We will discuss these modules in
    the next two sections. Before you proceed to those sections, however,
    examine the grafchar.h header file (Listing 14-4).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*   grafchar.c -- draws graphics characters with      */
    /*                 attributes on the screen            */
    /*  Program list : grafchar.c, initstuf.c, drawchar.c, */
    /*                  scrfun.lib                         */
    /*  User include files: keys.h, scrn.h, grafchar.h     */
    /*  Note: activate Screen Swapping On in Debug menu    */

    #include "grafchar.h"
    unsigned char Grchr[NUMCHARS];  /* to store graphics set */
    void Init_stuff(void);      /* in initstuf.c */
    void Draw_chars(void);      /* in drawchar.c */

    main()
    {
        Init_stuff();  /* initialize vital elements */
        Draw_chars();  /* map keys to graphics characters */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-3.  The GRAFCHAR.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* grafchar.h -- header file for grafchar.c program */
    /*               Version 1                          */
    #define NUMCHARS 48  /* number of graphics chars  */
    #define SPACE '\040'
    #define BOTLINE 19   /* line # for end of drawing space */
    #define PAGE 0
    #define GCSTART 0xB0 /* ascii for first graphics char */
    #define BEEP '\a'
    #define ESC '\033'
    #define TRUE 1
    #define FALSE 0
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-4.  The grafchar.h header file.

    Setting Up the Program: initstuf.c

    The initstuf.c module (Listing 14-5 on the following page) sets up the
    GRAFCHAR.C program. It initializes the external array grafchar.c to the 48
    graphics characters and clears the screen. At the bottom of the screen, it
    prints the graphics characters and their corresponding keystrokes. Also
    listed are the following non-ASCII keys and their functions: The F1
    function key sets the normal white-on-black text attribute; F2 selects
    reverse video; F3 toggles blinking; and F4 toggles foreground intensity.
    The program uses Print_attr() to show how the last three attributes appear
    on screen. For example, the phrase F3 : Blinking is displayed on screen in
    the blinking mode.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  initstuf.c -- initializing module for grafchar.c */
    /*  assigns graphics character codes to an array     */
    /*  and initializes screen                           */

    #include "scrn.h"   /* Clearscr(), Home(), Setcurs() */
    #include "grafchar.h"
    extern unsigned char Grchr[];  /* defined in grafchar.c */
    void Print_attr(char *, unsigned char, unsigned char);
    [bn]
    void Init_stuff()
    {
        int i;

        /* initialize array with graphics characters */
        for (i = 0; i < NUMCHARS; i++)
            Grchr[i] = GCSTART + i;
        Clearscr();
        Home();

        /* show key meanings at bottom of screen */
        Setcurs(BOTLINE + 1, 0, PAGE);
        for (i = 0; i < 40; i++) /* graphics chars */
            {
            putch(Grchr[i]);
            putch(SPACE);
            }
        Setcurs(BOTLINE + 2, 0, PAGE);
        for (i = 0; i < 40; i++)  /* key assignments */
            {
            putch('0' + i);
            putch(SPACE);
            }
        Setcurs(BOTLINE + 3, 0, PAGE);
        for (i = 40; i < NUMCHARS; i++) /* second row */
            {
            putch(Grchr[i]);
            putch(SPACE);
            }
        /* show function key assignments */
        printf(" SPACE : ERASE  PgUp : No Draw ");
        printf(" PgDn : Draw  ESC : Quit");
        Setcurs(BOTLINE + 4, 0, PAGE);
        for (i = 40; i < NUMCHARS; i++) /* second row */
            {
            putch('0' + i);
            putch(SPACE);
            }
        /* more function key assignments */
        Print_attr("F1 : Normal ", NORMAL, PAGE);
        Print_attr("F2 : Reverse Video ", VIDREV, PAGE);
        Setcurs(BOTLINE + 5, 16, PAGE);
        Print_attr("F3 : Blinking ", NORMAL | BLINK, PAGE);
        Print_attr("F4 : Intense ", NORMAL | INTENSE, PAGE);
        Home();
    }

    void Print_attr(str, attr, page)
    char *str;
    unsigned char attr, page;
    {
        while (*str != '\0')
            {
            Write_ch_atr(*str++, attr, page, 1);
            Cursrt();
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-5.  The initstuf.c module.

    Drawing the Characters: drawchar.c

    The final module, drawchar.c (Listing 14-6), contains the code that
    translates keystrokes into action. First, it maps the 48 keystrokes to the
    graphics characters. After the program initializes the Spacebar character,
    it uses a switch statement to process PgUp, PgDn, the cursor control keys,
    and the four function keys. Figure 14-5 on p. 467 shows some sample
    output from this program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* drawchar.c -- drawing module for grafdraw.c         */
    /* translates keystrokes to graphic characters,        */
    /* manages cursor control and function keys            */

    #include <conio.h>
    #include "keys.h"
    #include "scrn.h"
    #include "grafchar.h"
    extern unsigned char Grchr[];  /* defined in grafchar.c */

    void Draw_chars()
    {
        int ch, chout;
        unsigned char attrib = NORMAL;
        unsigned char draw = TRUE;

        chout = Grchr[0];  /* default  graphics character */
        while ((ch = getch()) != ESC)
            {
            if (ch >= '0' && ch <= '_')
                chout = Grchr[ch - '0'];
                /* this maps the 0 key to the first */
                /* graphics character, etc.         */
            else if (ch == SPACE)
                chout = SPACE;
            else if (ch == 0) /* process cursor keys */
                {             /* and function keys   */
                ch = getch();
                switch (ch)
                    {
                    case PU : draw = FALSE;
                            break;
                    case PD : draw = TRUE;
                            break;
                    case UP : if (draw)
                                Write_ch_atr(chout, attrib,
                                                PAGE, 1);
                            if (!Cursup())
                                putch(BEEP);
                            break;
                    case DN : if (draw)
                                Write_ch_atr(chout, attrib,
                                                PAGE, 1);
                            if (!Cursdn_lim(BOTLINE))
                                putch(BEEP);
                            break;
                    case LT : if (draw)
                                Write_ch_atr(chout, attrib,
                                                PAGE, 1);
                            if (!Curslt())
                                putch(BEEP);
                            break;
                    case RT : if (draw)
                                Write_ch_atr(chout, attrib,
                                                PAGE, 1);
                            if (!Cursrt())
                                putch(BEEP);
                            break;
                    case F1 : attrib = NORMAL; break;
                    case F2 : attrib = VIDREV; break;
                    case F3 : attrib ^= BLINK; break;
                    case F4 : attrib ^= INTENSE; break;
                    default : putch(BEEP);
                    }
                }
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-6.  The drawchar.c module.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 14-5 can be found on p.467 of the printed version of the book.  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 14-5. Drawing with GRAFCHAR.C.

Details of the Program

    The easiest way to see how the program works is to try it out. Move the
    cursor around with the arrow keys and use the keyboard to select different
    graphics characters. (Remember to have Screen Swapping On active if you're
    working in the QuickC environment.) To help you see why it works the way
    it does, we'll look at some of the programming details next.

    In the Draw_chars() function, the following statement maps the keystrokes
    to the graphics characters:

    if (ch >= '0' && ch <= '_')
        chout = Grchr[ch - '0'];

    In this function, ch is the input character; chout is the output character
    used when the cursor keys are pressed. When the user presses the 0 key,
    the program uses the array index of '0' - '0', or 0, which selects the
    first graphics character in the array. Similarly, the 1 key selects the
    second graphics character, and so on.

    Next, look at how the program handles the cursor key:

    case UP : if (draw)
                    Write_ch_atr(chout, attrib, PAGE, 1);
                if (!Cursup())
                    putch(BEEP);
                break;

    If draw is set to TRUE, the program displays the current output character
    (chout) using the current attribute (attrib). In this example, the cursor
    then moves up one line unless it already is at the top line, in which case
    the program issues a beep.

    The other arrow keys are processed similarly. Note that the Down Arrow key
    uses Cursdn_lim(BOTLINE) instead of Cursdn(). Recall from Chapter 13 that
    Cursdn() is a macro that moves the cursor down as far as line 25;
    Cursdn_lim(), however, is limited by a passed argument. Because we reserve
    the bottom of the screen for the key table, the BOTLINE limit keeps the
    cursor from intruding.

    The program uses the following code for selecting an attribute:

    case F1 : attrib = NORMAL; break;
    case F2 : attrib = VIDREV; break;
    case F3 : attrib ^= BLINK; break;
    case F4 : attrib ^= INTENSE; break;

    F1 and F2 set the attribute to the normal and reverse video modes,
    respectively. F3 and F4 use the EXCLUSIVE OR operator to toggle the
    intensify and the blink modes. Why directly set two modes and toggle the
    other two? The toggled intensify and blink modes can be on simultaneously
    and compounded with the other modes. However, NORMAL must be off when
    VIDREV is on, and vice versa. If both were on at the same time, the screen
    would display a white foreground on a white backgroundâ”€â”€that is, a
    featureless white square. If both were off, the display would be black on
    black, or no display.

    Limitations of the Program

    To make the GRAFCHAR.C program compatible with all monitors (except
    40-by-25 displays), we must impose some limitations. Most importantly, the
    program limits attributes to monochrome values; less importantly, it uses
    only page 0 of memory.

    If you have a color monitor, you can add color to the program by setting
    the function keys as follows:

    case F1 : attrib ^= BLUE; break;
    case F2 : attrib ^= GREEN; break;
    case F3 : attrib ^= RED; break;
    case F4 : attrib ^= BG_BLUE; break;
    case F5 : attrib ^= BG_GREEN; break;
    case F6 : attrib ^= BG_RED; break;
    case F7 : attrib ^= BLINK; break;
    case F8 : attrib ^= INTENSE; break;

    Also, make the following definitions:

    #define BLUE   0x1
    #define GREEN  0x2
    #define RED    0x4
    #define BG_BLUE   0x10
    #define BG_GREEN  0x20
    #define BG_RED    0x40

    This lets you independently toggle each bit of the attribute. When the
    attribute is initially set to NORMAL, blue, green, and red are all toggled
    on. Pressing F2, for example, turns green off and leaves the red-blue
    (magenta) combination.

    You should also change the key table at the bottom of the screen to
    reflect the new uses of the function keys.


Direct Memory Access

    Thus far, we've used BIOS routines to place the proper character and
    attribute bytes into video memory. This method offers two advantagesâ”€â”€it
    saves us work and lets us write hardware-independent programs that run on
    the MDA, CGA, EGA, VGA, and MCGA. However, we can create faster programs
    by bypassing the BIOS and placing data directly into video memory. This
    programming technique is called "Direct Video Memory Access," which we
    will refer to as DMA for the remainder of this book. (Don't confuse this
    use of DMA with the DMA chip built into the IBM PC and compatibles, which
    performs a different function.)

DMA Basics

    To copy information to or from a memory location, you need to use the
    address of that location. Often, you do so symbolically and indirectly by
    using variables and array names. Pointers provide a more obvious way to
    use addresses. So what do you use to access video memory?

    Because video memory is a large block of bytes, it's natural to think of
    it as a large array. As you've learned, arrays can often be described by
    either array notation or pointer notation. But with video memory, you must
    use pointers. The reason is that the compiler chooses the physical
    addresses to which an array corresponds, but you can choose the physical
    address to which a pointer points. In particular, you can choose to have a
    pointer point to the beginning of video memory.

    The specific address you use depends on the hardware. The MDA uses 0xB0000
    (720,896 in decimal), and the CGA uses 0xB8000 (753,664 in decimal). The
    EGA and VGA use 0xB0000 for the monochrome mode and 0xB8000 for the color
    text modes.

    To use the address you must typecast the numeric value to the proper
    pointer type. Also, in the small and medium memory models, a data pointer
    is a 16-bit quantity. Neither of the addresses we need fits into 16 bits.
    The large memory model uses a 32-bit pointer, but not in a way that lets
    us make our simple assignment. So before we can assign the video RAM
    address to a pointer, we must first examine how the PC and QuickC handle
    memory addresses.

Segmented Memory

    The PC has the same problem with large addresses that the small and medium
    models do. The 8086 chip normally uses a 16-bit register for addresses.
    However, this permits the register to address a maximum of 64 KB of
    memory, which falls far short of the address needed to access the video
    RAM.

    The 8086 family of microprocessors uses segmented memory to overcome this
    problem. The maximum size of each segment is 64 KB, the size addressable
    by an address register. Typically, a program uses one segment for program
    code and a second segment for data.

    Addresses for the program code are 16-bit addresses relative to the
    beginning of the program segment, and data addresses are relative to the
    beginning of the data segment. These relative addresses are called
    "offsets." In C, this offset is what is stored in a 16-bit pointer. The
    following statement:

    printf("Address of x is %u\n", &x);

    prints out the offset, in bytes, of x from the beginning of a data
    segment. To keep track of where the code and data segments are, the PC
    uses special registers: the CS, or Code Segment register, and the DS, or
    Data Segment register.

    To solve the problem of identifying the location of a segment using only
    16 bits, the PC divides the actual address of the segment by 16 (0x10
    hex). For example, 0xB0000 divided by 0x10 is 0xB000. This divided
    quantity is called the "segment value." (See Figure 14-6.) Thus, a
    segment value of 0xA000 corresponds to a segment address of 0xA0000. As a
    result of this system, segments must start at addresses that are multiples
    of 16.

    Suppose you want to specify the 0x20th byte of video memory. The absolute
    address of this byte is 0xB0020. The PC represents this by setting the
    data segment register DS to the segment value of 0xB000 and setting the
    data offset register to 0x20. The following equation expresses the
    relationship more generally:

    absolute address = 0x10 x segment value + offset

                                        â”Œâ”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                                        â”‚ â”‚                      â”‚
                                        â”‚ â”‚                      â”‚
                                        â”‚ â”‚                      â”‚
                                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                            Data segmentâ”€â”€â”€â”¤ â”‚  01001101 01001111   â”‚â”€â”€â”€Data at
                                (64 KB)   â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤â”€â” specifie
                                        â”‚ â”‚                      â”‚ â”‚ location
        DS register                        â”‚ â”‚                      â”‚ â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”                     â”‚ â”‚                      â”‚ â”‚
    â”‚ Segment value â”‚                     â”‚ â”‚                      â”‚ â”œâ”€Offset
    â””â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”˜                     â”‚ â”‚                      â”‚ â”‚
            â”‚                              â”‚ â”‚                      â”‚ â”‚
            â–¼                              â””â”€â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜â”€â”˜
    Segment value * 16 = Segment addressâ”€â”€â”€â”€â”˜

    Figure 14-6. Data addresses are represented by a segment value and an
    offset.

    Note that you can represent the same physical address in many ways. For
    example, the absolute address 0xB0020 also can be represented with a
    segment value of 0xB001 and an offset of 0x10.

    C, Segments, and Offsets

    As you already know, C has two classes of pointersâ”€â”€near and far. Near
    pointers, which are 16 bits, hold only the offset. Far pointers, which are
    32 bits, use the high 16 bits to hold the segment value and the low 16
    bits to hold the offset, as shown in Figure 14-7. Compact and large
    models use far data pointers by default. Small and medium models use near
    data pointers by default. However, you can use the nonstandard C keyword
    far to create far pointers in the small and medium models. To use the far
    keyword in QuickC, choose Language Extensions in the Compile Options
    dialog box.

    Using a Far Pointer

    To access the video memory, we must declare a far pointer, initialize its
    high bytes to the segment value for the video RAM, and use its low bytes
    for the offset. Declare a far pointer by using the keyword far, as
    follows:

    unsigned short far *far_pnt; /* far pointer */

    This creates a 32-bit pointer that points to a 2-byte unit. Each 2-byte
    unit holds the ASCII code and the attribute of a single displayed
    character.

    Next, let's set the pointer to an absolute screen address of 0xB0020. This
    corresponds to a segment value of 0xB000 (0xB0000 / 0x10) and an offset of
    0x20. To place the segment value into the high bytes, left-shift it 16
    places; because the offset goes into the lower bytes, you needn't
    manipulate it at all.

    far_pnt = (unsigned short far *) (0xB000L << 16) | 0x20;

    Note that we used a typecast to convert the right side (type long) to the
    correct type. Next, we used the L suffix to make the segment value type
    long. Otherwise, 0xB000 would be treated as type int (a 16-bit type on a
    PC), and the 16-bit left-shift would shift all the bits out, leaving only
    zeros. (See Figure 14-8 on the following page.)

    Note also that the bitwise OR (|) operator combines the segment value and
    the offset. Because one resides entirely in the upper bytes and the other
    is confined to the lower bytes, this has the same effect as addition, but
    is faster.

        Segment value        Offset
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚                 â”‚                 â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜
        High bytes         Low bytes

    Figure 14-7. Filling a far pointer.

                        â”‚ 1 byte â”‚
                        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”
                        â”‚  B 8   â”‚  0 0   â”‚
                        â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                â–’
                            B800 << 16
                                â–’
            â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’
            â–’                    â–’
            â–¼           â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”
        B 8     0 0      â”‚  0 0   â”‚  0 0   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    Discarded Values

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚  0 0   â”‚  0 0   â”‚  B 8   â”‚  0 0   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                        â–’
                    B800L  << 16
                        â–’
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚  B 8   â”‚  0 0   â”‚  0 0   â”‚  0 0   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 14-8. The left-shift operator.

    Finally, note that the far pointer does not hold the absolute address. It
    holds two quantities: segment value and offset. If, for some reason, you
    want the absolute address, you can obtain it by using the following
    expression:

    abs_addr = 0x10 * (far_ptr >> 16) + far_ptr & 0xFFFF;

    The right-shift produces the segment value; multiplying by 0x10 gives the
    segment address; and the 0xFFFF mask screens the segment value of the
    pointer, leaving just the offset. The variable abs_addr should be type
    long or unsigned long so that it can hold the entire address.

Using Direct Memory Accessâ”€â”€An Example

    To use DMA to access video RAM, we must declare a far pointer and
    initialize it to point to the beginning of video memory. To do so, we must
    first decide which data type to point to. Think of one page of video
    memory as 2000 character-attribute units, with each unit describing a
    particular screen location. In QuickC, two bytes constitute a short value,
    so our pointer must be a far pointer to unsigned short. Use typedef to
    make VIDMEM a synonym for that type:

    typedef unsigned short (far * VIDMEM);

    Then declare screen as a pointer of that type, as follows:

    VIDMEM screen;

    Next, you must decide which segment value to use. For the monochrome mode
    (mode 7), use 0xB000. For the CGA and CGA-compatible modes (0 through 6),
    use 0xB800. Because we must left-shift the segment value 16 bits to use it
    with a C far pointer, we represent our values as follows:

    #define MONMEM ((VIDMEM) (0xB000L << 16))
    #define CGAMEM ((VIDMEM) (0xB800L << 16))

    The L suffix makes the addresses 32-bit quantities, and the typecasting to
    type VIDMEM gives the numeric values the same type as the screen pointer.

    Recall that in the character-attribute pair, the low byte holds the
    character and the high byte holds the attribute. Therefore, if screen is
    the pointer to the beginning of video memory, if offset is the character
    position we wish to set, and if ch and attrib are character and attribute
    values, we use the following statement:

    *(screen + offset) = (attrib << 8) | ch;

    The left-shift puts attrib into the high byte, and the bitwise OR operator
    combines the resulting values, as shown in Table 14-5. Note that in
    QuickC, attrib must be at least a 16-bit type. If it is an 8-bit type, the
    significant bits are lost. (With older versions of Microsoft C, type char
    was converted to int for calculation, and no bits were discarded.)

    Let's use this information in a simple program. The CH2000.C program
    (Listing 14-7 on the following page) echoes any pressed ASCII key.
    However, instead of echoing it once, the program uses DMA to echo it 2000
    times. Also, the program cycles through all possible attribute values,
    making the color version more spectacular than the monochrome version. (Be
    sure Screen Swapping On is active. Also, use CGAMEM instead of MONMEM if
    you are using a color display.)

    The program first reads a character. The for loop displays the character
    at all 2000 positions. By using the increment operator on attrib, we
    change the attribute at each position and cycle through all 256
    possibilities.

    Table 14-5 Manipulating Character and Attribute in RAM
    Byte(s)            Bit Values                           Hex Equivalents
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    attrib             00000000 00000111                    0x0007
    attrib << 8        00000111 00000000                    0x0700
    ch                 01000001                             0x41
    (attrib << 8) | ch 00000111 01000001                    0x0741
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* ch2000.c -- fills screen with 2000 characters       */
    /*    This program demonstrates direct memory access   */
    /*    of video memory.  It is set up for the MDA.      */
    /*    Assign CGAMEM instead of MONMEM to screen for    */
    /*    CGA and CGA-compatible modes.                    */
    /*    Press a key to fill; press Esc to quit.          */
    /* Note: activate Screen Swapping On in Debug menu     */

    #include <conio.h>
    #include "scrn.h"
    typedef unsigned short (far * VIDMEM);
    #define MONMEM ((VIDMEM) (0xB000L << 16)) /* monochrome */
    #define CGAMEM ((VIDMEM) (0xB800L << 16)) /* CGA, EGA */
    #define ESC '\033'
    #define CHARS 2000
    #define AMASK 0xFF   /* keep attribute in range */
    main()
    {
        unsigned ch;          /* character to be displayed */
        unsigned attrib = 7;  /* initial attribute         */
        VIDMEM screen;        /* pointer to video RAM      */
        int offset;           /* location on screen        */

        screen = MONMEM;      /* monochrome initialization */
        while ((ch = getch()) != ESC)
            {
            for (offset = 0; offset < CHARS; offset++)
                *(screen + offset) = ((attrib++ & AMASK) << 8) | ch;
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-7.  The CH2000.C program.

    Notice how quickly the program fills the screen. To appreciate the speed
    of this program, rewrite it using the BIOS-based Write_ch_atr() function
    from SCRFUN.LIB and note the difference!

Making DMA More Compatible

    CH2000.C is fast and simple, but it doesn't work with all controllers. The
    program needs to be able to choose the correct memory value itself.
    Function 15 of the BIOS 0x10 video I/O interrupt enables it to do so.
    Because this routine returns the current video mode, the program can use
    that value to select the right video RAM address. Our SCRFUN.C file
    includes the Getvmode() function (Listing 14-8) based on that BIOS call.
    Note that the constant GETMODE is defined in the scrn.h file.

    Now rewrite CH2000.C as shown in the CH2001.C program (Listing 14-9). The
    constants TEXTMONO, TEXTBW80, and TEXTC80 are defined in scrn.h; they
    represent mode 7 (monochrome), mode 2 (CGA 80-by-25 B/W), and mode 3 (CGA
    80-by-25 Color), respectively.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    #include <dos.h>
    #include "scrn.h"
    /* Getvmode() -- obtains the current video mode */
    unsigned char Getvmode()
    {
        union REGS reg;

        reg.h.ah = GETMODE;
        int86(VIDEO, &reg, &reg);
        return reg.h.al;
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-8.  The Getvmode() function.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* ch2001.c -- fills screen with 2000 characters       */
    /*    This program demonstrates direct memory access   */
    /*    of video memory.  It uses the current video mode */
    /*    value to select the proper video RAM address.    */
    /*    Press a key to fill; press Esc to quit.          */
    /* Program list: ch2001.c, scrfun.lib                  */
    /* Note: activate Screen Swapping On in Debug menu     */

    #include <conio.h>
    #include "scrn.h"
    typedef unsigned short (far * VIDMEM);
    #define MONMEM ((VIDMEM) (0xB000L << 16)) /* monochrome */
    #define CGAMEM ((VIDMEM) (0xB800L << 16)) /* CGA, EGA */
    #define ESC '\033'
    #define CHARS 2000
    #define AMASK 0xFF
    main()
    {
        unsigned ch, mode;
        unsigned attrib = 7;
        VIDMEM screen;         /* pointer to video RAM */
        int offset;

        if ((mode = Getvmode()) == TEXTMONO)
            screen = MONMEM;
        else if (mode == TEXTC80 || mode == TEXTBW80)
            screen = CGAMEM;
        else
            exit(1);
        while ((ch = getch()) != ESC)
            {
            for (offset = 0; offset < CHARS; offset++)
                *(screen + offset) = ((attrib++ & AMASK) << 8) | ch;
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-9.  The CH2001.C program.

Storing and Displaying a Screen

    Let's use DMA to add some useful capabilities to the GRAFCHAR.C program.
    Although this program lets you draw on the screen using the graphics
    character set, when you quit the program, the drawing is lost. The program
    would be more useful if it let you store the created image in a file so
    you could use it later.

    DMA is ideally suited to copying information from the screen to a file and
    back again. We can incorporate the saving code into the program and make
    the recall a separate program.

    Saving the Screen

    To save the screen, rewrite the main program as SAVEGRAF.C (Listing
    14-10). In addition, we need to add some new definitions to the
    grafchar.h file. Listing 14-11 shows the new version. Be sure Screen
    Swapping On is active (on the Debug menu) before you run the program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* savegraf.c -- uses DMA to save screen of graphics  */
    /*               characters and attributes            */
    /* Program list - savegraf.c, initstuf.c, drawchar.c, */
    /*                savescrn.c, scrfun.lib              */
    /* User include files - scrn.h, keys.h, grafchar.h    */
    /* Note: activate Screen Swapping On in Debug menu    */

    #include "grafchar.h"
    unsigned char Grchr[NUMCHARS];  /* to store graphics set */
    void Init_stuff(void);
    void Draw_chars(void);
    void Save_screen(void);  /* in savescrn.c */

    main()
    {
        int ch;

        Init_stuff();  /* initialize vital elements */
        Draw_chars();  /* map keys to graphics characters */
        Setcurs(BOTLINE + 1, 0, PAGE);
        printf("%-80s", "Save screen? <y/n> ");
        Setcurs(BOTLINE + 1, 20, PAGE);
        ch = getche();
        if (ch == 'y' || ch == 'Y')
            Save_screen();
        Setcurs(BOTLINE + 2, 0, PAGE);
        printf("%-80s\n", "BYE!");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-10.  The SAVEGRAF.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* grafchar.h -- definitions for savescrn.c and       */
    /*               recall.c   Version 2                 */
    #define NUMCHARS 48
    #define SPACE '\040'
    #define BOTLINE 19  /* line # for end of drawing space */
    #define PAGE 0
    #define GCSTART 0xB0 /* ascii for first graphics char */
    #define BEEP '\a'
    #define ESC '\033'
    #define TRUE 1
    #define FALSE 0
    #define CHARS (BOTLINE + 1) * 80  /*    number of     */
                                    /* character positions */
    typedef unsigned short (far * VIDMEM);
    #define MONMEM ((VIDMEM) (0xB000L << 16)) /* mono */
    #define CGAMEM ((VIDMEM) (0xB800L << 16)) /* CGA, EGA */
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-11.   The revised grafchar.h header file.

    The SAVEGRAF.C program uses Setcurs() to position the text outside the
    drawing area. If the user chooses to save the screen, the Save_screen()
    function (Listing 14-12) does the work.

    Program Notes

    Because line numbering starts with 0, there are BOTLINE + 1 total lines.
    Therefore, the total number of character-attribute pairs that must be
    saved is that figure times 80; CHARS is defined as that value.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* savescrn.c -- saves screen, including attribute    */
    /*               values, in a file                    */
    /*               Uses direct memory access.           */

    #include <stdio.h>  /* for file handling */
    #include "scrn.h"
    #include "grafchar.h"
    void Save_screen()
    {
        FILE *save;
        char filename[80];
        unsigned char mode;
        unsigned short char_attr;  /* character, attribute */
        int offset;
        VIDMEM screen;

        if ((mode = Getvmode()) == TEXTMONO)
            screen = MONMEM;
        else if (mode == TEXTC80 || mode == TEXTBW80)
            screen = CGAMEM;
        else
            exit(1);
        Setcurs(BOTLINE + 1, 0, PAGE);
        printf("Please enter name for save file: ");
        scanf("%s", filename);
        if ((save = fopen(filename, "wb")) == NULL)
            {
            fprintf(stderr, "Can't open %s\n", filename);
            exit(1);
            }
        for (offset = 0; offset < CHARS; offset++)
            {
            char_attr = screen[offset];
            fwrite(&char_attr, 2, 1, save);
            }
        fclose(save);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-12.  The Save_screen()< function.

    In general, screen + offset points to the character-attribute offset
    positions from the beginning of video RAM. The value of that pair is
    *(screen + offset), which can also be written as screen[offset].

    The standard I/O function fwrite() copies the contents of screen memory
    one character-attribute pair at a time. This function takes four
    arguments: a pointer to a memory location, the number of bytes per display
    unit (here 2), the number of units to be copied, and a file stream
    pointer. The program first copies the video pair to char_attr because, in
    the default medium memory model used by QuickC, fwrite() expects a near
    pointer. In the large memory model, you could replace the for loop with
    the following code:

    fwrite(screen, 2, CHARS, save);  /* large model */

    Thus, in the large memory model, fwrite() uses a far pointer and can
    access video RAM directly. By specifying CHARS units to be copied by the
    function, you can dispense with the loop.

    Recovering the Screen

    To recover the stored screen, we need to reverse the storage process. That
    is, the program should open the file in the read mode. The
    attribute-character pairs found there should then be copied into the video
    memory, a natural task for DMA. From these basic techniques we develop the
    RECALL.C program (Listing 14-13). (To run the program, be sure that
    Screen Swapping On is active.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* recall.c -- displays previously stored screen,     */
    /*             including attributes.  Uses DMA.       */
    /* Program list: recall.c, scrfun.lib                 */
    /* User include files: scrn.h, grafchar.h             */
    /* Note: activate Screen Swapping On in Debug menu      */

    #include <stdio.h>
    #include <conio.h>
    #include "scrn.h"
    #include "grafchar.h"

    main(ac, ar)
    int ac;
    char *ar[];
    {
        unsigned char mode;
        unsigned short char_attr;
        FILE *save;
        unsigned int offset;
        char filename[81];
        VIDMEM screen;

        if (ac < 2)
            {
            fprintf(stderr, "Usage: %s filename\n", ar[0]);
            exit(1);
            }

        if ((save = fopen(ar[1], "rb")) == NULL)
            {
            fprintf(stderr, "Can't open %s\n", ar[1]);
            exit(1);
            }

        if ((mode = Getvmode()) == TEXTMONO)
            screen = MONMEM;
        else if (mode == TEXTC80 || mode == TEXTBW80)
            screen = CGAMEM;
        else
            exit(1);

        Clearscr();
        for (offset = 0; offset < CHARS; offset++)
            {
            fread(&char_attr, 2, 1, save);
            screen[offset] = char_attr;
            }
        fclose(save);
        Setcurs(23, 0, PAGE);
        getch();   /* anti-scrolling for QC environment */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-13.  The RECALL.C program.

    In the program, fread() recovers from the files what fwrite() placed into
    them. The Setcurs() call positions the MS-DOS prompt outside the drawing
    area when the program ends. The getch() call simply requires the user to
    press a key to terminate the program. Without this code, when you run the
    program in the QuickC environment, the QuickC prompt causes the screen to
    scroll up when the program ends. It still causes scrolling with this
    program, but not until you press a key.


Paging

    Now let's turn to a text topic that lies beyond the scope of the
    Monochrome Display Adapterâ”€â”€ paging. The CGA, EGA, and VGA have enough
    memory to store more than one screenful, or page, of text. The 16 KB video
    memory of the CGA, for example, can hold four text pages. The BIOS
    supports the use of pages by providing routines for setting the page and
    for determining the current page number. Many other BIOS routines require
    page information. The SCRFUN.C file we developed in Chapter 13 contains
    two page-related functionsâ”€â”€Getpage() and Setpage(), which are combined in
    Listing 14-14. As usual, the manifest constants are defined in scrn.h.

    Paging is very fast, even compared to DMA, because the video RAM doesn't
    need to be rewritten. The video controller simply changes the section of
    video memory that it reads. A typical application for paging stores a help
    screen on one page, while an application uses another page. This permits a
    rapid transition between the two screens without calling data from program
    memory or a disk file.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* Getpage() -- obtains the current video page */
    unsigned char Getpage()
    {
        union REGS reg;

        reg.h.ah = GETMODE;
        int86(VIDEO, &reg, &reg);
        return reg.h.bh;
    }
    /* Setpage() -- sets page to given value */
    void Setpage(page)
    unsigned char page;
    {
        union REGS reg;

        reg.h.ah = SETPAGE;
        reg.h.al = page;
        int86(VIDEO, &reg, &reg);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-14.  The Getpage() and Setpage() functions.

    Let's develop a basic program that can switch back and forth between page
    0 and a help screen on page 1. We could use BIOS calls to write the
    contents of the two screens, but direct memory access is faster. However,
    to use direct memory access, we need to supply the address of page 1.
    Because each page holds 2000 character-attribute pairs, or 4000 bytes, you
    might expect that page 1 is offset 4000 bytes from the beginning of video
    memory. But computers relate more to powers of 2 than to powers of 10, so
    the actual offset is 4096 bytes, 0x1000 in hex. (You can use the extra
    bytes between pages to color in page borders.)

    We use the VIDMEM type pointer again to point to video memory. Because we
    define it to point to a 2-byte unit (the character-attribute pair), the
    offset in VIDMEM units is 2048 pairs, which is 0x800 in hex.

    The HELP.C program (Listing 14-15) is fairly simple. (Be sure Screen
    Swapping On is active before you run it.) The key points to note are its
    use of Setpage() to change pages and its use of direct memory access to
    write to the screen. The program uses two direct memory access modules.
    The writechr.c module (Listing 14-16 on the following page) writes a
    character-attribute pair a specified number of times beginning at a
    specified memory location. The writestr.c module (Listing 14-17 on p.
    483) is similar, but it writes a string once instead of a single character
    repeatedly. By choosing the appropriate memory location, you can use these
    functions to write to either page, no matter which one is currently
    displayed. For convenience, we've collected definitions of the colors in a
    file called color.h (Listing 14-18 on p. 483).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  help.c -- uses paging and direct memory access    */
    /*            to display a help screen                */
    /*  Program list: help.c, writestr.c, writechr.c,     */
    /*                scrfun.lib                          */
    /*  User include files: scrn.h, color.h               */
    /*  Note: activate Screen Swapping On in Debug menu   */

    #include <stdio.h>
    #include <conio.h>
    #include "color.h"
    #include "scrn.h"
    typedef unsigned int (far * VIDMEM);
    #define CGAMEM ((VIDMEM) (0xB800L << 16))
    #define PAGESIZE 2000
    #define PAGEOFFSET 0x800L
    #define ESC '\033'
    #define ATTR1 (BG_BLUE | YELLOW)
    #define ATTR2 (BG_YELLOW | BLUE)
    #define ATTR3 (BG_RED | YELLOW | BLINK | INTENSE)
    #define CH1 (unsigned short) '\xB1'
    char *str1 = "Press ? key for help.";
    char *str2 = "Press Enter key to return.";
    char *str3 = "Press ESC key to quit.";
    char *str4 = "\xB1HELP!\xB1";
    void Write_chars(VIDMEM, unsigned short, unsigned
                        short, unsigned short);
    void Write_str(VIDMEM, unsigned short, char *);
    main()
    {
        int ch;
        unsigned char page = 0;
        unsigned char mode;

        mode = Getvmode();
        if (mode != TEXTC80 && mode != TEXTBW80)
            {
            printf("Only modes 2 and 3 supported. Bye.\n");
            exit(1);
            }
        Setpage(page);
        Write_chars(CGAMEM, '\0', ATTR2, PAGESIZE);
        Write_str(CGAMEM + 2 * COLS, ATTR1, str1);
        Write_str(CGAMEM + 2 * COLS, ATTR1, str1);
        Write_str(CGAMEM + 22 * COLS, ATTR1, str3);
        Write_chars(CGAMEM + PAGEOFFSET, '\0', ATTR1, PAGESIZE);
        Write_str(CGAMEM + PAGEOFFSET + 20 * COLS, ATTR2, str2);
        Write_str(CGAMEM + PAGEOFFSET + 22 * COLS, ATTR1, str3);
        Write_chars(CGAMEM + PAGEOFFSET + 10 * COLS + 36,
                    CH1, ATTR3, 7);
        Write_str(CGAMEM + PAGEOFFSET + 11 * COLS + 36,
                ATTR3, str4);
        Write_chars(CGAMEM + PAGEOFFSET + 12 * COLS + 36,
                    CH1, ATTR3, 7);

        while ((ch = getch()) != ESC)
            {
            if (ch == '?' && page == 0)
                Setpage(page = 1);
            else if (ch == '\r' && page == 1)
                Setpage(page = 0);
            }
        Write_chars(CGAMEM, '\0', NORMAL, PAGESIZE);
        Write_chars(CGAMEM + PAGEOFFSET, '\0', NORMAL, PAGESIZE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-15.  The HELP.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* writechr.c -- writes char and attribute repeatedly */
    /*               using DMA                            */
    /* write character ch with attribute attr num times   */
    /* starting at location pstart -- uses array notation */

    typedef unsigned int (far * VIDMEM);

    void Write_chars(pstart, ch, attr, num)
    VIDMEM pstart;
    unsigned short ch, attr, num;
    {
        register count;
        unsigned short pair;
        pair = (attr << 8) | (ch & 0x00FF) ;
        for (count = 0; count < num; count++)
            pstart[count] = pair;
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-16.  The writechr.c module.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  writestr.c -- writes string and attribute using DMA */
    /*  Write the string str with attribute attr at         */
    /*  location pstart -- uses pointer notation.           */

    typedef unsigned int (far * VIDMEM);

    void Write_str(pstart, attr, str)
    VIDMEM pstart;
    unsigned short attr;
    char *str;
    {
        while (*str != '\0')
            *pstart++ = (attr << 8) | (*str++ & 0x00FF);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-17.  The writestr.c module.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* color.h -- defines the color attributes  */
        /* foreground colors */
    #define  BLACK   0x0
    #define  BLUE    0x1
    #define  GREEN   0x2
    #define  RED     0x4
    #define  CYAN    0x3
    #define  MAGENTA 0x5
    #define  YELLOW  0x6
    #define  WHITE   0x7
        /* background colors */
    #define  BG_BLACK   0x00
    #define  BG_BLUE    0x10
    #define  BG_GREEN   0x20
    #define  BG_RED     0x40
    #define  BG_CYAN    0x30
    #define  BG_MAGENTA 0x50
    #define  BG_YELLOW  0x60
    #define  BG_WHITE   0x70
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-18.  The color.h include file.

    Most of the HELP.C program involves using the new Write_chars() and
    Write_str() functions, so let's examine them. The two functions are quite
    similar in behavior, but to illustrate different programming techniques,
    one uses array notation and the other uses pointer notation.

    Write_chars() starts by combining the attribute and character into a
    2-byte unit. It left-shifts the attribute into the high byte and places
    the character in the low byte. Next, the function performs a logical AND
    operation with the character and 0x00FF to limit the character to the
    range 0 through 0xFF, or 0 through 255. Next, a loop assigns the 2-byte
    pair to num consecutive locations in memory, beginning with the location
    pointed to by pstart. Recall that the notation pstart[count] is equivalent
    to *(pstart + count).

    In the program, Write_chars() clears the two pages, setting them to yellow
    and blue, respectively. To clear the screen, the program sets the
    character part of the byte to a null character; the attribute sets the
    color.

    The Write_str() function uses pointer notation to display a string. Like
    the preceding function, it combines the left-shifted attribute with a
    masked character value. In this case, str initially points to the first
    character in the string, so *str represents the value of that character.
    The while loop continues until it reaches the terminating null character
    of the string. During each cycle, the increment operator advances the
    video memory pointer and the string pointer after they are used.

    In the main program, note how we use addresses to specify locations on the
    screen. Consider, for example, the following statement:

    Write_str(CGAMEM + PAGEOFFSET + 11 * COLS + 36,
                ATTR3, str4);

    The address CGAMEM locates the beginning of the CGA (and EGA and VGA)
    memory. The PAGEOFFSET value is the offset to the beginning of the next
    page. Each line contains COLS characters, so the expression 11 * COLS is
    the offset to the beginning of line 11 (the twelfth line, because
    numbering starts with zero). Finally, the 36 gives the offset, or the
    indention measured in character widths, from the left side of the display.

    Note that the QuickC Graphics Library provides alternatives to many of our
    BIOS-based functions, including functions that clear the screen and set
    the page. However, using the Graphics Library produces final code
    noticeably larger than that of our examples. We use the Graphics Library
    only in graphics programs, in which its power and generality become
    evident.


Ports

    Any discussion of hardware-dependent programming methods must mention
    "ports," which are information conduits between the CPU and the other
    devices and processors in a PC. In general, each processor or device has
    one or more registers of its own. Values placed in these registers can
    control the operation of the processor or, perhaps, test its state of
    readiness. In the PC, various registers are assigned "port addresses" that
    are completely separate from the memory address system and are handled
    differently. The CPU accesses registers through ports by using special
    port instructions. (See Figure 14-9.)

    An 8086 CPU can address as many as 64,000 8-bit ports, but only a small
    fraction of that number (fewer than 200) are actually used. In assembly
    language, you access the ports with the instructions IN and OUT: IN reads
    a register; OUT writes to it. C does not contain these instructions, so
    QuickC supplies the non-ANSI inp() and outp() functions to serve the same
    purpose.

Reading Ports with inp()

    As mentioned in Chapter 13, the inp() and outp() functions are defined in
    conio.h. The following is the syntax for inp():

    #include <conio.h>

    int inp(port)
    unsigned port;    /* port number */

    This function reads the register at port number port, which can be a value
    in the range 0 through 65,535. It then returns the byte it reads. With
    write-only ports, inp() returns the value 255, or all bits set to 1.
    However, a return value of 255 does not always signal a write-only
    register because 255 is also a valid register setting.

                        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                        â”‚ Video controller  â”‚
                        â”‚    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”    â”‚
                        â”‚    â”‚register â”‚    â”‚
                        â””â”€â”€â”€â”€â”´â”€â”€â”€â”€â•¥â”€â”€â”€â”€â”´â”€â”€â”€â”€â”˜
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”                 â•‘
    â”‚         â”Œâ”€â”¤                 â•‘
    â”‚         â”‚ â”‚â—„â”€â”€Port 0x3B8    â•‘
    â”‚         â”‚ â•žâ•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•
    â”‚   CPU   â””â”€â”¤
    â”‚         â”Œâ”€â”¤
    â”‚         â”‚ â•žâ•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•—
    â”‚         â”‚ â”‚â—„â”€â”€Port 0x67     â•‘
    â”‚         â””â”€â”¤                 â•‘
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜                 â•‘
                        â”Œâ”€â”€â”€â”€â”¬â”€â”€â”€â”€â•¨â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”
                        â”‚    â”‚register â”‚    â”‚
                        â”‚    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜    â”‚
                        â”‚ Speaker controllerâ”‚
                        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 14-9. Ports and registers.

    The short PORTINFO.C program (Listing 14-19) lets you access and read
    various ports. Note that it uses the return value of scanf() to terminate
    the input loop. We prompt for hexadecimal port numbers because technical
    manuals usually list them in that form. Note that scanf() returns a value
    equal to the number of successful reads. Therefore, if it reads a hex
    value, it returns 1. If it finds input that is not hex, such as the letter
    q, scanf() returns 0, and the loop terminates.

    The following is a sample run:

    Enter number (in hex) of the port you wish to read: 3da
    Value returned for port 3da is 199 (decimal)  c6 (hex)
    Next port? (q to quit): 61
    Value returned for port 61 is 32 (decimal)  31 (hex)
    Next port? (q to quit): 42
    Value returned for port 42 is 174 (decimal)  60 (hex)
    Next port? (q to quit): 3b8
    Value returned for port 3b8 is 255 (decimal)  ff (hex)
    Next port? (q to quit): q

    You may get different values from those in this sample runâ”€â”€some of the
    registers change values as you use the computer.

    In the IBM PC and compatibles, the 0x3DA port reports status information
    about the MDA. Port 61 controls the speaker, and port 42 regulates the
    frequency of the 8253 timer chip. Finally, port 3B8 is the control port
    for the 6845 video controller on the MDA. (Because the last port is a
    write-only port, the reported value is not necessarily the true one.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* portinfo.c -- reads port values                    */
    /* program list -- portinfo.c (inp() not in core lib) */

    #include <conio.h>
    #include <stdio.h>
    main()
    {
        unsigned int portnum;
        int regvalue;

        printf("Enter number (in hex) of the port ");
        printf("you wish to read: ");
        while (scanf("%x", &portnum) == 1)
            {
        regvalue = inp(portnum);
        printf("\nValue returned for port %x is %d (decimal)"
                "  %x (hex)\n", portnum, regvalue, regvalue);
        printf("Next port? (q to quit): ");
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-19.  The PORTINFO.C program.

    As you can see, reading a register is a simple procedure. The difficult
    part is wading through the technical literature to see which port
    addresses correspond to which devices and to find out the meaning of the
    register settings.

Writing to a Port with outp()

    You write to a port with the outp() function by using the following
    syntax:

    #include <conio.h>

    int outp(port, value)
    unsigned port;             /* port number  */
    int value;                 /* output value */

    The function sends value to port number port. Although value is declared
    type int, you should use only numbers in the range 0 through 255. The
    function returns the same value it sends.

    Although it is easy to write to a port, you must do so with caution.
    Sending wrong values to some video controller registers, for example, can
    damage your monitor. Other ports can disable your keyboard, the system
    memory, the monitor, and so on. Do not use the experimental method when
    you write to ports! Before we write a sample program that uses port number
    0x3B8, the MDA control register, study the function of each bit in the
    register as described in Table 14-6.

    Let's write a short program that blanks the screen and then restores it.
    We can turn off the display by setting bit 3 to 0. Because this does not
    affect the video RAM, resetting bit 3 to 1 restores the display.

    Ideally, we would use inp() to read and save the current register setting.
    Then we could use that value to restore the original setting when we are
    done. However, 3B8 is a write-only register, so we must use Table 14-6 to
    select the proper setting.

    Table 14-6 Video Control Register Functions
    Bit         Function
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    0           If this bit is 0, no communication is permitted between the
                CPU and the video display memory. (This prevents data from
                being changed.) If this bit is 1 (the default value),
                communication between the CPU and the video display memory is
                enabled. (This lets the CPU read from and write to memory.)
                1, 2
                Not used.
    3           If this bit is 0, the display is disabled, which blanks the
                screen. The contents of video RAM, however, are unaffected. If
                this bit is 1 (the default value), the display is enabled, and
                data stored in video RAM is displayed.
    4           Not used.
    5           If this bit is 0, the blink attribute bit in video RAM
                controls the background intensity. If this bit is 1 (the
                default value), it controls blinking.
    6, 7        Not used.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Clearly, we originally want bit 0 to be 1. Normally, bits 3 and 5 should
    be 1, too. Because the other bits don't affect the port, we can set them
    to 0. This makes our default setting 00101001 in binary, or 0x29 in hex.
    To turn the display off, set bit 3 to 0, which changes the setting to 0010
    0001 in binary, or 0x21 in hex.

    The short BLANK.C program (Listing 14-20) demonstrates the results of our
    efforts.

    As we mentioned, the port approach is hardware-dependent. For example,
    changing the register number from 3B8 to 3D8 makes this program work with
    the CGA, but not with the EGA. By accessing the ports directly, you can
    make the video controllers do things that are impossible with BIOS calls
    alone. However, a new display adapter (and different port assignments) can
    render your program nonfunctional. Our BLANK.C program illustrates both
    these points.

    But sometimes you must use ports. For example, there are no BIOS calls
    that control the speaker; therefore, if you want to play a little tune,
    programming the port is the only method available.

Eliminating CGA Snow

    Let's examine another port example. The CGA can display "snow" when used
    with direct memory access. The problem arises from the interference caused
    when the CPU sends data to the video RAM at the same time that the CGA
    controller reads the RAM. (The other controllers don't have this problem.)
    The problem can be solved by not writing to the video RAM when the video
    controller is in the horizontal retrace mode. (The video display works by
    scanning an electron beam in horizontal lines across the screen. When the
    beam reaches the edge of the screen, it must be reset to the beginning of
    the next line. That resetting of the beam is called the horizontal
    retrace.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* blank.c -- blanks MDA screen                        */
    /* program list -- blank.c (outp() not in core lib)    */

    #include <conio.h>
    #define CONTROLREG 0x3B8 /* control register MDA */
    #define DEFAULTSET 0x29
    #define VIDEOOFF 0x21
    main()
    {
        outp(CONTROLREG, VIDEOOFF);
        getch();
        outp(CONTROLREG, DEFAULTSET);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-20.  The BLANK.C program.

    The CGA read-only 0x3DA port contains the controller status and reports
    when the video RAM can be written to without interfering with the display.
    When the video RAM can be accessed without interference, bit 0 is set to
    1. The code uses that information to limit access to the proper times:

    while ((inp (0x3DA) & 01) != 0)
        {;}  /* wait to end of current retrace */
    while ((inp (0x3DA) & 01) == 0)
        {;} /* wait for next retrace */
    /* put memory access code here */

    The second loop is obviousâ”€â”€it waits until bit 0 is 1 before accessing the
    video memory. The first loop prevents memory access from starting part way
    through a horizontal retrace. Suppose, for example, a retrace is 90%
    complete. Without the first loop, the program skips the second loop
    because bit 0 currently would be 1. However, that leaves only 10% of the
    retrace time to perform all the memory access, and that might not be
    enough time.


The EGA and VGA

    The normal text modes for the EGA and VGA systems are modes 3 and 4, which
    emulate the CGA 80-by-25 B/W and Color text modes. (Both systems also
    support mode 7 so that they can be used with a monochrome monitor.) All
    the applications we've discussed so far, aside from the port example, work
    with the EGA and VGA. These video controllers, however, have additional
    text capabilities that you might want to exploit.

    Normally, when used with a high-resolution monitor, the EGA and VGA use
    more pixels per character than the CGA to achieve better-looking text.
    However, these controllers also can produce smaller characters by using
    the CGA 8-by-8 character grid instead of the normal 8-by-14 (EGA) or
    9-by-16 (VGA) grid. This lets us generate a 43-line screen with the EGA
    and a 50-line screen with the VGA. For simplicity, we'll use the term
    "extended-line" to describe either.

    The EGA and VGA handle fonts differently than the MDA and CGA. The EGA and
    VGA store some standard fonts in ROM, much like the CGA and MDA. However,
    rather than scanning the ROM directly to get font information, the EGA and
    VGA first copy the fonts to a video RAM area beginning at memory location
    0xA0000. Then they scan the RAM for font information. Thus, you can use
    BIOS calls to select a font, or you can even load a font of your own
    design. To access the extended-line mode, you must load the 8-by-8 font
    instead of the default (8-by-14 or 9-by-16) font.

    To produce the extended-line display, you must reset several video
    controller registers. (New BIOS routines that come with these controllers
    simplify the process.) The LINES43.C program (Listing 14-21 on the
    following page) sets up the extended-line mode. If ANSI.SYS is running,
    this program will not work properlyâ”€â”€it displays the small characters, but
    it limits the display to 25 lines.

    The program first sets the usual text mode. Next, it calls a new routine
    added to the EGA and VGA versions of interrupt 0x10. Routine 0x11, labeled
    CHAR_GEN in our program, specifies the character font to be used. Setting
    register AL to 0x12 selects the 8-by-8-pixel character set stored in the
    video ROM and resets the register settings to display 43 (or 50) lines.

    Why did the program set a block to 0? The EGA and VGA can simultaneously
    store as many as four fonts. Block 0 refers to the first font, block 1 to
    the second, and so on. Because block 0 is used unless you explicitly
    switch to another, we copied the font to that block.

    For this program, use the Run menu to select the .exe compilation. You
    must leave QuickC to run the program because it has no effect in the
    QuickC environment. Use the MS-DOS MODE CO80 command to restore the usual
    mode.

    What happens if you set the extended-line mode and then run another
    program? Some programs reset the mode and undo the change. Some display
    the small characters but assume that only 25 lines can be displayed. Some,
    like QuickC, check to see the number of lines in use and display the full
    43 (or 50) lines.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* lines43.c -- leaves EGA in 43-line mode */

    #include <dos.h>
    #include <conio.h>
    #define VIDEO 0x10
    #define SETVMODE 0
    #define CHAR_GEN 0x11   /* an EGA BIOS function number */
    #define ROM8X8   0x12
    #define BLOCK 0
    #define TEXTC80 3

    main()
    {
        union REGS reg;

        reg.h.ah = SETVMODE;    /* set text mode */
        reg.h.al = TEXTC80;
        int86(VIDEO, &reg, &reg);

        reg.h.ah = CHAR_GEN;   /* char generator routine */
        reg.h.al = ROM8X8;  /* use 8x8 ROM character box */
        reg.h.bl = BLOCK;   /* copy to block 0 */
        int86(VIDEO, &reg, &reg);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 14-21.  The LINES43.C program.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€