Chapter 2  Starting with QuickC

    You are now ready to explore the QuickC environment. In this chapter we
    describe the environment, show how to set up QuickC on your computer
    system, present an overview of the QuickC menus and dialog boxes, and help
    you create and run your first QuickC program. We also show how to get help
    from QuickC and how to fix program errors. When you finish this chapter,
    you will be comfortable with QuickC and ready to learn the C language
    itself.


Our Book and Their Book

    QuickC comes with an excellent user manual that details the mechanics of
    using QuickC. It explains how to configure the system, how to use the
    menus, the meaning of the options in each menu and dialog box, and how to
    use the programs that comprise the QuickC programming tools. The QuickC
    package also includes two reference guides, the Microsoft QuickC Language
    Reference and the Microsoft QuickC Run-Time Library Reference. The first
    guide describes the rudiments of the C language; the second provides
    specific information for using each of the more than 350 C library
    routines.

    Our book is designed to complement the QuickC user manual by focusing on
    teaching C programming with QuickC rather than rehashing operational
    details from the manual. However, because you need to master QuickC's
    features to write effective C code, we sometimes present a brief overview
    of a procedure or subject and then refer you to the manual for a complete
    discussion. We use this approach particularly when we discuss system setup
    and configuration, for which the manual provides extensive and detailed
    guidance.

    We also do not discuss all the editor commands and keystrokes. You can
    learn these from the QuickC manual and through one of QuickC's excellent
    help screens. However, when we know of some useful tricks that aren't
    covered in the manual, we pass them along immediately.


Directories and Files Used by QuickC

    Programming in C usually involves combining several files to eventually
    form an executable program. These files include definitions of data
    structures and functions (header files), libraries of precompiled
    functions, and your own program code. The QuickC environment uses several
    directories to organize the files into distinct groups, according to
    purpose, such as function libraries, include files, and so on. QuickC also
    uses distinctive filename extensions to identify files that are used or
    created in the compiling and linking process.

Why So Many Files?

    If you use languages such as BASIC or some versions of Pascal, you might
    wonder why QuickC needs such an elaborate system of files and directories.
    With most versions of BASIC, for example, you need only two files: the
    BASIC interpreter program that creates and runs your programs, and the
    file that contains your BASIC program. Although the QuickC environment can
    look quite complicated by comparison, QuickC sets up most of the
    directories and files for you (especially if you have a hard disk) and
    makes it easy for you to move among all the files of a programming
    project. Nevertheless, it is important to understand how QuickC organizes
    files, especially if you need to modify the default organization to avoid
    conflicts with existing directories or for some similar reason.

    To explain the "environment" you work in, we must examine QuickC's
    directories and the files they contain. We use the QuickC default names in
    our discussion, because the actual name and location of the directories
    depend on how you invoke the SETUP program and whether you use a
    floppy-disk or hard-disk system.

Base Directory and Subdirectories

    QuickC installs directories as subdirectories of a "base" directory. If
    you use QuickC by itself, the base directory usually is c:\qc; if you use
    QuickC as part of the Microsoft C 5.0 Optimizing Compiler package, the
    command is usually c:\c5\qc. Thus the actual pathname for the \BIN, or
    base, directory probably is C:\QC\BIN or C:\C5\QC\BIN.

    The most important QuickC directories are \BIN, \INCLUDE, and \LIB. Let's
    look at these and some optional directories that you might find useful.

The \BIN Directory, Compiler, and Linker Programs

    The \BIN directory contains the program QC.EXE, which runs QuickC,
    provides the integrated programming environment, and lets you write,
    compile, link, and execute QuickC programs. (The name "BIN," by the way,
    is short for "binary." The \BIN directory is usually reserved for "binary
    files," or files containing executable programs.)

    The QuickC package actually contains two compiler programs: QC.EXE, which
    comprises the integrated programming environment with its editor, menus,
    and so on; and QCL.EXE, a much shorter program, which generates a
    "command-line" version of the QuickC compiler. (To help you distinguish
    between the programs, think of QCL as "QuickC Line-oriented.") QCL is much
    like the traditional C compiler we described in the Introduction. Rather
    than using menus and dialog boxes, you can compile a program only by going
    to the MS-DOS prompt and typing a command line with options. Another
    program in the \BIN directory, called LINK.EXE, combines your compiled
    programs and stand-alone libraries into a single executable program.
    QuickC usually performs this linking as an invisible process, although
    you can specify linker options when necessary. When you use QCL, you
    control the linker directly with a series of command-line options.

    QC.EXE, with its integrated programming environment, is more convenient to
    use, and we assume in most parts of this book that you will use it to
    compile and run your programs. However, the command-line compiler QCL.EXE
    is very useful for doing what are called batch compilations, for setting
    specific combinations of compile options, for compiling with alternate
    memory models, or for using an alternative program editor with QuickC. QCL
    also lets you use "make" files created with the Microsoft C Optimizing
    Compiler, version 4.0 or 5.0. (Make files are files that keep track of the
    compilation of multiple program modules. QuickC offers an easy-to-use
    alternative called "program lists," which we discuss in Chapter 6.)

The \INCLUDE Directory and Header Files

    The "core" of C is greatly extended by compiler vendors who develop new
    sets of predefined constants, macros, data structures, and functions for
    such areas as graphics, device I/O, and DOS. Some of these are standard
    (proposed ANSI standard or UNIX System V standard) and are found in
    virtually all compilers; others are specific to the IBM PC or to
    Microsoft. The QuickC \INCLUDE directory contains many text files of both
    types. These are known as "include files" because your program can include
    definitions from one or more of these files. (They are also known as
    "header files," because their names must be specified at the beginning, or
    head, of a program.) This is also where you'll put any third-party
    libraries you obtain.

    Include files are not executable files or complete C source programs; they
    are ordinary text files that contain useful function definitions; they
    provide an interface between your program and the compiled code in
    stand-alone libraries. When a program references an include file, the code
    in the include file is inserted into and compiled with the code you
    actually typed in.

    For example, the include file stdio.h contains many of the most commonly
    used input and output functions, and graphics.h contains definitions for
    data structures and functions in the Graphics Library. The following table
    lists the standard QuickC include files. Note that include files have
    filenames with the .h extension. (Don't worry about understanding this
    comprehensive list yet; we will discuss many of them in detail as we use
    them in programs throughout the book.)

    QuickC Include Files
â•“â”Œâ”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â•–
    File       Main Purpose
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    assert.h   Debugging expressions
    conio.h    PC-specific console (keyboard) and port (device) I/O
    ctype.h    Character testing and conversion
    direct.h   Creating, removing, and changing MS-DOS directories
    dos.h      Setting and reading 8086 registers for MS-DOS calls
    errno.h    System-wide error numbers
    fcntl.h    Opening MS-DOS files with various modes
    float.h    Implementation-dependent values for advanced floating-point
    File       Main Purpose
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    float.h    Implementation-dependent values for advanced floating-point
                operations
    graph.h    Microsoft-specific data structures and functions for monochrome
                (MDA), CGA, EGA, MCGA, and VGA graphics
    io.h       Low-level file-handling and I/O routines
    limits.h   Implementation-dependent values for sizes and ranges for data
                types, etc.
    malloc.h   Memory allocation functions
    math.h     Definitions used by math library
    memory.h   Memory manipulation routines (buffer setup, etc.)
    process.h  Used with routines that allow a program to "spawn" (run)
                another program as a "child process"
    search.h   Sorting and searching routines
    setjmp.h   Used for saving and restoring the program state during a "long
                jump" (jump to a different memory segment)
    share.h    Flags controlling sharing of a file among several users (i.e.
                on a network)
    signal.h   Values for "signals" that can be sent to interrupt handlers,
                etc.
    File       Main Purpose
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
                etc.
    stdarg.h   Allows a function to use a variable number of arguments (ANSI
                style)
    stddef.h   Miscellaneous constants, types, and variables
    stdio.h    UNIX-compatible standard I/O, such as functions to get and put
                characters to the console or a file
    stdlib.h   Definitions for miscellaneous library functions
    string.h   Definitions for string manipulation functions
    time.h     Data structures used for accessing system time
    varargs.h  Allows a function to use a variable number of arguments
                (XENIX-style)

    The \SYS subdirectory of \INCLUDE contains:
    locking.h  Flags for locking files (for networks)
    stat.h     Defines structure used to return status of an MS-DOS file or
                directory
    timeb.h    Types used by ftime() (used to get current time)
    types.h    Types used in values returned by functions for time and file
                status information
    File       Main Purpose
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
                status information
    utime.h    Used by utime() to update access and modification times for
                MS-DOS files
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€


    In QuickC, the \INCLUDE directory also contains a subdirectory called
    \SYS. This subdirectory contains "system specific" include files for IBM
    personal computers and compatibles.

The \LIB Directory and Libraries

    Much of C programming involves writing code that uses standard C functions
    to perform such tasks as getting a character from the keyboard or sending
    a text string to the screen. Microsoft has already compiled these
    functions for you and has placed them in files called "libraries." The
    \LIB directory contains these library files, which have either the
    filename extension .LIB or .QLB. As noted earlier, when QuickC starts, it
    includes in memory the code for a considerable number of commonly used
    functions. In addition, Microsoft provides "Quick Library" versions of
    some libraries, and you can specify that these be loaded as well to
    provide fast, in-memory access. You can also create your own custom Quick
    Libraries. Quick Libraries all have the same extension .QLB.

    If you examine the PACKING.LST file on the QuickC Product disk, you will
    see many libraries with similar names, such as SLIBC.LIB, SLIBFP.LIB, or
    MLIBC.LIB. Why are there so many libraries? The architecture of the Intel
    8086 and 80286 processors used by the IBM PC family requires that memory
    be divided into 64 KB segments. As a result, special instructions are
    needed to access program instructions or data that go beyond a single
    segment. The designers of C compilers address this problem by providing
    programmers with multiple memory models, each containing a different
    allocation of segments for code and data. (QuickC uses compact, small,
    medium, and large memory models. Microsoft C 5.0 adds a "huge" model.)
    Additional libraries handle floating-point (decimal) calculations: Some
    use the 8087 floating-point coprocessor chip, others use software that
    emulates its functions. Also included is an optional graphics library,
    GRAPHICS.LIB.

    Combined Libraries

    You can use libraries in two ways. When you compile, you can tell the
    linker to include specified libraries (a memory-model library, a
    floating-point library, a graphics library, and so on). Although this is
    most easily done using a "program list," it can involve a bit of
    bookkeeping. The easier way to use libraries is to use the SETUP program
    (discussed later in this chapter), to build one or more combined
    libraries. A combined library is a package that contains one library for
    the floating-point option, one standard library for the specified memory
    model, some general purpose "helper" libraries, and possibly the optional
    GRAPHICS.LIB. The advantage of creating a combined library is that QuickC
    uses it by default, so you don't have to specify library names when you
    compile and link. The \LIB directory contains any combined libraries you
    create with the setup process.

    Note: If you intend to write graphics programs, use SETUP to combine the
    Graphics Library with your standard library. That way, QuickC always
    includes this library in compilations.

The \TMP Directory

    QuickC uses the \TMP directory to store temporary files created during
    compilation. Normally, QuickC removes these files when it finishes with
    them. However, if something "hangs" the system during a compile, you might
    want to check the \TMP library and delete any vestigial files.

The \SAMPLE Directory

    If your computer has a hard disk, the QuickC SETUP program creates a
    \SAMPLE directory and stores in it several example programs. You can use
    these to practice loading, editing, compiling, and running QuickC
    programs.

The \PROG or \SOURCE Directory

    By default, QuickC stores your programs in the current directory when you
    invoke the compiler. All other files created by the compiling and linking
    process are also stored there. You also can create directories to store
    the source code (the actual program text) for the C programs you write and
    the various files made from your program by QuickC. Although this is
    entirely optional, it makes for a more orderly directory and helps you
    organize and find your programs more easily.

    Whatever your current directory, compiling programs creates the following
    kinds of files, depending on the compiler and linker options you select:

    NAME.Câ”€â”€Source code for the C program name

    NAME.OBJâ”€â”€Object code produced by the compiler for the C program name

    NAME.MAPâ”€â”€A "map" file showing the addresses used by the linker when it
    linked the program name

    NAME.EXEâ”€â”€The compiled and linked object code for the program name, which
    can be executed by typing name at the MS-DOS prompt

    NAME.MAKâ”€â”€A "make" file containing instructions that QuickC uses to
    recompile or "rebuild" your program if you change it

    Figure 2-1 summarizes our tour of QuickC directories and files. Without
    listing all the QuickC files, the chart shows a typical directory
    structure for QuickC on a hard disk. (The structure of directories on a
    floppy-disk system has several modifications that we will describe in the
    section "Setting Up QuickC for Floppy-Disk Systems" on page 32.)

                                                    C:\
                                                â”€â”€â”¬â”€â”€
                                                    â”‚
                                                    â”‚
                                                c:\qc
                    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
                    â”‚                     â”‚                     â”‚
                c:\qc\bin             c:\qc\lib           c:\qc\include
            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”         â”€â”€â”€â”€â”¬â”€â”€â”€â”€         â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
            â”‚                 â”‚             â”‚             â”‚                â”‚
    c:\qc\bin\sample       qc.exe      mlibce.lib     assert.h    c:\qc\include
    â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€      qcl.exe      slibc7.lib      bios.h     â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€
            â”‚               qc.hlp     graphics.lib    conio.h             â”‚
        cflow.c          link.exe     graphics.qlb     (etc.)         locking.h
    new-conf.sys        lib.exe        (etc.)                        stat.h
    new-vars.bat                                                     (etc.)

    Figure 2-1. Typical directory structure for QuickC.

From Source to Object: An Overview

    Now that we've surveyed the compiler, linker, include files, and
    libraries, let's see how they work together when you run a program with
    QuickC. Let's assume your program uses two include files, stdio.h and
    graph.h. When you "run" or "start" the QuickC compile/link phase, the
    compiler starts by "reading" your source code in the editor buffer. First,
    it sees the instructions to add the include files. The compiler then loads
    the stdio.h file and compiles the code found there. (The code in an
    include file is not already compiled.) Next it loads and compiles graph.h.
    These include files contain, among other things, definitions of functions
    whose compiled code resides in libraries. (The standard library for each
    memory model contains the code corresponding to standard header files such
    as stdio.h; GRAPHICS.LIB contains graph.h.) As it compiles the include
    file, the compiler notes these references to library code and passes them
    to the linker.

    After the compiler generates the object code for the part of the program
    you wrote yourself, the linker "resolves" all library references: It
    extracts the "modules" that contain the necessary code from the
    appropriate libraries and combines them with the rest of the code. The
    result is a compiled object program. QuickC's default creates an object
    program that runs from within the QuickC environment. This enables you to
    run the program immediately after you link it and lets you quickly test
    programs without leaving the QuickC environment. However, you can also
    create a .EXE file, or executable MS-DOS file, that you can run from the
    MS-DOS prompt. Figure 2-2 on the next page summarizes this process
    graphically.

                    Editor
                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    Program    â”‚ #include stdio.h  â”‚
    references â”‚ #include graph.h  â”‚
    include    â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€      â”‚
    files      â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€      â”‚
                â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€      â”‚
                â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€      â”‚
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                        â”‚
                        â”‚     Preprocessor     â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”            â”‚stdio.h   â”‚
    Included â–’ â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€       â”‚     â”Œâ”€â”€â”€â”€â”€ â”‚ â”€â”€â”€â”€â”€    â”‚
    source   â–’ â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€       â”‚     â”‚      â”‚ â”€â”€â”€â”€â”€    â”‚
    code â”€â”€â”€ â–’ â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€       â”‚â—„â”€â”€â”€â”€â”˜      â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚                   â”‚â—„â”€â”€â”€â”€â”      â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    Your â”€â”€â”€ â–’ â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€       â”‚     â”‚      â”‚graph.h   â”‚
    source   â–’ â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€       â”‚     â””â”€â”€â”€â”€â”€ â”‚ â”€â”€â”€â”€â”€    â”‚
    code       â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜            â”‚ â”€â”€â”€â”€â”€    â”‚
                        â”‚                      â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                        â”‚     Compiler
                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    Compiled â–’ â”‚ ---------â”€â”€â”€?     â”‚
    library  â–’ â”‚ ---------â”€â”€â”€?     â”‚
    references â”‚                   â”‚
                â”‚                   â”‚
    Your â”€â”€â”€ â–’ â”‚ ------------      â”‚
    compiled â–’ â”‚ ------------      â”‚
    code       â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                        â”‚
                        â”‚     Linker
                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”          â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    Final      â”‚ -----------       â”‚          â”‚ Libraries   â”‚
    object     â”‚ -----------       â”‚â—„â”€â”€â”€â”€â”€â”€â”€â”€â”€â”‚ (combined   â”‚
    program    â”‚ -----------       â”‚          â”‚     or      â”‚
    (in memory â”‚ -----------       â”‚          â”‚ separate)   â”‚
    or .EXE)   â”‚ -----------       â”‚          â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚ -----------       â”‚
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-2. Compiling and linking with include files and libraries.


Running the QuickC SETUP Program

    Microsoft distributes QuickC on five floppy disks. These disks and their
    hundreds of files contain the two compilers (integrated-environment and
    command-line), a full set of libraries for each memory model with a choice
    of 8087 hardware or emulation, a rich assortment of more than 30 include
    files, several utility programs, and many other goodies. The QuickC SETUP
    program lets you set up a working QuickC environment with directories
    containing only those files that you need and provides automatic access to
    directories as you specify.

    SETUP performs the following operations:

    â–   Sets up variables and commands in the MS-DOS environment that tell the
        operating system where to find all QuickC programs and files

    â–   Sets up a home directory for QuickC, creates the \BIN, \INCLUDE, \LIB,
        and \TMP subdirectories, and moves files from the floppy disks to these
        directories

    â–   Creates one or more combined libraries, depending on the memory
        model(s) and form of floating-point support you specify

    Note: SETUP for a floppy-disk system creates only the combined library.
    You must do the rest partly "by hand." See the section "Setting Up QuickC
    for Floppy-Disk Systems" on page 32.

MS-DOS Variables and QuickC

    As we mentioned above, QuickC sets up and uses some MS-DOS commands and
    variables. MS-DOS uses variables (sometimes called MS-DOS "environmental"
    variables) to specify the location of system resources. When you boot an
    MS-DOS disk, the operating system calls on two files to configure the
    system: AUTOEXEC.BAT and CONFIG.SYS. Commands in these files control the
    environment that QuickC uses when you run it.

    When you run the SETUP program for a hard-disk system, QuickC sets
    environmental MS-DOS variables in two files: NEW-VARS.BAT and
    NEW-CONF.SYS. You can use these files as is or insert their contents into
    the AUTOEXEC.BAT and CONFIG.SYS files respectively. We recommend the
    latter procedure unless there are serious conflicts with your existing
    settings.

    You can use any editor (such as SideKick or EDLIN) to insert NEW-VARS.BAT
    in your AUTOEXEC.BAT file. If you have no AUTOEXEC.BAT, use MS-DOS to
    rename NEW-VARS.BAT as AUTOEXEC.BAT. The resulting file might look like
    this:

    setclockâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Set system clock
    fastopen c:â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Install file access cache
    skâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Run SideKick
    set PATH=c:\;c:\wp;c:\c5\bin;c:\qc\bin;a:\â”€â”€â”€Combined with your old path
    set INCLUDE=c:\qc\include
    set LIB=c:\qc\lib
    set TMP=c:\qc\tmp

    After you insert the SET commands found in NEW-VARS.BAT, you will probably
    have two PATH= commands in your AUTOEXEC.BAT file. Combine the directories
    in the path provided by SETUP with your existing path, as shown in Figure
    2-3. You can usually use the rest of the SET commands without
    modification. (By default, MS-DOS permits only 128 bytes of space for
    storing MS-DOS variable values.) If this amount proves insufficient,
    modify it as described in the sidebar on the next page.

        AUTOEXEC.BAT               NEW-VARS.BAT
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”     â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚     â”‚set PATH=c:\qc\bin    â”‚
    â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚     â”‚set INCLUDE...        â”‚
    â”‚ set PATH=c:\     â”‚     â”‚set LIB...            â”‚
    â”‚                  â”‚     â”‚set TMP...            â”‚
    â”‚                  â”‚     â”‚                      â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
            â”‚                          â”‚
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                        â”‚
            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
            â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€                â”‚
            â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€                â”‚
            â”‚ set PATH=c:\; c:qc\bin â—„â”€â”€â”€â”¼â”€â”€â”€â”€ Combined paths from
            â”‚ set INCLUDE=c:\qc\include  â”‚â–’    AUTOEXEC.BAT and NEW-VARS
            â”‚ set LIB=c:\qc\lib          â”‚â–’â”€â”€â”€ As is, from
            â”‚ set TMP=c:\qc\tmp          â”‚â–’    NEW-VARS.BAT
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜


        CONFIG.SYS               NEW-CONF.SYS
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”     â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚     â”‚ FILES=20 â—„â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€ This is larger, so
    â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚     â”‚ BUFFERS=10       â”‚   replace existing FILES
    â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚     â”‚                  â”‚   command
    â”‚ FILES=10         â”‚     â”‚                  â”‚
    â”‚ BUFFERS=10       â”‚     â”‚                  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
            â”‚                          â”‚
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                        â”‚
            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
            â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€                â”‚
            â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€                â”‚
            â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€                â”‚
            â”‚ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€                â”‚
            â”‚ FILES=20                   â”‚
            â”‚ BUFFERS=10                 â”‚
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-3. Editing AUTOEXEC.BAT and CONFIG.SYS.

    Here's what the NEW-VARS.BAT commands do. PATH is an MS-DOS command that
    specifies the directories that MS-DOS searches to execute a program.
    Whenever you tell MS-DOS to execute a program on your hard disk (such as
    the QuickC linker or library manager), it first looks in the root
    directory of drive C:, and then checks the specified directories in the
    order they are listed. The next command tells QuickC that include files
    are in the \INCLUDE subdirectory of the main QuickC directory. Similarly,
    the other variables show that libraries are found in \QC\LIB and temporary
    files are in \QC\TMP.


Setting Up QuickC

    Now let's set up the QuickC working environment. The QuickC manual should
    be your source for detailed information about setup procedures and the
    various options involved, but here are "quick start" instructions that can
    simplify the process and probably save you time.

    The basic steps you should follow are:

    â–   Check the PACKING.LST file on the first QuickC distribution disk. Be
        sure you have a complete set of disks and manuals.

    â–   Back up the QuickC disks to floppy disks (use the MS-DOS DISKCOPY
        command to ensure you have an exact copy). Then use the backups during
        the setup process.

    â–   Run the SETUP program.

    Before you run SETUP and before you use QuickC to develop programs, be
    sure that you have at least 448 KB of free memory. QuickC may appear to
    run fine with somewhat less than 448 KB until you try to compile certain
    programs.

    To verify the amount of free memory, type the CHKDSK command at the MS-DOS
    prompt. To increase the amount of free memory, you might be able to change
    your AUTOEXEC.BAT file so that some memory-resident programs are not
    loaded. Then, reboot to free the memory those programs were reserving.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Out of Environment Space?
    If your current AUTOEXEC.BAT has many SET commands or a long PATH=
    statement, you might get an MS-DOS "out of environment space" error when
    you add the QuickC variables. If this happens, expand the available
    environment space by putting this command in your CONFIG.SYS file:

    shell=c:\command.com /e:<size>/p

    For MS-DOS versions 3.0 and 3.1, size is the number of 16-byte
    "paragraphs" you want to reserve for the MS-DOS environmental variables;
    for MS-DOS versions 3.2 and later it is the actual number of bytes. The
    default size is 10 paragraphs, or 160 bytes. To set the environment to 256
    bytes, use:

    shell=command.com /e:16/pâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€MS-DOS version 3.0 or 3.1
    shell=command.com /e:256/pâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€MS-DOS version 3.2 or later

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    If you normally use memory-resident programs or a RAM disk, we recommend
    that you reboot without installing them before running SETUP. The SETUP
    program will fail without at least 385 KB of available RAM. After you set
    up the QuickC environment, experiment with memory-resident programs or RAM
    disks if you wish.

    Setting up a hard-disk system for QuickC differs from setting up a
    floppy-disk system. Therefore, we have developed separate walkthroughs for
    hard-disk and floppy-disk users. If you have a floppy-disk system, skip
    the next section and read "Setting Up QuickC for Floppy-Disk Systems" on
    page 32.

Setting Up QuickC for Hard-Disk Systems

    First, put Libraries Disk #1 in drive A and type the SETUP command. The
    following line is a typical SETUP command:

    C>SETUP H C:\QC M EM GR

    The H specifies that your system has a hard disk.

    C:\QC is the pathname of your QuickC "base" directory. By default, QuickC
    creates the following subdirectories under the base directory:

    C:\QC\BIN                     Compiler, linker, and other executable
                                programs
    C:QC\BIN\SAMPLE               Sample C programs
    C:\QC\INCLUDE                 Include (header) files
    C:\QCINCLUDE\SYS              System-specific include files
    C:\QC\LIB                     Libraries
    C:\QC\TMP                     Temporary files
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Are You Using both QuickC and Microsoft C 5.0?
    If you use both QuickC and the Microsoft C Optimizing Compiler 5.0, you
    can install both compilers on your hard disk without causing any conflict.
    Because both compilers use the same library and include files, and because
    both compilers use the same environment variable names to locate these
    files, you won't have to create separate directories for each compiler's
    library and include files. The only planning and organizational work
    you'll need to do is to organize the compiler files and the source code
    files.

    Any program that you can compile with QuickC can be recompiled without
    change by Microsoft C 5.0. QuickC's fast compiler can save time in program
    development, and then the sophisticated optimizations of Microsoft C 5.0
    can speed the execution of your program. Furthermore, QuickC provides
    syntax checking for features unique to Microsoft C 5.0. If a program is
    syntactically correct but uses features of the larger compiler (the huge
    memory model, for instance), QuickC simply ignores those features when you
    run the program.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Note that SETUP overwrites any file with the same name as a QuickC
    distribution file. If you follow our recommendation to create a new
    directory for QuickC, \QC, in your root directory, you eliminate this
    problem.

    The M option in the SETUP command lets you use the "medium memory model"
    to compile programs. Note that you can specify other or additional memory
    models when you run SETUP. (See the manual for details.) Although we will
    explain all memory models in later chapters, we use the medium model
    throughout this book because it is the only supported model for programs
    compiled in the QuickC environment. (If you use the command-line compiler,
    which assumes a small model, you might want to create a small model
    combined library that conveniently collects all of the functions you
    normally use with QCL. You can create new combined libraries without
    running SETUP again.)

    The EM in the SETUP command specifies that all floating-point arithmetic
    be performed by software "emulation" of the 8087 math coprocessor chip. If
    you have an 8087/80287/80387 chip in your PC, you might prefer to use the
    87 option which directs floating-point calculations to the coprocessor.
    When QuickC builds your core library, it uses this specification to select
    the appropriate floating-point library. Note, however, that any .EXE file
    you create with the 87 option will not run on machines without a math
    coprocessor. If you are concerned about portability, use EM when you set
    up QuickC. The QuickC environment uses only the emulator; if a coprocessor
    is present the emulator detects that fact and uses it.

    Finally, the GR option specifies that QuickC's Graphics Library functions
    be included in your combined libraries. We recommend that you use this
    option so that you can run the graphics programs in this book without
    specifying the GRAPHICS.LIB every time you link. (Of course, if your
    computer has only a monochrome text display, you should not use this
    option. This installation will proceed, but programs that you subsequently
    create that use graphics will not work.)

    After you enter the initial SETUP command, the program asks you if you
    want to delete the "library subcomponents," or parts of libraries that are
    not needed for the configuration you chose. Unless you plan to use memory
    models or floating-point packages other than those specified in the SETUP
    command, you can save a lot of disk space by typing y at this prompt. The
    SETUP program then prompts you to insert the appropriate distribution
    disks in drive A.

    Without any further input, SETUP creates the QuickC directories, places
    header files in the \INCLUDE subdirectory, creates a "combined library"
    for each specified memory model using the floating-point option you
    selected, and places the combined libraries in the \LIB subdirectory. This
    library is called your "standard library" because it contains compiled
    versions of all the standard C routines (with specified options, such as
    graphics).

    If you have already edited your MS-DOS AUTOEXEC.BAT and CONFIG.SYS files,
    your QuickC environment is now set up and ready to use. Please skip the
    next section, which is for floppy-disk users.

Setting Up QuickC for Floppy-Disk Systems

    Setting up QuickC for a floppy-disk system differs from hard-disk setup in
    two principal ways: First, the floppy-disk setup does not create the
    NEW-VARS.BAT and NEW-CONF.SYS files, so you have to set your own MS-DOS
    variables; second, because you have only 720 KB of disk space on two
    floppy drives, you must be more choosy about which files to install. (If
    you have two 1.4 MB 3.5-inch disk drives, as found in the IBM PS/2 line,
    you need not be so constrained.)

    As explained in the Microsoft QuickC Programmer's Guide, you need to
    format at least two floppy disks: one disk for each memory model and one
    "scratch" disk to hold temporary files created during the setup process.

    Insert your copy of the Libraries Disk #1 in drive A and a blank formatted
    disk in drive B. You are now ready to run SETUP. We recommend that you
    type the following command:

    setup f b: m em gr

    This specifies a floppy-disk setup that places the combined library on
    drive B. The M option lets you use the "medium memory model" to compile
    programs. Although we will explain all memory models in later chapters, we
    use the medium model throughout this book because it is the only model
    supported for programs compiled in the QuickC environment.

    The EM in the setup command specifies that all floating-point arithmetic
    be performed by software "emulation" of the 8087 math coprocessor chip. If
    you have an 8087/80287/80387 chip in your PC, you might want to use the 87
    option instead. When QuickC builds your core library, it uses this
    specification to select the appropriate floating-point library. Note,
    however, that any .EXE file you create with the 87 option will not run on
    machines without a math coprocessor. If you are concerned about
    portability, use EM when you set up QuickC.

    Finally, the GR option specifies that QuickC's Graphics Library functions
    be included in your combined libraries. We recommend that you use this
    option so that you can run the graphics programs in this book without
    specifying the library GRAPHICS.LIB every time you link. (Of course, if
    your computer has only a monochrome text display, you should not use this
    option. The installation will proceed, but programs that you subsequently
    create that use graphics will not work.)

    As it builds the QuickC combined library, SETUP prompts you for the
    necessary disks. The setup process on floppy disks can take as long as 15
    minutes, so don't be alarmed at the seemingly interminable grinding of the
    disk drives. To create library disks for additional memory models or other
    floating-point options, run the SETUP program again.

    Setting Up the MS-DOS Environment

    Because the floppy-disk setup procedure does not create the NEW-VARS.BAT
    and NEW-CONFIG.SYS files, you need to set the MS-DOS variables yourself.
    To do this, add the following two variables to your AUTOEXEC.BAT file:

    set include=a:\include
    set lib=b:

    (If you do not have an AUTOEXEC.BAT, create one and type in the preceding
    variables.)

    This tells QuickC to look for include files in A:\INCLUDE and for
    libraries on drive B.

    Also, edit your CONFIG.SYS so that it assigns values of at least:

    files=15
    buffers=20

    Note that you will have to reboot your system if you are planning on
    running QuickC right away, so the new setting will take effect. Figure
    2-4 summarizes how QuickC is set up and run on floppy disks.

            Drive A                      Drive B
        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”          â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
        â”‚ QC.EXE           â”‚          â”‚ MLIBCE.LIB       â”‚ â”€â”€â”€â”€â”€ Libraries
        â”‚                  â”‚          â”‚                  â”‚
        â”‚                  â”‚          â”‚ QCHELLO.C        â”‚ â–’â”€â”€â”€â”€ Your source
        â”‚                  â”‚ â—„â”€â”€â”€â”€â”€â”€â–º â”‚ CIRCLE.C         â”‚ â–’     files
        â”‚                  â”‚          â”‚                  â”‚
        â”‚                  â”‚          â”‚ QCHELLO.EXE      â”‚ â–’â”€â”€â”€â”€ Temporary
    â”Œâ”€â”€â”‚                  â—„â”€â”€â”       â”‚ â”€â”€â”€â”€â”€â”€â”€â”€         â”‚ â–’     and object
    â”‚  â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜  â”‚       â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜       files
    â”‚                        â”‚
    â”‚  Swapped after startup â”‚
    â”‚  â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”  â”‚
    â””â”€â”€â–º                  â”œâ”€â”€â”˜
        â”‚ \INCLUDE         â”‚â”€â”€â”€â”€â”€ Include files
        â”‚                  â”‚
        â”‚ QC.OVL           â”‚â”€â”€â”€â”€â”€ Overlay file
        â”‚                  â”‚
        â”‚ QC.HLP           â”‚â”€â”€â”€â”€â”€ Help screens
        â”‚                  â”‚
        â”‚ LINK.EXE         â”‚â”€â”€â”€â”€â”€ Linker
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-4. Floppy-disk setup for QuickC.

    Differences for Floppy-Disk Users

    The examples in this book assume you have a hard disk with QuickC residing
    in a directory on drive C. Floppy-disk users can use these examples by
    substituting references as follows:

    Hard Disk                            Floppy Disks
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    c:\qc\bin                            a:
    c:\qc\include                        a:\include
    c:\qc\lib                            b:
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€


Starting QuickC

    Now we're ready to start using QuickC.

    If you have QuickC on a hard disk and have correctly included \QC\BIN in
    the PATH variable in the AUTOEXEC.BAT file, run QuickC by typing

    qc

    at the C> prompt. (If you haven't changed your PATH variable to include
    \QC\BIN, you must change to this directory before you can run QuickC.)

    To use QuickC on a floppy-disk system:

    1.  Boot your system with an MS-DOS disk that contains the new QuickC
        AUTOEXEC.BAT and CONFIG.SYS files

    2.  Put your copy of the Product Disk in drive A

    3.  Start QuickC by typing qc at the A> prompt

    4.  When the QuickC screen appears, replace the disk in drive A with a
        copy of the Work Disk

    Drive A now contains an "overlay" file (this lets QuickC access files
    without further disk swapping), the Help menus, the linker, and the
    \INCLUDE directory.

Improving the QuickC Display

    When you type qc on the MS-DOS command line, QuickC assumes you have a
    color monitor. If you have a monochrome monitor, this default setting can
    reduce the contrast of the characters on your screen and make them hard to
    read. To fix this, exit QuickC by selecting Exit from the File menu, and
    start QuickC in its "black-and-white" mode by typing qc /b.

    If you use a computer that refreshes the screen at a faster rate than
    standard ATs, such as some higher-performance models of COMPAQ computers,
    you can speed screen displays by using the command qc /g to start QuickC.

    If your computer has an EGA card, you can set the screen to display 43
    lines, instead of the normal 25, by starting QuickC with the qc /h
    command. Note that unless you have a high-resolution monitor, text can be
    very hard to read in this mode.

    You can combine these modes by separating them with a space. For example,
    qc /b /g starts QuickC in monochrome mode and accelerates the screen
    refresh rate. You can also put the qc command and options in a batch file
    so you don't have to type them each time you start.

Overview of the QuickC Screen

    If you've used menu-based integrated programming environments such as
    Turbo Pascal and Microsoft QuickBASIC before, the QuickC screen should
    look familiar. (See Figure 2-5.)

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 2-5 can be found on p.35 of the printed version of the book.    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-5. QuickC startup screen.

    Notice the following screen elements:

    â–   The menu bar across the top of the screen lists the following options:
        File, Edit, View, Search, Run, Debug, Calls, and Help.

    â–   The "title bar" displays the name of the program currently loaded into
        the editor. (Because we haven't written a program yet, it now reads
        untitled.c.)

    â–   The main area of the screen, now blank, is the workspace for your
        program.

    â–   Two "scroll bars," a vertical one on the right side of the screen and a
        horizontal one near the bottom of the screen, let you use an optional
        mouse to scroll text up and down or side to side.

    â–   The status line at the bottom of the screen keeps track of the name of
        the current program, the status of your program, and the current cursor
        position. Note the Context section of the line. QuickC uses this area
        to remind you of your current stage of program development. Because no
        program is loaded, it reads <Program not compiled>.

Making Selections

    The Microsoft QuickC Programmer's Guide gives exhaustive information on
    how to select menu items, move among parts of a dialog box, accept or
    cancel selections, and so on. Following is a brief and convenient summary
    of this material, explaining both keyboard and mouse commands. The QuickC
    manual also discusses several alternative selection methods you might want
    to explore. To save space and time we show only one method each for mouse
    and keyboard.

    Keyboard Shortcuts ("Hot Keys")

    QuickC lets you select certain frequently used menu items without opening
    the menu first. These "shortcut" or "hot" keys are particularly handy when
    you use the editor. Here are some of the most useful ones:

    Key                      Function
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    F2                       Open last file used
    Alt-Backspace            Undo last edit
    Shift-Del                Cut marked text
    Ctrl-Ins                 Copy marked text
    Del                      Clear editor buffer
    F4                       View output screen
    Ctrl-/                   Search for selected text
    F3                       Repeat last search
    Shift-F3                 Find next error
    Shift-F4                 Find previous error
    Shift-F5                 Start program
    F5                       Continue stopped program
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    (The Microsoft QuickC Programmer's Guide contains additional
    combinations.)

    The Mouse

    Although you can select all QuickC functions from the keyboard, you might
    want to try using a mouse if you have one. With a mouse, you need only to
    point and click to select anything on the screen. Because you don't have
    to learn all the keystroke combinations for making selections or using the
    editor, you can concentrate on learning C right away. Further, the mouse
    makes it easier to select items from a dialog box. You might want to learn
    both the mouse and keyboard methods and see which one best suits you. Or
    you can mix them, using the keyboard for making menu selections and the
    mouse for making selections in dialog boxes, for example.

    You must use a Microsoft mouse or a compatible mouse (such as the IBM PS/2
    mouse or the Logitech serial mouse) with QuickC. Before you can use any
    mouse with QuickC, however, you must install a "mouse driver," either in
    your CONFIG.SYS file or as a .COM file in your AUTOEXEC.BAT. (See your
    mouse documentation for instructions.) The driver is the software that
    lets QuickC recognize the mouse and respond to its movements as though
    they were commands. If you currently use a mouse for other programs, your
    system is probably set up correctly already.

Writing a Program

    Now we're ready to write a simple C program, which we will call QCHELLO.C.
    First, select the File menu. If you have a mouse, move the mouse until the
    pointer on the screen is on the File menu, and click the left button. This
    reveals the menu, as shown in Figure 2-6. Now, move the pointer to the
    Open option, and click the left button again. To reveal the File menu
    using the keyboard, press the Alt key and then press the f key. Notice
    that each menu item has a highlighted letter (often, but not always, the
    first letter in the word or phrase). Type this letter to select the menu
    item. Select the Open option by typing o.

    Note the Exit option in the File menu. Choose this option when you're
    ready to end your QuickC session. If you select Exit after changing your
    current program, QuickC first asks if you want to save the changed
    program. When you exit QuickC, you return to the MS-DOS prompt.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 2-6 can be found on p.37 of the printed version of the book.    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-6. QuickC File menu.

Selecting a File

    When you select the Open option on the File menu, a dialog box appears.
    (See Figure 2-7.) QuickC uses dialog boxes to obtain the information it
    needs to carry out your request.

    You can select a file from a dialog box in two ways. Notice the long
    rectangle near the top of the dialog box with a cursor blinking in it.
    Typing a filename in this rectangle is the most straightforward method of
    selecting a file. Below is a larger rectangle with some names in it. This
    box lists the contents of the current directory. Names in ALL CAPS are
    directories; names in lowercase are files. (The contents of the current
    directory in your system may vary from those in the example.)

    To make a selection from a dialog box:

    â–   With a mouse, move the pointer to the item you want. Click the left
        button to select the item.

    â–   With the keyboard, use the Tab or back-Tab (shifted tab) key to move
        from one section of the dialog box to another. Press Enter to select
        the item.

    When you select a directory, QuickC lists all files and subdirectories in
    that directory. Each list you display also has a .. entry. Selecting this
    entry moves you back to the parent directory of the directory shown. Thus
    you can easily browse through the file system with only a few keystrokes.

    With the back-Tab or your mouse, move the cursor to the File Name text
    box. Type qchello.c and then press the Enter key. Another small dialog box
    appears to inform you that this file does not exist. Accept the default of
    Yes to create it.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 2-7 can be found on p.38 of the printed version of the book.    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-7. File "Open" dialog box.

Typing in the Program

    You are now ready to type in a program. QuickC's default mode is in fact
    "edit mode," and the large area of the screen with the cursor in it is the
    Edit window. As you type the listing below, use the arrow keys to move the
    cursor, the Backspace key to make corrections, and press Enter at the end
    of each line. After you enter the text shown in Listing 2-1, your screen
    should look like Figure 2-8.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* qchello.c -- a simple C program */

    main()
    {
        printf("Hello, and welcome to QuickC!\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 2-1.  The QCHELLO.C program.

What Does It Do?

    Although we won't look at the structure and anatomy of C until the next
    chapter, this program gives you a hint of C style. The first line
    (enclosed by the characters /* and */) is a comment that briefly describes
    the program. It is optional but highly recommended. The word main()
    indicates the beginning of the main function or related group of
    statements in the program. (Most C programs have many functions in
    addition to the main one.) As the name suggests, printf() prints the
    string in the parentheses that follow. The braces, { and }, set off the
    group of statements (only one in this case) that make up the main
    function. So, it's easy to see what this program does: It prints Hello,
    and welcome to QuickC! on the screen. (The \n at the end of the string
    simply moves the cursor to the beginning of a new line.)

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 2-8 can be found on p.39 of the printed version of the book.    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-8. QCHELLO.C as typed into the edit window.

Running QCHELLO.C

    Running the program is simple. Select the Run menu. As you probably know,
    before we can run our program we must first compile and link it. The Start
    option in the Run menu executes all of these steps for you.

    When you select Start, a dialog box tells you that the program has been
    "modified" and asks if you want to "rebuild" (compile and link) it.
    Whenever you change a program, you must recompile. QuickC treats this new
    program as a changed program, so press Enter or click on Yes to compile
    it.

    Before you can blink an eye, QuickC compiles and runs the program. QuickC
    is fast, as you will see when you write longer programs, and because this
    little program doesn't use any include files or libraries, it compiles
    instantaneously.

    After the program runs, the screen displays the following:

    Hello, and welcome to QuickC!
    Program returned (13). Press any key

    You are now looking at the "output screen." QuickC keeps track of the
    output screen, which always holds the results of your programs, so you can
    switch back and forth between it and the QuickC environment screen. Press
    any key to return to QuickC. For now, don't worry about the return value
    mentioned in the second output line.

Saving the Program

    To save this program to disk for future reference, open the File menu
    again. Notice the Save and Save As options. Select Save to write the
    program to disk. If you want to save the program with a new name, select
    Save As. When the dialog box appears, type the new name and press Enter.
    (You might try QCHELLO2.C.)

Compiling to a .EXE File

    QuickC compiles programs to memory by default. Because it is fast, this is
    often the best way to compile while developing a new program. However, the
    compiled version of a program compiled to memory disappears when you
    compile another program or quit QuickC. Eventually you need a compiled
    version of the program on disk, so you can run it without recompiling.
    Also, you eventually want to create programs that a user can run directly
    from MS-DOS without QuickC available. To produce an MS-DOS-executable
    file, we need to "compile to .EXE."

    Select the Run menu. Now select the Compile item. The dialog box shown in
    Figure 2-9 appears.

    This large dialog box lets you select many options. (We will explain the
    options later as we use them.) Notice the center column, Output Options.
    The small black dot in the parentheses next to the word Memory indicates
    that it is the currently selected output option. We want to change this
    option to Exe. If you have a mouse, move the pointer between the
    parentheses next to Exe and click. From the keyboard, you can move the
    cursor to this position with the Tab and Down Arrow keys and press Enter.
    But there's an even faster way. Note that the letter x in Exe is
    highlighted. To select this item, you need only type the letter x.

    Now you can compile the program. Note the four small rectangles at the
    bottom of the dialog box. The first one, Build Program, has a double
    border, which signifies that it is the default. You can select it in one
    of three ways: tab to it and press Enter, click on it with a mouse, or
    type b.

    The Compile box displays the numbers of the program lines being processed
    as the program is compiled. Because this program is being compiled as a
    stand-alone .EXE file, it must be linked to various disk files.

    Very quickly, the program returns you to the familiar QuickC environment
    screen. Note that the program didn't run and produce output as it did when
    you compiled it earlier. This compile created a .EXE file, and these
    executable files cannot be run directly from QuickC. However, QuickC
    provides an easy way to run it.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 2-9 can be found on p.41 of the printed version of the book.    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-9. Compile dialog box.

Escaping to MS-DOS

    At the File menu, select the item DOS Shell. This option switches the
    display to the output screen where the MS-DOS sign-on message and prompt
    appear. You can now run any MS-DOS command, as well as most programs and
    batch files.

    To run QCHELLO.EXE, type:

    C>qchello

    The screen displays the expected output. (No instruction to press a key
    appears, of course, because QuickC is not running. We are at the MS-DOS
    level.)

    Now type:

    C>exit

    to return to QuickC exactly where you left off.


Getting Help

    We will not cover every feature of QuickC in this book so that we can
    devote more time to C itself. Although we occasionally refer you to the
    QuickC manual, there's another source of help as near as your keyboardâ”€â”€
    the QuickC Help facility. In fact, you can select from three levels of
    help: general, topic, and keyword.

General Help Screens

    Press the F1 key to select the General help option (or use the mouse to
    make the selection). The first screen you see is shown in Figure 2-10.
    Notice that it displays a summary of some editor commands as well as some
    other frequently used commands. The small rectangles at the bottom of the
    dialog box let you select the Next or Previous help screen. Next, with its
    double border, is the default. Press Enter or click on the box with the
    mouse to display the next screen. Don't try to memorize or even understand
    these screens. Just get an idea of the general information that is
    available for future reference.

Topic Help

    If you select Topic help, you can page through lists of topics until you
    find the information you are looking for. (See Figure 2-11.) For example,
    you could select "preprocessor directives," and then select the particular
    directive for which you want help. To choose Topic help directly from the
    editor window, press Shift-F1.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 2-10 can be found on p.43 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-10. A QuickC help box.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 2-11 can be found on p.43 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-11. Topic help.

Keyword Help

    Return to the editor window, and move the cursor to the word printf.
    Suppose you are writing a program and you are not sure how this C function
    works. By pressing Shift-F1, you can retrieve information about the C
    keyword or standard function currently marked by the cursor. (See Figure
    2-12.)

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 2-12 can be found on p.44 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-12. Keyword Help screen.


Fixing Errors

    The last section of this chapter discusses how to fix errors in a C
    program. The QCHELLO.C program should still be in the Edit window. Let's
    make some changes in the program so we can practice fixing errors.
    (Normally, we programmers don't have to manufacture errors; we run into
    enough of them on our own!)

    Use the arrow keys or the mouse to move the cursor to the word printf.
    Change it to primtf. Next, go to the end of the line and delete the
    semicolon.

    Now select Run and Start to compile and run the program. QuickC soon
    displays a rectangular error window at the bottom of the screen as shown
    in Figure 2-13.

    The error message tells you that a semicolon is missing before the closing
    }. Notice on your screen that the cursor in the edit window is on the
    character immediately following the error. This makes it easy to find and
    correct the error. (In this case, the next character is on the next line,
    however, so you have to move the cursor to the end of the preceding line
    to insert the semicolon after the ).

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 2-13 can be found on p.45 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 2-13. Error window.

    Now run the program again. The next error message, `primtf' : unresolved
    external, is less clear than the preceding one. Simply stated, it means
    that primtf is not one of the standard QuickC functions. When you change
    the m back to an n, the program again runs correctly.


Preparing for the Next Chapter

    In the next chapter we begin our study of the elements of the C language.
    Although we discuss additional QuickC features as needed, we will not
    concentrate on using the QuickC environment. So now is a good time to get
    comfortable with your new QuickC environment.

    We recommend that you try the following:

    â–   Save QCHELLO.C under another name, and then use the Open option in the
        File menu to load it into the editor.

    â–   Practice compiling and running the program to memory and to a .EXE
        file.

    â–   Use the DOS Shell item of the File menu to exit to MS-DOS, run a .EXE
        program, and then use Exit to return to QuickC.

    â–   Make some errors in QCHELLO.C and try running the program. Observe the
        error messages, fix the errors, and run the program again. What happens
        if the last } is missing? What happens if you change the word "Hello"
        to "Hi"?

    â–   Read Chapter 6 in the Microsoft QuickC Programmer's Guide to learn
        about the advanced features of the editor. We suggest you study them
        when you want a break from reading this book. None of these editor
        features are needed for you to use this book, but they make it easier
        to enter and modify long programs. Remember to use the Help screen to
        remind you of common editing functions.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€