Chapter 15  Graphics and QuickC

    Generating computer graphics is one of the PC's most spectacular uses. All
    the video controllers listed in the preceding chaptersâ”€â”€except the MDAâ”€â”€
    offer graphics modes that permit pixel-by-pixel control of the entire
    screen, enabling you to create figures and patterns and to set colors for
    individual pixels. The quality of graphics (and graphics programming in
    general) is hardware-dependent. The CGA, EGA, and VGA offer various
    graphics modes that are not compatible with one another. Fortunately,
    QuickC's extensive Graphics Library substantially simplifies graphics
    programming. We devote most of this chapter to exploring this library.


The Graphics Modes

    First, let's review the available graphics modes. All of these modes are
    dependent on specific video controllers and displays. Table 15-1 on the
    following page shows which modes are available to various hardware
    systems.

    Table 15-1 Graphics Modes
    Mode      Adapters     Displays           Resolution   Colors per   Palette
                                                            Palette
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    4         CGA, EGA,    B/Wâ˜¼ , CDâ˜¼ , EDâ˜¼ , 320 x 200    4            2
            VGA          VDâ˜¼
    5       CGA, EGA, CDâ˜¼ , EDâ˜¼ ,    320 x 200 4          1           4 gray
            VGA       VDâ˜¼
    6       CGA, EGA, B/Wâ˜¼ , CDâ˜¼ ,   640 x 200 2          1           2 B/Wâ˜¼
            VGA       EDâ˜¼ , VDâ˜¼
    13      EGA, VGA  CDâ˜¼ , EDâ˜¼ ,    320 x 200 16         User-       16
                    VDâ˜¼                                 definable
    14      EGA, VGA  EDâ˜¼ , VDâ˜¼      640 x 200 16         User-       16
                                                        definable
    15      EGA, VGA  MDâ˜¼            650 x 350 2          1           2 B/Wâ˜¼
    16      EGA, VGA  EDâ˜¼ , VDâ˜¼      640 x 350 4/16       User-       16/64
                                                        definable
    17      VGA       VDâ˜¼            640 x 480 2          User-       262,144
                                                        definable
    18      VGA       VDâ˜¼            640 x 480 16         User-       262,144
                                                        definable
    19      VGA       VDâ˜¼            320 x 200 256        User-       262,144
                                                        definable
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Notes: For the EGA and VGA, mode 5 is the same as mode 4.
            For mode 16, the number of colors available to the EGA depends on
            the size of EGA memory. The lower figure is for 64 KB of memory;
            the higher figure is for 128 KB or more of EGA memory.
            To use any of these graphics modes from within a program, specify
            the mode with a BIOS call or with one of the Graphics Library
            functions.

Modes and BIOS

    In Chapter 14 we used the BIOS-based Getvmode() function from our
    SCRFUN.LIB library to obtain the current video mode. That library also
    provides the Setvmode() function shown in Listing 15-1.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* Setvmode() -- sets video mode to given mode */
    #include <dos.h>
    #include "scrn.h"
    void Setvmode(mode)
    unsigned char mode;
    {
        union REGS reg;

        reg.h.ah = SETMODE;
        reg.h.al = mode;
        int86(VIDEO, &reg, &reg);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-1.  The Setvmode() function.

    You use this function to set mode 4, for example, with the following
    program lines:

    if (Getvmode() != 7)  /* not the monochrome */
        Setvmode(4);
    else
        {
        printf("Monochrome monitor does not use mode 4.\n");
        exit(1);
        }

    The Graphics Library routines, however, simplify and enhance this
    procedure.

Modes and the Graphics Library

    The QuickC Graphics Library contains functions specifically designed to
    handle the display interface and resides in the library file GRAPHICS.LIB
    and in the QuickC library file GRAPHICS.QLB. The graphics routines are not
    part of the standard QuickC core library. However, they are easy to
    access. First, you can use a program list containing the name of your
    program's file. This causes QuickC to use its linker, which accesses the
    whole library, including GRAPHICS.LIB. Or you can place the graphics
    routines in QuickC's in-memory library by using the /l option:

    qc /l graphics.qlb

    The second method produces faster compilation, and we assume that you use
    it. However, if your computer doesn't have enough memory to follow that
    method, you can use a program list instead.

    To use the graphics functions, you must include the header file graph.h.
    The following sections describe some of its mode-related functions.

    The _setvideomode() Function

    This more sophisticated version of our Setvmode() function takes as an
    argument the number of the desired mode. The graph.h file (Listing 15-2
    on the following page) contains the list of manifest constants that you
    can use.

    The _setvideomode() function has a few important features that Setvmode()
    lacks. For one thing, it keeps track of the original video mode, which
    means that you can use the _DEFAULTMODE argument to restore that mode.
    Another feature of _setvideomode() is that it has a return value. If the
    function succeeds in setting the requested mode, it returns a nonzero
    value. If the function fails, it returns a zero. Using the return value,
    we can rewrite our DMA (Direct Video Memory Access) examples from Chapter
    14 so that they don't need to first obtain the current mode. The relevant
    code in those examples follows:

    if ((mode = Getvmode()) == TEXTMONO)
        screen = MONMEM;
    else if (mode == TEXTC80 || mode == TEXTBW80)
        screen = CGAMEM;
    else
        exit(1);

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*   Mode constants from graph.h  */
    /*   arguments to _setvideomode() */
    #define _DEFAULTMODE  -1
                        /* restore screen to original mode */
    #define _TEXTBW40      0  /* 40 x 25 text, 16-gray */
    #define _TEXTC40       1  /* 40 x 25 text, 16/8-color */
    #define _TEXTBW80      2  /* 80 x 25 text, 16-gray */
    #define _TEXTC80       3  /* 80 x 25 text, 16/8-color */
    #define _MRES4COLOR    4  /* 320 x 200, 4-color */
    #define _MRESNOCOLOR   5  /* 320 x 200, 4-gray */
    #define _HRESBW        6  /* 640 x 200, B/W */
    #define _TEXTMONO      7  /* 80 x 25 text, B/W */
    #define _MRES16COLOR  13  /* 320 x 200, 16-color */
    #define _HRES16COLOR  14  /* 640 x 200, 16-color */
    #define _ERESNOCOLOR  15  /* 640 x 350, B/W */
    #define _ERESCOLOR    16  /* 640 x 350, 4- or 16-color */
    #define _VRES2COLOR   17  /* 640 x 480, 2-color */
    #define _VRES16COLOR  18  /* 640 x 480, 16-color */
    #define _MRES256COLOR 19  /* 320 x 200, 256-color */
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-2.  Mode constants from graph.h.

    After we add the #include <graph.h> line to the program, we can replace
    the preceding code with the following:

    if (_setvideomode(_TEXTMONO))
        screen = MONMEM;
    else if (_setvideomode(_TEXTC80) || _setvideomode(_TEXTBW80))
        screen = CGAMEM;
    else
        exit(1);

    This program attempts to set the MDA mode. If it succeeds, it sets the
    video display pointer to the MDA value. If it fails to set the MDA mode,
    it attempts to set either the CGA color 80-by-25 mode or the B/W
    equivalent. If either of those attempts succeeds, it sets the video
    display pointer to the CGA value. If none of these attempts succeed, the
    program exits. Note the way the second if works. If _setvideomode()
    succeeds in setting the _TEXTC80 mode, the function returns a true value.
    Because the first part of the logical OR expression is true, the whole
    expression is true, and thus the second half of the expression need not be
    evaluated.

    The _getvideoconfig() Function

    The Graphics Library also lets us retrieve a variety of information about
    the current mode. The _getvideoconfig() function fills a structure called
    videoconfig with mode-related information. The function is defined in the
    graph.h file, as shown in Listing 15-3. The listing also shows the
    defined constants that you can use with the videoconfig structure.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* video configuration information from graph.h  */
    struct videoconfig {
        short numxpixels;    /* number of pixels on X axis */
        short numypixels;    /* number of pixels on Y axis */
        short numtextcols;   /* number of text columns available */
        short numtextrows;   /* number of text rows available */
        short numcolors;     /* number of actual colors */
        short bitsperpixel;  /* number of bits per pixel */
        short numvideopages; /* number of available video pages */
        short mode;          /* current video mode */
        short adapter;       /* active display adapter */
        short monitor;       /* active display monitor */
        short memory;        /* adapter video memory in K bytes */
    };

    /* videoconfig adapter values */
    /* These manifest constants can be used to test adapter     */
    /* values for a particular adapter using the bitwise AND    */
    /* operator (&). */
    #define _MDPA   0x0001 /* Monochrome Display Adapter (MDPA) */
    #define _CGA    0x0002 /* Color Graphics Adapter     (CGA)  */
    #define _EGA    0x0004 /* Enhanced Graphics Adapter  (EGA)  */
    #define _MCGA   0x0008 /* Multi-Color Graphics Array (MCGA) */
    #define _VGA     0x0010 /* Video Graphics Array      (VGA)  */

    /* videoconfig monitor values */
    /* These manifest constants can be used to test monitor     */
    /* values for a particular monitor using the bitwise AND    */
    /* operator (&). */
    #define _MONO     0x0001  /* Monochrome                     */
    #define _COLOR    0x0002  /* Color (or Enhanced emulating   */
                            /* color)                         */
    #define _ENHCOLOR 0x0004  /* Enhanced Color                 */
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-3.  Video configuration information from graph.h.

    When you pass the _setvideomode() function the address of a struct
    videoconfig structure, the function fills the structure with the indicated
    data. The MODEINFO.C program (Listing 15-4 on the following pages) cycles
    through the modes supported by QuickC and displays the mode-related
    information. When the program ends, the _setvideomode(_DEFAULTMODE)
    function call restores the original mode setting.

    Notice in the output of MODEINFO.C that the _getvideoconfig() function
    returns 32 for the number of colors available in all text modes, including
    monochrome. This value indicates the range of values accepted by the
    _settextcolor() function, not necessarily the number of unique color
    options.

    Because the actual mode values do not form a set of consecutive integers,
    the program holds the values in an array. However, the array indexes are
    consecutive, so they can be used in a loop.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* modeinfo.c -- sets modes and obtains information    */
    /* Demonstrates _setvideomode() and _getvideoconfig()  */
    /* If you load graphics.qlb, no program list is needed.*/

    #include <conio.h>
    #include <graph.h>
    struct videoconfig vc;
    int modes[15] ={_TEXTBW40, _TEXTC40, _TEXTBW80, _TEXTC80,
            _MRES4COLOR, _MRESNOCOLOR, _HRESBW, _TEXTMONO,
            _MRES16COLOR, _HRES16COLOR, _ERESNOCOLOR, _ERESCOLOR,
            _VRES2COLOR, _VRES16COLOR, _MRES256COLOR};
    char *Adapt(short), *Display(short);
    main()
    {
        int i;

        for (i = 0; i < 15; i++)
            {
            if (_setvideomode(modes[i]))
                {
                _getvideoconfig(&vc);
                printf("video mode is %d\n", vc.mode);
                printf("number of columns is %d\n", vc.numtextcols);
                printf("number of colors is %d\n", vc.numcolors);
                printf("number of pages is %d\n", vc.numvideopages);
                printf("adapter is %s\n", Adapt(vc.adapter));
                printf("display is %s\n", Display(vc.monitor));
                printf("the adapter has %dK of memory\n",
                        vc.memory);
                }
            else
                printf("mode %d not supported\n", modes[i]);
            printf("press a key for next mode\n");
            getch();
            }
        _setvideomode(_DEFAULTMODE);
    }

    /* Adapt() returns a pointer to a string describing   */
    /* the adapter characterized by adapt_num.            */
    char *Adapt(adapt_num)
    short adapt_num; /* videoconfig.adapter value         */
    {
        static char *anames[6] = {"Monochrome", "CGA", "EGA",
                                "MCGA", "VGA", "Not known"};
        char *point;

        switch (adapt_num)
            {
            case _MDPA : point = anames[0];
                        break;
            case _CGA  : point = anames[1];
                        break;
            case _EGA  : point = anames[2];
                        break;
            case _MCGA : point = anames[3];
                        break;
            case _VGA  : point = anames[4];
                        break;
            default    : point = anames[5];
            }
        return point;
    }

    /* Display() returns a pointer to a string describing  */
    /* the monitor characterized by disp.                  */
    char *Display(disp)
    short disp;  /* videoconfig.monitor value              */
    {
        static char *types[5] = {"monochrome", "color",
                                "enhanced color", "analog",
                                "unknown"};
        char *point;

        if (disp & _MONO)
            point = types[0];
        else if (disp & _COLOR)
            point = types[1];
        else if (disp & _ENHCOLOR)
            point = types[2];
        else if (disp & _ANALOG)
            point = types[3];
        else
            point = types[4];
        return point;
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-4.  The MODEINFO.C program.

    The Adapt() function uses a switch statement to select the string that
    corresponds to the adapter value returned by _getvideoconfig(). The
    Display() function uses the manifest constants defined in graph.h and
    logical AND testing to identify the monitor. The returned values, being
    powers of 2, are such that mode & _MONO is zero (false) unless mode is
    _MONO and so on.


CGA Graphics

    We now have the tools to select a mode. The first mode we will explore is
    mode 4 (_MRES4COLOR) because all the graphics video controllers support
    it. This is the medium-resolution CGA mode.

    Because the graphics modes allow each screen pixel to be set individually,
    they require more video memory than do the text modes. The exact amount of
    memory, however, depends on how much information is needed to describe
    each pixel. For example, a black-and-white mode requires only one bit per
    pixel because the two possible values of the bit (0 and 1) are enough to
    describe the two possible values for the pixel (off and on). With color
    modes, the amount of memory needed depends on the number of colors
    available to each pixel. With a fixed amount of memory, using more bits
    per pixel increases the color options but decreases the total number of
    pixels that can be mapped. The CGA 320-by-200 four-color mode
    (_MRES4COLOR) offers a compromise between resolution and color variety by
    restricting the display to four colors at a time.

The Graphics Palette and Background

    The CGA four-color mode represents each pixel with two bits of memory.
    This unit of memory can be set to a number in the range 0 through 3, thus
    providing a choice of four colors. Color 0 represents the background
    color, and the other three colors constitute the "palette." The background
    color and the palette are set in separate operations.

    You can set the background color to any one of 16 values, numbers 0
    through 15. The values 0 through 7 are the text foreground choices we
    previously listed in the color.h file (Listing 14-18 on p. 483). The
    values 8 through 15 are the intensified versions of these same colors.
    Note that the graphics background choice applies to the entire screen; the
    text background applies only to a particular character box. Thus, in the
    graphics mode, only one background choice can be in effect at a time.

    In CGA four-color mode, you can choose one of only two palettes, which are
    described in Table 15-2. Suppose you set the palette to 0 and the
    background to blue. When you set a bit pair in the video memory to 0, the
    corresponding pixel is set to blue. Setting the bit pair to 1, 2, or 3
    produces the colors green, red, and dark yellow, respectively. Setting the
    video mode clears the display because it sets all the video display bits
    to 0. Thus, initially, the entire screen is the background color.

    Now suppose you create a pattern on the screen. If you select a different
    background color, the background for the entire screen changes, but the
    video display memory remains unchanged. Changing the background color
    essentially tells the controller how to interpret a zero value in the
    video memory. Similarly, changing the palette actually tells the
    controller how to interpret values of 1, 2, or 3 in the video memory.

    Table 15-2 Mode 4 Palette Choices
    Palette            Color 1           Color 2            Color 3
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    0                  Green             Red                Dark yellow
    1                  Cyan              Magenta            Light gray
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

The QuickC Graphics Library

    Creating a graphics image requires several steps. First, set a graphics
    mode such as _MRES4COLOR. Then select a background color and a palette.
    Finally, set the appropriate bits in the video memory to the required
    values. To perform these tasks, you can use the BIOS video I/O routines or
    the QuickC Graphics Library functions, or you can directly access the
    video display memory and the controller registers. We will use the
    Graphics Library routines, but first let's briefly outline the other
    approaches.

    The BIOS provides modest support for the graphics mode. It includes
    interrupt routines for selecting a background color and a palette. Other
    routines read a pixel from the screen, write a pixel to the screen, and
    generate text. After that, you are on your own. To draw a line, you first
    must figure out which pixels to turn on; then you must turn them on
    individually. The BIOS routines are also quite slow. The write-pixel
    routine, for example, takes a long time to fill a square.

    On the other hand, the direct memory access approach is extremely fast.
    But the programming is difficult. First, because each byte of memory
    represents four separate pixels, you must use bitwise manipulations to
    alter only one of those pixels. Second, the CGA stores the bit pairs for
    the odd-numbered rows in a different section of memory than the
    even-numbered rows. To fill a solid figure on the screen, you must jump
    back and forth in the video display memory.

    The Graphics Library overcomes the difficulties of the other two
    programming methods. Its drawing routines are much faster than the BIOS
    routines because they use direct memory access. The library functions are
    conveniently oriented toward end results, not internal representations.
    For example, the library provides functions to draw boxes and circles, and
    the functions describe the screen in terms of screen position, not in
    terms of memory location. Also, the library simplifies creating programs
    that work in more than one graphics mode. The EGA and VGA graphics modes,
    for example, use a different memory location (0xA0000) and different
    schemes for representing pixels and colors; the library makes those
    differences invisible to the user. The main drawback in using the Graphics
    Library is the size it adds to a program. However, in our opinion, the
    speed, convenience, power, and monitor-compatibility of the library
    approach easily outweigh that factor for writing graphics programs.

Choosing in Modes

    Let's explore the rudiments of graphics programming by creating a program
    that turns on a few pixels. Although we use the CGA medium-resolution mode
    4, you might want to try the program in another mode. To make that easy to
    do, we use the following code (on the next page) with most of our
    examples.

    #include <stdlib.h>
    main (argc, argv)
    int argc;
    char *argv[];
    {
        int mode = _MRES4COLOR;
        int ch;

        if (argc > 1)
            mode = atoi(argv[1]);

        if (_setvideomode(mode) == 0)
            {
            printf("Can't do mode %d.\n", mode);
            exit(1);
            }

    This code fragment sets the mode to _MRES4COLOR by default. However, if
    you use a command-line argument (argc > 1), mode is set to that argument.
    The function atoi(), which is declared in STDLIB.C, converts the argument
    from a string to a numeric value. To select a mode by this method, display
    the Runtime Options dialog box before running the program and then enter
    the desired mode number in the command-line window. For example, entering
    16 causes the program to set mode 16 (_ERESCOLOR).

    One convenient feature of the Graphics Library is that the same function
    calls work for all modes. Although different modes might require different
    argument values because the screen has more or fewer pixels, you can use
    _getvideoconfig() information to scale argument values accordingly. That
    is the approach we use.

    Setting the mode also clears the screen, so you don't need to clear it
    explicitly. (When you do need to clear the screen, the Graphics Library
    provides a _clearscreen() function.)

Color Basics

    Use the _selectpalette() function to choose a palette. This function takes
    the palette number as its argument and returns the former palette value.
    The Graphics Library supplements the two palettes provided by the BIOS
    with intensified versions of each. (See Table 15-3.) In all cases, color
    0 is the current background color.

    Table 15-3 Palette Values for _selectpalette()
    Palette            Color 1           Color 2            Color 3
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    0                  Green             Red                Dark yellow
    1                  Cyan              Magenta            Light gray
    2                  Light green       Light red          Yellow
    3                  Light cyan        Light magenta      White
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    To select a particular color from a palette, use _setcolor(). For example,
    if palette 0 is in effect, _setcolor(2) sets the color to red. (This
    function interprets color values differently in the EGA and VGA modes, as
    we'll see later.) When you call a drawing function from the Graphics
    Library, it draws with the currently defined color.

    The Graphics Library function for setting the background color is
    _setbkcolor(). It takes a long color value as an argument and returns the
    color value of the background in effect when the function is called. The
    numeric value of the argument depends on whether you use _setbkcolor() in
    a text mode or in a graphics mode. This complication arises from the need
    to make the function compatible with the VGA graphics modes. Table 15-4
    lists the color values and the manifest constant names defined in graph.h.

    The graphics color values are not consecutive values. Therefore, it is
    often convenient to initialize an array to the values so they can be
    accessed consecutively with an array index. The DOTS.C program (on p.
    503) demonstrates this procedure.

    Table 15-4 Background Color Values
    Color               Text Color    Graphics Color   Manifest Constant
                        Value (dec)   Value (hex)
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Black                0L           0x000000L        _BLACK
    Blue                 1L           0x2A0000L        _BLUE
    Green                2L           0x002A00L        _GREEN
    Cyan                 3L           0x2A2A00L        _CYAN
    Red                  4L           0x00002AL        _RED
    Magenta              5L           0x2A002AL        _MAGENTA
    Dark yellow (brown)  6L           0x00152AL        _BROWN
    White (light gray)   7L           0x2A2A2AL        _WHITE
    Dark gray            8L           0x151515L        _GRAY
    Light blue           9L           0x3F1515L        _LIGHTBLUE
    Light green         10L           0x153F15L        _LIGHTGREEN
    Light cyan          11L           0x3F3F15L        _LIGHTCYAN
    Light red           12L           0x15153FL        _LIGHTRED
    Light magenta       13L           0x3F153FL        _LIGHTMAGENTA
    Light yellow        14L           0x153F3FL        _LIGHTYELLOW
    Bright white        15L           0x3F3F3FL        _LIGHTWHITE
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Physical Coordinates

    The library drawing functions use coordinates to determine the location
    images on the screen. Functions in the library use two forms of
    coordinates: physical coordinates and logical coordinates. Physical
    coordinates use the upper-left corner of the screen as their origin;
    logical coordinates let you select the origin. Most of the drawing
    functions use the logical coordinates. However, by default, the logical
    coordinates are the same as the physical coordinates, so let's discuss
    physical coordinates first.

    Both systems measure distances in pixels. The physical coordinate system
    uses the upper-left corner as the origin, that is, as the point whose
    coordinates are (0, 0). The column number, or x value, is listed first,
    and the row number, or y value, is listed second. The column values
    increase to the right, and the row values increase downward. Thus, for a
    320-by-200 mode, the physical coordinates of the lower-right corner are
    (319, 199). Remember that numbering starts with 0, so column 319 is the
    320th column. (See Figure 15-1.)

    A Simple Example

    Let's write a small program that uses the _setpixel() function. This
    function takes two argumentsâ”€â”€the horizontal and vertical location of a
    pixelâ”€â”€then sets that pixel to the color last set by _setcolor(). Our
    program uses the default logical coordinate system, whose origin is at the
    upper-left corner of the screen. If coordinates fall outside the drawing
    region, the function returns a value of -1.

    The DOTS.C program (Listing 15-5) uses nested loops to draw a rectangular
    pattern of pixels. Recall that you can override the default mode
    (_MRES4COLOR) with a command-line argument. After the program draws a
    pattern, you can press p to change the palette and press b to change the
    background. Each keystroke increments the palette or background number by
    one. (Palette changing works only in the CGA modes.) Remember that you
    must either use the \l option to load the GRAPHICS.QLB library into memory
    or else use a program list to access it. To exit the program, press the
    Esc key.

    â”Œâ”€â”€Origin at upper-left corner (x = 0, y = 0)
    â”‚
    â”‚
    â”‚      â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â””â”€â”€â”€â”€â”€â”€â”¼â–ºâ–’â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–º                                â”‚
            â”‚ â”‚  x pixels   |                                â”‚
            â”‚ â”‚             |                                â”‚
            â”‚ â”‚y pixels     |                                â”‚
            â”‚ â”‚             |                                â”‚
            â”‚ â–¼-------------â–“â—„â”€â”€â”€â”€pixel                      â”‚
            â”‚                                                â”‚
            â”‚                                                â”‚
            â”‚                                                â”‚
            â”‚                                                â”‚
            â”‚                                                â”‚
            â”‚                                                â”‚
            â”‚                                                â”‚
            â”‚                                                â”‚
            â”‚                                                â”‚
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-1. Locating a pixel using physical coordinates.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* dots.c -- illustrates the _setcolor(), _setpixel(), */
    /*           and _selectpalette() functions from the   */
    /*           QuickC Graphics Library                   */
    /* If you load graphics.qlb, no program list is needed.*/

    #include <conio.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <graph.h>
    #define ESC '\033'
    #define BKCOLS 8      /* number of background colors */
    #define PALNUM 4      /* number of palettes */
    long Bkcolors[BKCOLS] = {_BLACK, _BLUE, _GREEN, _CYAN, _RED,
                            _MAGENTA, _BROWN, _WHITE};
    main(argc, argv)
    int argc;
    char *argv[];
    {
        struct videoconfig vc;
        unsigned int col, row;
        short color = 0;
        int bkc_index = 1;  /* blue background */
        short palette = 0;  /* red, green, brown */
        int firstcol, firstrow, lastrow, lastcol;
        int mode = _MRES4COLOR;
        int ch;

        if (argc > 1)
            mode = atoi(argv[1]);

        if (_setvideomode(mode) == 0)
            {
            printf("Can't do that mode.\n");
            exit(1);
            }
        _getvideoconfig(&vc);
        firstcol = vc.numxpixels / 5;
        firstrow = vc.numypixels / 5;
        lastcol = 4 * vc.numxpixels / 5;
        lastrow = 4 * vc.numypixels / 5;
        _selectpalette(palette);
        _setbkcolor(Bkcolors[bkc_index]);
        for (col = firstcol; col <= lastcol; ++col)
            {
            _setcolor((++color / 3) % vc.numcolors);
            for (row = firstrow; row <= lastrow; ++row)
                _setpixel(col, row);
            }
        while ((ch = getch()) != ESC)
            {
            if (ch == 'p')
                _selectpalette(++palette % PALNUM);
            else if (ch == 'b')
                _setbkcolor(Bkcolors[++bkc_index % BKCOLS]);
            }
        _setvideomode(_DEFAULTMODE);  /* reset orig. mode */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-5.  The DOTS.C program.

    Program Notes

    Drawing the pattern dot by dot is a slow process. But palette and
    background changes are practically instantaneous because they do not alter
    the video memory; they merely alter the interpretation of the bits already
    present.

    The Bkcolors[] array is initialized to the first eight background colors.
    Later, the program steps through these nonsequential background color
    values by incrementing the array index.

    The program uses mode-dependent information to draw the figure to scale.
    The _getvideoconfig() function obtains the number of pixels per row and
    column, and the program sizes the figure accordingly. The following code
    defines an area covering 60 percent of the rows and of the columns:

    firstcol = vc.numxpixels / 5;
    firstrow = vc.numypixels / 5;
    lastcol = 4 * vc.numxpixels / 5;
    lastrow = 4 * vc.numypixels / 5;

    Thus, in the 320-by-200 mode, the first column is 64 and the last column
    is 256, while in the 640-by-350 EGA mode, the first column is 128 and the
    last is 512.

    The following statement changes the current color value:

    _setcolor((++color / 3) % vc.numcolors);

    This increments color each time the program writes a new column. However,
    because integer division is truncated, the expression color / 3 increases
    only when color increases by 3. Thus, the columns change color every third
    column instead of every column. Unbounded incrementing causes color to
    exceed the valid range. Therefore, the code uses the modulus operator to
    produce a value in the range 0 through vc.numcolors - 1. For the
    _MRES4COLOR mode, where vc.numcolors is equal to 4, this range is 0
    through 3. (Using vc.numcolors makes the program more portable among
    different video modes.)

EGA and VGA Considerations

    Recall that the Runtime Options feature lets the program run in EGA and
    VGA modes. How does changing the mode affect the program? First, the row
    and column limits are set to reflect the new height and width of the
    screen in pixels. Second, the vc.numcolors value is reset to the new mode.
    The _MRES4COLOR mode sets a value of 4 in vc.numcolors; the _ERESCOLOR
    reports a value of 16 if sufficient EGA memory is available, and it
    reports a value of 4 otherwise.

    Those are the explicit provisions we made for other modes. In addition,
    some of the functions work differently. The _selectpalette() function, for
    example, is recognized only by the 320-by-200 four-color mode and the
    320-by-200 B/W mode; other color graphics modes ignore it because they
    don't use the simple CGA palette system. Instead, the EGA and VGA
    graphics-mode palettes contain more than four colors and also let you
    select the palette colors individually. The default palette for the
    EGA/VGA modes is essentially the same as the background colors shown in
    Table 15-4 on p. 501. (The EGA/VGA brown, however, is a different tint
    than the CGA brown.) The _setcolor() function uses the same numeric values
    as shown in the text color column of Table 15-4, except that it uses type
    short instead of type long.

Drawing Lines

    Two minor modifications to the DOTS.C program produce major changes in its
    operation. First, we can speed up the program noticeably by using the
    _lineto() function from the Graphics Library. This function takes a column
    coordinate and a row coordinate as arguments and draws a line from the
    current screen position to the specified position. The _moveto() function
    changes the current screen position to the column and row specified by its
    two arguments. This function lets you relocate your figurative drawing pen
    without drawing. It's easy to modify DOTS.C to use these functions instead
    of _setpixel(). First, use the MS-DOS COPY command or, within QuickC,
    choose Merge or Save As from the File menu to create a copy of DOTS.C.
    Then modify the copy by replacing the following lines:

    for (col = firstcol; col <= lastcol; ++col)
        {
        _setcolor((++color / 3) % vc.numcolors);
        for (row = firstrow; row <= lastrow; ++row)
            _setpixel(col, row);
        }

    with these lines:

    for (col = firstcol; col <= lastcol; ++col)
        {
        _setcolor((++color / 3) % vc.numcolors);
        _moveto(col, firstrow);   /* new and improved */
        _lineto(col, lastrow);    /* version          */
        }

    This replaces the inner for loop of DOTS.C with two library functions that
    make this version of the program approximately 10 times faster than the
    original.

A Beautiful Example

    If _lineto() draws so much faster than _setpixel(), why bother to use the
    latter function at all? One reason is that _setpixel() offers more
    detailed control. It lets you create involved and intriguing displays, as
    the next example shows.

    One way to create interesting patterns is to key the color of a pixel to
    the value of its coordinates. Make another copy of DOTS.C and name it
    MOIRE.C. Alter the lines

    for (col = firstcol; col <= lastcol; ++col)
        {
        _setcolor((++color / 3) % vc.numcolors);
        for (row = firstrow; row <= lastrow; ++row)
            _setpixel(col, row);
        }

    so that they read as follows:

    for (col = firstcol; col <= lastcol; ++col)
        {
        for (row = firstrow; row <= lastrow; ++row)
            {
            _setcolor(((row * row + col * col) / 10)
                        % vc.numcolors);
            _setpixel(col, row);
            }
        }

    Note that the _setcolor() function has a new argument and that it has been
    moved to the inner loop.

    This alteration produces a dramatic change in the displayâ”€â”€complex,
    interlocking patterns called "Moire patterns." The difference is even more
    impressive in the EGA and VGA modes because of their higher resolution and
    greater number of colors.

Logical Coordinates

    Many of the drawing functions, including the ones we've used, take logical
    coordinates rather than physical coordinates. By default, they are the
    same, so we haven't made a distinction between the two. However, the
    _setlogorg() function lets you select another point as the origin of the
    logical coordinate system. To use the function, pass it the physical
    coordinates of the new origin. For example, using the call _setlogorg(100,
    50) makes the point (100, 50) the new origin. Points to the left of the
    new origin now have negative row values, and points to the right are
    positive. Similarly, points above the new origin have negative row values,
    and points below have positive values. (See Figure 15-2.)

                â”Œâ”€â”€Origin set by _setlogorg()
                â”‚
                â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚            â”‚   â”‚Negative y                        â”‚
    â”‚            â”‚   â”‚                                  â”‚
    â”‚Negative x  â””â”€â”€â–ºâ”‚                   Positive x     â”‚
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–’â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚                â”‚  x pixels   |                    â”‚
    â”‚                â”‚             |                    â”‚
    â”‚                â”‚y pixels     |                    â”‚
    â”‚                â”‚             |                    â”‚
    â”‚                â–¼-------------â–“                    â”‚
    â”‚                â”‚                                  â”‚
    â”‚                â”‚                                  â”‚
    â”‚                â”‚Positive y                        â”‚
    â”‚                â”‚                                  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-2. Locating a pixel using logical coordinates.

    Using logical coordinates can simplify specifying locations. For example,
    the center of the screen is a common choice as the logical origin because
    the signs of the coordinates signal which quadrant of the screen a point
    is in.

Drawing Rectangles

    Now let's draw some rectangles. You could use _lineto(), but the Graphics
    Library contains a ready-made function for the task, _rectangle(). This
    function lets you do the following:

    â–   Specify whether the rectangle is drawn in outline or as a filled
        figure.

    â–   Specify the size and location of the rectangle.

    â–   Select a color.

    â–   Select a line-drawing style for outlined rectangles.

    â–   Select a fill pattern for filled rectangles.

    Function arguments determine the type, size, and location of the
    rectangle. The first argument specifies whether the rectangle is an
    outline or solid. The two values for this argument (from the graph.h file)
    are as follows:

    #define _GBORDER         2    /* draw outline only  */
    #define _GFILLINTERIOR   3    /* fill using current */
                                    /* fill mask          */

    Outlined figures are drawn using the current line style, which is, by
    default, a solid line. Likewise, filled figures use the current fill
    pattern ("fill mask"), which is, by default, a solid color.

    The remaining four arguments are the x and y logical coordinates of the
    upper-left corner of the rectangle and the x and y logical coordinates of
    the lower-right corner of the rectangle.

    The drawing color (outline or fill pattern) is the last value of
    _setcolor(). The _setlinestyle() function specifies the line style, and
    the _setfillmask() function specifies the fill pattern. The _rectangle()
    function uses the last value set by these two functions or, if they aren't
    used, it uses the default values.

    The RECT.C program (Listing 15-6) illustrates logical coordinates,
    _rectangle(), and _setlinestyle(). Figure 15-3 shows output from the
    program.

    Program Notes

    Using logical coordinates, you can easily center rectangles on the screen:
    Merely assign the upper-left corner the negative coordinates of the
    lower-right corner. This program generates a series of centered rectangles
    by repeatedly scaling down the dimensions. Specifying this sequence of
    rectangles in the physical coordinate system is a more tedious task
    because you have to calculate all the coordinates.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 15-3 can be found on p.508 of the printed version of the book.  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-3. Output of RECT.C.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  rect.c -- illustrates logical coordinates,         */
    /*            the _rectangle() and _setlinestyle()     */
    /*            functions                                */
    /* If you load graphics.qlb, no program list is needed.*/

    #include <stdio.h>
    #include <graph.h>
    #include <conio.h>
    #define STYLES 5
    short Linestyles[STYLES] = {0xFFFF, 0x8888, 0x7777,
                                0x00FF, 0x8787};
    main(argc, argv)
    int argc;
    char *argv[];
    {
        struct videoconfig vc;
        int mode = _MRES4COLOR;
        int xcent, ycent;
        int xsize, ysize;
        int i;

        if (argc > 1)
            mode = atoi(argv[1]);
        if (_setvideomode(mode) == 0)
            {
            printf("Can't open that mode.\n");
            exit(1);
            }
        _getvideoconfig(&vc);
        xcent = vc.numxpixels / 2 - 1;
        ycent = vc.numypixels / 2 - 1;
        _setlogorg(xcent, ycent);
        xsize = 0.9 * xcent;
        ysize = 0.9 * ycent;
        _selectpalette(1);
        _setcolor(3);
        _rectangle(_GBORDER, -xsize, -ysize, xsize, ysize);
        xsize *= 0.9;
        ysize *= 0.9;
        _setcolor(1);
        _rectangle(_GFILLINTERIOR, -xsize, -ysize, xsize, ysize);
        for (i = 0; i < 16; i++)
            {
            _setcolor(((i % 2) == 0) ? 2 : 3);
            _setlinestyle(Linestyles[i % 5]);
            xsize *= 0.9;
            ysize *= 0.9;
            _rectangle(_GBORDER, -xsize, -ysize, xsize, ysize);
            }
        getch();      /* Type a key to terminate. */
        _setvideomode(_DEFAULTMODE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-6.  The RECT.C program.

    The program draws the outer rectangle in outline and the next rectangle is
    solid. Then it draws a series of diminishing outline rectangles using a
    variety of line styles. The following statement:

    _setcolor(((i % 2) == 0) ? 2 : 3);

    chooses color 2 if the index i is even, and color 3 if the index is odd;
    this prevents the use of color 1, which would not appear against a
    background of the same color.

    Line Styles

    Now let's see how the rectangle-drawing loop cycles though a list of line
    styles.

    The _setlinestyle() function takes one argument, a 16-bit "mask." This
    mask is a template in which each bit represents a pixel in the line being
    drawn. If a bit is set to 1, the corresponding pixel is turned on when the
    line is drawn. The pixel is set to the background color if the bit is 0.
    This template covers only 16 pixels, but you can visualize it as being
    moved along the line 16 pixels at a time.

    The default line style is a solid line. That translates into a mask of
    sixteen 1s, or the hex value 0xFFFF. Now consider the following statement:

    _setlinestyle(0x0F0F);

    This function call creates a mask with the bit pattern 0000111100001111,
    which produces a pixel pattern of four pixels off, four pixels on, four
    off, four onâ”€â”€a dashed line. (See Figure 15-4.)

    In RECT.C, the linestyles array contains five line masks. The for loop
    near the end of the program cycles through these line styles as it draws a
    series of rectangles of decreasing size.

    Hex                Binary
            â”Œâ”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”¬â”€â”
    OxOFOF  â”‚0â”‚0â”‚0â”‚0â”‚1â”‚1â”‚1â”‚1â”‚0â”‚0â”‚0â”‚0â”‚1â”‚1â”‚1â”‚1â”‚
            â””â”€â”´â”€â”´â”€â”´â”€â”´â”€â”´â”€â”´â”€â”´â”€â”´â”€â”´â”€â”´â”€â”´â”€â”´â”€â”´â”€â”´â”€â”´â”€â”˜
                        â”‚               â”‚
                        â–¼               â–¼
                    â–’â–’â–’â–’â–’â–’â–’         â–’â–’â–’â–’â–’â–’â–’
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                        Line style

    Figure 15-4. A line style mask.

The _ellipse() Function

    The Graphics Library does not limit you to lines and rectangles. The
    _ellipse() function, for example, lets you draw ellipses. It takes the
    same argument list as _rectangle() and draws an ellipse that fits just
    inside the rectangular framework. The EGGS.C program (Listing 15-7)
    presents an example of this function and also illustrates what happens
    when solid figures overlap. (See Figure 15-5 on p. 512.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  eggs.c -- draws colorful eggs                                     */
    /*  This program illustrates use of the video configuration           */
    /*  structure, the _ellipse() function, the effect of over-           */
    /*  lapping solid figures, and the use of logical coordinates.        */
    /*  If you load graphics.qlb, no program list is needed.              */

    #include <stdio.h>
    #include <stdlib.h>
    #include <graph.h>
    #include <conio.h>
    #define ESC '\033'

    main(argc, argv)
    int argc;
    char *argv[];
    {
        struct videoconfig vc;
        int mode = _MRES4COLOR;
        short xcent[3], ycent[3]; /* egg centers */
        short xsize, ysize;       /* egg limits  */
        int egg;

        if (argc > 1)
            mode = atoi(argv[1]);
        if (_setvideomode(mode) == 0)
            {
            printf("Can't open mode %d\n", mode);
            exit(1);
            }
        _getvideoconfig(&vc);
        xsize = 0.3 * vc.numxpixels;
        ysize = 0.3 * vc.numypixels;
        xcent[0] = 0.3 * vc.numxpixels;
        xcent[1] = 0.5 * vc.numxpixels;
        xcent[2] = 0.7 * vc.numxpixels;
        ycent[0] = ycent[2] = 0.4 * vc.numypixels;
        ycent[1] = 0.6 * vc.numypixels;
        _selectpalette(0);
        _setbkcolor(_MAGENTA);
        for (egg = 0; egg < 3; egg++)
            {
            _setlogorg(xcent[egg], ycent[egg]);
            _setcolor(egg + 1);
            _ellipse(_GFILLINTERIOR, -xsize, -ysize, xsize, ysize);
            }
        _settextposition(24, 0);
        _settextcolor(1);
        _outtext("Strike any key to terminate.");
        getch();
        _setvideomode(_DEFAULTMODE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-7.  The EGGS.C program.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 15-5 can be found on p.512 of the printed version of the book.  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-5. Output of EGGS.C.

    This program produces three colored Easter eggs. When figures overlap, the
    figure drawn last prevails. Again, we use logical coordinates to simplify
    specifying the figures. The arrays xcent[] and ycent[] contain the
    coordinates for the centers of the three ellipses. The same command draws
    all three figures; however, the program changes the logical coordinates
    each time so that the ellipses are centered on different points.

    We also use Graphics Library text functions in this program. Unlike
    printf(), these functions let you specify the location and color of the
    text. The _settextposition() function positions the text on the screen.
    Unlike the graphics functions, it measures positions in character rows and
    columns rather than in pixel columns and rows. Thus, our program positions
    text at row 24, column 0. The _settextcolor() command sets the color of
    the text. In the CGA graphics modes, you select the colors from the
    graphics palette. The EGA and VGA modes use the EGA and VGA palettes. In
    the color text modes, the colors follow the usual schemeâ”€â”€1 is blue, 2 is
    green, and so on. The _outtext() function takes an argument of a pointer
    to a string and prints it using the location and color specified by the
    previous functions.

Filling Figures: _setfillmask() and _floodfill()

    Just as _rectangle() uses a line mask to determine the line style,
    _rectangle() and _ellipse() use a "fill mask" to determine the pattern
    that fills a figure. By default, this pattern is a solid color, but you
    can redefine the pattern with _setfillmask(). Recall how _setlinestyle()
    uses a 16-bit pattern to represent a 16-pixel section of line. The
    _setfillmask() function uses an 8-by-8-bit pattern to represent a pixel
    pattern. In particular, it uses an array of eight bytes, with each byte
    representing one row.

    To create a bit map, draw an 8-by-8 pattern of squares. Fill in the
    squares that represent turned-on pixels. Then visualize each row as a
    binary number, each dark square representing a 1 and each clear square
    representing a 0. Take these eight binary numbers and convert them into a
    form recognized by C. (Use hexadecimal notation because each set of four
    bits corresponds to one hex digit.) After you initialize an array with
    those eight values, you can use the array as a fill mask.

    Figure 15-6 shows a pattern that you can use repeatedly to create a
    brick-like pattern. The first row has a bit pattern of 1111 1111. The
    pattern 1111 corresponds to the hex value F; therefore, the entire byte is
    0xFF in hex. The remaining rows generate the values shown in the figure.
    Create a mask that uses these values with the following declaration:

    unsigned char Mask[]= {0xFF, 0x80, 0x80, 0x80,
                            0xFF, 0x08, 0x08, 0x08};

    Use this as the fill mask with the following statement:

    _setfillmask(Mask);

    directly before you call _rectangle() or _ellipse() in the fill mode. The
    color of this mask is the same as the color of the figure.

    To make the fill a different color than the outline, draw the figure in
    the outline mode, change the current color, and use the _floodfill()
    function to fill the figure. This function takes three arguments: x, or
    pixel column, position; y, or pixel row, position; and a color number. If
    the specified position falls within a closed boundary drawn in the
    indicated color, the interior of the figure is filled with the current
    fill pattern. If the point is outside the figure, the exterior is filled.
    Do not specify a point that lies on the line.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 15-6 can be found on p.513 of the printed version of the book.  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-6. A fill mask.

    The MASKS.C program (Listing 15-8) demonstrates how to use masks. Note
    that this program looks better in the CGA mode than it does in either the
    EGA or VGA modes. That's because the patterns are larger at lower
    resolution and because the colors 1, 2, and 3 in the other modes don't
    look as good together as do the colors of the CGA palette 0. The program
    first draws a large rectangle and divides it into three parts. Then a for
    loop fills the parts using three separate masks and three different
    colors. (See Figure 15-7.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  masks.c -- illustrates _setfillmask() and          */
    /*             _floodfill()                            */
    /* Program list: masks.c                               */
    /* If you load graphics.qlb, no program list is needed.*/

    #include <stdio.h>
    #include <stdlib.h>
    #include <conio.h>
    #include <graph.h>
    unsigned char Inversemask[8];
    unsigned char Masks[3][8] = {
                {0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00},
                {0xFF, 0x80, 0x80, 0x80, 0xFF, 0x08, 0x08, 0x08},
                {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA}};
    main(argc, argv)
    int argc;
    char *argv[];
    {
        struct videoconfig vc;
        int mode = _MRES4COLOR;
        short xc, yc;
        short box, i;

        if (argc > 1)
            mode = atoi(argv[1]);
        if (_setvideomode(mode) == 0)
            {
            fprintf(stderr, "Can't set mode %d\n", mode);
            exit(1);
            }
        _getvideoconfig(&vc);
        xc = vc.numxpixels / 2;
        yc = vc.numypixels / 2;
        for (i = 0; i < 8; i++)
            Inversemask[i] = ~Masks[1][i];
        _setlogorg(xc, yc);
        _selectpalette(0);
        _setcolor(1);
        _rectangle(_GBORDER, -xc + 1, -yc + 1, xc - 1, yc - 1);
        _moveto(-xc + 1, -yc / 3);
        _lineto(xc - 1, -yc / 3);
        _moveto(-xc + 1, yc / 3);
        _lineto(xc - 1, yc / 3);
        for (box = 0; box < 3; box++)
            {
            _setcolor(box + 1);
            _setfillmask(Masks[box]);
            _floodfill(0, (box - 1) * yc / 2, 1);
            }
        _settextposition(5, 10);
        _outtext("Press a key to continue");
        getch();
        _setcolor(3);
        _setfillmask(Inversemask);
        _floodfill (0, 0, 1);
        _setcolor(2);
        _setfillmask(Masks[0]);
        _floodfill(0, yc / 2, 1);
        _settextposition(5, 10);
        _outtext("Press a key to terminate");
        getch();
        _setvideomode(_DEFAULTMODE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-8.  The MASKS.C program.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 15-7 can be found on p.515 of the printed version of the book.  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-7. Output of MASKS.C.

    Pressing a key initiates the second phase of the program, which
    illustrates what happens when you refill a figure. For example, the
    program overlays the bottom third of the rectangle with the mask used in
    the top third. Wherever the top mask has a bit set to 1, it covers the
    bottom pattern; wherever it has a bit set to 0, the bottom shows through.
    Thus, those portions of a mask set to 0 are "transparent."

    The middle third of the rectangle demonstrates another aspect of
    superimposed masks. Inversemask[] is the opposite of Masks[1][]:

    for (i = 0; i < 8; i++)
        Inversemask[i] = ~Masks[1][i];

    The loop uses the bitwise ~ operator to create a mask containing the
    reversed bits of Masks[1][] (1s become 0s, and 0s become 1s).
    Superimposing the inverse mask on the original mask but using a different
    color produces a two-color pattern. (See Figure 15-8.)

    When you use _floodfill(), use a solid border; the pattern "leaks" through
    a border with gaps. If you superimpose one pattern on top of another, the
    boundary color (the third argument to _floodfill()) must be a different
    color from the original pattern. The _floodfill() function turns on pixels
    until it reaches pixels set with the specified boundary color. If the
    pixels from the first mask have the same color as the boundary, the fill
    function stops when it encounters them, and thus it does not fill the
    entire figure.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 15-8 can be found on p.516 of the printed version of the book.  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-8. More output of MASKS.C.

Filling Other Shapes

    You can use the _floodfill() command with any area enclosed by a solid
    boundary. The ARROW.C program (Listing 15-9) provides an example using
    the _lineto() function. Figure 15-9 on the following page shows the
    output. Note that the Mask pattern fills the interior of the figure, and
    the Outmask pattern fills the exterior.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* arrow.c -- fills inside and outside of a line       */
    /*            drawing                                  */
    /* If you load graphics.qlb, no program list is needed.*/

    #include <stdio.h>
    #include <graph.h>
    #include <conio.h>
    #define ESC '\033'
    #define BKCOLS 16   /* use 16 background colors */
    long Bkcolors[BKCOLS] = {_BLACK, _BLUE, _GREEN, _CYAN,
                    _RED, _MAGENTA, _BROWN, _WHITE,
                    _GRAY, _LIGHTBLUE, _LIGHTGREEN,
                    _LIGHTCYAN, _LIGHTRED, _LIGHTMAGENTA,
                    _LIGHTYELLOW,_BRIGHTWHITE};
    char Mask[8] = {0x90, 0x68, 0x34, 0x19, 0x19, 0x34, 0x68,
                    0x90};
    char Outmask[8] = {0xFF, 0x80, 0x80, 0x80, 0xFF, 0x08, 0x08,
                        0x08};
    main(argc, argv)
    int argc;
    char *argv[];
    {
        struct videoconfig vc;
        int mode = _MRES4COLOR;
        float x1, y1, x2, y2, x3, y3, y4, x5, y5;
        long bk = _BLUE;

        if (argc > 1)
            mode = atoi(argv[1]);
        if (_setvideomode(mode) == 0)
            {
            printf("Can't set mode %d.\n", mode);
            exit(1);
            }
        _getvideoconfig(&vc);

        x1 = 0.1 * vc.numxpixels;
        x2 = 0.7 * vc.numxpixels;
        x3 = 0.6 * vc.numxpixels;
        x5 = 0.9 * vc.numxpixels;
        y1 = 0.45 * vc.numypixels;
        y2 = 0.55 * vc.numypixels;
        y3 = 0.3 * vc.numypixels;
        y4 = 0.7 * vc.numypixels;
        y5 = 0.5 * vc.numypixels;
        _selectpalette(0);
        _setcolor(1);
        _moveto(x1, y1);
        _lineto(x2, y1);
        _lineto(x3, y3);
        _lineto(x5, y5);
        _lineto(x3, y4);
        _lineto(x2, y2);
        _lineto(x1, y2);
        _lineto(x1, y1);
        _setcolor(2);
        _setfillmask(Mask);
        _floodfill(x2, y5, 1) ;
        _setcolor(3);
        _setfillmask(Outmask);     /* restores default mask */
        _floodfill(5, 5, 1) ;
        _settextcolor(1);
        _settextposition(23, 0);
        _outtext("Press <enter> to change background.");
        _settextposition(24, 0);
        _outtext("Press <esc> to end.");
        while (getch() != ESC)
            _setbkcolor(Bkcolors[++bk % BKCOLS]);
        _setvideomode(_DEFAULTMODE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-9.  The ARROW.C program.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 15-9 can be found on p.518 of the printed version of the book.  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-9. Output of ARROW.C.

    This program uses a 16-element array of background color values to display
    all 16 background colors. In the CGA mode, the background extends beyond
    the area filled by the Outmask pattern. In the EGA and VGA modes, the
    background area is the same as the fill area.

Replicating Images

    Sometimes you might want to use an image on the screen more than once.
    Rather than redrawing it several times, you can use the Graphics Library
    _getimage() and _putimage() functions to transfer the image from the
    screen to memory and then back to a different screen location.

    The _getimage() Function

    The _getimage() function copies a rectangular region into memory using the
    following format:

    _getimage(xa, ya, xb, yb, storage);

    In this syntax, xa and ya are the coordinates of the upper-left corner of
    the region to be copied, and xb and yb are the coordinates of the
    lower-right corner. The storage parameter is a far pointer to a block of
    memory large enough to hold all the pixel information.

    Typically, you use the _imagesize() function to calculate the number of
    bytes required and then use malloc() to allocate the necessary memory, as
    follows:

    char far *storage;
        ...
    storage = (char far *) malloc((unsigned int) _imagesize(xa, ya, xb,
    yb));

    The _imagesize() function requires as arguments the same corner
    coordinates used by _getimage(). It returns type long far, so you must use
    a typecast to make it agree with malloc().

    The _putimage() Function

    The _putimage() function copies a previously stored image from memory to a
    specified screen location using the following format:

    _putimage(x, y, storage, action);

    The x and y arguments are the coordinates of the upper-left corner of the
    desired position for the image. The storage argument is a pointer to the
    memory location containing the image. The action parameter describes how
    the new image interacts with any existing image at that location. The
    graph.h file contains a list of defined constants, or "action verbs," that
    can be used as action arguments. Table 15-5 on the following page lists
    and explains these constants.

    Table 15-5 Action Verbs for _putimage()
    Action Verb  Meaning
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    _GAND        Combine the new and old images using a logical AND. That is,
                the final color for a pixel is newcolor & oldcolor.
    _GOR         Combine the new and old images using a logical OR. That is,
                the final color for a pixel is newcolor | oldcolor.
    _GXOR        Combine the new and old images using a logical EXCLUSIVE OR.
                That is, the final color for a pixel is newcolor ^ oldcolor.
    _GPSET       Overwrite the old image and display the transferred image as
                it originally appeared. That is, the final color for a pixel
                is newcolor.
    _GPRESET     Overwrite the old image and display the transferred image in
                inverted color. That is, the final color for a pixel is
                ~newcolor.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    The GETPUT.C program (Listing 15-10) demonstrates all the action verbs.
    It draws an image in the upper-left quadrant of the screen. Next, it fills
    the other three quadrants with striped patterns. Then it copies the
    original image five times to each of the other quadrants, using all five
    action verbs. The original image consists of vertical stripes of the
    palette colors 1, 2, and 3, and the backgrounds consist of horizontal
    stripes of the same colors. Therefore, this example shows all possible
    interactions. (See Figure 15-10 on p. 523.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  getput.c -- illustrates _getimage(), _putimage(),  */
    /*              the image-background interaction, and  */
    /*              the aspect ratio                       */
    /* If you load graphics.qlb, no program list is needed.*/

    #include <stdio.h>
    #include <stdlib.h>  /* declares malloc()  */
    #include <graph.h>
    #include <conio.h>
    #define ESC '\033'

    /* The following variables describe various          */
    /* coordinates and sizes.                            */
    /* They are declared externally so that they can be  */
    /* shared easily by several functions.               */
    int X1, Yb1, X2, Y2, Xdelta, Xside, Yside; /* image  */
    int Xmid, Xmax, Ymid, Ymax;           /* background  */
    int Xps, Xpr, Xand, Xor, Xxor, Ytop, Ybot; /* copies */
    int X[3], Y[3];
    float Ar;    /* aspect ratio */

    struct videoconfig Vc;
    char Mask[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0};
    void Initialize(void), Drawfig(void),
        Drawbackground(void), Drawcopies(void);
    main(argc, argv)
    int argc;
    char *argv[];
    {
        int mode = _MRES4COLOR;

        if (argc > 1)
            mode = atoi(argv[1]);
        if (_setvideomode(mode) == 0)
            {
            fprintf(stderr, "Can't handle mode %d\n", mode);
            exit(1);
            }
        Initialize();
        Drawfig();
        Drawbackground();
        Drawcopies();
        _settextposition(1, 1);
        _outtext("Press a key to end");
        _settextposition(3, 1);
        _outtext("_GPSET _GPRESET _GAND");
        _settextposition(11, 5);
        _outtext("_GOR _GXOR");
        getch();
        _setvideomode(_DEFAULTMODE);
    }

    void Initialize()
    {
        _getvideoconfig(&Vc);
        Ar = (float) (10 * Vc.numypixels) /
            (6.5 * Vc.numxpixels);
        _setlogorg(0, 0);
        Xmid = Vc.numxpixels / 2;
        Ymid = Vc.numypixels / 2;
        Xmax = Vc.numxpixels - 1;
        Ymax = Vc.numypixels - 1;
        /* locate three background rectangles */
        X[0] = Xmid;
        Y[0] = 0;
        X[1] = Xmid;
        Y[1] = Ymid;
        X[2] = 0;
        Y[2] = Ymid;
        X1 = 0.2 * Vc.numxpixels;
        Yb1 = 0.2 * Vc.numypixels;
        Xdelta = 0.033 * Vc.numxpixels;
        Xside = 3 * Xdelta;
        Yside = 3 * Ar * Xdelta;
        X2 = X1 + Xside;
        Y2 = Yb1 + Yside;
        /* offsets for _putimage() */
        Xps = .05 * Vc.numxpixels;
        Xpr = .20 * Vc.numxpixels;
        Xand = 0.35 * Vc.numxpixels;
        Xor = .10 * Vc.numxpixels;
        Xxor = .30 * Vc.numxpixels;
        Ytop = .05 * Vc.numypixels;
        Ybot = 2 * Ytop + Yside;
        _selectpalette(0);
    }

    void Drawfig()
    {
        _setcolor(1);
        _rectangle(_GFILLINTERIOR, X1, Yb1,
                    X1 + Xdelta, Y2);
        _setcolor(2);
        _rectangle(_GFILLINTERIOR, X1 + Xdelta + 1, Yb1,
                    X1 + 2 * Xdelta, Y2);
        _setcolor(3);
        _rectangle(_GFILLINTERIOR, X1 +  2 * Xdelta + 1,
                    Yb1, X2, Y2);

    }

    void Drawbackground()
    {
        _setfillmask(Mask);
        _setcolor(1);
        _rectangle(_GFILLINTERIOR, Xmid, 0, Xmax - 1, Ymid - 1);
        _setcolor(2);
        _rectangle(_GFILLINTERIOR, Xmid, Ymid, Xmax, Ymax);
        _setcolor(3);
        _rectangle(_GFILLINTERIOR, 0, Ymid, Xmid - 1, Ymax);

    }

    void Drawcopies()
    {
        int quad;   /* quadrant used */
        char far *storage;

        storage = (char far *) malloc((unsigned)_imagesize
                    (X1, Yb1, X2, Y2));
        _getimage(X1, Yb1, X2, Y2, storage);
        for (quad = 0; quad < 3; quad++)
            {
            _putimage(X[quad] + Xps, Y[quad] + Ytop,
                    storage, _GPSET);
            _putimage(X[quad] + Xpr, Y[quad] + Ytop,
                    storage, _GPRESET);
            _putimage(X[quad] + Xand, Y[quad] + Ytop,
                    storage, _GAND);
            _putimage(X[quad] + Xor, Y[quad] + Ybot,
                    storage, _GOR);
            _putimage(X[quad] + Xxor, Y[quad] + Ybot,
                    storage, _GXOR);
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-10.  The GETPUT.C program.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 15-10 can be found on p.523 of the printed version of the book. â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-10. Output of GETPUT.C.

    To recognize the precise interactions, you must understand the action of
    C's bitwise operators, and you must remember that the verbs operate on the
    palette numbers, not the color numbers. For example, if CGA palette 0 is
    in effect, and you select the color green, the action verbs use the
    palette number (1), not the color number for green (2). Because of this,
    the action verbs affect CGA mode colors differently than EGA or VGA
    colors. For example, when CGA palette 0 is used, palette number 1 is
    green. In the two-digit binary that represents CGA palette choices, the
    number is actually 01. When you apply the bitwise negation operator
    _GPRESET to the number, you get 10. In decimal, this is palette choice 2,
    or brown. Therefore, in CGA modes, _GPRESET converts a green image to
    brown. However, the EGA mode uses a 16-color palette. The default palette
    represents green with palette number 2, which is 0010 in binary. _GPRESET
    converts this to 1101 in binary, which is intensified magenta. Therefore,
    in EGA modes, _GPRESET converts green not to brown but to intensified
    magentaâ”€â”€quite different from the CGA operation.

Aspect Ratios

    The GETPUT.C program also illustrates how to make squares. In most modes,
    the pixel width is different from the pixel height, so you cannot make a
    square figure by creating a rectangle with equal numbers of horizontal and
    vertical pixels. To create square rectangles (or circular ellipses), you
    need to calculate the proper "aspect ratio." This is the ratio of the
    number of pixels in a vertical line to the number of pixels in a
    horizontal line of the same physical length. The aspect ratio is the
    product of two ratios:

    â–   (screen height in pixels) / (screen width in pixels)

    â–   (screen height in inches) / (screen width in inches)

    The GETPUT.C program represents that ratio with the following code:

    Ar = (float) (10 * Vc.numypixels) / (6.5 * Vc.numxpixels);

    Then the program uses the aspect ratio to scale the number of y pixels:

    Xside = 3 * Xdelta;
    Yside = 3 * Ar * Xdelta;

    This results in Yside and Xside representing equal lengths on the screen.
    Of course, the vertical and horizontal size settings on your monitor will
    affect your results.

Simple Animation

    You can use the _getimage() and _putimage() functions to create animation.
    The method is to erase the current image and to put a copy of the image at
    a slightly displaced location. To erase, you can superimpose a copy on the
    original using the _GXOR action verb. Because this operation combines like
    bits to produce an off bit, all bits get turned off.

    The RACE.C program (Listing 15-11) uses this animation technique to stage
    a race across the screen. The contestants are three patterned circles. The
    race, in this case, goes to the luckiest, for the program uses the rand()
    random number function to control the motion. At each movement
    opportunity, the program calls rand(). If it returns an even value, the
    circle moves ahead a step; otherwise it stays put.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* race.c -- race of the patterned circles             */
    /*    Illustrates animation with _getimage() and       */
    /*    _putimage(), random number use with srand() and  */
    /*    rand(), and system clock use with time() and     */
    /*    ftime().                                         */
    /* Program list: race.c (for srand(), rand(), and      */
    /*                       ftime())                      */

    #include <stdio.h>
    #include <stdlib.h>
    #include <conio.h>
    #include <graph.h>
    #include <time.h>
    #include <sys\types.h>
    #include <sys\timeb.h>

    #define END 25
    #define FIGNUM 3
    typedef char far *PTFRCHAR;
    PTFRCHAR Bufs[FIGNUM];
    unsigned char Masks[FIGNUM][8] = {
                {0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00},
                {0xF0, 0xF0, 0xF0, 0xF0, 0x0F, 0x0F, 0x0F, 0x0F},
                {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA}};
    short Xul[FIGNUM], Yul[FIGNUM];  /* figure locations */
    short Xsize, Ysize;              /* figure size      */
    struct videoconfig Vc;
    void Initialize(void);
    void Draw_n_store(void);
    void Move_figs(void);
    void Wait(double);

    main(argc, argv)
    int argc;
    char *argv[];
    {
        int mode = _MRES4COLOR;

        if (argc > 1)
            mode = atoi(argv[1]);
        if (_setvideomode(mode) == 0)
            {
            fprintf(stderr, "mode %d not supported\n", mode);
            exit(1);
            }
        Initialize();
        Draw_n_store();
        _settextcolor(2);
        _settextposition(1, 1);
        _outtext("Place your bets and press a key");
        _settextposition(25, 1);
        _outtext("Press a key again when done");
        getch();
        Move_figs();
        getch();
        _setvideomode(_DEFAULTMODE);
    }

    void Initialize()
    {
        int i;
        float ar;  /* aspect ratio */

        _getvideoconfig(&Vc);
        ar = (float)(10 * Vc.numypixels) / (6.5 * Vc.numxpixels);
        /* set size, initial positions */
        Xsize = Vc.numxpixels / 30;
        Ysize = ar * Xsize;
        for(i = 0; i < FIGNUM; i++)
            {
            Xul[i] = 0;
            Yul[i] = (i + 1) * Vc.numypixels /
                        (FIGNUM + 1);
            }
        _selectpalette(0);
        _setcolor(1);
            /*  draw finish line */
        _moveto(END * Xsize, 0);
        _lineto(END * Xsize, Vc.numypixels - 1);
    }

    void Draw_n_store() /* draw images, save them */
    {
        int i;

        for (i = 0; i < FIGNUM; i++)
            {
            _setcolor(i + 1);
            _setfillmask(Masks[i]);
            _ellipse(_GFILLINTERIOR, Xul[i], Yul[i],
                    Xul[i] + Xsize, Yul[i] + Ysize);
            _ellipse(_GBORDER, Xul[i], Yul[i],
                    Xul[i] + Xsize, Yul[i] + Ysize);
            Bufs[i] = (PTFRCHAR) malloc((unsigned int)
                    _imagesize(0, Yul[i], Xul[i] +
                    Xsize, Yul[i] + Ysize));
            _getimage(Xul[i], Yul[i], Xul[i] + Xsize, Yul[i] +
                    Ysize, Bufs[i]);

            }
    }
    void Move_figs()
    {
        int i, j;
        static int dx[FIGNUM] = {0, 0, 0}; /* displacements */
        time_t tval;

        time(&tval);    /*   use the current time value   */
        srand(tval);    /*   to initialize rand()         */
        while (dx[0] < END && dx[1] < END && dx[2] < END)
            {
            for (i = 0; i < FIGNUM; i++)
                {
                /* Advance the figure one position if  */
                /* rand() returns an even number.      */
                if (rand() % 2 == 0)
                    {
                    /* erase old image */
                    _putimage(dx[i] * Xsize, Yul[i],
                            Bufs[i], _GXOR);
                    /* redraw in new position */
                    _putimage((1 + dx[i]) * Xsize, Yul[i],
                            Bufs[i], _GPSET);
                    dx[i]++;
                    }
                }
            Wait(0.15);
            }
        for (j = 0; j < 5; j++)
            {
            for(i = 0; i < FIGNUM; i++)
                {
                /* flash winning figure */
                if (dx[i] >= END)
                    {
                    Wait(0.2);
                    _putimage(dx[i] * Xsize, Yul[i],
                            Bufs[i], _GPRESET);
                    Wait(0.2);
                    _putimage(dx[i] * Xsize, Yul[i],
                            Bufs[i], _GPSET);
                    }
                }
            }
    }

    void Wait(pause) /* wait for pause seconds */
    double pause;
    {
        struct timeb start, end;
        long delay;
        delay = 1000 * pause;  /* convert to milliseconds */
        ftime(&start);
        ftime(&end);
        while ((1000 * (end.time - start.time) +
                + end.millitm - start.millitm) < delay)
            ftime(&end);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-11.  The RACE.C program.

    The RACE.C program uses three action verbs. The _GPSET verb generates new
    ("moving") images. The _GXOR verb erases the old images. Finally, the
    program alternates between _GPSET and _GPRESET, creating a flashing image
    for the winner. (Ties are possible, in which case the cowinners flash.)

    The program also features several standard C functions. The rand()
    function returns a random number in the range 0 through 32,767. Actually,
    it returns a "pseudorandom" number, meaning that eventually the function
    returns the same sequence of numbers. Also, rand() always starts with the
    same sequence of numbers unless you first use srand() to select a
    different starting point. The program uses the time() function to "seed"
    srand() with a different argument each time the program is called. As a
    result, the program always runs using a different sequence of random
    numbers. (The time() function places the number of seconds elapsed between
    00:00:00, January 1, 1970 [GMT] and the current clock time into the
    location whose address is passed to it as an argument.)

    Programs such as this can run into problems because different computers
    and different video modes run the animation at different speeds. What
    plods on one system might blur on another. To meet this problem, RACE.C
    uses the system clock to run the animation at a constant rate. The Wait()
    function causes the program to pause for the number of seconds indicated
    by its floating-point argument. Wait(), in turn, uses the standard C
    function ftime(). The argument for this function is a pointer to a type
    struct timeb structure, as defined in <SYS\timeb.h>. The time field of
    this structure is the time in seconds since 00:00:00 GMT, January 1, 1970
    (the value provided by time()). The millitm field is a fraction of a
    second in milliseconds. This added information allows Wait() to pause for
    fractions of a second. (Wait() converts all times to milliseconds to
    facilitate finding the difference between two times.)

    Although the timeb structure tells time to the nearest millisecond, the
    system clock might progress in larger jumps. The IBM PC/XT/AT clock, for
    example, has 18.2 ticks per second; so each tick advances the time
    approximately 50 milliseconds.


EGA Graphics

    As Table 15-1 on p. 492 suggests, the EGA offers more graphics
    capabilities than the CGA offers. The two adapters also map video memory
    to the display differently, but the QuickC Graphics Library functions hide
    those details from us. What QuickC can't hide are the different ways that
    the EGA graphics modes handle color.

The Palette

    For comparison, let's quickly review the CGA palette. It has four colors
    numbered 0 through 3, and you can use the _setcolor() function to choose a
    particular color from the palette. Color 0 is the background color, and
    you set its value with the _setbkcolor() function by using one of the
    manifest constants in Table 15-4 on p. 501. The other three colors are
    chosen by using _selectpalette() to select one of the four preset
    combinations in Table 15-3 on p. 500.

    The EGA has a 16-color palette, using values in the range 0 through 15.
    Palette value 0 represents the background color. By default, the EGA color
    palette is set to the same colors shown in Table 15-3. As with the CGA,
    you can use _setcolor() to select a particular color from this palette;
    merely use the palette number as the argument. However, the EGA modes
    ignore the _selectpalette() function. Instead, these modes use the
    _remappalette() and _remapallpalette() functions to reassign colors to the
    palette values. That is, palette value 1, by default, is blue. But the
    remapping functions let you assign red, for example, to palette value 1.

    The remapping functions provide you with a powerful tool. Suppose you've
    drawn and colored a figure, but you want to change the colors. Rather than
    redraw the figure and fill it again, you can remap the palette assignments
    and change the on-screen colors almost immediately.

    Specifying Palette Values and Color Values

    In the EGA graphics modes, each pixel is represented by four bits in the
    EGA video memory. These bits represent the palette value, which is a
    number in the range 0 through 15. If a particular pixel has a palette
    number of 3, for example, the EGA looks up the "color value" for that
    palette number and makes the pixel that color. The EGA color value, in
    turn, is a 6-bit number. Essentially, the palette number is an index to a
    table of color values, and the remapping functions alter that table.

    The 6-bit EGA color values can generate 64 colors, but only mode 16
    (_ERESCOLOR) makes all 64 available. The other modes use only 16 colors of
    the default palette; however, they let you select the palette number which
    will correspond to a given color. The total range of EGA colors uses the
    color values 0 through 63. However, the QuickC remapping functions use VGA
    color values for compatibility reasons. This complicates accessing all 64
    EGA colors because, in the VGA representation, the EGA colors are not
    consecutive values. However, you can access the 16 colors of the default
    palette by using the manifest constants in graph.h. (See Table 15-6 on
    the following page.) These are set to the VGA values shown in the second
    column. The EGA values are provided for your information. (Later we will
    show you how to access all 64 colors.)

    Setting the Palette

    The QuickC Graphics Library contains two functions for setting the EGA
    palette. One, called _remappalette(), lets you assign a color value to a
    particular palette value. You can use it, for example, to change palette
    value 3 from cyan to magenta.

    Table 15-6 VGA Color Values for the Default Palette
    #define Name       VGA Color Value   EGA Color Value
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
                        Hex               rgb   RGB   Octal
    _BLACK             0x000000L         000   000   000
    _BLUE              0x2A0000L         000   001   001
    _GREEN             0x002A00L         000   010   002
    _CYAN              0x2A2A00L         000   011   003
    _RED               0x00002AL         000   100   004
    _MAGENTA           0x2A002AL         000   101   005
    _BROWN             0x00152AL         010   100   024
    _WHITE             0x2A2A2AL         000   111   007
    _GRAY              0x151515L         111   000   070
    _LIGHTBLUE         0x3F1515L         111   001   071
    _LIGHTGREEN        0x153F15L         111   010   072
    _LIGHTCYAN         0x3F3F15L         111   011   073
    _LIGHTRED          0x15153FL         111   100   074
    _LIGHTMAGENTA      0x3F153FL         111   101   075
    _LIGHTYELLOW       0x153F3FL         111   110   076
    _BRIGHTWHITE       0x3F3F3FL         111   111   077
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    The function uses VGA color values, for which it's convenient to use the
    graph.h constants. To make palette value 3 represent magenta, use the
    following call:

    _remappalette(3,_MAGENTA);

    The second function, called _remapallpalette(), lets you remap all the
    palette values simultaneously. Its argument is an array of the desired
    color values. Because the VGA color values are type long, use a type long
    array initialized to the desired VGA color values.

    The RINGS.C program (Listing 15-12 beginning on p. 532) presents an
    interesting example of palette remapping. It initializes the newpalette[]
    array to light blue for all but three palette values. Palette value 0
    (which represents the background) is assigned gray, and palette values 1
    and 8 are assigned red and light red. Then _remapallpalette() sets the
    palette to the values provided by newpalette[]. Next, a for loop draws a
    series of concentric circles:

    for (index = 2; index < 16; index++)
        {
        xmax /= 1.4;
        ymax /= 1.4;
        _setcolor(index);
        _ellipse(_GFILLINTERIOR, -xmax, -ymax, xmax, ymax);
        }

    If the palette weren't reset, this code would produce concentric rings of
    different colors. However, with the new palette, all but two rings are
    light blue, and all but those two rings blend into a featureless
    background.

    Next, the program enters a loop that shifts the color values in
    newpalette[] by one array element; then it remaps the palette. The first
    pass through this loop assigns red to palette value 2 and light red to
    palette value 9. On the screen, this produces the illusion that each ring
    has moved one position inward. (See Figure 15-12 on the following page.)
    One final program feature lets you use the keys 2 through 7 to change the
    ring colorsâ”€â”€by changing the color assignments for newpalette[]. Press the
    Esc key to quit.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    EGA Color Values
    The QuickC Graphics Library doesn't use the EGA color values explicitly,
    but here's how they work. Each of the 64 EGA colors is represented by a
    6-bit color value. The left three bits represent low-intensity red, green,
    and blue, respectively. The right three bits represent normal-intensity
    red, green, and blue, respectively. The sequence rgbRGB represents this
    order symbolically. The binary value 000001, for example, has the B bit
    (normal-intensity blue) set.

    How then does the EGA form the intensified colorsâ”€â”€light blue, light red,
    and so on? The CGA forms them by adding low-intensity white to the
    standard colors. Low-intensity white is 111000 in EGA notation, so light
    blue, for example, is 111001. Table 15-6 defines brown as 010100, or red
    plus low-intensity green. This produces a different tint than the
    corresponding CGA color, which is yellow, or 000110.

    The EGA has other combinations with no CGA equivalents. For example,
    001000 would be a low-intensity blue, and 010100 would be a mixture of
    low-intensity green and normal-intensity red. Altogether, the 6-bit
    representation permits 64 combinations, corresponding to the integers 0
    through 63. Another way of looking at the color value is that each color
    is described by two bits, permitting four intensity settings for that
    color: off, low, normal, and high-intensity, as shown in Figure 15-11.
    The rgb bits are sometimes referred to as the "1/3" intensity bits and the
    RGB bits as the "2/3" intensity bits. Setting both gives full intensity.
    Note, however, that the actual ratios of intensities depend on the
    display's brightness and contrast settings. (The rgbRGB system is also
    reflected in the EGA hardware, which uses six wires, one for each bit, to
    communicate color information to the monitor.)

                                â”Œâ”€â”      â”Œâ”€â”
    EGA color value bits  r  g â”‚bâ”‚ R  G â”‚Bâ”‚      Blue intensity
                                â””â”€â”˜      â””â”€â”˜
                    â”Œâ”€â”€        0        0        0   (off)
        Bit values â”€â”€â”¤          1        0       1/3  (low intensity)
                    â”‚          0        1       2/3  (normal)
                    â””â”€â”€        1        1        1   (high intensity)

    Figure 15-11. The EGA supports four intensities for blue.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 15-12 can be found on p.532 of the printed version of the book. â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-12. Output of RINGS.C.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  rings.c -- shoots colored rings                     */
    /*  This program illustrates _remapallpalette() and     */
    /*  how it can be used to produce the appearance of     */
    /*  motion. The program is intended for EGA modes 13,   */
    /*  14, and 16.                                         */
    /*  Program list: rings.c                               */
    /*  If you load graphics.qlb, no program list is needed.*/

    #include <stdio.h>
    #include <stdlib.h>
    #include <conio.h>
    #include <graph.h>
    #define ESC '\033'

    long Colors[16] = {_BLACK, _BLUE, _GREEN, _CYAN,
                    _RED, _MAGENTA, _BROWN, _WHITE,
                    _GRAY, _LIGHTBLUE, _LIGHTGREEN,
                    _LIGHTCYAN, _LIGHTRED, _LIGHTMAGENTA,
                    _LIGHTYELLOW, _BRIGHTWHITE};

    main(argc, argv)
    int argc;
    char *argv[];
    {
        struct videoconfig vc;
        float aspect;
        short xmax, ymax;
        long int newpalette[16];
        long int temp;
        int index;
        int hot1 = 1;  /* first colored ring  */
        int hot2 = 8;  /* second colored ring */
        int mode = _ERESCOLOR;
        int ch;

        if (argc > 1)
            mode = atoi(argv[1]);
        if (mode < 13)
            {
            fprintf(stderr, "Requires EGA or VGA mode\n");
            exit(1);
            }
        if (_setvideomode(mode) == 0)
            {
            fprintf(stderr, "% d mode unavailable\n", mode);
            exit(2);
            }
        _getvideoconfig(&vc);
        _setlogorg(vc.numxpixels / 2 - 1, vc.numypixels / 2 - 1);
        aspect = (10.0 * vc.numypixels) / (6.5 * vc.numxpixels);
        ymax = vc.numypixels / 2 - 2;
        xmax = ymax / aspect;
        for (index = 2; index < 16; index++)
            newpalette[index] = _LIGHTBLUE;
        newpalette[0] = _GRAY;
        newpalette[hot1] = _RED;
        newpalette[hot2] = _LIGHTRED;
        _remapallpalette(newpalette);  /* set initial palette */
        _setcolor(1);
        _ellipse(_GFILLINTERIOR, -xmax, -ymax, xmax, ymax);
        /* draw concentric circles */
        for (index = 2; index < 16; index++)
            {
            xmax /= 1.4;
            ymax /= 1.4;
            _setcolor(index);
            _ellipse(_GFILLINTERIOR, -xmax, -ymax, xmax, ymax);
            }
        do
            {
            while (!kbhit())
                {
                temp = newpalette[15];
                for(index = 15; index > 1; index--)
                    newpalette[index] = newpalette[index - 1];
                newpalette[1] = temp;
                _remapallpalette(newpalette);
                hot1 = hot1 % 15 + 1;  /* index of colored ring */
                hot2 = hot2 % 15 + 1;
                }
            ch = getch();
            if (ch > '1' && ch < '8')  /* reassign colors */
                {
                newpalette[hot1] = Colors[ch - '0'];
                newpalette[hot2] = Colors[ch - '0' + 8];
                }
            } while (ch != ESC);
        _clearscreen(_GCLEARSCREEN);
        _setvideomode(_DEFAULTMODE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-12.  The RINGS.C program.

    The program illustrates a useful graphics programming techniqueâ”€â”€using an
    array to hold the standard color values:

    long Colors[16] = {_BLACK, _BLUE, _GREEN, _CYAN,
                        _RED, _MAGENTA, _BROWN, _WHITE,
                        _GRAY, _LIGHTBLUE, _LIGHTGREEN,
                        _LIGHTCYAN, _LIGHTRED, _LIGHTMAGENTA,
                        _LIGHTYELLOW, _BRIGHTWHITE};

    This use of an array lets a program access the nonsequential VGA values
    with a sequential array index.

Accessing All 64 EGA Colors

    The _ERESCOLOR mode lets you use all 64 EGA colors. However, to do so with
    the QuickC remapping functions, you must use the VGA color code for these
    colors. Although the graph.h list of manifest constants provides 16 of
    these codes, 48 EGA colors are unrepresented. To access them, you need to
    generate their VGA codes.

    The VGA uses six bits to describe the intensity of each of the three
    primary colors. Six bits produce 64 intensity levels for each primary
    color, so the total number of combinations is 64 x 64 x 64, or 262,144
    colors. The VGA stores this information in a 4-byte unit. The leftmost
    byte is set to 0, the next byte contains the 6-bit code for blue
    intensity, the next byte contains the 6-bit code for green intensity, and
    the last byte contains the 6-bit code for red intensity. Each of these
    color bytes has its leftmost two bits set to 0. (See Figure 15-13.)

    How does this compare to the EGA system? Consider the color blue. The EGA
    rgbRGB system can generate four levels of blue: 000000, 001000, 000001,
    and 001001. They represent 0, 1/3, 2/3, and full intensity. The VGA has 64
    levels of intensity, represented by a blue byte in the range 0 through 63.
    Zero intensity is 0. The 1/3 level is 21 decimal, or 0x15 hex. The 2/3
    intensity level is 42 decimal, or 0x2A hex. The full level is 63 decimal,
    or 0x3F hex. Extending this analysis to red and green produces the list of
    correspondences shown in Table 15-7. Hex is the natural base to use for
    VGA values because two hex digits can represent one byte. Thus, the first
    two hex digits represent the blue intensity, the second two hex digits
    represent the green intensity, and the final two hex digits represent the
    red intensity.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 15-13 can be found on p.535 of the printed version of the book. â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-13. VGA color value storage.

    Table 15-7 EGA Bit to VGA Byte Conversion
    EGA Color Bit        VGA Equivalent       Color
    Setting
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    000 001              0x2A0000             Blue (2/3 intensity)
    000 010              0x002A00             Green (2/3 intensity)
    000 100              0x00002A             Red (2/3 intensity)
    001 000              0x150000             Blue (1/3 intensity)
    010 000              0x001500             Green (1/3 intensity)
    100 000              0x000015             Red (1/3 intensity)
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Because the table lists all of the EGA color bits as VGA values, you can
    now combine them to represent any EGA color. For example, cyan is blue
    plus green, or 0x2A2A00. For another example, consider light blue, which
    is 111001 in EGA notation. We can sum the VGA equivalents as follows:

    EGA                  VGA                  Color
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    100 000              0x000015             Blue (1/3 intensity)
    010 000              0x001500             Green (1/3 intensity)
    001 000              0x150000             Red (1/3 intensity)
    000 001              0x2A0000             Blue (2/3 intensity)
    -------              --------             ---------------------
    111 001              0x3F1515             Light blue
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    The final value, 0x3F1515, matches VGA_LIGHTBLUE in Table 15-3 on p. 530.

    Defining Nonpalette Colors

    You can use this information to construct a header file (Listing 15-13 on
    the following page) to supplement the graph.h color value constants.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* egacolor.h -- vga equivalents for base ega colors */
    #define r 0x000015L      /* 1/3 intensity red   */
    #define g 0x001500L      /* 1/3 intensity green */
    #define b 0x150000L      /* 1/3 intensity blue  */
    #define R 0x00002AL      /* 2/3 intensity red   */
    #define G 0x002A00L      /* 2/3 intensity green */
    #define B 0x2A0000L      /* 2/3 intensity blue  */
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-13.  The egacolor.h program.

    The constants in egacolor.h provide the base color values. To generate any
    other EGA color, use the bitwise OR operator with these values. For
    example, a color whose rgbRGB representation is 101010 has the VGA value r
    | b | G. What color is this? Well, 111000 is dim white (dark gray), and
    101010 replaces the faint green of 111000 with a brighter green. The
    result is a greenish gray.

    The SCAPE.C program (Listing 15-14) demonstrates how to define other
    colors in terms of the base colors. It draws a simple scene, shown in
    Figure 15-14, in fresh, new colors, none of which are in the default
    palette.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* scape.c -- uses nondefault EGA colors               */
    /* If you load graphics.qlb, no program list is needed.*/

    #include <stdio.h>
    #include <graph.h>
    #include "egacolor.h"
    #include <stdlib.h>
    #include <conio.h>
    #define SKY (b | B | g)
    #define OCEAN b
    #define SAND (R | g | b)
    #define SUN (R | G | r | g)

    main(argc, argv)
    int argc;
    char *argv[];
    {
        struct videoconfig vc;
        int mode = _ERESCOLOR;
        short xmax, ymax, sunx, suny, sunsizex, sunsizey;
        float ar;

        if (argc > 1)
            mode = atoi(argv[1]);
        if (_setvideomode(mode) == 0)
            {
            fprintf(stderr, "mode %d not supported\n", mode);
            exit(1);
            }
        _getvideoconfig(&vc);
        xmax = vc.numxpixels - 1;
        ymax = vc.numypixels - 1;
        sunx = 0.7 * xmax;
        suny = 0.2 * ymax;
        ar = (float)(10 * vc.numypixels) / (6.5 * vc.numxpixels);
        sunsizex = xmax / 30;
        sunsizey = ar * sunsizex;
        _remappalette(1, SKY);
        _remappalette(2, OCEAN);
        _remappalette(3, SAND);
        _remappalette(4, SUN);
        _setcolor(1);
        _rectangle(_GFILLINTERIOR, 0, 0, xmax, 2 * ymax / 5);
        _setcolor(4);
        _ellipse(_GFILLINTERIOR, sunx - sunsizex, suny -
                sunsizey, sunx + sunsizex, suny + sunsizey);
        _setcolor(2);
        _rectangle(_GFILLINTERIOR, 0, 2 * ymax / 5, xmax,
                    2 * ymax / 3);
        _setcolor(3);
        _rectangle(_GFILLINTERIOR, 0, 2 * ymax / 3, xmax, ymax);
        getch();
        _setvideomode(_DEFAULTMODE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-14.  The SCAPE.C program.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 15-14 can be found on p.537 of the printed version of the book. â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 15-14. Output of SCAPE.C.

    Automatic Color Value Conversion

    A second approach to using nonpalette colors is to write a function that
    converts an EGA value to the corresponding VGA value. This lets us map the
    simple EGA color values into the complicated VGA color values that the
    library functions use. Listing 15-15 presents a function that takes an
    EGA color value as an argument and returns the corresponding VGA color
    value.

    The program's egacolor >> bit operation shifts a specified bit to position
    0. The &1 operation then masks all the other bits. This gives the
    expression a value of 1 if the bit is 1; otherwise it is a 0. This is
    multiplied by the VGA equivalent for the bit, and the loop obtains a
    running total.

    A Palette-Mapping Example

    Now we can look at all of the hidden 48 EGA colors. The ALLCOLOR.C program
    (Listing 15-16) uses Ega_to_vga() and _remappalette() to display all the
    EGA colors. It divides the screen vertically into two rectangles. The left
    rectangle fills with blue, and the right with red. Windows at the bottom
    of each rectangle show the current color value. Pressing g advances the
    color value of the left rectangle by 1 (it remaps palette value 1 to the
    next color value). Similarly, h advances the color value of the right
    rectangle. Pressing Shift with these keys decrements the color values.
    Using this program, you can thus match any two of the 64 colors side by
    side and see the sometimes subtle distinctions.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* egatovga.c -- converts ega color values to vga      */
    /*               color values                          */

    long Ega_to_vga(egacolor)
    int egacolor;        /* ega color value */
    {
        static long vgavals[6] = {0x2A0000L, 0x002A00L,
                            0x00002AL, 0x150000L,
                            0x001500L, 0x000015L};
        /* array holds VGA equivalents to EGA bits */
        long vgacolor = 0L; /* vga color value */
        int bit;

        /* convert each bit to equivalent and sum */
        for (bit = 0; bit < 6; bit++)
            vgacolor += ((egacolor >> bit) &1) * vgavals[bit];
        return (vgacolor);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-15.  The Ega_to_vga() function.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* allcolor.c -- shows _ERESCOLOR 64-color palette     */
    /* If you load graphics.qlb, no program list is needed.*/

    /*  Press <g> to advance left palette, <G> to go back. */
    /*  Press <h> to advance right palette, <H> to go back.*/
    /*  Press <Esc> to quit.                               */
    #include <stdio.h>
    #include <graph.h>
    #include <conio.h>
    #define MAXCOLORS 64
    #define ESC '\033'
    long Ega_to_vga(int);   /* color value conversion */

    main(argc, argv)
    int argc;
    char *argv[];
    {
        struct videoconfig vc;
        int mode = _ERESCOLOR;
        int xmax, ymax;
        int c1 = 1;
        int c2 = 4;
        char left[11];
        char right[11];
        int lpos, rpos;
        char ch;

        if (argc > 1)
            mode = atoi(argv[1]);
        if (_setvideomode(mode) == 0)
            {
            fprintf(stderr, "%d mode not supported\n", mode);
            exit(1);
            }
        _getvideoconfig(&vc);
        _setlogorg(vc.numxpixels / 2, vc.numypixels / 2);

        xmax = vc.numxpixels / 2 - 1;
        ymax = vc.numypixels / 2 - 1;
        lpos = vc.numxpixels / 32 - 5;
        rpos = lpos + vc.numxpixels / 16;
        _setcolor(1);
        _rectangle(_GFILLINTERIOR, -xmax, -ymax, 0, ymax);
        _setcolor(4);
        _rectangle(_GFILLINTERIOR, 1, -ymax, xmax, ymax);
        sprintf(left, "<-G %2d g->", c1);
        sprintf(right, "<-H %2d h->", c2);
        _settextcolor(6);
        _settextposition(0, 0);
        _outtext("Press Esc to quit");
        _settextposition(24, lpos);
        _outtext(left);
        _settextposition(24, rpos);
        _outtext(right);
        while ((ch = getch()) != ESC)
            {
            switch (ch)
                {
                case 'g': c1 = (c1 + 1) % MAXCOLORS;
                        _remappalette(1, Ega_to_vga(c1));
                        break;
                case 'G': c1 = (c1 - 1) % MAXCOLORS;
                        _remappalette(1, Ega_to_vga(c1));
                        break;
                case 'h': c2 = (c2 + 1) % MAXCOLORS;
                        _remappalette(4, Ega_to_vga(c2));
                        break;
                case 'H': c2 = (c2 - 1) % MAXCOLORS;
                        _remappalette(4, Ega_to_vga(c2));
                        break;
                }
            sprintf(left, "<-G %2d ->g", c1);
            sprintf(right, "<-H %2d ->h", c2);
            _settextposition(0, 0);
            _outtext("Press Esc to quit");
            _settextposition(24, lpos);
            _outtext(left);
            _settextposition(24, rpos);
            _outtext(right);
            }
        _setvideomode(_DEFAULTMODE);
    }
    long Ega_to_vga(egacolor)
    int egacolor;       /* ega color value */
    {
        static long vgavals[6] = {0x2A0000L, 0x002A00L, 0x00002AL,
                                0x150000L, 0x001500L, 0x000015L};
        long vgacolor = 0L; /* vga color value */
        int bit;
        for (bit = 0; bit < 6; bit++)
            vgacolor += ((egacolor >> bit) &1) * vgavals[bit];
        return (vgacolor);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-16.  The ALLCOLOR.C program.

    In ALLCOLOR.C, the following code does the remapping:

    case 'g': c1 = (c1 + 1) % MAXCOLORS;
                _remappalette(1, Ega_to_vga(c1));
                break;

    When g is pressed, the program increments by one the color value (c1) for
    the left rectangle. The modulus operator limits the final value to the
    range 0 through 63. The Ega_to_vga() function converts the EGA color value
    to a VGA color value, which is then used as an argument to
    _remappalette(). Notice how fast the colors change using the remapping
    approach.

Remapping the Entire Palette

    The RINGS.C program (Listing 15-12 beginning on p. 532) demonstrated how
    to use the _remapallpalette() function to reassign the 16 default colors
    to different palette values. Now let's use the function with all 64 EGA
    colors.

    First, we must initialize a 64-element array to the VGA color values for
    the EGA colors and then initialize a 16-element array to the color values
    for a particular palette. Thus, the 64-element array supplies color values
    for the palette array, and we can use the palette array with
    _remapallpalette() to remap the palette.

    To see how this works, let's apply the approach to our MOIRE.C program;
    the resulting program is REMOIRE.C (Listing 15-17). After it draws a
    pattern, the program begins remapping the colors. Press any key to stop
    the remapping; press any key (except Esc) again to restart the program. To
    terminate the program, press the Esc key while the program is paused. The
    screen shown on the back cover of this book is a sample of the moire
    pattern produced by this program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* remoire.c -- adds palette remapping to moire.c      */
    #include <conio.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <graph.h>
    #define ESC '\033'
    #define MAXCOLORS 64
    #define PALCOLORS 16
    long Ega_to_vga(int);

    main (argc, argv)
    int argc;
    char *argv[];
    {
        struct videoconfig vc;
        unsigned int col, row;
        long colors[MAXCOLORS];
        long palette[PALCOLORS];
        int index;
        int shift = 1;
        int firstcol, firstrow, lastrow, lastcol;
        int mode = _ERESCOLOR;

        if (argc > 1)
            mode = atoi(argv[1]);
        if (_setvideomode(mode) == 0)
            {
            printf("Can't do that mode.\n");
            exit(1);
            }
        /* Create array of all 64 color values. */
        for (index = 0; index < MAXCOLORS; index++)
            colors[index] = Ega_to_vga(index);
        /* Create array of 16 palette choices. */
        for (index = 0; index < PALCOLORS; index++)
            palette[index] = colors[index];
        _remapallpalette(palette);
        _getvideoconfig(&vc);
        firstcol = vc.numxpixels / 5;
        firstrow = vc.numypixels / 5;
        lastcol = 4 * vc.numxpixels / 5;
        lastrow = 4 * vc.numypixels / 5;

        for (col = firstcol; col <= lastcol; ++col)
            {
            for (row = firstrow; row <= lastrow; ++row)
                {
                _setcolor(((row * row + col * col) / 10)
                            % vc.numcolors);
                _setpixel(col, row);
                }
            }
        _settextposition(1, 1);
        _outtext("Press a key to stop or start.");
        _settextposition(2, 1);
        _outtext("Press Esc while paused to quit.");
        do
            {
            while (!kbhit())
                {
                /*  Set palette array to new color values. */
                for (index = 1; index < PALCOLORS; index++)
                    palette[index] = (colors[(index + shift)
                                    % MAXCOLORS]);
                _remapallpalette(palette);
                shift++;
                }
            getch();  /* pause until key is pressed */
            } while (getch() != ESC);

        _setvideomode(_DEFAULTMODE);  /* reset orig. mode */
    }
    long Ega_to_vga(egacolor)
    int egacolor;       /* ega color value */
    {
        static long vgavals[6] = {0x2A0000L, 0x002A00L, 0x00002AL,
                                0x150000L, 0x001500L, 0x000015L};
        long vgacolor = 0L; /* vga color value */
        int bit;

        for (bit = 0; bit < 6; bit++)
            vgacolor += ((egacolor >> bit) &1) * vgavals[bit];
        return (vgacolor);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-17.  The REMOIRE.C program.

    The following code initializes the arrays:

    /* Create array of all 64 color values. */
    for (index = 0; index < MAXCOLORS; index++)
        colors[index] = Ega_to_vga(index);
    /* Create array of 16 palette choices. */
    for (index = 0; index < PALCOLORS; index++)
        palette[index] = colors[index];

    The first loop initializes colors[] to the VGA color values. The second
    loop sets palette[] to the first 16 EGA colors. Note that this is not the
    default EGA palette. (See Table 15-6 on p. 530.)

    The following code reassigns the colors to palette[]:

    do
        {
        while (!kbhit())
            {
            /*  Set palette array to new color values. */
            for (index = 1; index < PALCOLORS; index++)
                palette[index] = (colors[(index + shift) % MAXCOLORS]);
            _remapallpalette(palette);
            shift++;
            }
        getch();  /* pause until key is pressed */
        } while (getch() != ESC);

    Because shift is initialized to 1, the first pass through this loop sets
    the palette array to the second through seventeenth members of colors[].
    When shift is incremented, the next pass moves the palette one element
    further into colors[].

    This example showcases the speed of remapping compared to the time the
    program originally took to color the screen.


VGA Graphics

    Now let's look at some programs that exclusively use VGA features. The VGA
    supports all EGA modes while providing three additional modes. Modes 17
    and 18 offer even a higher resolution (640 by 480 pixels) than does EGA
    mode 16. Mode 17 uses a 2-color palette, and mode 18 uses a 16-color
    palette. Mode 19 uses only medium resolution (320 by 200 pixels) but
    offers a 256-color palette. Furthermore, you can select the colors used in
    these modes from 262,144 color values. By choosing a suitable palette, you
    can construct images with much more realistic shadings of color than you
    can get from the CGA or EGA palettes. (The MCGA supports only mode 19 of
    these three.)

    To use these modes, you need the proper video display controller (VGA,
    MCGA, or a clone) and the proper monitor. Unlike the CGA and EGA adapters,
    which control display colors with digital signals, the VGA and MCGA use
    analog signals. Thus, they cannot be used with CGA or EGA display
    monitors. (The popular multisync monitors, however, can handle both
    digital and analog signals and can be used with all these adapters. Some
    automatically switch between digital and analog modes; others require you
    to manually set a switch.)

The 256-Color Palette

    The 256-color palette makes mode 19 the most interesting of the new VGA
    modes, and because both the MCGA and the VGA support it, mode 19 is also
    the most general. The COL256.C program (Listing 15-18) displays the
    256-color default palette. It draws a rectangular border and then uses
    _moveto() and _lineto() to divide the screen into a 16-by-16 array of
    rectangles. Finally, the program uses _floodfill() to display all 256
    colors. The expression:

    _setcolor(row * ROWS + col);

    in the final nested for loop sets the palette value (the argument to
    _setcolor()) to 0 through 255 in turnâ”€â”€the full range of palette values in
    this mode.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* col256.c  -- shows 256 colors in mode 19             */
    /* If you load graphics.qlb, no program list is needed. */

    #include <stdio.h>
    #include <graph.h>
    #include <conio.h>
    #define ESC '\033'
    #define ROWS 16
    #define COLS 16
    main()
    {
        struct videoconfig vc;
        int mode = _MRES256COLOR;
        short xmax, ymax;           /* screen size */
        short xcs[ROWS][COLS];      /* coordinates of the */
        short ycs[ROWS][COLS];      /* 256 rectangles     */
        short row, col;

        if (_setvideomode(mode) == 0)
            {
            fprintf(stderr, "%d mode not supported\n", mode);
            exit(1);
            }
        _getvideoconfig(&vc);

        xmax = vc.numxpixels - 1;
        ymax = vc.numypixels - 1;

        /* Compute an interior point for each rectangle. */
        for (col = 0; col < COLS; col++)
            for (row = 0; row < ROWS; row++)
                {
                xcs[row][col] =  col * xmax / COLS + 5;
                ycs[row][col] =  row * ymax / ROWS + 5;
                }

        /* draw outside boundary */
        _setcolor(1);
        _rectangle(_GBORDER, 0, 0, xmax, ymax);

        /* draw gridwork */
        for (col = 1; col < COLS ; col++)
            {
            _moveto(col * (xmax + 1) / COLS, 0);
            _lineto(col * (xmax + 1) / COLS, ymax);
            }
        for (row = 1; row < ROWS;  row++)
            {
            _moveto(0, row * (ymax + 1) / ROWS);
            _lineto(xmax, row * (ymax + 1) / ROWS);
            }

        /*  fill in rectangles with palette colors */
        for (col = 0; col < COLS; col++)
            for (row = 0; row < ROWS; row++)
                {
                _setcolor(row * ROWS + col);
                _floodfill(xcs[row][col], ycs[row][col], 1);
                }

        /* terminate program */
        getch();
        _setvideomode(_DEFAULTMODE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-18.  The COL256.C program.

Changing the Palette

    You can use the _remappalette() and _remapallpalette() functions to change
    the palette settings. Of course, you must use the VGA color value system
    to do so. Recall that the color value is represented by a 4-byte number.
    The low byte represents the red intensity level and can have any value
    from 0 through 63. Similarly, the next byte describes 64 levels of green
    intensity, and the third byte describes 64 levels of blue intensity.
    Therefore, we can represent any of the 262,144 available colors by the
    following form:

    colorvalue = blue << 16 | green << 8 | red;

    The shift operators use type long values to place the intensity values in
    the correct bytes. For example, to generate a color that is "nearly" a
    blend of blue at half intensity, green at quarter intensity, and red at
    three-quarters intensity, use the following color value assignment:

    colorvalue = 32L << 16 | 16L << 8 | 48L

    We say "nearly" because, using 63 to represent full intensity, you can't
    exactly specify half, quarter, and three-quarter intensities with
    integers.

    The VGAMAP.C program (Listing 15-19) extends COL256.C to demonstrate the
    remapping techniques for mode 19. It starts by showing the default
    palette. Pressing a key initializes a 256-element array to a new palette.
    (This array is declared externally so that it won't use up stack space.)
    The first 64 elements are set to the 64 levels of blue; the second 64 are
    set to the green levels; and the third 64 elements are set to the red
    levels. The final 64 are set to some of the red-blue (magenta) blends.
    (With 64 choices for each, there are 64 x 64, or 4096, red-blue blends.)
    These illustrate the shadings possible by varying only one of the three
    color components. The program uses _remapallpalette() to reset the palette
    to the new color values in this array.

    When you press another key, the program uses rand() to generate a randomly
    placed rectangle. It then selects random blue, green, and red intensity
    levels, constructs a color value from them, and sets the rectangle to that
    color. This process continues until you press a key. Any key press (except
    the Esc key) now toggles the random remapping on and off. Press the Esc
    key to terminate the program. Note that _remappalette() uses a short
    argument for the palette value, palval, and a long argument for the color
    value, colval.

    A color intensity range of 64 levels makes extremely subtle color
    variations possible. The ALLVGA.C program (Listing 15-20, beginning on p.
    548) modifies the ALLCOLOR.C program (Listing 15-16, beginning on p. 539)
    so that you can investigate these color possibilities. Rather than using
    one key to step through the 262,144 values, we use one key to control the
    blue level, one to control the green level, and one to control the red
    level.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  vgamap.c  -- remaps the vga mode 19 palette        */
    /*  Program list: vgamap.c (for rand())                */
    #include <stdio.h>
    #include <graph.h>
    #include <conio.h>
    #define ESC '\033'
    #define PALSIZE 256
    #define ROWS 16
    #define COLS 16
    #define MIDBLUE 0x190000L
    long newpal[PALSIZE]; /* array of color values */

    main()
    {
        struct videoconfig vc;
        int mode = _MRES256COLOR;
        short xmax, ymax;
        short xcs[ROWS][COLS];
        short ycs[ROWS][COLS];
        short row, col;
        long colorval;       /* VGA color value */
        long index;          /* looping index   */
        short palval;        /* palette value   */
        int c_base;  /* color base -- blue, green, or red */
        int ch;

        if (_setvideomode(mode) == 0)
            {
            fprintf(stderr, "%d mode not supported\n", mode);
            exit(1);
            }
        _getvideoconfig(&vc);
        xmax = vc.numxpixels - 1;
        ymax = vc.numypixels - 1;
        for (col = 0; col < COLS; col++)
            for (row = 0; row < ROWS; row++)
                {
                xcs[row][col] =  col * xmax / COLS + 5;
                ycs[row][col] =  row * ymax / ROWS + 5;
                }
        _setcolor(1);
        _rectangle(_GBORDER, 0, 0, xmax, ymax);
        for (col = 1; col < COLS; col++)
            {
            _moveto(col * (xmax + 1) / COLS, 0);
            _lineto(col * (xmax + 1) / COLS, ymax);
            }
        for (row = 1; row < ROWS;  row++)
            {
            _moveto(0, row * (ymax + 1) / ROWS);
            _lineto(xmax, row * (ymax + 1) / ROWS);
            }
        for (col = 0; col < COLS; col++)
            for (row = 0; row < ROWS; row++)
                {
                _setcolor(row * ROWS + col);
                _floodfill(xcs[row][col], ycs[row][col], 1);
                }
        getch();

        /*  Initialize newpal[] to 64 shades of blue, 64
            shades of green, 64 shades of red, and 64 shades
            of magenta. */
        for (index = 0; index < 64; index++)
            {
            newpal[index] = index << 16;
            newpal[index + 64] = index << 8;
            newpal[index + 128] = index;
            newpal[index + 192] = index | MIDBLUE;
            }
        _remapallpalette(newpal);
        getch();

        /* Set squares and colors randomly -- ESC
            terminates loop, and other keystrokes toggle
            it on and off. */
        do
            {
            while (!kbhit())
                {
                palval = rand() % PALSIZE;
                colorval = 0L;
                for (c_base = 0; c_base < 3; c_base++)
                    colorval += ((long) rand() % 64) <<
                                (c_base * 8);
                _remappalette (palval, colorval);
                }
            ch = getch();
            if (ch != ESC)
                ch = getch();
            } while (ch != ESC);
        _setvideomode(_DEFAULTMODE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-19.  The VGAMAP.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* allvga.c -- shows _MRES256COLOR 256K colors         */
    /* If you load graphics.qlb, no program list is needed.*/

    #include <stdio.h>
    #include <stdlib.h>
    #include <graph.h>
    #include <conio.h>
    #define FULLBRIGHT 64
    #define ESC '\033'
    char label[2][7] = {"ACTIVE", "      "};

    main(argc, argv)
    int argc;
    char *argv[];
    {
        struct videoconfig vc;
        int mode = _MRES256COLOR;
        int xmax, ymax;
        static long colors[2] = {_BLUE, _RED};
        char left[11];
        char right [11];
        int lpos, rpos;
        char ch;
        unsigned long blue = _BLUE >> 16;
        unsigned long green = 0L;
        unsigned long red = 0L;
        long color;
        short palnum = 0;

        if (argc > 1)
            mode = atoi(argv[1]);
        if (_setvideomode(mode) == 0)
            {
            fprintf(stderr, "%d mode not supported\n", mode);
            exit(1);
            }
        _getvideoconfig(&vc);
        _setlogorg(vc.numxpixels / 2, vc.numypixels / 2);

        xmax = vc.numxpixels / 2 - 1;
        ymax = vc.numypixels / 2 - 1;
        lpos = vc.numxpixels / 32 - 5;
        rpos = lpos + vc.numxpixels / 16;
        _remappalette(2, _RED);
        _setcolor(1);
        _rectangle(_GFILLINTERIOR, -xmax, -ymax, 0, ymax);
        _setcolor(2);
        _rectangle(_GFILLINTERIOR, 1, -ymax, xmax, ymax);
        sprintf(left, " %6lxH ", colors[0]);
        sprintf(right, " %6lxH ", colors[1]);
        _settextcolor(6);
        _settextposition(1, 1);
        _outtext("Press Tab to toggle panels, Esc to quit.");
        _settextposition(2, 1);
        _outtext("B increases blue level, b decreases it. ");
        _settextposition(3, 1);
        _outtext("G and g control green, R and r red.     ");
        _settextposition(24, lpos);
        _outtext(left);
        _settextposition(24, rpos);
        _outtext(right);
        _settextposition(5, 7);
        _outtext(label[0]);
        _settextposition(5, 27);
        _outtext(label[1]);
        while ((ch = getch()) != ESC)
            {
            switch (ch)
                {
                case '\t': _settextposition(5, 27);
                            _outtext(label[palnum]);
                            palnum ^= 1;
                            blue = (colors[palnum] << 16) & 0x3F;
                            green = (colors[palnum] << 8) & 0x3F;
                            red = colors[palnum] & 0x3F;
                            _settextposition(5, 7);
                            _outtext(label[palnum]);

                            break;
                case 'B':  blue = (blue + 1) % FULLBRIGHT;
                            colors[palnum] = blue << 16 |
                                    green << 8 | red;
                            _remappalette(palnum + 1, colors[palnum]);

                            break;
                case 'b':  blue = (blue - 1) % FULLBRIGHT;
                            colors[palnum] = blue << 16 |
                                    green << 8 | red;
                            _remappalette(palnum + 1, colors[palnum]);

                            break;
                case 'G':  green = (green + 1) % FULLBRIGHT;
                            colors[palnum] = blue << 16 |
                                    green << 8 | red;
                            _remappalette(palnum + 1, colors[palnum]);

                            break;
                case 'g':  green = (green - 1) % FULLBRIGHT;
                            colors[palnum] = blue << 16 |
                                    green << 8 | red;
                            _remappalette(palnum + 1, colors[palnum]);

                            break;
                case 'R':  red = (red + 1) % FULLBRIGHT;
                            colors[palnum] = blue << 16 |
                                    green << 8 | red;
                            _remappalette(palnum + 1, colors[palnum]);

                            break;
                case 'r':  red = (red - 1) % FULLBRIGHT;
                            colors[palnum] = blue << 16 |
                                    green << 8 | red;
                            _remappalette(palnum + 1, colors[palnum]);

                            break;

                }
            sprintf(left, " %6lxH ", colors[0]);
            sprintf(right, " %6lxH ", colors[1]);
            _settextposition(24, lpos);
            _outtext(left);
            _settextposition(24, rpos);
            _outtext(right);
            }
        _setvideomode(_DEFAULTMODE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 15-20.  The ALLVGA.C program.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€