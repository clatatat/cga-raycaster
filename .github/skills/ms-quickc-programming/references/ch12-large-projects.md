Chapter 12  Large Projects

    As your programs become larger and more complex, revising and maintaining
    them become less straightforward. Consequently, as your programming skills
    increase, you inevitably will find yourself looking for more efficient
    ways of handling programs. For example, you might want to:

    â–   Use one function in several programs without having to retype it every
        time.

    â–   Compile a program one way for testing and another for actual useâ”€â”€
        without having to rewrite it.

    â–   Combine several .C files into a single program, while recompiling only
        those files that need to be changed.

    â–   Transport one of your programs to another machine or compiler and
        compile it without needing to rewrite it.

    This chapter offers solutions for these and other common programming
    needs. We'll discuss how to use the C preprocessor for conditional
    compilation and for creating macros. Next, we'll show you how to create
    and manage QuickC's "program lists." Finally, we'll show you how to
    develop custom C libraries and how to access them from within QuickC.


Advanced C Preprocessor

    Although compiling under QuickC appears to be a single swift process, it
    is actually three processes combined into one. First, your C program is
    "preprocessed." In this phase, conditional compilation occurs, and other
    preprocessing directives are executed: For example, #define MAX 3 converts
    all instances of MAX to 3. Second, the QuickC compiler translates your
    preprocessed code into machine language, or code that the computer can
    understand. Finally, your compiled machine code is combined (linked) with
    the precompiled code in the standard C Library of functions (such as
    printf()) to form the finished, executable program.

    Conditional compilation occurs in the preprocessing stage. Using lines
    that begin with a # character (pronounced "pound" or "number"), you can
    write code that compiles one way for testing and another for actual use.
    You can also write code that compiles differently on different machines or
    different compilers.

    The C preprocessor recognizes only lines of text that begin with the #
    character, such as #define and #include. Table 12-1 lists the complete
    set of these "preprocessor directives."

    Table 12-1 The Preprocessor Directives
â•“â”Œâ”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â•–
    Directive       Description
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    #define x y     Uses x as an alias for y throughout the program.
    #include <file> Reads file from the INCLUDE subdirectory and inserts it
                    into your program at this point.
    #include "file" Reads file from the current working directory and inserts
                    it into your program at this point.
    #ifdef x        If x is defined, compiles all program code between this
                    and the next matching #endif, #elif, or #else.
    #if (x)         If the integer constant expression x is true (nonzero),
                    compiles all program code between this directive and the
                    next matching #endif, #elif, or #else.
    Directive       Description
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
                    next matching #endif, #elif, or #else.
    #ifndef x       If x is not defined, compiles all program code between
                    this and the next matching #endif, #elif, or #else.
    #else           The inverse of the above three if directives. If the if is
                    true, the code before the #else is compiled. If the if is
                    false, the code following the #else is compiled.
    #elif (x)       The else if extension for #if in a chain of conditions.
    #endif          Terminates the current matching #if, #ifdef, or #ifndef.
    #line lineno    Sets the current line number to lineno and the current
    "file"          file to file.
    #pragma         Sets "compiler-specific" options.
    #define x(y) z  Defines preprocessor macros.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€


Conditional Compilation

    Occasionally, you will need to compile only part of your codeâ”€â”€for
    example, during debugging, or when you compile different versions for
    different users, or while compiling your program on a different computer
    or compiler. The C preprocessor offers an assortment of directives to
    facilitate this selective compiling process, called "conditional
    compilation."

    The #if and #endif Directives

    The most frequently used conditional directives are #if and #endif. The
    #if directive tests what is known as a restricted constant expression in
    your code to see if that expression is zero. If it is a nonzero (true)
    value, QuickC compiles all the code between that #if and its matching
    #endif. Use the directive as follows:

    #define BYTES 4

    #if (BYTES == 4)
    /* compile this code */
    #endif

    In this example, the expression (BYTES == 4) is a "constant expression"
    because it becomes (4 == 4) (the logical comparison of two integer
    constants). It is also a "restricted" constant expression, which is a
    constant expression that cannot contain:

    â–   sizeof operations

    â–   enumerated constants

    â–   typecasts

    â–   floating-point constants

    Therefore, the following directives are legal:

    #if (BYTES < 8)
    #if ((6 * 9 / 3) != (2 % 1))

    and the following are not:

    #if (sizeof(int) == 4)â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€sizeof illegal

    enum {true, false} yorn;
    #if (true == 0)â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Enumerated constant illegal

    #if (NULL == (char *)0)â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Typecast illegal

    #if (MIN < 4.2)â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€float constant illegal

    One common use for the #define directive is in debugging. The program in
    Listing 12-1 on the following page, BUG.C, illustrates one possible way
    to use #define to change the behavior of your program. By using #define to
    define DEBUG_LEVEL to one of the values 0, 1, or 2, then recompiling and
    running, you will cause the program to print one of three messages to your
    screen. For a #define value of 0, nothing is printed; for 1, the calls to
    the subroutine sub() are documented; and for 2, entry into and exit from
    main() are printed.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* bug.c  --  shows how different levels of debugging  */
    /*            output can be produced using #if         */

    #define DEBUG_LEVEL 2     /* 0 = none, 1-2 for debug   */
    #include <stdio.h>

    main()
    {
        int ret;

    #if (DEBUG_LEVEL == 2)
        fprintf(stderr, "Entering main()\n");
    #endif

    #if (DEBUG_LEVEL == 1)
        fprintf(stderr, "Calling sub()\n");
    #endif

        ret = sub();

    #if (DEBUG_LEVEL == 1)
        fprintf(stderr, "sub() returned %d\n", ret);
    #endif

    #if (DEBUG_LEVEL == 2)
        fprintf(stderr, "Leaving main()\n");
    #endif

    }

    sub()
    {
        return (5);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-1.  The BUG.C program.

    defined and #ifdef

    You can use the defined keyword with the #if directive to detect whether
    or not a name has been specified by #define:

    #if defined(name)

    If defined(name) determines that name was used in a #define directive, it
    evaluates to true. The keyword defined is used by the preprocessor only in
    this context; therefore, you can use it anywhere in your program without
    causing a conflict.

    The defined variation of #if replaces the pre-ANSI directive #ifdef. That
    is, although the following are equivalent:

    #if defined(name)
    #ifdef name

    the first form is preferable.

    You can use the same technique to see if a name has not been specified
    with #define, as follows:

    #if !defined(name)
    #ifndef name

    Again, the first form is preferable to the second.

    The defined variation of #if is especially useful for writing programs
    that will be compiled on another type of computer or a different compiler.
    The BITOUT.C program (Listing 12-2) is an adaptation of the Bitout()
    function used in the BITWISE.C program (Listing 7-12 on p. 218). After
    the user enters an integer, the program prints that integer in binary
    form. Note that it uses #if defined to print the bits one way on an
    80286-based computer and another way on a 68000-based machine.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* bitout.c  -- compiles one way on an IBM PC and      */
    /*              another on a 68000 chipâ”€based machine  */

    #define CHIP_80286    /* don't define on a 68000 machine */
    #include <stdio.h>

    main()
    {
        int num;

        printf("Enter an integer number and I will print"
                " it out in binary\nNumber: ");

        if (scanf("%d", &num) != 1)
            {
            fprintf(stderr, "Not an integer\n");
            exit(1);
            }
        Bitout(num);
    }

    Bitout(unsigned int num)
    {
        int i, j;
        unsigned char *cp;

        cp = (char *)&num;
    #if defined(CHIP_80286)    /* IBM PC */
        for (i = 1; i >= 0; --i)
    #endif
    #if !defined(CHIP_80286)   /* otherwise 68000 machine */
        for (i = 0; i < 4; ++i)
    #endif
            {
            for (j = 7; j >= 0; --j)
                putchar((cp[i] & (1 << j)) ? '1' : '0');
            }
        putchar('\n');
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-2.  The BITOUT.C program.

    #else and elif

    We can simplify the two #if directives in BITOUT.C by using the #else
    directive:

    #if defined(CHIP_80286)
        for (i = 1; i >= 0; --i)
    #else
        for (i = 0; i < 4; ++i)
    #endif

    In this example, the preprocessor compiles the first for statement if
    CHIP_80286 has been defined using #define; otherwise, it compiles the
    second for statement.

    By using the #elif (else if) directive, you can create a whole chain of
    conditions. The following series of directives, for example,

    #if defined(CHIP_8086)
        for (i = 1; i >= 0; --i)
    #elif defined(CHIP_80286)
        for (i = 1; i >= 0; --i)
    #elif defined(CHIP_68000)
        for (i = 0; i < 4; ++i)
    #else
        fprintf(stderr, "Unknown chip\n");
        return;
    #endif

    tells the preprocessor to compile the first for statement if CHIP_8086 is
    defined, to compile the second for statement if CHIP_80286 is defined, or
    to compile the third for statement if CHIP_68000 is defined. If none of
    these is defined, the preprocessor compiles code to print an error and
    return.

    Logical Operators and #if

    Many of the preceding #if tests use similar code. You can take a coding
    shortcut by combining #if expressions using the C logical operators && and
    ||. For example, you can shorten the previous #elif sequence by using the
    logical OR operator as follows:

                            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Logical OR
    #if defined(CHIP_8086) || defined(CHIP_80286)
        for (i = 1; i >= 0; --i)
    #elif defined(CHIP_68000)
        for (i = 0; i < 4; ++i)
    #else
        fprint(stderr, "Unknown chip\n");
        return;
    #endif

    The #if directives and their corresponding #endif and #elif directives can
    be nested. However, when you nest them, we recommend that you use indents
    to show the levels of nesting, as follows:

    #if defined(IBMPC)
        #if defined(CGA) || defined(EGA)
            sp = (int far *)0xB8000000;
        #else
            sp = (int far *)0xB0000000;
        #endif
    #else
        fprintf(stderr, "No Screen Memory\n");
        return;
    #endif

    In this example, if IBMPC is not defined, the last #else executes. If
    IBMPC is defined, the program checks to see if either CGA or EGA (for the
    corresponding graphic adapter cards) is defined. If either is, we assign
    the address value 0xB8000000 (the location of screen memory for those
    cards) to the pointer sp. Otherwise, we use the address 0xB0000000 (the
    location of screen memory for the regular monochrome adapter).

    You can avoid problems when using # preprocessor directives by remembering
    two general rules. First, the # must always begin a line. Second, each
    directive can occupy only one line unless you extend it by typing a
    backslash and pressing Enter:

    #if defined(EGA) \â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Line extended
        ||    \â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Line extended
        defined(CGA)

    Predefined Names

    QuickC always predefines two names: __FILE__ and __LINE__. (Note that both
    have two leading and two trailing underscore characters.) The name
    __FILE__ is always the name of the current C source file being compiled.
    It is a quoted string constant, so you can safely use it anywhere that
    strings are legal. The predefined name __LINE__ is an integer constant
    number that is always the current line number in the current file. You can
    use it anywhere as a legal integer constant.

    These two predefined names are generally used to print meaningful
    diagnostics during debugging. The ERR.C program (Listing 12-3)
    demonstrates their use for tracing the flow of a small program. By placing
    a #define ERR inside a #if directive, you can turn on and off custom
    tracing with a single change in code:

    #define TRACE 0      /* change to 1 to turn on */

    #if (TRACE > 0)
    #define ERR printf("Tracing: \"%s\" line %d\n",\
                        __FILE__, __LINE__ );
    #else
    #define ERR
    #endif

    If TRACE is defined as a value greater than zero, QuickC traces the
    program. If, on the other hand, TRACE is 0, then tracing is disabled.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* err.c  --  illustrates __FILE__ and __LINE__ in */
    /*            tracing a small program              */

    #define ERR printf("Tracing: \"%s\" line %d\n",\
                        __FILE__, __LINE__);
    main()
    {
        ERR
        err1();
        ERR
        err2();
        ERR
    }

    err1()
    {
        ERR
        err2();
    }

    err2()
    {
        ERR
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-3.  The ERR.C program.

#pragma Instructions to the Compiler

    You can use the #pragma preprocessor directive to give compiler-specific
    instructions to the compiler (that is, instructions that usually must be
    given as part of the MS-DOS command line or by presetting QuickC's compile
    time options). Use it in the following way:

    #pragma instruction

    #pragma pack(1|2|4)

    The pack pragma tells the compiler to place structure members into memory
    on 1-byte, 2-byte, or 4-byte boundaries. Ordinarily, QuickC places
    structure members into memory so that int and long types always begin in
    an even address, which is equivalent to pack(2). (See Figure 12-1a.) By
    using the #pragma pack() preprocessor directive, you can tell the compiler
    to store structures in a smaller space (see Figure 12-1b) or to spread
    them out into a larger space with pack(4). (See Figure 12-1c.)

                            â”Œâ”€â”€
                            â”‚ struct {
                            â”‚   char a;
                            â”‚   int b;
    For the declaration â”€â”€â”¤   char c;
                            â”‚   long d;
                            â”‚ };
                            â””â”€â”€

                                                            â”Œâ”€â”€â”€â”€â”€â”€â”€â”â”€â”
                                                        400 â”‚       â”‚ â”œâ”€a
                                                            â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤
                                                        401 â”‚       â”‚ â”‚
        â”Œâ”€â”€â”€â”€â”€â”€â”€â”â”€â”                â”Œâ”€â”€â”€â”€â”€â”€â”€â”â”€â”             â”œâ”€     â”€â”¤ â”‚
    402 â”‚       â”‚ â”œâ”€a          402 â”‚       â”‚ â”œâ”€a       402 â”‚       â”‚ â”œâ”€unused
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤                â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤             â”œâ”€     â”€â”¤ â”‚
    403 â”‚       â”‚ â”œâ”€unused     403 â”‚       â”‚ â”‚         403 â”‚       â”‚ â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤                â”œâ”€     â”€â”¤ â”œâ”€b           â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤
    404 â”‚       â”‚ â”‚            404 â”‚       â”‚ â”‚         404 â”‚       â”‚ â”‚
        â”œâ”€     â”€â”¤ â”œâ”€b              â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤             â”œâ”€     â”€â”¤ â”œâ”€b
    405 â”‚       â”‚ â”‚            405 â”‚       â”‚ â”œâ”€c       405 â”‚       â”‚ â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤                â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤             â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤
    406 â”‚       â”‚ â”œâ”€c          406 â”‚       â”‚ â”‚         406 â”‚       â”‚ â”œâ”€c
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤                â”œâ”€     â”€â”¤ â”‚             â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤
    407 â”‚       â”‚ â”œâ”€unused     407 â”‚       â”‚ â”‚         407 â”‚       â”‚ â”œâ”€unused
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤                â”œâ”€     â”€â”¤ â”œâ”€d           â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤
    408 â”‚       â”‚ â”‚            408 â”‚       â”‚ â”‚         408 â”‚       â”‚ â”‚
        â”œâ”€     â”€â”¤ â”‚                â”œâ”€     â”€â”¤ â”‚             â”œâ”€     â”€â”¤ â”‚
    409 â”‚       â”‚ â”‚            409 â”‚       â”‚ â”‚         409 â”‚       â”‚ â”‚
        â”œâ”€     â”€â”¤ â”œâ”€ d             â””â”€â”€â”€â”€â”€â”€â”€â”˜â”€â”˜             â”œâ”€     â”€â”¤ â”œâ”€d
    410 â”‚       â”‚ â”‚                                    410 â”‚       â”‚ â”‚
        â”œâ”€     â”€â”¤ â”‚                                        â”œâ”€     â”€â”¤ â”‚
    411 â”‚       â”‚ â”‚                                    411 â”‚       â”‚ â”‚
        â””â”€â”€â”€â”€â”€â”€â”€â”˜â”€â”˜                                        â””â”€â”€â”€â”€â”€â”€â”€â”˜â”€â”˜

    (A) RESULT OF USING         (B) RESULT OF US
    ING     (C) RESULT OF USING
        #pragma pack (2)            #pragma pack (1)        #pragma pack (4)
        (QuickC default)

    Figure 12-1. The pack() pragma determines how structures are placed
    into memory.

    The PACK.C program (Listing 12-4) illustrates this structure packing.
    When you run the program, note the addresses it prints. Then change the 1
    in #pragma pack(1) to a 2 and recompile and run PACK.C again. Finally,
    change that 2 to a 4 and repeat the process.

    An extension to the #pragma pack() directive lets you turn packing on and
    off:

    #pragma pack(1)â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Set one-byte packing
    ...
    #pragma pack() noâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Turn packing off
    ...
    #pragma pack() yesâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Turn packing back on

    The example first tells the compiler to pack all structure members to the
    nearest 1-byte boundary. Next, the no tells the compiler to stop packing
    and revert to its default even-byte boundary arrangement. Finally, the yes
    tells the compiler to resume packing on 1-byte boundaries.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* pack.c  --  demonstrates structure packing with */
    /*             the #pragma pack() directive        */

    #pragma pack(4)        /* 1, 2 or 4 */

    main()
    {
        struct {
            char ch1;
            int  int1;
            char ch2;
            long int2;
        } s;

        printf("ch1  -> %lu\n", (unsigned long)(&s.ch1));
        printf("int1 -> %lu\n", (unsigned long)(&s.int1));
        printf("ch2  -> %lu\n", (unsigned long)(&s.ch2));
        printf("int2 -> %lu\n", (unsigned long)(&s.int2));
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-4.  The PACK.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    The Intel 80386 chip executes at its fastest if int and long types begin
    on modulo 4-byte address boundaries. The Intel 80286 and earlier chips
    execute fastest when those types begin on even addresses. If size is more
    important to you than speed, use the #pragma pack(1) directive.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Preprocessor Macros

    The #define preprocessor directive has a second form that is called a
    #define macro, or a preprocessor macro. The #define macro is an extremely
    powerful tool, used by programmers to place "in-line" code into a program
    in a manner that resembles a subroutine call. Take a moment to use
    QuickC's View Include feature to look at the <stdio.h> header file. Notice
    in line 105 of that file that the getc() function you have been using all
    along is not really a function at all. It is a #define macro. Because it
    is a macro, the preprocessor expands each occurrence of getc(stdin) in
    your program to the following:

    (â”€â”€â”€â”€(stdin)->cnt >= 0 ? 0xFF & *(stdin)->_ptr++ : _filbuf(stdin))

    Certainly, it is easier to type getc(stdin) than to type this complex code
    sequence.

    The form for a #define macro is as follows:

    #define TRIPLE(x) (x*3)

    In this example, the defined name is TRIPLE and the (x) is its formal
    argument. The expression TRIPLE(x) is defined as an alias for the
    expression (x*3). This means that anywhere in the program that you use the
    following expression:

    TRIPLE(2)

    the actual argument (here 2) replaces every occurrence of the formal
    argument, x, in the original definition. This produces the following
    expansion:

    TRIPLE(2)
        â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Expands to
        â”‚
        â–¼
    (2*3)

    To illustrate further, examine the following macro definition for MAX, a
    macro that compares two values and yields a new value that is the higher
    of the two:

                â”Œâ”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Two formal arguments
    #define MAX(x,y) (((x) > (y)) ? (x) : (y))          separated by a comma
            â””â”€â”€â”¬â”€â”€â”€â”˜ â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Macro definition
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Macro

    This example shows that macros can take more than one formal argumentâ”€â”€but
    arguments must be separated from one another by commas. The x in the macro
    replaces each x in the macro definition with its corresponding actual
    argument, and each y replaces its corresponding y. If you use the above
    macro definition in your code and then use the following expression:

    oldest = MAX(age1, age2);

    with int variables age1 and age2, the preprocessor expands the macro as
    follows:

    oldest = (((age1) > (age2)) ? (age1) : (age2));

    Potential Problems with Macros

    Use preprocessor macros with careâ”€â”€actual arguments to macros can cause
    unexpected changes, such as reading an extra character. You should avoid
    using the following types of arguments because they can produce unwanted
    side effects:

    â–   function calls

    â–   other macros

    â–   the increment (++) and decrement (--) operators

    â–   the assignment operator (=)

    For example, consider the following ISQ macro:

    #define ISQ(letter) ((letter) == 'q' || (letter) == 'Q')

    This macro detects whether a letter is an uppercase or lowercase 'Q' and
    is useful for testing if a user is quitting a program. You correctly use
    this macro as follows:

    ch = getchar();

    if (ISQ(ch))
        exit(0);

    In the preceding code, ch is a char variable; therefore, the if statement
    expands to

    if (((ch) == 'q' || (ch) == 'Q'))

    which is what you expect. However, if you use this macro incorrectlyâ”€â”€for
    example, with a function call such as getchar(),

    if (ISQ(getchar()))

    it expands to an expression that doesn't do what you expect:

    if (((getchar()) == 'q' || (getchar()) == 'Q'))

    This example illustrates a common problem. The first call to getchar()
    reads a character and compares the value to 'q'. If that character is not
    a 'q', getchar() is called again to read a new character and to compare
    the new character to 'Q'. This is not what you intended, however. You want
    MAX to read only the first character and then to compare that character to
    both 'q' and 'Q'.

    Macros and Semicolons

    Never end a macro definition with a semicolon. For example, the following
    macro converts a printable character into a control character value:

    #define CTRL(x) ('x' - '@');

    The expression CTRL(A) expands to the expression ('A' - '@'); and yields
    the desired ASCII value 1 (Ctrl-A). However, the trailing semicolon causes
    a syntax error when you use the macro in an expression such as:

    printf("And 'A' prints as %c\n", CTRL(A));

    Note the syntax error that results when this expands to

        printf("And 'A' prints as %c\n", ('A'-'@'););
                                                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Wrong

    Macros and Quotes

    As in normal #define directives, preprocessor macros do not substitute
    actual arguments inside full quotation marks. For example, the following
    macro would be a useful tool for debugging:

    #define PERR(x) printf("The value of x is %d\n", x)

    Unfortunately it won't work. Because the first x is inside full quotation
    marks, it isn't expanded. However, the final x is expanded:

    int val = 5;
    PERR(val);
    â””â”€â”€â”€â”€â”¬â”€â”€â”€â”˜
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Expands to
                        â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    printf("The value of x is %d\n", val);

    We can rectify this by using the preprocessor's "stringizing" operator #.
    When placed before a formal argument in a macro definition, the # causes
    that argument to be expanded and quoted. Thus, the correct way to define
    PERR is as follows:

    #define PERR(x) printf("The value of " #x " is %d\n", x)
                                            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Stringizing operator

    This correctly expands as:

    int val = 5;
    PERR(val);
    â””â”€â”€â”€â”¬â”€â”€â”€â”˜
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Expands to
                    â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    printf("The value of " "val" " is %d\n", val);

    The example works because the compiler joins adjacent quoted string
    constants into a single string. The result is that printf() correctly
    prints the following:

    The value of val is 5


Using QuickC for Large Projects

    Imagine you are writing a text editor program such as the one shown in
    Figure 12-2 on p. 381. With sufficient memory, QuickC can easily load and
    compile programs of this size. However, the larger a program is, the
    longer it takes to compile, load, and save. Therefore, you can manage
    large programs more easily when you break them into several smaller files
    by logically grouping the subroutines according to use. This approach has
    several advantages.

    â–   When a program consists of several files, you need to recompile only
        those files that change.

    â–   Grouping subroutines by usage lets you easily trace the logic of the
        program during debugging.

    â–   Perfected subroutines that no longer need to be recompiled can be
        shared by many programs.

QuickC Program Lists

    The QuickC "program list" feature compiles several small files or library
    modules and combines them into a single executable program. This lets you
    create complex, large programs from many small, easily maintained files.
    Before we examine this feature, enter and save the following three files:
    TEXED.C (Listing 12-5), KEYS.C (Listing 12-6), and FILE.C (Listing
    12-7 on the following page). These are three small pieces of our
    imaginary text editor in Figure 12-2. Although these modules don't do
    much, they demonstrate the basics of using QuickC program lists.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* texed.c  --  main entry point to the editor; the   */
    /*              menu and signal handlers are here     */

    main(argc, argv)
    int argc;
    char *argv[];
    {
        char ch;

        while (1)
            {
            printf("\nTexEd Main Menu\n");
            printf("Select from:\n");
            printf("0) Quit\n\n");
            printf("1) Load File\n");
            printf("2) Save File\n");
            printf("3) Edit File\n");
            printf("Which: ");
            do
                {
                ch = getch();
                ch -= '0';
                } while (ch < 0 || ch > 3);
            printf("%d\n\n", (int)ch);
            switch(ch)
                {
                case 0: exit(0);
                case 1: Load_file(); break;
                case 2: Save_file(); break;
                case 3: Edit_file(); break;
                }
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-5.  The TEXED.C file.

    2000-line text editor                Broken into separate files
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”               â”Œâ”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚                   â”‚               â”‚ â”‚ Main()            â”‚
    â”‚                   â”‚               â”‚ â”‚ Signal handlers   â”‚â”€â”€â”€â”€texted.c
    â”‚                   â”‚               â”‚ â”‚ menu()            â”‚
    â”‚                   â”‚               â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚                   â”‚               â”‚ â”‚                   â”‚
    â”‚                   â”‚               â”‚ â”‚ Read and process  â”‚â”€â”€â”€â”€keys.c
    â”‚                   â”‚               â”‚ â”‚ typed keys        â”‚
    â”‚                   â”‚               â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚                   â”‚               â”‚ â”‚                   â”‚
    â”‚                   â”‚â”€â”€â”€texted.câ”€â”€â”€â–ºâ”‚ â”‚ Update the        â”‚â”€â”€â”€â”€screen.c
    â”‚                   â”‚               â”‚ â”‚ screen            â”‚
    â”‚                   â”‚               â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚                   â”‚               â”‚ â”‚                   â”‚
    â”‚                   â”‚               â”‚ â”‚ Special commands  â”‚â”€â”€â”€â”€cmds.c
    â”‚                   â”‚               â”‚ â”‚ like 'delete line'â”‚
    â”‚                   â”‚               â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚                   â”‚               â”‚ â”‚                   â”‚
    â”‚                   â”‚               â”‚ â”‚ File read and     â”‚â”€â”€â”€â”€file.c
    â”‚                   â”‚               â”‚ â”‚ write routines    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜               â””â”€â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 12-2. A large program is often best split into several smaller and
    more manageable files.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* keys.c  --   The keyboard input-handling routines  */
    /*              for the texed editor                  */

    Edit_file()
    {
        char ch;

        printf("\nYou are now in the editor.\n");
        printf("Press 'Q' to exit back to main menu.\n");

        do
            {
            ch = getch();
            putch(ch);
            } while (ch != 'Q');

        printf("\n\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-6.  The KEYS.C file.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* file.c  --  the file I/O routines for texed */

    Load_file()
    {
        printf("\nLoading ..... done.\n");
    }

    Save_file()
    {
        printf("\nSaving ...... done.\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-7.  The FILE.C file.

    Next select Set Program List from the File menu and enter texed.mak in the
    File Name text box. This program list name is composed of two parts. The
    first, texed, is the name of your finished program. The second, the
    extension .mak, signifies that this program list file is a "make" file.
    (We'll explain make files in the next section.)

    After you enter the name texed.mak, QuickC prompts "`texed.mak' does not
    exist Create?". A Yes response displays the Edit Program List dialog box.
    This is where you specify the files in your program list. Enter the
    filenames TEXED.C, KEYS.C, and FILE.C. As you enter each, its name appears
    in the bottom window labeled Program List. After you enter all three
    files, your screen appears as in Figure 12-3. Now choose the Save List
    option to save your program list on disk and return to the main QuickC
    screen.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 12-3 can be found on p.382 of the printed version of the book.  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 12-3. The Edit Program List dialog box.

    At the bottom left of the QuickC screen you now see Program List: Texed.
    This message signals that you will build your program from several files,
    not only from the one currently loaded, and that those files are in the
    program list named Texed. TEXED.MAK has three files in it, and TEXED.C is
    one of them. Now, every time you open TEXED.C, QuickC reminds you that a
    .MAK file and various other files are connected to it.

    To compile a program from a program list, display the Compile dialog box,
    but this time, instead of selecting Compile File, select Build Program.
    Notice that each of your files is loaded in turn and compiled. After all
    three have been compiled, the Microsoft Overlay Loader executes. This link
    program combines your compiled files, along with any precompiled routines
    that you use from the standard C Library (such as printf()). This process
    creates a single, executable program that you can run from within QuickC.

Program List Files

    Program list files contain rules and instructions that tell QuickC how to
    build your program. They are composed of four elements: comment lines
    (lines that begin with a # character), production rules, dependencies, and
    link commands. Look inside the TEXED.MAK file that follows. This is a make
    file, a subset of the kind used by the MAKE program.

    #
    # Program; Texed
    #

    .c.obj:â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Production rule--turn a .C into a .OBJ
        qcl  -c  -W1  -Ze  -AM $*.câ”€â”€â”€â”€â”€â”€â”€â”€â”€How to accomplish the above rule

    texed.obj : texed.câ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Dependencies
                                    â”‚
    keys.obj : keys.câ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                                    â”‚
    file.obj : file.câ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Texed.exe : texed.obj keys.obj file.obâ”€More dependencies used to go from
            del Texed.lnk                     .OBJs to. EXEs
            echo texed.obj+ >>Texed.lnk
            echo keys.obj+ >>Texed.lnk
            echo file.obj >>Texed.lnk
            echo Texed.exe >>Texed.lnk
            echo Texed.map >>Texed.lnk
            link @Texed.lnk /NOI $(LDFLAGS);

    Production Rules in Program List Files

    A production rule is a description of how one file type is changed into
    another. For example, the production rule in our program list

    .c.obj:
        â””â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Turn a .C file into a .OBJ file

    tells QuickC to change .C files (such as KEYS.C) into precompiled object
    files called .OBJ files (such as KEYS.OBJ). Microsoft's Overlay Loader
    later links these .OBJ files with functions from the standard C Library to
    produce the executable program.

    The line following the production rule is the command line:

    qcl -c -W1 -Ze -AM $*.c

    This tells QuickC how to make the transformation specified in the first
    line. It is the same command line you would enter at the MS-DOS prompt,
    except for the $*.c. The $*.c tells QuickC to use the name of a real .C
    file, such as KEYS.C, at this position in the command line. The other
    elements represent the following:

    Element  Description
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    qcl      The command-line version of QuickC.
    -c       Compile to a .OBJ file and stop. That is, do not continue by
            calling LINK.
    -W1      Set the compile time warning level to level 1.
    -Ze      Handle language extensions, such as far, as reserved keywords.
    -AM      Use the medium-memory model.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Production rules are one of the features of QuickC program lists that make
    building programs easy. For example, when you select the Compile menu to
    compile KEYS.C, you don't have to enter the command line. Instead, QuickC
    runs the following MS-DOS command:

    qcl -c -W1 -Ze -AM keys.c

    and compiles KEYS.C into KEYS.OBJ.

    Dependency Lines in the Program List File

    Dependency lines tell QuickC how to create one file from two or more
    files. A dependency has the following form:

    target : infile1 infile2 ...

    This tells QuickC to create a new "target" file (usually a .OBJ or .EXE)
    if any infiles have changed and to make that target by running the
    specified MS-DOS command line. Examine the following dependency lines in
    TEXED.MAK:

    texed.obj : texed.c

    keys.obj : keys.c

    file.obj : file.c

    Texed.exe : texed.obj keys.obj file.obj
            del Texed.lnk
            ...

    Note that each of the first three lines is followed by a blank line (no
    MS-DOS command line). We'll discuss these first three dependencies first,
    then we'll cover the last in detail.

    When a dependency does not specify an MS-DOS command line, QuickC uses the
    previously defined production rule (.c.obj:) in place of the missing
    command line. For the first three lines, then, the command line derived
    from the production rule becomes the following:

    texed.obj : texed.c
        qcl -c -W1 -Ze -AM texed.c

    keys.obj : keys.c
        qcl -c -W1 -Ze -AM keys.c

    file.obj : file.c
        qcl -c -W1 -Ze -AM texed.c

    Running the Linker

    The dependency for TEXED.EXE, the executable file of your finished
    program, is as follows:

    Texed.exe : texed.obj keys.obj file.objâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Dependency

    The dependency tells QuickC to create TEXED.EXE from TEXED.OBJ, KEYS.OBJ,
    and FILE.OBJ.

    The LINK program combines your .OBJ files with subroutines from the
    standard C Library and creates an executable (.EXE) program as the result.
    When you run the LINK program, it asks you the following series of
    questions:

    Object Modules [.OBJ]:
    Run File [.EXE]:
    List File [NUL.MAP]:

    First, LINK asks for the names of the .OBJ files you want to combine to
    form your program. Add a + to each file that you specify to tell LINK that
    you will add more .OBJ files. The LINK program continues to prompt for
    object modules until you list one without a trailing +:

    Object Modules [.OBJ]:texed.obj+
    Object Modules [.OBJ]:keys.obj+
    Object Modules [.OBJ]:file.obj

    Next, LINK prompts for the name of your executable program (Run File). In
    our example, we enter the name texed.exe.

    Finally, LINK asks for the name of a "map" file. A map file merely
    contains a cross-referenced listing of your executable program. Therefore,
    you respond as follows:

    List File [NUL.MAP]:texed.map

    Using LINK from a Text File

    When you run LINK, you have the option to use a text file that contains
    the prewritten answers to its questions. To do this, when you run LINK,
    specify the file by preceding its name with an "at" character, @, as
    follows:

    link @Texed.lnk
                â””â”€â”€â”€â”€â”€â”€â”€â”€ File questions containing answers to LINK's questions

    To understand how this works, let's examine the MS-DOS commands that
    follow the dependency for TEXED.EXE in your TEXED.MAK program list file:

    Texed.exe : texed.obj keys.obj file.â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Dependency
            del Texed.lnkâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
            echo texed.obj+ >>Texed.lnk        â”‚
            echo keys.obj+ >>Texed.lnk         â”‚
            echo file.obj >>Texed.lnk          â”œâ”€â”€â”€â”€â”€â”€â”€ MS-DOS command lines
            echo Texed.exe >>Texed.lnk         â”‚
            echo Texed.map >>Texed.lnk         â”‚
            link @Texed.lnk /NOI $(LDFLAGS);â”€â”€â”€â”˜

    First, the file TEXED.LNK is deleted in case it already exists. Next, five
    "redirect and append" commands (>>) tell echo to place the text into the
    file TEXED.LNK. TEXED.LNK now contains the following lines:

    texed.obj+
    keys.obj+
    file.obj
    Texed.exe
    Texed.map

    Finally, LINK executes using the file @TEXED.LNK as the file that contains
    the answers to its questions. This is equivalent to running LINK yourself
    and answering those questions as follows:

    Object Modules [.OBJ]:texed.obj+
    Object Modules [.OBJ]:keys.obj+
    Object Modules [.OBJ]:file.obj
    Run File [.EXE]:Texed.exe
    List File [NUL.MAP]:Texed.map

    Other Arguments to LINK

    The LINK command in our TEXED.MAK program list file has two arguments in
    addition to the @TEXED.LNK argument:

        link @Texed.lnk /NOI $(LDFLAGS);
                        â”‚       â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Other flags
                        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Don't ignore case

    The first, /NOI, tells LINK not to ignore case. That is, it tells LINK to
    treat uppercase letters as different from lowercase letters in variable
    and function names.

    The second, $(LDFLAGS), is a make macro definition that QuickC defines as
    nothing. To modify your .MAK program list file and add arguments to LINK,
    you must define LDFLAGS. See Chapter 11 in your Microsoft QuickC
    Programmer's Guide for information about this procedure. But beware, the
    LDFLAGS macro is the only macro that QuickC recognizes and preserves.

Keeping Track of Changes

    QuickC keeps track of which files have changed in a program list. To see
    how this works, select Build Program from the Run menu. Now load the
    KEYS.C file and change it by inserting a blank line anywhere. Save that
    file and select Build Program again. This time, QuickC recompiles the
    KEYS.C file, but it does not compile the other two .C files because they
    haven't changed.

    Before QuickC runs a command line to create the target file from the
    infiles (based on a dependency in its program list), it first checks the
    modification dates for the target file and for each of the infiles. If
    this target was created after the infiles, QuickC doesn't need to
    recompile because the infiles have not changed. Specifically, in the
    dependency

    texed.obj : texed.c

    if TEXED.OBJ is newer than TEXED.C (its modification date and time is more
    recent), then QuickC does not recompile because TEXED.C has not changed
    since the last time it was compiled. But if TEXED.C is newer or if
    TEXED.OBJ doesn't yet exist, QuickC creates a new TEXED.OBJ by applying
    the .c.obj production rule and thus running the MS-DOS command line:

    qcl -c -W1 -Ze -AM texed.c

    This ability to know which files need to be recompiled makes QuickC a
    powerful tool for developing large and complex programs that are composed
    of many individual .C files.

Header Files

    Programs formed from separate .C files often share identical declarations.
    For example, examine the two files in Listings 12-8a and 12-8b on the
    following page. These parts of a larger text editor program both use
    structures of the same pattern, and both use the #define directive to
    define the values OK and ERROR. (These listings are not intended to be
    compiled and run independently.) If you need to change the structures (by
    adding a member, for example), or to change the definition of ERROR (from
    1 to -1, for example), you must make changes in both files (and possibly
    many other files if the text editor program uses those values throughout).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    #define OK 1
    #define ERROR 0
    menu()
    {
        struct key_struct {
            char key;
            unsigned char move;
        } *kp, *Read_kbd();
        int cur_key, cur_move;

        kp = Read_kbd();
        cur_key = kp->key;
        cur_move = kp->move;
        if (cur_key == ERROR)
            return (cur_move);
        return (cur_key);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-8a.  The TEXED.C file.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    #define OK 1
    #define ERROR 0
    struct key_struct {
        char key;
        unsigned char move;
    };

    struct key_struct *Read_key()
    {
        struct key_struct k;

        k.key = getch();
        if (k.key == ERROR)
            k.move = getch();
        return (&k);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-8b.  The KEYS.C file.

    Therefore, your program is easier to maintain if you gather such common
    definitions into a single, separate file called a "header file," or a .h
    file. Listing 12-9 shows one such header file for our text editor
    program. Now you can easily make changes that affect all files. Simply
    modify TEXED.C and KEYS.C to use the #include preprocessor directive, as
    shown in Listings 12-10a and 12-10b. Because we use full quotation marks
    with that directive (rather than angle brackets as with #include
    <stdio.h>), the compiler looks for the header file in our current working
    directory.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    #define OK 1
    #define ERROR 0

    struct key_struct {
        char key;
        unsigned char move;
    };
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-9.  The texed.h header file.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    #include "texed.h"
    menu()
    {
        struct key_struct *kp, *Read_kbd();
        int cur_key, cur_move;

        kp = Read_kbd();
        cur_key = kp->key;
        cur_move = kp->move;
        if (cur_key == ERROR)
            return (cur_move);
        return (cur_key);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-10a.  The TEXED.C file (modified).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    #include "texed.h"
    struct key_struct *Read_key()
    {
        struct key_struct k;

        k.key = getch();
        if (k.key == ERROR)
            k.move = getch();
        return (&k);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-10b.  The KEYS.C File (modified).

    Variables in Header Files

    You can also place declarations in header files that make variables global
    to all files. However, you cannot initialize variables in header files
    that are shared by more than one .C file. That is, in the header file
    texed.h,

    char Last_key;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Legal
    int  Upper_flag = 1;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Illegal

    the declaration for Last_key is always legal, but the declaration for
    Upper_flag is illegal because this .h file is specified by #include in
    several .C files.

    You can declare and initialize a global variable only once in a program.
    If you want to declare and initialize a global variable in one file and
    access that variable from another file, you must make this an explicit
    operation by placing the extern keyword in the second file, as follows:

    /* First file */  /* Second file */  /* Third file */
    ...               ...                ...
    int Key = 1;      extern int Key;    extern int Key;
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Initialized once among
                                                        several files

    The extern keyword tells QuickC that the integer Key is located in another
    file.

    If a global variable is not initialized as part of its declaration, you
    can declare it in all files without the extern keyword, as follows:

    /* First file */  /* Second file */  /* Third file */
    ...               ...                 ...
    int Key = 1;      extern int Key;    extern int Key;

    The extern keyword tells QuickC that the integer Key is located in another
    file.

    If a global variable is not initialized as part of its declaration, you
    can declare it in all files without the extern keyword, as follows:

    /* First file */  /* Second file */  /* Third file */
    ...               ...                ...
    int Key;          int Key;           int Key;

    This is the same as declaring it once in a header file and then specifying
    that header with #include, as follows:

    /* Header file "head.h" */
    ...
    int Key;

    /* First file */  /* Second file */  /* Third file */
    ...               ...                ...
    #include "head.h" #include "head.h"  #include "head.h"

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Dependencies in Header Files
    Because a change in a header file results in a change in a .C file, you
    might wonder if you can place header files into your QuickC program list
    as a dependency, as follows:

    texed.obj :  texed.c texed.h

    keys.obj : keys.c texed.h

    As this dependency is written, it tells QuickC (in our program list) to
    recompile TEXED.OBJ if either TEXED.C or texed.h changes and to recompile
    KEYS.OBJ if either KEYS.C or texed.h changes.

    QuickC does allow you to place header file dependencies into your program
    lists: It recognizes and maintains them, but it does not treat .h files as
    real dependencies. That means, for example, that TEXED.OBJ is not
    recompiled if only texed.h changes. This is intentional and not a bug.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Libraries

    In addition to listing .C files in a QuickC program list file, you can
    also list library (.LIB) files. Libraries are files that contain
    precompiled .OBJ files that you can use as part of a program.

    During the course of your programming, you will develop many general
    subroutines that can be used in many programs. By placing those
    subroutines into a special library, you can access them through a QuickC
    program list without having to recompile them. For example, consider the
    following three subroutines: leftstr.c (Listing 12-11), midstr.c (Listing
    12-12), and rightstr.c (Listing 12-13). (These subroutines, shown on
    pages 392-93, are C analogs to the BASIC functions LEFT$, MID$, and
    RIGHT$.)

    To create a library for these three subroutines, enter them using the
    QuickC editor, and then save each as an individual .C file. Now exit
    QuickC and compile each with qcl and the following MS-DOS commands:

    qcl /c /AM leftstr.c
    qcl /c /AM midstr.c
    qcl /c /AM rightstr.c

    qcl is the command-line version of QuickC. The /c tells QuickC to create a
    .OBJ file from the .C file, and /AM tells QuickC to use the medium-memory
    model.

    After you generate the three .OBJ files, you create a library for them by
    running the LIB program and answering its questions, as follows:

    Library name:basic.lib
    Library does not exist. Create?y
    Operations:+leftstr.obj&
    Operations:+midstr.obj&
    Operations:+rightstr.obj
    List file:

    The first and second lines tell LIB to create a library named BASIC.LIB.
    In the three Operations: lines, the + tells LIB that we are adding a .OBJ
    file to the library. The & following two of the lines is a signal that
    more files will be added. At the List file prompt we simply press Enter
    because our library is small, and we don't need a list of its contents.
    After a short wait, QuickC produces a library file named BASIC.LIB that we
    can place into any program list. To return to the QuickC menu, enter exit
    at the MS-DOS prompt.

    Now we'll create a program to test our library and demonstrate how to use
    a library from a program list. Enter the TEST.C program (Listing 12-14 on
    p. 393) and save it on disk. Next, choose Set Program List from the File
    menu and enter TEST.MAK as the name of the program list.

    After you press Enter and answer Yes to Test.mak doesn't exist. Create?,
    the Edit Program List dialog box appears. Select test.c as the first item
    in the list. Notice that the name of our library is not displayed. That's
    okay; simply type basic.lib. Finally, save this program list.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* leftstr.c -- a C version of BASIC's LEFT$ */

    #include <stdio.h>

    char *Leftstr(char *str, int cnt)
    {
        static char *cp = NULL;
        char *malloc();

        if (cnt > strlen(str))
            cnt = strlen(str);
        if (cp != NULL)
            free(cp);
        if ((cp = malloc(cnt + 1)) == NULL)
            return (NULL);
        strncpy(cp, str, cnt);
        return (cp);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-11.  The leftstr.c subroutine.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* midstr.c -- a C version of BASIC's MID$  */

    #include <stdio.h>

    char *Midstr(char *str, int where, int cnt)
    {
        static char *cp = NULL;
        char *malloc();

        if (cnt > strlen(str + where))
            cnt = strlen(str + where);
        if (cp != NULL)
            free(cp);
        if ((cp = malloc(cnt + 1)) == NULL)
            return (NULL);
        strncpy(cp, str+where, cnt);
        return (cp);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-12.  The midstr.c subroutine.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* rightstr.c -- a C version of BASIC's RIGHT$ */

    #include <stdio.h>

    char *Rightstr(char *str, int cnt)
    {
        static char *cp = NULL;
        char *malloc();

        if (cnt > strlen(str))
            cnt = strlen(str);
        if (cp != NULL)
            free(cp);
        if ((cp = malloc(cnt + 1)) == NULL)
            return (NULL);
        strcpy(cp, str + strlen(str) - cnt);
        return (cp);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-13.  The rightstr.c subroutine.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* test.c -- tests the routines in basic.lib */
    /* Program list: test.c and basic.lib        */

    #include <stdio.h>

    main()
    {
        static char string[] = "This is a test.";
        char *cp, *Leftstr(), *Midstr(), *Rightstr();

        printf("Testing: \"%s\"\n", string);

        if ((cp = Leftstr(string, 4)) == NULL)
            {
            printf("Error in Leftstr()\n");
            exit(1);
            }
        printf("Leftstr() returned: \"%s\"\n", cp);

        if ((cp = Midstr(string, 4, 5)) == NULL)
            {
            printf("Error in Midstr()\n");
            exit(1);
            }
        printf("Midstr() returned: \"%s\"\n", cp);

        if ((cp = Rightstr(string, 5)) == NULL)
            {
            printf("Error in Rightstr()\n");
            exit(1);
            }
        printf("Rightstr() returned: \"%s\"\n", cp);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 12-14.  The TEST.C program.

    At the QuickC editor, choose Compile from the Run menu. Because we are
    compiling from a program list, use Build Program to compile TEST.C and
    then combine it with the subroutines in BASIC.LIB.

    One additional advantage offered by .LIB files is that you can place them
    in your environmental LIB directory. From there, QuickC can find them no
    matter where you are in the directory hierarchy. The result of all this is
    that you need only one copy of common subroutines in a single library, and
    you can access those subroutines through a program list from any
    directory.

Quick Libraries

    QuickC offers another kind of library, called a Quick Library. This
    alternative library can be loaded into memory when you first run QuickC.
    The advantage it offers is that you don't need to use a program list to
    access the subroutines in it.

    Let's build a Quick Library using the same subroutines that we used to
    build BASIC.LIB: leftstr.c (Listing 12-11), midstr.c (Listing 12-12),
    and rightstr.c (Listing 12-13). Begin by running qcl to create the .OBJ
    files:

    qcl /c /AM leftstr.c
    qcl /c /AM midstr.c
    qcl /c /AM rightstr.c

    Now run LINK to create the Quick Library:

    link
    Object Modules [.OBJ]:c:\lib\quicklib.obj +
    Object Modules [.OBJ]:leftstr.obj +
    Object Modules [.OBJ]:midstr.obj +
    Object Modules [.OBJ]:rightstr.obj /Q
    Run File [C:QUICKLIB.QLB]:basic.qlb /NOI
    List File [NUL.MAP]:
    Libraries [.LIB]:

    In this example, c:\lib\quicklib.obj is the full pathname of a special
    object file that you must use as the first listing in your Quick Library.
    (We've stored the file in the C:\LIB directory, but you can use any
    directory. We suggest that you specify your environmental LIB directory.)
    The + characters tell LINK that we will list more object files. The /Q
    after the last .OBJ tells LINK that this is a Quick Library. Then we
    specify basic.qlb as the name of our Quick Library and follow that name
    with /NOI, which tells LINK not to ignore case. Finally, we press Enter to
    skip the final prompts, List File and Libraries.

    Now you can have QuickC load the BASIC.QLB Quick Library every time you
    run QuickC. To do this, use the QuickC /l command-line argument, as
    follows:

    qc /lbasic.qlb test.c

    This tells QuickC first to load the BASIC.QLB Quick Library and then to
    load TEST.C in the editor. (Before you do this on your system, erase the
    TEST.MAK program list; otherwise, QuickC will try to use the .OBJ files
    from the disk rather than from your new Quick Library.)

    Now, when you compile TEST.C, QuickC always finds the functions Leftstr(),
    Midstr(), and Rightstr() in memory. Notice how much faster TEST.C compiles
    when you use this approach.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€