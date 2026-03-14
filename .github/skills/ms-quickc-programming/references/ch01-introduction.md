Chapter 1  Introduction


Why Learn C?

    If you have experience with C, you are probably familiar with its
    advantages over alternatives such as BASIC or Pascal, and you may want to
    skip to the next section, which discusses the specific advantages of
    QuickC for C programmers. Here we compare C with two other popular
    languages, BASIC and Pascal.

    Although Pascal has its enthusiasts, and our old friend BASIC certainly
    has been improved in many ways (Microsoft's QuickBASIC for example), C has
    quickly become the premier language for professional programming both on
    micros, such as the IBM PC family, and on larger machines, such as those
    running the UNIX/XENIX operating system. Why is C so popular?

Portability and Standards

    One reason is portability. The core of standard C is so designed that the
    same program runs on an IBM PC, a VAX mini, and an IBM mainframe.
    Portability comes about from adhering to standards that guarantee common
    features and functions regardless of the vendor, implementation, or
    hardware environment. The first, informal C standard was proclaimed by the
    famous "white book," Brian W. Kernighan and Dennis M. Ritchie's The C
    Programming Language (New Jersey: Prentice-Hall, 1978). The specifications
    in this book have been widely adopted in the design of C compilers, but
    the definitions are not comprehensive and specific enough to provide a
    true standard. Therefore, the American National Standards Institute (ANSI)
    has proposed a draft standard for the C language. (At the time of this
    writing, the standard has not been officially adopted, but most of its
    features seem stable.) Most current and future C compilers will be written
    to conform with the ANSI standard. QuickC is compatible with the ANSI
    standard. It also permits you to verify that your code uses only
    ANSI-compatible functions and definitions or to identify nonstandard
    features, such as those needed to support functions specific to MS-DOS and
    to IBM hardware.

    Another reason for the popularity of C is its close ties to the UNIX
    operating system. UNIX was written in C, and a variety of standards
    support the use of C in the UNIX environment. QuickC is functionally
    compatible with the UNIX System V standard library specifications.

    But what does all of this mean to you, the QuickC programmer?

    A C program written under QuickC on an IBM PC can, if it uses only
    ANSI-standard features, be moved to an Apple Macintosh, and you can
    compile it with an ANSI-standard Macintosh C compiler and run it in the
    new environment.

    This level of standardization is not common in programming languages.
    Pascal is only partially standardized: A Turbo Pascal program for the IBM
    PC, for example, cannot run under standard IBM Pascal without
    modification. In the IBM PC world, the ubiquitous BASICA program has
    offered a kind of standard, but other models of computers are provided
    with quite different dialects of BASIC, and you must do an extensive
    conversion to get a BASIC program written on one machine to run on another
    manufacturer's hardware.

    Notice that this discussion applies specifically to the "core" of C: the
    control structures, data structures, and basic input/output functions.
    Outside of this standard core, however, a number of areas of a C
    implementation are machine-dependent, such as the size of various kinds of
    numbers, keyboard codes, the video screen, graphics, and features of the
    operating system that handle files. To be worth its salt, a C compiler
    that runs on the IBM PC must include functions that give programs access
    to MS-DOS features, the underlying BIOS, and the hardware. Similarly, a C
    compiler for the Macintosh must include functions that give a program
    access to such elements as the machine's system toolbox. These functions
    are hardware-dependent and implementation-specificâ”€â”€by definition, they
    are not portable, but they are essential to getting the most out of your
    machine. C, as you will discover, provides a way to gather the
    machine-dependent parts in an organized manner, something other languages
    can't do.

    BASIC and, to a lesser extent, Pascal approach hardware dependence by
    customizing the language itself to include commands or functions that take
    care of the machine-dependent features. For example, a BASIC statement to
    control the speaker might be called PLAY. Another version of BASIC might
    call it MUSIC. The problem with this approach is apparent when you try to
    convert a program to run on a different machine; you cannot easily find
    the parts of the program that you must change to manipulate proprietary
    features. Also, such hardware-dependent statements may work differently on
    computers with different hardware configurations.

A Modular Approach

    The programmer's task is more manageable with C. Each C compiler includes
    files of definitions, called include files, and collections of precompiled
    functions, called function libraries, which you can use to supplement the
    core of C to take full advantage of the features of a given machine. Your
    QuickC function library includes a rich collection of definitions and
    functions for MDA, CGA, EGA, MCGA, and VGA graphics (as well as Hercules
    graphics, starting with version 1.01); the whole set of MS-DOS function
    calls; and much more.

    The result is that a C programmer has several choices. If you don't need
    graphics or machine-specific features, you can write an ANSI-standard
    text-only C program and easily move it to other machines and operating
    systems. If you do need machine-dependent features in your program, you
    can use the "no-frills" version of the program and then add graphics and
    other hardware-dependent features in easily identified include files and
    libraries. For a particular hardware environment, you can then merge the
    appropriate include files and libraries into your program. Figure 1-1 on
    the following page illustrates the concept of portability.

    Portability requires many trade-offs. In general, the less portable (in
    other words, the more hardware-dependent) a program is, the faster it
    runs, and the more it takes advantage of graphics and other special
    hardware features. On the other hand, the more portable a program is, the
    easier it is to maintain, modify, or convert it to work with new hardware.

    Throughout this book, we point out portability issues and suggest ways to
    deal with them. For example, we note those features of QuickC that are
    compatible with ANSI and UNIX System V. We also look at portability versus
    performance in the MS-DOS world. For example, we discuss alternative ways
    for dealing with devices such as the keyboard and video display on MS-DOS
    machines (standard I/O, console I/O, and BIOS) and point out the
    portability trade-offs involved with each.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚                            â”‚  Not
    â”‚    Customized statements   â”‚  portable
    â”‚                            â”‚
    â”‚â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”‚
    â”œâ”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”¤
    â”‚                            â”‚
    â”‚      MS-DOS and BIOS       â”‚
    â”‚                            â”‚
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚          Hardware          â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    (A)  BASIC--A SNUG FIT BUT NOT PORTABLE


            ANSI/UNIX
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”  Can run on
    â”‚     Standard functions     â”‚  IBM PC, VAX,
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜  Macintosh,
            â”‚        â”‚            and others.
            â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”¤
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”   â–¼    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”  Implementation
    â”‚         â”‚        â”‚         â”‚  of C, such as
    â”‚         â”‚        â”‚         â”‚  Microsoft C or
    â”‚         â””â”€â”€â”€â”€â”€â”€â”€â”€â”˜         â”‚  Quick C.
    â”‚ Machine-specific libraries â”‚
    â”‚â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”‚
    â””â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜
                â”‚
                â–¼
    â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â” â”Œâ”€â”
    â”Œâ”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”˜ â””â”€â”  Specific
    â”‚                            â”‚  machine-
    â”‚      MS-DOS and BIOS       â”‚  IBM PC,
    â”‚                            â”‚  for example.
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚          Hardware          â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    (B)  C--A PORTABLE CORE

    Figure 1-1.  Portability in C.

C Is Powerful

    Portability is desirable, but you also want to write code that takes full
    advantage of the hardware. In this age of drop-down menus, windows, mice,
    and help screens, users expect a lot more out of software than they did
    only a few years ago. As a programmer you are often pushing the limits of
    the hardware, whether in processing speed, I/O, or graphics.

    When it comes to harnessing the hardware, C really shines. For example,
    other languages try to hide the fact that you are manipulating the
    contents of memory when you write code; with C pointers, you can easily
    manipulate memory directly. With Pascal, you can also directly manipulate
    memory with pointers, but the syntax is not as simple or as powerful as
    that of C. And in BASIC, you can use a PEEK and a POKE to access memory,
    but they lack the flexibility of pointers.

    Another important indicator of the power of a language is its ability to
    use machine resources efficiently. All high-level compiled languages
    translate program statements into machine instructions. With most
    languages you have little control over the efficiency of the resulting
    machine instructions. You are at the mercy of the assumptions the compiler
    or interpreter makes about your program and how it will be used. Suppose,
    for example, that your program uses one or two variables frequently in a
    loop that will be executed many times. In C, you declare register
    variables that are stored, if possible, in internal CPU registers; thus,
    delays in loading or retrieving their values in memory are avoided. The
    result is faster execution speed.

    Another important feature of C is its ability to create a variety of
    memory models. A memory model describes the way RAM is used during
    compilation and the way program code and data are shared in RAM. With most
    older BASICs you can use only 64 KB of memory to hold program code and
    data. Today, most MS-DOS machines have at least 256 KB (and often 640 KB
    of memory or more). Thus, newer compilers for BASIC, Pascal, and other
    languages often allow access to a larger amount of RAM. But C compilers go
    a step further: Youâ”€â”€the programmerâ”€â”€decide how the computer will allocate
    memory. Depending on the needs of your program, you can choose to use most
    of the machine's memory for storing compiled instructions, you can use
    most of the memory to store data (such as arrays, structures, or lists),
    or you can allocate varying numbers of 64 KB memory segments to both.
    Figure 1-2 on the following page shows the concepts of register
    variables, pointers, and memory models.

    Pointers, register variables, and memory models are only some of the
    options C gives you for controlling the machine. In addition, most C
    compilers let you improve, or "optimize," the machine code generated from
    your program. You can optimize for program size (a smaller .EXE file) or
    for faster execution or for a combination of these. For example, QuickC
    performs some optimization for you and lets you choose other features as
    appropriate. In addition, you can use QuickC in combination with Microsoft
    C (the professional, industrial-strength C compiler) to provide
    optimization that is truly state of the art.

    Pointers   â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”              â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    for direct â”‚ main ()          â”‚              â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    access to  â”‚ int * ptr; â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”       â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    memory     â”‚ ptr ++; â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”  â”‚       â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚ ...              â”‚   â”‚  â”‚       â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚                  â”‚   â”‚  â”‚       â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚                  â”‚   â”‚  â”‚       â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜   â”‚  â”‚       â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                    Program          â”‚  â””â”€â”€â”€â”€â”€â”€â–ºâ”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                                    â”‚          â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                                                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                                        Memory

    (A)                         POINTERS


    Fast       â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”              â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    register   â”‚ main ()          â”‚â”€â”€â”€â”€â”€â–º CPU    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    access     â”‚ register int i;  â”‚â—„â”€â”€â”€â”€â”€        â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚ ...              â”‚              â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    Regular    â”‚                  â”‚â—„â”€ â”€ â”€ â”€ â”€ â”€  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    memory     â”‚ int regular_varn â”‚  â”€ â”€ â”€ â”€ â”€â–º  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    access     â”‚ ...              â”‚              â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜              â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                    Program                     â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                                                â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                                                â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                                                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                                        Memory

    (B)                     REGISTER VARIABLES


                                    â”Œâ”€â”€â”€â”€â”€â”€â”
                                    â”‚      â”‚
                    â”Œâ”€â”€â”€â”€â”€â”€â”         â”‚ Code â”‚          â”Œâ”€â”€â”€â”€â”€â”€â”
                    â”‚ Code â”‚         â”‚      â”‚          â”‚      â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”        â”œâ”€â”€â”€â”€â”€â”€â”¤         â”œâ”€â”€â”€â”€â”€â”€â”¤          â”‚ Code â”‚
    â”‚ Code â”‚        â”‚      â”‚         â”‚      â”‚          â”‚      â”‚
    â”œâ”€â”€â”€â”€â”€â”€â”¤        â”‚ Data â”‚         â”‚ Data â”‚          â”œâ”€â”€â”€â”€â”€â”€â”¤
    â”‚ Data â”‚        â”‚      â”‚         â”‚      â”‚          â”‚ Data â”‚
    â””â”€â”€â”€â”€â”€â”€â”˜        â””â”€â”€â”€â”€â”€â”€â”˜         â””â”€â”€â”€â”€â”€â”€â”˜          â””â”€â”€â”€â”€â”€â”€â”˜

    (C)                        MEMORY MODELS

    Figure 1-2.  C gives you control of the machine.

C Is Extensible

    C also lets you customize the contents of include files and libraries so
    that they contain only the definitions and functions your program needs.
    These custom files can contain functions for anything from manipulating a
    database to formatting text. After you write and test these definitions
    and functions, your main program can use them as easily as it can use the
    standard include files and libraries provided with your compiler. On large
    real-world programming projects, teams of programmers can receive
    specifications for each set of routines needed, and each team can create
    resources that can be used anywhere in the project. Although most
    languages offer a version of this building-block methodology, the C
    approach is the simplest, the most flexible, and the easiest to use.

    The very popularity of C enhances the value of such language extensions.
    Hundreds of vendors have created C function libraries for almost every
    imaginable task. Figure 1-3 shows conceptually how you can use function
    libraries from both QuickC and other vendors in your programs. You can
    easily integrate vendor libraries into your own code, and because they are
    the products of professional C programmers, they are likely to be fast and
    efficient. You can almost always avoid the age-old problem of reinventing
    the wheel.

                                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                                â”‚  MS-DOS  â”‚
                                â”‚     â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                                â”‚     â”‚   I/O    â”‚
                                â”‚     â”‚     â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                                â””â”€â”€â”€â”€â”€â”‚     â”‚ Graphics â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”                â”‚     â”‚          â”‚
    â”‚             â”‚                â””â”€â”€â”€â”€â”€â”‚          â”‚
    â”‚ Included  â—„â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”‚          â”‚
    â”‚ definitions â”‚                      â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ â”‚
    â”‚ Your code   â”‚                              Third-           Your
    â”‚ main ()     â”‚           Microsoft          party            custom
    â”‚ ...         â”‚           libraries          libraries        library
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜           â”Œâ”€â”â”Œâ”€â”â”Œâ”€â”          â”Œâ”€â”â”Œâ”€â”           â”Œâ”€â”
            â”‚ Compile          â”‚ â”‚â”‚ â”‚â”‚ â”‚          â”‚ â”‚â”‚ â”‚           â”‚ â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”       â””â”€â”˜â””â”€â”˜â””â”€â”˜          â””â”€â”˜â””â”€â”˜           â””â”€â”˜
    â”‚ Compiled Modules  â”‚â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜  â”‚               â”‚             â”‚
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤              â”‚               â”‚             â”‚
    â”‚ Standard Library  â”‚â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜               â”‚             â”‚
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤                              â”‚             â”‚
    â”‚ Graphics          â”‚â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜             â”‚
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤                                            â”‚
    â”‚ Database          â”‚â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚ Special functions â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
            â”‚ Link
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚   Ready-to-run    â”‚
    â”‚      program      â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 1-3.  Using include files and libraries.

C Is Structured

    The syntax of the C language itself supports structured programming. C
    provides the control structures of a modern structured language, such as
    if/then/else, for, while, while...do, and switch. (The last is like
    Pascal's case statement.) If you are experienced in Pascal or in one of
    the newer BASICs (such as Microsoft QuickBASIC), you will find these
    control structures conceptually familiar. However, you will have to learn
    syntax differences for C, and boxes in the text point these out. If you
    are used to one of the older BASICs, you will be pleasantly surprised at
    how these structures enable you to avoid nearly all goto statements that
    lead to disorganized "spaghetti code."

C Is Concise

    Although C is a well-structured language, it encourages concise rather
    than verbose statements. For example, it uses braces to begin and end
    blocks of code, rather than Pascal's begin and end. C provides shorthand
    operators for assigning values to variables and for incrementing
    variables. To show the flavor of C, the following table presents a few
    comparisons of C, Pascal, and BASIC assignment statements:

    Some Comparisons of BASIC, Pascal, and C
                            BASIC           Pascal           C
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    1. Set a, b, and c to 0  a = 0           a := 0;          a = b = c = 0;
                            b = 0           b := 0;
                            c = 0           c := 0;
    2. Set i to i + 1        i = i + 1       i := i + 1;      i++;
    3. Set a to a + 5        a = a + 5       a := a + 5;      a += 5;
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Such conciseness speeds the typing of programs and makes C source files
    more compact and easier to edit. C functions are more accessible than
    their Pascal counterparts and much more efficient than the awkward
    subroutine mechanism of BASIC. With the C preprocessor, you can create
    your own shorthand, or macro, definitions with which you insert
    expressions or whole blocks of code in text by typing the name of the
    definition.

    This brief overview of the general features of C should suggest why the
    language is so popular. Let's now look more closely at the product with
    which this book is concerned, Microsoft QuickC, and see how its particular
    features and advantages make programming in C even more attractive.


Why QuickC?

    Traditionally, C has had one big drawback compared with interpreted
    languages such as BASICâ”€â”€a complex compilation and debugging process. You
    probably know that C is a compiled language, and MS-DOSâ”€based compiled
    languages traditionally have required that you go through a lengthy series
    of steps to produce an executable file.

    The steps to compiling a traditional C program are the following:

    1.  Start a text editor or word processor and write a program.

    2.  Save the program to disk and exit the editor.

    3.  Run the compiler program by issuing a command line from the DOS
        prompt, usually with several filenames and options included, that tell
        it, for example, what memory model to use and whether to generate a
        listing file.

    4.  Look at the listing produced by the compiler, and study every error
        message.

    5.  Print out this error list for reference.

    6.  Start the editor again, open your C program file, and for each error
        try to find the exact line in which the error occurred and correct the
        program.

    7.  Go back to step 3 and try again until the program compiles without
        errors into an object code file.

    8.  Now run the linker, and tell it what libraries to combine with your
        object code file to produce an executable program (an MS-DOS .EXE
        file). If you used an incorrect function name or failed to specify the
        correct libraries, you will now get a new batch of error messages,
        this time from the linker. (They may, for example, report an
        "unresolved external," which probably means the name you used for a
        function in your code did not match the name of the function defined
        in the library.) To fix these errors, you may need to look at listings
        of include files. Or you may have to go back to the editor and correct
        your program. In any case, you must recompile and then try to link
        again.

    9.  When the code links without errors, you can finally run the program.
        Did it execute as you expected? No? Do you want to make some changes?
        Well, go back to the editor and try again.

    Just reading through these steps suggests how tedious a traditional
    compiled language can be. With interpreted languages, such as BASIC, LOGO,
    or HyperTalk, you can type a line or two of code, execute it immediately,
    and see the results. If your line of code contains errors or if you want
    to add or change something, the interpreter usually provides a simple text
    editor or line editor you can use immediately.

    But interpreted languages have one critical drawbackâ”€â”€they're slow. Each
    line in a program in an interpreted language has to be translated into
    machine-executable instructions each time it is encountered. Therefore,
    only the simplest interpreted-language applications run fast enough for
    use in the real world.

    The philosophy behind QuickC is to provide a programming environment that
    is as easy to use as an interpreter, but with the execution speed
    obtainable only through a compiler. With QuickC, writing and testing
    programs is so easy that C can be a beginning programmer's first language.

The QuickC Programming Environment

    With QuickC, you do all of your program development in and from the same
    placeâ”€â”€the QuickC integrated programming environment. (Figure 1-4 shows
    the way your screen looks when you start QuickC.) This environment offers
    many advantages:

    1.  You can open a file for editing by using the Open command on the File
        menu, or you can simply start typing a new program. The QuickC
        full-screen editor is immediately available, with insert/delete,
        cut/paste, indentionâ”€â”€all the features you need to type a program as
        easily as you type a letter with a word processor. And you never
        really "leave" this editor. You merely select whatever service you
        need from the menus.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 1-4 can be found on p.12 of the printed version of the book.    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 1-4.  The initial QuickC screen.

    2.  To run the program you can click on the mouse or type a command. When
        you work with a program that has not yet been compiled, the compiler
        and linker are called as needed. There are no complex command-line
        options to type. If your program is error free, the program runs in
        seconds on the output screen.

        The main reason your programs compile, link, and run so quickly with
        QuickC is that, unlike traditional C compilers that compile and link
        to disk, QuickC by default compiles to memory. Thus, it can compile
        10,000 lines a minute on a standard IBM PC/AT. Another reason is that
        some of the most commonly needed functions are held in memory. You
        also can create libraries that can be loaded into memory. The result
        is that QuickC uses available memory very efficiently.

    3.  As you view an error message, the cursor follows along through your
        program text; you can instantly correct each error with the built-in
        editor. No printed listings to pore over; no error numbers to look up!

    4.  Suppose your program compiles correctly but doesn't work as you
        expected. Without leaving QuickC, you can turn on the debugging and
        trace features, rerun your program, and then watch the changing values
        of selected variables, follow the flow of execution, and check the
        values being passed to and from functions called by your program.

        What about multiple-module programsâ”€â”€C programs that have several
        separately compiled libraries and code files? Traditionally, you had
        to run a special "make" program and give it a file with a unique
        syntax that told the compiler how to rebuild such a complex program
        after any change was made. With QuickC's program list feature, you
        simply tell QuickC what libraries and source code files you want to
        use. QuickC keeps track of all the other details, such as the
        relationship between modules and the date each module was last
        compiled.

    5.  Do you need access to MS-DOS? Need to make a new directory or back up
        some programs? Maybe you want to run some previously compiled C
        programs from MS-DOS. With a traditional, command-line-driven C
        compiler, you exit the compiler, work in MS-DOS, and then run the
        compiler again and figure out where you left off. With QuickC, you
        never leave the integrated programming environment. Using QuickC's DOS
        Shell feature, you exit to MS-DOS, take care of your business, and
        return to QuickC where you left off.

    You can select many other features from the QuickC programming environment
    in the same easy way. With a command-line compiler, most features require
    that you type obscure flags or option switches on the command line or
    create batch files to simplify complicated compiler commands. With QuickC,
    you select with a mouse click or keystroke such features as the error
    warning level, language extensions, and optimization. But don't let the
    convenience deceive youâ”€â”€underneath the covers, QuickC is constructing the
    proper list of options so that you can use the same linker. (QuickC also
    includes a command-line-driven compiler for those times you have a special
    need, such as compiling under certain memory models, or when you want to
    work outside the QuickC environment.)

QuickC Performs

    QuickC is faster in almost all cases than its nearest competitors, and it
    beats them hands down in floating-point operation.

    QuickC also is fully compatible with its "big brother," the Microsoft C
    Optimizing Compiler, versions 5.0 and later. Any program that compiles
    under QuickC compiles under Microsoft C, version 5.0. Therefore, you can
    develop programs with QuickC and then effortlessly recompile them under
    Microsoft C for fine tuning, using a variety of optimization techniques.

QuickC: Standard and Comprehensive

    Earlier we discussed ANSI and other official standards for C. There are
    also unofficial industry standards that are almost as important. When you
    use QuickC, you have the benefits of using a compiler that has become the
    industry standard for PCs: Microsoft C. QuickC is fully compatible with
    that standard. Thus, dozens of third-party C code libraries work with your
    programs because the programs you write are compatible with the ANSI or
    UNIX System V standards or with the MS-DOSâ”€specific features of
    Microsoft C.

    The extras that come with the QuickC product are also impressive. Each
    standard-model library (small, medium, compact, large) supports the 8087
    coprocessor. There are libraries for every kind of PC graphics from
    monochrome and CGA to the latest VGA graphics for the IBM PS/2. The QuickC
    Graphics Library routines feature easy-to-use routines for drawing points
    and lines and manipulating complete images, including filling and
    animation, all with impressive speed. QuickC also has libraries that allow
    your programs complete access to MS-DOS and BIOS calls. And, because of
    QuickC's UNIX compatibility, you can also use UNIX System V functions for
    writing programs that can be ported to work in the UNIX environment.


Hardware Requirements

    To run QuickC you need an IBM PC/XT, PC/AT, PS/2, or compatible computer
    with at least 448 KB of RAM and at least two floppy-disk drives. We
    suggest, however, that you develop QuickC programs on a hard disk.
    Compiling or linking to disk with floppy disks is time-consuming compared
    with hard disks. Also, fitting all the files you need for developing
    programs onto two disks can be tricky. But because some of you will be
    using floppy-disk-based systems, we will give you some tips later that
    should help you make the best of the situation. (And the situation is
    anything but grim: You can certainly develop programs that run great under
    QuickC on a floppy-based system.)

    We also recommend (but don't presuppose) that you use QuickC with a
    compatible mouse. You can handle all QuickC functions from the keyboard,
    but why get bogged down learning the keystroke combinations? With a mouse
    in hand, you simply point at what you want and select it.

    On the other hand, many people don't have (or choose not to use) a mouse.
    With QuickC, you can use short keystroke combinations. For example,
    Alt-r-s selects the Run menu's Start option to compile and run a program.
    (Even if you have a mouse, typing is sometimes faster.)

    Graphics capability is optional for most of this book. Chapter 15, which
    deals with graphics, requires a CGA, of course; for advanced graphics, you
    need an EGA; and the VGA section requires a PS/2, or a VGA board for older
    PCs. (If you have the new VGA, you also have CGA and EGA capability.) Even
    if you have only the basic monochrome adapter, you can create many
    interesting QuickC programs with the built-in IBM graphics character set.

    Finally, we recommend that you have a printer (although a printer is not
    required for this book).


Knowledge Requirements

    Some programming experienceâ”€â”€with BASIC or Pascal, for exampleâ”€â”€will help.
    But thanks to the ease of use of QuickC, C can be your first programming
    language, although you may have to work a bit harder than more experienced
    programmers.

    Because many of you have programmed in BASIC (such as Microsoft's BASICA
    or QuickBASIC) or Pascal (Borland's Turbo Pascal, for example), we scatter
    "asides" throughout the text for BASIC and Pascal programmers. These point
    out the ways in which C is similar to and different from those languages.
    Familiarity with another language is a two-edged sword when it comes to
    learning C. On the one hand, you already know many programming concepts
    used in C. On the other hand, differences in syntax and usage can trip you
    up if you aren't careful.

    If you are a UNIX programmer, you will feel right at homeâ”€â”€as soon as you
    get used to QuickC's much more comfortable living room! The QuickC
    environment is far easier to use than the UNIX cc compiler and ln linker,
    and you won't have to write any make scripts. You probably already know
    the fundamentals of C, but watch out for features that are different in
    the IBM PC/MS-DOS environment, especially graphics and MS-DOS system
    calls. But as we noted, with a few minor exceptions, Microsoft C supports
    the standard I/O and other library functions used on UNIX systems.
    Occasional boxes point out matters of interest to UNIX programmers.


Conventions and Style

    We have chosen the following typographical conventions for the
    descriptions of a C program in the text:

    â–   Names of ordinary (local) variables are lowercase italic. Example:
        count, sum

    â–   Names of external or global variables are also italic, but the first
        letter is capitalized. Example: Model

    â–   Underscores join the words of multiple-word variable names. Example:
        Grand_total (an external variable) or line_count (an ordinary variable)

    â–   Constants created with #define are uppercase italic. Example: PI

    â–   Macro definitions are uppercase italic. Example: PRINT_ERROR(MSG)

    â–   Function names are lowercase italic. Underscores join multiple-word
        function names. Examples: main(), count_lines(), printf()

        You'll also notice that names of Microsoft library functions that are
        non-ANSI-standard (such as the graphics functions) are lowercase italic
        and preceded by an underscore. Example: _getvideoconfig() (a Graphics
        Library function)

    â–   In #include statements, names of header files that we create are in
        double quotation marks. Example: #include "chr_graphics"

        Names of header files provided by Microsoft are in angle brackets.
        Example: #include <graphics.h> (This convention affects the way in
        which the compiler searches for header files on disk.)

    â–   Built-in "keywords," or reserved words, of the C language are lowercase
        italic. Examples: int, do, while

    â–   Program names are uppercase roman. Example: HELLO.C

    â–   Filenames and pathnames are uppercase roman. Examples:
        \LIB\GRAPHICS.LIB, SCREEN.DAT

    â–   Names of special keys are spelled as they appear on the standard IBM PC
        extended keyboard. Examples: Enter (not Return), Ctrl-C, the Esc key

Program Listings

    Program listings are set off from the text in a monospace font. Constants,
    variables, and function names are capitalized as indicated in the
    preceding list but are not italicized.

    In many cases, we provide a sample session that demonstrates how a program
    interacts with the user. In these listings, user input is italic.

    guessâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Run the guess.c program
    What number am I thinking of?â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Program response
    7â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€User input
    Wrong! Try Again?
    3
    Right! You win!

    NOTE: The comments at the right in the sample session above are not part
    of actual program dialogue.

Program Style Conventions

    A clear, consistent typographical style makes programs easier to read. No
    single style is universally accepted for C program listings. Ultimately,
    you fashion your own, based on your judgment and the prevailing usage. In
    some cases, more than one kind of syntax can be used. Although C itself
    doesn't care about spacing between the elements of a statement or an
    expression, we use a space between elements unless removing the space is
    clearer. Also, we use a 4-space indention for nested statements and the
    braces that enclose them.

    We always align braces ({ and }) verticallyâ”€â”€a major stylistic departure
    from Kernighan and Ritchie. That is, we put

    function_name()
    {
    <body of function>
    }

    rather than

    function_name() {
    <body of function>
    }

    We believe this style enables you to read the listings and identify blocks
    of code more easily. Be warned, however, that you will find lots of C
    listings that contain the second style.

    Finally, because experienced C programmers often make a virtue of saying a
    lot with a little, we point out concise, idiomatic coding styles that you
    are likely to see in program listings from various sources, and we
    sometimes show two or more ways to code a statement.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€