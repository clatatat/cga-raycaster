Chapter 16  Debugging

    Ever since that fateful day in the 1940s when a moth flew into the back of
    a computer and caused a vacuum tube to short circuit, programmers have
    been beset by bugs. Most errors, however, are not ex machina; they are
    caused by programmers themselves.

    Myriad are the ways in which a programmer can err. One common type of
    program error can be classed as the misuse of symbols. For example, you
    can mistype words and operators, misemploy keywords, and jumble syntax.
    You detect most of these errors before a program ever runs. Logic errors,
    the second major class of errors, are more insidious. These often carry
    through to an operational program, producing mysterious behavior.

    Fortunately, the situation is not hopeless. The compiler helps detect many
    kinds of errors, and the QuickC debugger can actually help trace errors in
    logic. In this chapter, we try to increase your awareness of common types
    of errors so that you can develop practices that reduce the likelihood of
    going astray in the first place. Many of the errors we show might seem
    obvious because we present them as the central attractions in short
    programs. However, in the context of a large and complex program, these
    errors are much more difficult to notice.

    Debugging, or the finding of errors, can be a challenging, frustrating,
    rewarding, and time-consuming process. It requires a different mind-set
    than programming. Programming is an inventive, creative process. Although
    debugging can require creativity, it is primarily an investigative
    process. You must transform yourself from a designer into a sleuth.


Keyboard-Entry Errors

    With each line of code you enter from the keyboard, you run the risk of
    mistyping a word and creating an error. Fortunately, the compiler detects
    most of these errors.

    The MISIDENT.C program (Listing 16-1) is an error-laden program. When you
    compile it, QuickC returns the following message:

    Fatal error C1021: (1 of 1)
    bad preprocessor command 'defne'

    If you use QuickC's integrated environment, the compiler places the screen
    cursor on the line containing this error. If you run QuickC with QCL
    instead of QC, the compiler labels the error with a line number.

    What does this error message mean? When you compile a program, QuickC
    first runs a preprocessor to process the # statements. The preprocessor
    recognizes a limited set of directives, and #defne is not one of them.
    Note that compilation stops immediatelyâ”€â”€before it checks for program
    errors.

    To correct the error, replace #defne with #define and compile the program
    again. This time the compiler generates the error messages on the
    following page.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* misident.c -- careless typing              */

    #defne BIG 3
    main()
    {
        char ltr;
        integer num;

        num = 2 + BIG;
        lrt = 'a';
        printf("%c %d\n", ltr, num);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-1.  The MISIDENT.C program.

    error C2065: (1 of 4)
    'integer' undefined

    error C2146: (2 of 4)
    syntax error: missing ';' before identifier 'num'

    error C2065: (3 of 4)
    'num' : undefined

    error C2065: (4 of 4)
    'lrt' : undefined

    When QuickC finds several errors, it displays one message at a time, using
    the cursor to mark the applicable line. Shift-F3 advances one error
    message, and Shift-F4 backs up a message.

    This example illustrates one of the virtues of declaring variables.
    Because lrt was undeclared, the compiler quickly spots the "typo" as an
    error. It also shows how a simple error can produce several different
    error messages. The compiler fails to recognize integer as a type;
    therefore, it fails to understand that the statement is a type
    declaration. It detects a syntax error and views num as undefined.

Defensive Programming

    One way to reduce errors such as typing lrt for ltr is to use recognizable
    words as identifiers. If you scan through a long program, you can easily
    misread lrt for the intended ltr. But if you use a name such as letter,
    mistypings such as lerret or lettre are much more likely to catch your
    eye.

An Anomalous Example

    The compiler does not catch all typos. The BADSIGN.C program (Listing
    16-2) is an interesting example of this.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* badsign.c -- uncaught typo                 */

    main()
    {
        int i;
        int j = 1;

        for (i = 0; i < 10; i++)
            {
            j =+ 10;         /* transposed += */
            printf("%4d ", j);
            }
        printf("\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-2.  The BADSIGN.C program.

    This program is meant to print the numbers 1, 11, 21, 31, and so on by
    incrementing j by 10 during each loop cycle. Instead, it prints the
    following:

    10   10   10   10   10   10   10   10   10   10

    What happens is that the program uses =+ instead of +=. In the early days
    of C, the addition assignment operator was written =+, so at that time,
    the program would have run as intended. Later, after the switch was made
    from =+ to +=, this program might have run correctly but with a compiler
    warning message. If the compiler was not tolerant of anachronisms, it
    might have rejected the program altogether for using an unknown operator.

    QuickC runs it with no complaints about anachronisms or unknown
    operatorsâ”€â”€but the program produces unwanted results. The reason the
    program runs is that under the new ANSI standards for C, the + operator is
    recognized as a valid unary operator, so QuickC reads the assignment
    statement as follows:

    j = +10;

    That is, assign positive 10 to j. Under the old standard, the + could be
    used only as a binary operator to indicate addition. The moral here is:
    Don't be certain that the compiler will catch all mistypings.

    This particular error was easy to localize because j was printed every
    loop cycle. If j were not printed, finding the problem could be more
    difficult.

    One final point: C, unlike many popular languages, is case sensitive, so
    porter, Porter, and PORTER are three distinct identifiers. If you aren't
    used to this convention and QuickC rejects what you consider a valid
    identifier, check your usage of case.


Syntax Errors

    Syntax errors occur when you use valid symbols in an invalid manner.
    Because the compiler must recognize and enforce valid syntax, it will
    always catch these errors. However, it might not correctly interpret what
    you were trying to do.

Misuse of Operators

    The POWER.C program (Listing 16-3) might be written by a FORTRAN
    programmer who is accustomed to using the exponentiation operator of that
    language.

    Interestingly enough, QuickC doesn't complain that the FORTRAN
    exponentiation operator (**) is unknown. Instead, it returns the following
    error message:

    error C2100 : (1 of 1)
    illegal indirection

    As it happens, ** is also a valid operator in C; however, its C meaning is
    quite different than the FORTRAN meaning. In C, ** means "the value at the
    address pointed to by another address." Thus, it should be applied only to
    a quantity that has been declared to be a pointer to a pointer, and the
    number 3 fails to satisfy that requirement. The illegal indirection
    message indicates that the compiler thinks you used a pointer incorrectly.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* power.c -- attempt to raise to a power      */

    main()
    {
        int number;

        number = 10**3; /* raise 10 to 3rd power? */
        printf("%d\n", number);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-3.  The POWER.C program.

A Scrambled Operator

    In the CONDITN.C program (Listing 16-4), we reverse the order of the :
    and the ? in the conditional operator. The compiler finds the error, but
    the error message is not very illuminating:

    error C2143
    syntax error : missing ';' before ':'

    If you follow QuickC's analysis blindly and insert a semicolon before the
    colon, you receive the same error message when you compile again:

    error C2143
    syntax error : missing ';' before ':'

    The moral here is: The compiler is much better at detecting syntax errors
    than it is at figuring out exactly what went wrong. QuickC is reliable in
    locating a syntax error; however, you must take the analysis with a grain
    of salt. If the problem doesn't seem to be in the indicated line,
    carefully read its immediate neighbors.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* conditn.c -- attempt to use conditional op */

    main()
    {
        int n, m;

        n = 2;
        m = (n != 2) : 0 ? 1;  /* almost right */
        printf("%d\n", m);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-4.  The CONDITN.C program.

Another Anomalous Example

    The human capacity to err far exceeds the capabilities of compilers to
    respond helpfully. The DOWHILE.C program (Listing 16-5) provides an
    example.

    QuickC places the cursor on the VOOOM line and returns the following
    message:

    error C2061 : (1 of 1)
    syntax error: identifier 'printf'

    Apparently, the compiler doesn't recognize printf() as the name of a
    function. Because the compiler accepted the first printf() without
    complaint, this is a puzzling message. Indeed, not one of the lines near
    the reported error seems wrong.

    The error lies in our misuse of the do while loop. DOWHILE2.C (Listing
    16-6) shows the correct version of the command.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* dowhile.c -- misuse of do while loop     */

    main()
    {
        int i = 0;

        do while (i < 10)
            {
            printf("Happy Fourth of July!\n");
            i++;
            }
        printf("VOOOM\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-5.  The DOWHILE.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* dowhile2.c -- ok use of do while loop     */

    main()
    {
        int i = 0;

        do
            {
            printf("Happy Fourth of July!\n");
            i++;
            } while (i < 10) ;
        printf("VOOOM\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-6.  The DOWHILE2.C program.

    The first version had no obvious error near the marked line. But sometimes
    it is not enough to look at nearby lines. The compiler thinks in terms of
    statements, and the entire do while loop counts as a single statement. In
    that sense, the error was near the marked lineâ”€â”€it was in the immediately
    preceding statement, which happened to cover several lines. The moral here
    is: If QuickC shows an error in a line following an extended statement and
    you don't see a mistake in the marked line, check the syntax of the entire
    preceding statement.

Macro Problems

    When you use macros, the meaning of an error message might not be obvious.
    The compiler preprocessor first replaces the macros with the corresponding
    code. Next, it tries to compile the program. Thus, these compiler error
    messages refer to the substituted code, not your original code. This can
    be confusing, especially if you are using a system macro with which you
    are not familiar. The following BADPUTC.C program (Listing 16-7) looks
    innocent enough:

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* badputc.c -- misuses putc()                   */

    #include <stdio.h>
    main()
    {
        FILE *fp;
        int ch;

        if ((fp = fopen("junk", "w")) == NULL)
            exit(1);

        while ((ch = getchar()) != EOF)
            putc(fp, ch);
        fclose(fp);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-7.  The BADPUTC.C program.

    However, the compiler places the cursor on the putc() line and delivers
    the following messages:

    error C2036: (1 of 9)
    left of '->_cnt' must have a struct/union type

    error C2105: (2 of 9)
    'â”€â”€' needs lvalue

    error C2036: (3 of 9)
    left of '->_ptr' must have a struct/union type

    error C2105: (4 of 9)
    '++' needs lvalue
    error C2100: (5 of 9)
    illegal indirection

    warning C4047: (6 of 9)
    'argument': different levels of indirection

    warning C4024: (7 of 9)
    '_flsbuf': different types: parameter 1

    warning C4047: (8 of 9)
    '=' : different levels of indirection

    warning C4024: (9 of 9)
    '_flsbuf': different types: parameter 2

    These comments don't seem to relate to our code because we don't use
    ->_cnt and so on. However, putc() is a macro defined in stdio.h, and we
    can use the /P option of the QCL compiler-linker to see what a file looks
    like after the preprocessor finishes with it.

    Here's the proper command line:

    qcl /P badput.c

    QuickC gives the processed file the same basename as the original, but it
    adds a .I extension. Listing 16-8 shows part of that processed file. We
    add comments to indicate the location of the getchar() and putc() macros.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* badputc.i -- preprocessed putfile.c          */
    /*  Not shown are all the stdio.h contents that */
    /*  come at the top of the file.                */

    main()
    {
        struct _iobuf *fp;
        int ch;
        if ((fp = fopen("junk", "w")) == 0)
            exit(1);

        /* original was while ((ch = getchar()) != EOF) */
        while ((ch = (--((&_iob[0]))->_cnt >= 0 ? 0xff &
            *((&_iob[0]))->_ptr++ : _filbuf((&_iob[0]))))
            != (-1))

        /* original was putch(fp, ch); */
            (--(ch)->_cnt >= 0 ? 0xff &
            (*(ch)->_ptr++ = (fp)) : _flsbuf((fp),(ch)));

        fclose(fp);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-8.  The BADPUTC.I file.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    The getc() Macro

    The previous getc() and putc() macros might be a little obscure. Let's
    take a closer look at one of them to see what it does. The following is
    the macro definition for getc():

    #define  getc(f)  (--(f)->_cnt >= 0 ? 0xff & *(f)->_ptr++ : _filbuf(f))

    This defines getc() as a conditional expression having the form A ? B : C.
    If A is nonzero, the entire expression has the value of the B expression;
    if A is zero, the entire expression has the value of the C expression. The
    first operand (A) for the conditional expression is as follows:

    --(f)->_cnt >= 0

    Loosely translated, this means, "Decrement the _cnt member of the
    structure pointed to by f, and check if the result is greater than 0."
    From the definition, f is the argument to getc() and is a pointer to type
    file. Type file, in turn, is defined in stdio.h as a structure:

    extern FILE {
        char *_ptr;
        int   _cnt;
        char *_base;
        char  _flag;
        char  _file;
        } _NEAR _CDECL _iob[];

    This structure describes the file and the I/O buffer in use. The _cnt
    member describes the number of characters left in the buffer. If the
    number is greater than zero, then a character remains to be read, and the
    entire expression has the value of operand B, or:

    0xff & *(f)->_ptr++

    The first part (0xff ) is a mask to limit the final value to a byte. The
    second part (*(f)->_ptr++) is the value pointed to by the _ptr member of
    the structure pointed to by f. The _ptr member points to the current
    location in the buffer. Thus, if _cnt indicates that a character remains
    to be read, getc() evaluates to the buffer character currently pointed to.
    The increment operator then moves the pointer to the next buffer location.
    If, however, no characters remain, the entire expression has the value of
    the final operand:

    _filbuf(f)

    This is a "hidden" C function (one that the compiler uses but that is not
    part of the public library of C functions); it copies characters from the
    file to the buffer, reinitializes _ptr to point to the beginning of the
    buffer, and resets _cnt to the number of characters in the buffer. It also
    returns the value of the first character in the buffer or of EOF if the
    end of file has been reached. Therefore, if the buffer is empty, you can
    call this function to refill it.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Now that we see the actual code that is passed to the compiler, the
    message

    error C2036: (1 of 6)
    left of '->_cnt' must have a struct/union type

    makes sense. The code contains the following expression:

    --(ch)->_cnt

    Because the macro uses the -> operator with a pointer to a structure, this
    code suggests that ch should be a pointer to a structure. It isn't, so the
    compiler reports an error. However, note that fp is a pointer to a
    structure. If we switch fp with ch in the code, the code makes sense. And
    that's our mistakeâ”€â”€we should have used putc(ch, fp) rather than putc(fp,
    ch).

    This example illustrates one of the dangers of macros: They offer no
    provision for function prototyping or for checking the types of arguments.
    The example also illustrates the usefulness of viewing a file's
    preprocessor listing.


Run-Time Errors

    The most difficult errors to detect are those that the compiler misses.
    These errors can be inadvertent, such as the =+ error, or they can arise
    from logical errors in the design of the program.

Function Argument Problems

    If you don't use function prototypes, C does not try to match the types
    you pass to the expected types. Problems here can produce odd results, as
    the SUMNUMS.C program (Listing 16-9) points out.

    After the program initializes a to 10.0 and b to 20.0, it passes them to
    sums() to be added. The final output is as follows:

    sum of 10.0 and 20.0 is 0

    Clearly, this is false. To see what went wrong, compile in the Debug mode
    and set watch variables for a and x. Select the Trace feature from the
    Debug menu and use the F8 key to step through the program. At first, the
    value of a is undefined, but after the declaration is executed, variable a
    contains the correct value of 10. However, when the sums() function is
    entered, x is set to 0. Therefore, the problem must occur in the passing
    of arguments.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* sumnums.c -- type mismatch in function arguments  */
    /*              No function prototyping              */

    int sums();

    main()
    {
        float a = 10.0;
        float b = 20.0;
        int c;

        c = sums(a, b);
        printf("sum of %.1f and %.1f is %d\n", a, b, c); ;
    }

    int sums(x, y)
    int x, y;
    {
        return (x + y);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-9.  The SUMNUMS.C program.

    Knowing how C passes arguments can provide insight into the nature of this
    problem. Consider the call sums(a, b). First, QuickC converts float types
    to double when passing them as arguments. On a PC, this means that a and b
    are now 8-byte quantities. Next, the arguments are put into a memory area
    called the stack. The last argument, b, is pushed onto the stack first.
    (See Figure 16-1 on the following page.)

    When the called function executes, it reads the values off the stack and
    assigns them to its formal parameters. It uses the declared types of the
    formal parameters to determine how many bytes to read. And this is where
    the problem arises. Because the formal parameters x and y are declared to
    be type int, the sums() function reads two bytes off the stack for the
    value of x and the next two bytes for the value of y. (It should read
    eight bytes for x and eight bytes for y.)

    The net result of this process is that the first two bytes of a are
    assigned to x and the next two bytes of a are assigned to y. This leaves
    four bytes of a and all eight bytes of b unread, as illustrated in Figure
    16-2 on p. 565. Consequently, it is not surprising that the function gets
    the wrong values from the stack.

            b is 4-byte float
            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”
            â”‚        â”‚        â”‚        â”‚   20   â”‚
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    b is converted to double
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚        â”‚        â”‚        â”‚        â”‚        â”‚        â”‚        â”‚  20    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜


                        â”Œâ”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”
                        â”‚ â”‚  20   â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
    B is placedâ”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”‚ â”‚       â”‚
    in stack            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”œâ”€â”‚  10   â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
    Then a goesâ”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
    through the         â”‚ â”‚       â”‚
    same process        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
                        â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        â”‚ â”‚       â”‚
                        â””â”€â””â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 16-1. Passing arguments by means of the stack.

                            â”Œâ”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”
                            â”‚ â”‚  20   â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                            â”‚ â”‚       â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                            â”‚ â”‚       â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                            â”‚ â”‚       â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                        bâ”€â”€â”€â”€â–ºâ”‚ â”‚       â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                            â”‚ â”‚       â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                            â”‚ â”‚       â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
    Function call places     â”‚ â”‚       â”‚
    double arguments on      â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
    stack                    â”œâ”€â”‚  10   â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                            â”‚ â”‚       â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                            â”‚ â”‚       â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                            â”‚ â”‚       â”‚
                        aâ”€â”€â”€â”€â–ºâ”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”
                            â”‚ â”‚       â”‚ â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤ â”œâ”€â”€â”€â–ºy
                            â”‚ â”‚       â”‚ â”‚
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤      Called function removes
                            â”‚ â”‚       â”‚ â”‚      values from stack
                            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤ â”œâ”€â”€â”€â–ºx
                            â”‚ â”‚       â”‚ â”‚
                            â””â”€â””â”€â”€â”€â”€â”€â”€â”€â”˜â”€â”˜

    Figure 16-2. Misaligned data.

Function Prototyping to the Rescue

    The SUMNUMS2.C program (Listing 16-10) shows what happens when we add
    function prototyping to the previous example.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* sumnums2.c -- type mismatch in function arguments */
    /*               Function prototyping                */

    int sums(int, int);
    main()
    {
        float a = 10.0;
        float b = 20.0;
        int c;

        c = sums(a, b);
        printf("sum of %.1f and %.1f is %d\n", a, b, c);
    }
    int sums(x, y)
    int x, y;
    {
        return (x + y);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-10.  The SUMNUMS2.C program.

    The program now generates the correct output:

    sum of 10.0 and 20.0 is 30

    With function prototyping, a and b are converted to type int before going
    onto the stack, and sums() can retrieve the correct values. (See Figure
    16-3.)

                            â”Œâ”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”â”€â”
                            â”‚ â”‚  20   â”‚ â”‚
                        bâ”€â”€â–ºâ”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤ â”œâ”€â”€â–ºy
    Function call          â”‚ â”‚       â”‚ â”‚     Called function removes
    places int argument    â”œâ”€â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤     int values from stack
    on stack               â”‚ â”‚  10   â”‚ â”‚
                        aâ”€â”€â–ºâ”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¤ â”œâ”€â”€â–ºx
                            â”‚ â”‚       â”‚ â”‚
                            â””â”€â””â”€â”€â”€â”€â”€â”€â”€â”˜â”€â”˜

    Figure 16-3. Passing arguments with function prototyping.

    This is a convenient feature, but it can lead to another kind of error by
    not alerting you to a type mismatch. After all, the fact that you are
    passing the wrong type of argument can indicate a programming error. Or
    you may lose part of the data when converting from float to int. To use
    function prototyping without having to worry about missed errors, you
    merely need to select a higher warning level.

Warning Levels

    QuickC issues both error messages and warnings. Errors are mistakes that
    prevent compilation. Warnings alert you to usages that might be wrong but
    which don't prevent compilation. QuickC maintains four warning levels.
    Level 0 informs you only of errors. Level 1, the default, displays warning
    messages for those conditions most likely to cause problems, such as
    mixing levels of indirection in a pointer expression. Level 2 displays
    more warning messages, adding situations that are not usually serious
    problems, such as failing to declare as void a function without a return
    value. Level 3 warns of everything, including such "nonerrors" as non-ANSI
    keywords and omitted function prototypes.

    To see the effect of these warning levels, compile SUMNUMS2.C using all
    four levels. Levels 0 and 1 produce no warnings. Level 2, however,
    produces the following list of warnings:

    warning C4051: (1 of 6)
    data conversion

    warning C4051: (2 of 6)
    data conversion

    warning C4051: (3 of 6)
    data conversion

    warning C4051: (4 of 6)
    data conversion

    warning C4016: (5 of 6)
    'printf' : no function return type, using 'int' as default

    warning C4035: (6 of 6)
    'main' : no return value

    The first two warnings refer to the declarations for a and b. The reason
    for the warning is that C floating-point constants are always type double,
    yet a and b are declared type float. Because float uses fewer bytes, the
    potential exists for a partial loss of data.

    The second two warnings refer to the two conversions that take place in
    the sums() function call as a result of function prototyping. Because the
    values change from float to int, there is the possibility of a partial
    loss of data.

    The fifth warning tells us that we haven't declared the return type for
    the printf() function. Fix this by including the stdio.h file.

    The final warning informs us that main() has no return value. Because we
    did not explicitly declare a type for main(), the compiler assumes that
    main() is type int. Therefore, it expects main() to have an integer return
    value. To avoid this warning, declare main() as type void or provide a
    return value at the end of the function.

    Warning level 3 offers two new warnings, numbers 1 and 7:

    warning C4103: (1 of 8)
    'main' : function definition used as prototype

    warning C4051: (2 of 8)
    data conversion

    warning C4051: (3 of 8)
    data conversion
    warning C4051: (4 of 8)
    data conversion

    warning C4051: (5 of 8)
    data conversion

    warning C4016: (6 of 8)
    'printf' : no function return type, using 'int' as default

    warning C4071: (7 of 8)
    'printf' : no function prototype given

    warning C4035: (8 of 8)
    'main' : no return value

    The two new warnings lament the lack of function prototypes for the main()
    and printf() functions. If you want to check for the presence of function
    prototypes, go to warning level 3. To see if prototype conversions risk
    losing data or precision, level 2 is sufficient.


Common Run-Time Errors

    Some programming errors arise from the design of the C language itself.
    After we discuss how to avoid such errors in simple contexts, we will
    demonstrate how to detect them in more complex contexts.

The Misleading If Statement

    We begin with an error that almost every C programmer has made more than
    once. The LINE_CNT.C program (Listing 16-11) counts lines of input. It
    reads each character to EOF, which is signaled by Ctrl-Z with the
    getchar() function. A newline character increments the line count (lines).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  line_cnt.c -- an overly active line counter       */

    #include <stdio.h>
    main()
    {
        int ch;
        int lines = 0;

        while ((ch = getchar()) != EOF)
            if (ch = '\n')
                lines++;
        printf("There were %d lines\n", lines);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-11.  The LINE_CNT.C program.

    Following is a sample run:

    Cat <Enter>
    Hat <Enter>
    Bat <Enter>
    Ctrl-Z <Enter>
    There were 12 lines

    The problem is that we used the assignment operator (=) instead of the
    is-equal-to relational operator (==). Consider this statement:

    if (ch = '\n')
        lines++;

    This assigns the character \n to ch, giving it the numeric value of 10
    (the corresponding ASCII code). The entire expression ch = '\n' now has
    the value 10, which, being nonzero, is interpreted as being true. Thus,
    lines is incremented for every character, regardless of value. Because
    this is a legal construction, QuickC returns no syntax error message.

    Knowing about this potential error is not enough to protect you from
    occasionally making it, especially if you are a Pascal programmer
    accustomed to using = for comparison. It is not an eye-catching error.
    How, then, can we detect it in a large program listing?

    The telltale sign is an if branch or while loop that always executes, even
    when you think it shouldn't. The use of = instead of == isn't the only
    possible cause, but it is the first you should look for.

    The Debug facility can help find this type of bug. Suppose we didn't know
    what was wrong with Listing 16-11. We could select the Debug option, set
    a watch on ch, and use the c modifier (separated from ch by a comma) to
    display the value of ch as an ASCII character.

    As we first trace through the program, ch is undefined. After it is
    declared (but not initialized), it has a garbage value. Next, if we enter
    the word Cat as input, we see ch take the value C as we enter the if
    statement. When control goes to the lines++; statement, we see that ch now
    is '\n'. Therefore, ch is being assigned a new value, and that tells us to
    look for an incorrect assignment statement.

Examining Arrays, Part 1

    One of the most common tasks for a for loop is to process the elements of
    an array. The INDEXER.C program (Listing 16-12 on the following page) is
    a simple example that is meant to initialize three arrays, calculate the
    number of elements in the second array, and display its contents.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* indexer.c -- uses indexes to display an array     */

    #include <stdio.h>
    int code1[] = {2, 4, 6, 8};
    int code2[] = {1, 3, 7, 9};
    int code3[] = {5, 10, 15, 20};
    main()
    {
        int index;
        int size = (sizeof code2) / (sizeof (int));

        for (index = 1; index <= size; size++)
            printf("%3d ", code2[index]);
        putchar('\n');
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-12.  The INDEXER.C program.

    Instead, it prints the character 3 until you press Ctrl-Break.

    The reason for this failure is that the program increments size instead of
    incrementing the index variable. Thus, index remains at 1, while the
    comparison limit grows. (Eventually, the loop halts when size exceeds the
    maximum int value and becomes negative.) This is a C error that is
    inherent in the language. Most languages increment the loop variable for
    you, thus preventing you from making the mistake. C, as usual, chooses
    flexibility over the more restrictive but trouble-free approach.

    If you don't catch this error in the code, however, how can you spot it
    later? One way is to monitor the program as it runs. The QuickC Debug
    option provides a quick and simple method. If you have problems in a loop,
    set a watch on the loop index. Making index a watch variable and tracing
    through the above program soon reveals that index does not change, and
    that directs your attention to the update portion of the for control
    statement.

Examining Arrays, Part 2

    Fixing the above size error results in the INDEXER2.C program (Listing
    16-13). Running the revised program produces the following ouput:

    3   7   9   5

    Because the values should be 1, 3, 7, and 9, the program still fails. The
    new problem is the array index range. Array numbering starts with 0, not
    1. Thus, the correct limits for the loop are as follows:

    for (index = 0; index < size; index++)

    The original limits print the last three members of the array and the
    first element of the array that followed code2 in memory.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* indexer2.c -- uses indexes to display an array     */

    #include <stdio.h>
    int code1[] = {2, 4, 6, 8};
    int code2[] = {1, 3, 7, 9};
    int code3[] = {5, 10, 15, 20};
    main()
    {
        int index;
        int size = (sizeof code2) / (sizeof (int));
                    /* get number of elements in array */

        for (index = 1; index <= size; index++)
            printf("%3d ", code2[index]);
        putchar('\n');
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-13.  The INDEXER2.C program.

    The index limit error is easy to make, especially if you are accustomed to
    languages such as BASIC and FORTRAN, which start numbering from 1. This
    error is difficult to detect because C does not check for bounds errors.
    (Pascal gives a run-time error message when an index becomes too large or
    small; C doesn't.) You can use Debug to trace the array index, but that
    doesn't help if you forget the proper limits.

    You can prevent this error by habitually using a standard form for the for
    loop. For example, if an array has size elements, use either

    for (index = 0; index < size; index++) /* OK */

    or

    for (index = 0; index <= size - 1; index++) /* OK */

    but don't alternate between the two forms. If you do, you increase your
    chances of producing an incorrect hybrid form, such as the following:

    for (index = 0; index <= size; index++)  /* NO */

Mirror Words

    The BACKWARD.C program (Listing 16-14 on the following page) is designed
    to print a word in normal order and then reverse the order of the letters.

    A quick look at the program suggests that its output should be as follows:

    trap backwards is part

    And, indeed, the program prints that out. But it doesn't stop there. It
    keeps on printing. Some of the output is garbage, some appears to be words
    and phrases spelled backward. What went wrong?

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* backward.c -- the backwards word displayer         */

    #include <stdio.h>
    #define SIZE 5
    char word[SIZE] = "trap";
    main()
    {
        unsigned int index;

        printf("%s backwards is ", word);
        for (index = SIZE - 2; index >= 0; index--)
            putchar(word[index]);
        putchar('\n');
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-14.  The BACKWARD.C program.

    The first things to check when a loop unexpectedly becomes infinite are
    the loop's control statements. In this case, they look reasonable:

    (index = SIZE - 2; index >= 0; index--)

    SIZE is the number of elements, so SIZE - 1 is the index of the
    terminating null character, and SIZE - 2 is the index of the final
    character in the word. Each loop decrements the index by 1, thus moving
    back a character. When index reaches 0, the loop should display the last
    character and stop. But it doesn't. In this loop, the obvious variable to
    examine is index. Compile the program in the Debug mode, set a watch on
    index, and trace through the program step by step. The value of index
    follows this sequence: 3, 2, 1, 0, 65535, 65534, and so on. The index
    variable never becomes less than 0, so the loop never ends. Why not?
    Because index is declared an unsigned int. Change the type to int, and the
    program works properly. What at first looked like a looping error turns
    out to be a type error.

    The moral here is: Be careful when comparing unsigned quantities to zero.
    For example, if index is unsigned, index >= 0 is always true, and index <
    0 is always false. But index <= 0 can be either true or false.

Operator Priorities

    Because C has so many operators, you might at first have difficulty in
    remembering all the operator priorities. Certainly, multiplication has a
    higher priority than addition, but how do the increment operator and the
    indirect value operators compare? Does *ps++ mean (*ps)++ (use the
    pointed-to value and then increment the value) or *(ps++) (use the
    pointed-to value and then increment the pointer)? The second choice is the
    correct one; if you think the first interpretation is correct, you won't
    get the results you expect.

    For another example of priorities, consider the binary shift operator used
    in the SHIFTADD.C program (Listing 16-15).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* shiftadd.c -- shifts and adds numbers             */

    main()
    {
        int x = 0x12;
        int y;

        y = x << 8 + 2;
        printf("y is 0x%x\n", y);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-15.  The SHIFTADD.C program.

    From appearances, this program should left-shift x 8 places and then add
    2. Because each hex digit represents four binary digits, a left-shift of 8
    in binary is a 2-digit shift left in hex, so x << 8 is 0x1200. Adding 2
    gives 0x1202. But when you run the program, it prints a value of 0x4800.
    Addition has a higher priority than shifting; therefore, QuickC interprets
    the code as: Add 2 to 8 and do a 10-bit left-shift.

    You can find this type of error by using the Debug mode: Trace the values
    as they are calculated and compare them to calculations you perform by
    hand or with the assert() macro we discuss later.

    The best way to solve the problem is to avoid it in the first place. If
    you're not sure of priorities, look them up. The QuickC Help menu provides
    quick access to this information. Another method of avoiding the problem
    is always to use parentheses to clarify your intent, as follows:

    (x << 8) + 2

Scanning Problems

    The IBMIQ.C program (Listing 16-16) reveals one of the most common C
    errors.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* ibmiq.c -- a short dialogue                        */

    #include <stdio.h>
    main()
    {
        char name[80];
        int iq;

        printf("Enter your first name: -> ");
        scanf("%s", name);
        printf("Enter your IQ: -> ");
        scanf("%d", iq);
        printf("Well, %s, my IQ is %d!", name, 2 * iq - 1);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-16.  The IBMIQ.C program.

    The following is a sample dialogue produced by the program:

    Enter your first name: -> Mortimer
    Enter your IQ: -> 88
    Well, Mortimer, my IQ is -1!
    run-time error R6001
    -null pointer assignment

    Notice that the computer claims an IQ of -1 rather than the 175 you might
    expect from glancing at the program. Also, QuickC does not issue the
    run-time error message until after the program ends. These errors occur
    because in the second scanf() call, the program uses iq rather than the
    correct &iq.

    Most programmers make this kind of error through carelessness. For
    example, here we just used name as an argument. And because name didn't
    need the & operator, it's easy to forget that iq does.

    Let's look at the mechanics of this error and at the error message itself.
    The following sequence of events occurs. First, iq starts with a value of
    0. (We know this because that's the value that produces -1 for the machine
    IQ. You can also use the Debug mode to verify the iq value.) The scanf()
    function interprets 0 as the address 0; that is, it thinks it received a
    pointer to NULL. It then places the number 88 at that address rather than
    in iq. (See Figure 16-4.) Therefore, iq remains 0, and the program
    calculates the machine IQ as -1. Then the program ends. However, the C
    null pointer never points to valid data. To be sure of this, QuickC sets
    aside a "null block" which is to be untouched. QuickC also includes
    postmortem code in each program that checks the null block to see if it
    has been altered. If it has, something is wrong, and QuickC displays the
    null pointer error message.

    Note that the postmortem code doesn't detect data written to non-null
    locations. For example, if we initialize iq to 200, the program still
    fails to work properly, but, because address 200 is outside the null
    block, QuickC returns no error message. Thus, in general, you might not
    detect this kind of error unless you notice suspect data in the output.
    Unfortunately, this error can also overwrite legitimate data.

    Function prototyping won't help here. If you try an error level of 2 or 3,
    the compiler still doesn't complain about using a nonpointer as an
    argument. Looking at the function prototype in stdio.h shows us why:

    int _CDECL scanf(const char *, ...);

    The scanf() function is one of those rare functions that take a variable
    number of arguments. The first argument is always a string, but the others
    can be different types. Therefore, the prototype doesn't limit the nature
    and number of the remaining arguments: It type-checks only the first
    argument.

    (The _CDECL macro is set to cdecl when Microsoft enhancements are in
    effect. This keyword ensures that C functions use C calling conventions
    even if the /Gc compiler flag is set. That flag enables the Pascal and
    FORTRAN calling sequence for programs using mixed-language modules.)

    scanf ("%s", &iq) is the same as scanf
    ("%s", 3400), so an input of 88 is
    placed in location 3400.                         ADDRESS
                                        â”Œâ”€â”€â”€â”€â”€â”€â”€â”
                    scanf ("%s", &iq)â”€â”€â”€â”€â–ºâ”‚  88   â”‚   3400
                                        â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                                        â”‚       â”‚
                                        â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                                        â”‚       â”‚
                                        â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                                        â”‚       â”‚
                                        â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                                        â”‚       â”‚
                                        â””â”€â”€â”€â”€â”€â”€â”€â”˜

    scanf ("%s", iq) is the same as scanf
    ("%s", 0), so an input of 88 is      â”Œâ”€â”€â”€â”€â”€â”€â”€â”
    placed in location 0.                â”‚       â”‚
                                        â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                                        â”‚       â”‚
                                        â”œâ”€â”€â”€â”€â”€â”€â”€â”¤
                    scanf ("%s", iq)â”€â”€â”€â”€â”€â–ºâ”‚  88   â”‚   0000
                                        â””â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 16-4. Entering forbidden territory.

References

    The BADREF.C program (Listing 16-17) provides an example of a more subtle
    pointer error.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* badref.c -- misuses a pointer                      */
    main()
    {
        char name[81];
        char *pt_ch;

        printf("Enter your first name: -> ");
        scanf("%s", name);
        *pt_ch = name[1];
        printf("The second letter of your name is %c\n",
                *pt_ch);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-17.  The BADREF.C program.

    The following is a sample run of the program:

    Enter your first name: -> Fillmore
    The second letter of your name is i
    run-time error R6001
    -null pointer assignment

    This program gives the correct answer, but it also produces the null
    pointer error message, which means that data has been written in the null
    block. The program uses two pointers to assign data. First, in the call

    scanf("%s", name);

    the name variable is a pointer. This variable isn't a pointer to the null
    block, however, because the compiler allocates the space for name.

    Now look at the following assignment:

    *pt_ch = name[1];

    This tells QuickC to copy the contents of name to the location pointed to
    by pt_ch. The program allocates space for the pointer pt_ch, but it never
    specifies where pt_ch points. Therefore, pt_ch becomes an "unreferenced"
    pointerâ”€â”€it doesn't refer to a known location. As in the last example,
    because pt_ch has an initial value of 0, the data is copied to the null
    block.

    The unreferenced pointer is an insidious error. If such a pointer is
    initialized to a value that doesn't point to the null block, the
    postmortem program will not detect it. However, there is an effective
    method for preventing this kind of error. When you compile a program,
    enable the "Pointer Check" feature in the Compile dialog box. This adds
    code to your program that checks to see if each pointer is referenced
    before it is used. Recompile BADREF.C using this option. Following is a
    sample run:

    Enter your first name: -> Fillmore

    run-time error R6012
    -Illegal Near pointer assignment

    This time, instead of generating incorrect results, the program halts when
    it attempts to use the unreferenced pointer. If you compiled in the Debug
    mode, when you return to the editing screen, the cursor marks the guilty
    line of code.

    Obviously, the Pointer Check mode makes for safer programs. Unfortunately,
    it slows program execution, thus sacrificing one of C's strengths.
    Typically, you use this mode only when you suspect pointer problems (such
    as when you receive a null pointer warning). Once you rectify the problem
    by initializing the pointer to point to previously allocated memory, turn
    off the pointer check and recompile.


Design Errors

    So far we have focused on the misuse of the C language. However, you can
    write programs that use nothing but valid C statements but that fail
    because of design errors. The DIGSUM.C program (Listing 16-18), for
    example, contains a design flaw.

    The program examines input. Characters that are less than 0 and greater
    than 9 are considered nondigits, and the program lists them as others; the
    program lists values within that range as digits. Following is a sample
    dialogue:

    2b
    4c
    Ctrl-Z
    digits = 6, others = 0

    The program counts all input, including the newlines, as digits. The
    problem lies in the following test condition:

    if (ch <= '0' && ch >= '9')

    The expression is always false because it asks if ch is simultaneously
    less than '0' and greater than '9', which is impossible. You must use the
    logical OR operator (||) to express the test condition properly.

    Other than its flaw in logic, this program contains no C errors, and
    QuickC compiles it with no objections. The error becomes apparent when you
    analyze the output.

    You can ferret out this kind of logic error (expressing a test condition
    incorrectly) by using Debug to trace the program step by step. When you
    see that the program takes the wrong branch each time, you know to inspect
    the test condition.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* digsum.c -- sums digits in input                   */
    #include <stdio.h>
    main()
    {
        int ch;
        int digits = 0;  /* number of digits in input */
        int others = 0;  /* number of nondigits in input  */

        while ((ch = getchar()) != EOF)
        if (ch <= '0' && ch >= '9')
                others++;
            else
                digits++;
        printf("digits = %d, others = %d", digits, others);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-18.  The DIGSUM.C program.

Small Programs

    Often, with small programs, you can locate errors merely by examining the
    code, especially if the behavior of the program suggests where to look. By
    becoming familiar with common errors and the effects they produce, you
    will learn to detect them quickly.

    If a simple inspection fails to turn up the error, don't spend a lot of
    time poring over the code. Instead, gather more evidence. First, trace the
    values of key variables as a program runs. This gives you an inside view
    of program execution and can help uncover clues that let you deduce what
    is wrong. Traditionally, C programmers do this by embedding printf()
    statements at key locations. However, you do not need to use this methodâ”€â”€
    QuickC's Debug mode is a much quicker and more powerful technique.

    If your problem seems array related, check your use of indexes. If it's
    loop related, check your loop conditions, paying close attention to the
    starting and ending values.

    If pointers are involved, check to see if they are referenced properly.
    You should always assign a pointer an address before using it with the
    indirect value operator (*).

    Test conditions that combine two or more relationships are breeding
    grounds for errors, and you should put them high on your priority list of
    items to be checked.

Large Programs

    The difficulty of finding errors rapidly increases with program size. The
    Debug mode lets you watch the progress of several variables, but a large
    program can have so many things going on that Debug is of little help.
    Also, large programs often use complex interdependencies that make it
    difficult for you to visualize details.

    The key to debugging large programs is the same as the key to writing
    large programsâ”€â”€modularity. If you don't use a modular approach when you
    begin developing a large program, you greatly decrease your chances of
    debugging the result. Using the modular approach, you break a program into
    smaller, more manageable pieces; as a result, you can localize most
    problems with only a few debugging techniques.

    Stub Functions

    The "stub function" debugging technique is based on the top-down method of
    programming. You begin debugging by testing the highest level of program
    organization. Suppose that your main() function contains the overall
    organization of the program and calls upon other functions to handle the
    details. These second-level functions, in turn, might subdivide the work
    into further functions.

    With this method, you replace the second-level functions with simple,
    error-free routines called stub functions. For example, suppose one
    second-level function takes an array and an array size as arguments and
    performs a complex calculation.

    Replace it with the following stub function:

    void complex_calc(array, size)
    double array;
    int size;
    {
        printf("Function complex_calc was called with "
                "arguments %u and %d\n", array, size);
    }

    Do this with all second-level functions to concentrate on how main()
    works. Does it perform the proper sequence of steps? Does it pass the
    correct arguments? Use the Debug mode to trace the order in which the
    statements execute. If main() works properly, replace the stub functions
    with the originals one by one until a problem occurs. If necessary, you
    can use stubs within stubs.

    Drivers

    Another debugging method is the bottom-up approach. Here you start with
    the most basic functions. However, instead of testing them in the complex
    final environment, you use small programs called "drivers" to test the
    function.

    For convenience, design your driver so that it can feed a variety of
    values to the function to be tested. The MATHTEST.C program (Listing
    16-19) offers an example of such a driver.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* mathtest.c -- driver for do_math()                 */
    /* Program list: mathtest.c (to link math functions)  */

    #include <stdio.h>
    double do_math(double);
    main()
    {
        double input, result;

        printf("Enter a number: ");
        while (scanf("%lf", &input) == 1)
            {
            result = do_math(input);
            printf("input = %.2e, result = %.2e\n", input,
                    result);
            printf("Next number (q to quit): ");
            }
    }

    #include <math.h>
    double do_math(x)
    double x;
    {
        return (sin(x) * exp(-x));
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-19.  The MATHTEST.C program.

    The following is a sample run:

    Enter a number: 0
    input = 0.00e+000, result = 0.00e+000
    Next number (q to quit): 1
    input = 1.00e+000, result = 3.10e-001
    Next number (q to quit): -2p
    input = -2.00e+000, result = -6.72e+000
    Next number (q to quit): q

    Actually, any non-numeric input (not just q) causes scanf() to return a
    value other than 1 and thus terminates the loop.

    Notice that the driver function echoes the input value so that you know
    the do_math() function receives the intended value. That is good
    programming practice when using scanf() for input, because that function
    gives you two opportunities to make mistakes: You can omit the & operator
    or use the wrong format specifier. (For example, because input is a double
    value, we must use %lf for input rather than %f.)

    The assert() Routine

    The assert() macro is another tool for locating logic errors in a large
    program. Use this macro to test whether certain conditions are in fact
    true. The assert() macro takes an expression as an argument. If the
    expression is true, the program continues. If it is false, the program
    halts and prints a message identifying the file and line number of the
    incorrect assertion. The TESTER.C program (Listing 16-20) is a short
    example that illustrates how assert() works.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* tester.c -- demonstrates the assert() macro        */
    /* Program list: tester.c (to link math functions)    */

    #include <assert.h>
    #include <stdio.h>
    #include <math.h>
    main()
    {
        float s1 = 3.0;
        float s2 = 4.0;
        float sumsq;
        float hypot;

        sumsq = s1*s1 - s2*s2;
        assert(sumsq >= 0);
        hypot = sqrt(sumsq);
        printf("hypotenuse is %.2f\n", hypot);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 16-20.  The TESTER.C program.

    The program calculates the hypotenuse of a right triangle by finding the
    square root of the sum of the squares of the remaining sides. We
    deliberately introduce an error into the calculation so that sumsq
    contains a negative value. Because sumsq must always be positive or zero,
    we specify that with the assert() statement. When you run the program, it
    halts at the asssert() statement and displays the following message:

    Assertion failed: sumsq >= 0, file c:\qc\tester.c, line 15

    By placing assert() statements at strategic locations in a large program,
    you can localize logic errors, which enables you either to find the error
    or to use Debug more productively.

    One convenient feature of assert() statements is that once you fix your
    mistakes, you can recompile and eliminate the statements from the compiled
    program without altering your source code. To do so, merely place the
    following definition in your program:

    #define DEBUG /* turns off assert() macros */

    This causes the assert() macro to be defined as a blank.

    A Final Word of Advice

    QuickC offers you many powerful tools for debugging your programs.
    However, the ultimate tool in debugging is your own mind. Become familiar
    with common programming errors and study how to detect or prevent them.
    Most importantly, write your programs in a structured, modular form so
    that you can easily trace or localize the errors.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€