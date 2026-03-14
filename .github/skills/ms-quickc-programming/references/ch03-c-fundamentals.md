Chapter 3  C Fundamentals

    Now that you feel comfortable in the QuickC environment, we can turn our
    attention to the fundamentals of C. First, let's look at the basic
    elements of a C program.


Basic Elements of C Programs

    The simplest possible C program, which we call TINY.C, is shown in Listing
    3-1 on the following page. Type this program into the QuickC editor; then
    run it with the Start option from the Run menu. (We recommend that you
    enter and run all sample programs in this bookâ”€â”€we believe this will help
    you better understand and remember the concepts we discuss.)

    As you probably suspected, this program doesn't actually do anything when
    you run it. QuickC generated the message Program returned 1. Press any
    key, but the program produced no output at all. The main() function
    returns the value 1, in this sample, to the operating system. (The actual
    value might be different on your machine.) This value is significant only
    if you control it deliberately, as you might want to do when you call a C
    program from another program, for example.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* tiny.c -- the smallest possible C */
    /*           program with comments   */

    main() /* function name and argument list */
    {
            /* function definition in braces */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-1.  The TINY.C program.

A Program Consists of Function Definitions

    As simple as it is, however, this program illustrates a basic element of
    Câ”€â”€A C program is essentially a set of function definitions. A function
    contains statements (instructions) that the program "calls" to perform
    specific tasks. A function definition must contain at least the following
    elements:

    â–   The function name

    â–   An "argument list" enclosed in parentheses

    â–   A group of statements that define the function

    In practice, and especially with programs written in the new ANSI C
    standard, function definitions can be more complicated than this. But this
    simplest definition is all we need until we look at functions in more
    detail in Chapter 6.

    TINY.C has only one function, main(). The argument list, which follows the
    function and is enclosed in parentheses, often contains "parameters," or
    formal descriptions of information, that the function uses when it is
    called (executed). Although an argument list can also be empty, as it is
    in main(), the parentheses are still required. Because main() contains no
    function definition statements, the program does nothing when you run it.

    The QCHELLO.C program we developed in the last chapter is an even better
    example of the elements of a C program. Figure 3-1 identifies the parts
    of QCHELLO.C.

                Function name               Argument list
                    â”‚                         â”‚
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”   â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                            main ( )
                            â”Œâ”€
                            â”‚ {
    Function definition  â”€â”€â”€â”¤     printf("Hello, and welcome to QuickC!\n");
    enclosed in braces      â”‚ }   â”‚                                        â”‚
                            â””â”€    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                                    â”‚
                                        Statement in function definition

    Figure 3-1. Parts of the QCHELLO.C program.

A Function Definition Consists of a Group of Statements

    In C, a pair of braces ({ and }) encloses a group of statements. Notice
    the part of the program between the braces in Figure 3-1. The statement
    here defines the function main(). All stand-alone C programs begin with
    main(). The statements within braces are sometimes called the "function
    body," to distinguish them from the function name and argument list, which
    together form the "function header."

    The function body can consist of any number of program statements. Note,
    however, that the braces are still required even if the definition
    contains no statements. Think of braces as symbols that delimit
    "paragraphs" of C code.

    A Statement Is like a Sentence

    A statement in C consists of keywords, variable and function names, and
    operators, and, like an English sentence, describes a complete action.
    Statements always end with a semicolon. Below are some example C
    statements and their meanings:

    printf("This is a statement");â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Print This is a statement
    count = 1;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Set the variable count to 1
    getche(ch);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Wait for user to type a character,
                                            assign it to the variable ch, and
                                            echo (display) it on the screen

    QCHELLO.C has only one statement, printf("Hello, and welcome to
    QuickC!\n"); this statement translates as "Print the string `Hello, and
    welcome to QuickC!' and then go to the next line." (The \n specifies a
    newline character that moves the cursor to the next line.) This statement
    completely defines the function main() and describes what happens when the
    program executes the function.

    A Statement Can Contain Expressions

    Can an expression, such as count + 2, be a statement? Well, it doesn't end
    with a semicolon. But more importantly, it is not a complete statement.
    The word and number merely express a quantity ("two more than the value of
    the variable count"): They don't do anything with the quantity.

    Although an expression by itself is not a statement, it can be an
    important element of a C statement. For example, count = count + 2; is a
    complete C statement that assigns the quantity of the expression to the
    variable count.

    A Statement Can Call Functions

    Let's look at QCHELLO.C in more detail. (See Figure 3-2 on the following
    page.) What exactly is the printf() function at the start of the statement
    that defines the main() function? If you know BASIC, you might say, "It's
    the command you use to print in C." This isn't really correct, however. In
    BASIC, PRINT is a built-in BASIC command (or keyword) that prints a string
    or number. In C, printf doesn't execute a built-in command; it calls a
    function named printf() and gives ("passes") it an argument (or parameter)
    that tells it what to print.

                Function name               Argument list
                    â”‚                         â”‚
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”   â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                            main ( )
                            â”Œâ”€
                            â”‚ {
    Definition of main() â”€â”€â”€â”¤     printf ("Hello, and welcome to QuickC!\n");
    function in braces      â”‚ }     â”‚     â”‚                                 â”‚
                            â””â”€      â”‚     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                    â”‚                 â”‚
                                Name of    Argument list (string to print)
                                function
                                being called

    Figure 3-2. Parts of QCHELLO.C revisited.

    Compare the printf() statement with the line containing main(). Both
    consist of a name followed by parentheses: that is, a function name and an
    argument listâ”€â”€the list for main() is empty. (Note that when we show
    function names in text, we use a trailing set of parentheses to
    distinguish them from other C elements.)

    The main() function name with its empty argument list are followed by a
    pair of braces that enclose the function definition. (You'll notice in
    QCHELLO.C that no semicolon follows main() because the line isn't a
    complete statement: It's the header for the function definition that
    follows.) The line with printf(), however, needs no defining group of
    statements because we are not defining printf() here; we're merely using,
    or "calling," the function in a statement. To call a function, simply use
    its name and argument list in a statement. We refer to statements such as
    the printf() line as "function calls."

    Always remember that every function must be defined before you can call
    it, otherwise QuickC would not know what statements to use when it tries
    to compile the function name. So where is the definition of the printf()
    function we called in Figure 3-2? The printf() function is a "core
    library function." Its definition is built into QuickC so that your
    program always has access to it. When you link your program, QuickC
    inserts the appropriate machine code for printing.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    If you know Pascal, you recognize the use of the semicolon to end
    statements in C. However, there is one important difference between its
    use in C and in Pascal. In Pascal, the semicolon can be omitted if the
    statement is the last statement in a group (the statement before the word
    END). In C, every statement ends with a semicolon.

    Also notice that the braces in C serve the same function as the Pascal
    keywords BEGIN and END: They delimit a group of statements.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    We stress the difference between C's library functions and the built-in
    commands of some other languages to emphasize the all-important role that
    functions play in C. C makes no distinction in syntax between QuickC
    library functions, such as printf(); functions that you define yourself,
    such as main(); and C header files developed by Microsoft or other
    vendors.

The Flow of Execution Starts with main()

    When you run a C program, execution always begins with the function named
    main(), which must be present. What QuickC executes next depends on the
    functions that main() calls in its definition. In QCHELLO.C, execution
    starts with main(). In the definition of main(), QuickC encounters the
    name printf() and executes that function.


Punctuation and Spacing in C Programs

    Generally speaking, QuickC lets you break lines of code almost anywhere or
    insert many spaces (or none) between program elements. For example, you
    could rewrite the QCHELLO.C program as:

    main(){printf("Hello, and welcome to QuickC!\n");}

    or, at the other extreme, you could add line breaks to produce the
    NARROW.C program shown in Listing 3-2. There are, however, some
    exceptions to C's tolerance of white space and "free-form" syntax. You
    can't split a function name across two lines because the compiler reads
    the newline character at the end of the line as part of the function name.
    Also, you can't break a quoted string, such as the "Hello, and welcome to
    QuickC!" in our printf() statement, between two lines because the compiler
    won't let you use the newline character in a "string constant" (although
    you can specify a newline with the escape sequence \n, as we have seen).

    Because C is a somewhat cryptic language, you should use spacing and
    alignment of code to make it easier for other programmers to read and
    revise your programs. (Remember, after a few weeks you, too, are "another
    programmer" when you look at your code.) You'll also find that aligning
    braces vertically helps you avoid errors: The vertical alignment lets you
    easily match beginning and ending braces.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* narrow.c -- a choppy c program */

    main
    (
    )
    {
    printf
    ("Hello, and welcome to QuickC!\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-2.  The NARROW.C program.


Using Comments in C

    Listing 3-1 on p. 50 contains several lines or parts of lines that begin
    with /* and end with */; for example:

    /* tiny.c â”€â”€ the smallest possible C program */

    These lines are comments, or nonexecuting remarks, that explain how a
    program works. We strongly encourage you to use comments in your programs;
    they make the program much easier for a reader to understand. Because
    QuickC ignores comments, they can follow a program statement on the same
    line or cover many separate lines. The program examples in this book have
    an introductory comment, and we insert other comments where appropriate.

    Below are several different styles you can use for comments:

    /* Comment line one */
    /* Comment line two */

    or

    /* Comment line one
    comment line two */

    or

    /* Comment line one
    /* Comment line two
    /* Comment line three */

    However, you can't insert a comment within a comment as follows:

    /* Comment line one
    /* Nested comment line two */
    Comment line three */

    The reason you can't "nest" comments is that once the compiler sees the
    beginning of a comment (the /*), it considers everything that follows
    (including another /*) to be part of the comment until it sees */. In the
    nested comment above, the compiler considers the comment ended at the */
    after the word two. It then treats the word Comment on the next line as an
    undefined function or variable name.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    Many versions of Pascal use both /*...*/ and {...} to enclose comments. In
    C, you can never use braces for comments: They serve only to begin and end
    groups of statements.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€


Data Types and Declarations of Variables

    Variables are names for memory storage areas used by a program. Variables
    come in many shapes and sizes. Many BASIC programmers get along reasonably
    well using only two types of variables: numeric (representing a number)
    and string (representing a series of characters). A BASIC programmer might
    write:

    ITEM$="WIDGET"
    SERIAL=32767

    to define two variables. The $ at the end of ITEM signifies a string
    variable; its absence in SERIAL specifies a numeric variable. A BASIC
    interpreter sets up these variables "on the fly" as it analyzes the lines
    of code, without storing them in a particularly efficient way.

    With C, the situation is more complicated. In order to use computer memory
    more efficiently, the C compiler reserves a specific location in memory
    for each variable. To do this efficiently, it needs to know exactly how
    many bytes of storage to use and how to store the data in those bytes.
    Therefore, C uses many "data types" to specify such things as the range of
    numbers that a variable can hold, whether negative values should be
    accommodated, whether values can be integers only or include decimal
    fractions, and so on. If you are a BASIC programmer, this constant
    attention to data types takes a little getting used to. However, by the
    end of this chapter, you will know all the available types and when each
    should be used.

    Let's begin our survey of data types by considering some different types
    of data we might store in variables:

    â–   30 (the number of students in a class)

    â–   557,617,814 (number of seconds since a date in 1970)

    â–   22.95 (price of a computer book?)

    â–   1,000,000,000,000.00 (future U.S. budget?)

    â–   a (the letter a)

    As you probably know, data is stored in a computer as patterns of bits: 1s
    and 0s, "ons" and "offs." In the IBM PC family of computers, bits are
    organized in groups of eight (called bytes), or in groups of two bytes
    (called words), or in groups of four bytes (double words), depending on
    the operation involved and the processor used. Figure 3-3 on the
    following page shows how many bytes are needed to store the different
    sizes and kinds of numbers in the above list. The figure also shows the
    name of the data type that describes the storage involved. The addresses
    shown are arbitrary, but they demonstrate how successive items are stored
    with lower addresses.

    The QuickC sizeof operator returns the number of bytes that a given data
    type uses. The program VARSIZE.C (see Listing 3-3 on the following page)
    uses this operator and a series of printf() statements to print out the
    sizes (in bytes) of the following data types: char, int, long, float, and
    double.

                                        ADDRESSES   DATA                  TYPE
    Stored          â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    "downward"        â”‚              â”‚ 5003
    in memory         â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤                                   char
        â”‚      1 â”€â”€â”€ â–’â”‚              â”‚ 5002 â–’ â”€â”€â”€â”€ a
        â”‚     byte    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
        â”‚             â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
        â”‚            â–’â”‚              â”‚ 5001 â–’
        â”‚      2 â”€â”€â”€ â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’ â”€â”€â”€â”€ 30                    int
        â”‚    bytes   â–’â”‚              â”‚ 5000 â–’
        â–¼             â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                    â–’â”‚              â”‚ 4999 â–’
                    â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’
                    â–’â”‚              â”‚ 4998 â–’
                4 â”€â”€â”€ â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’ â”€â”€â”€â”€ 557,617,814           long
            bytes   â–’â”‚              â”‚ 4997 â–’
                    â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’
                    â–’â”‚              â”‚ 4996 â–’
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                    â–’â”‚              â”‚ 4995 â–’
                    â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’
                    â–’â”‚              â”‚ 4994 â–’
                4 â”€â”€â”€ â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’ â”€â”€â”€â”€ 22.95                 float
            bytes   â–’â”‚              â”‚ 4993 â–’
                    â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’
                    â–’â”‚              â”‚ 4992 â–’
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                    â–’â”‚              â”‚ 4991 â–’
                    â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’
                    â–’â”‚              â”‚ 4990 â–’
                    â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’
                    â–’â”‚              â”‚ 4989 â–’
                    â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’
                    â–’â”‚              â”‚ 4988 â–’
                8 â”€â”€â”€ â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’ â”€â”€â”€â”€ 1,000,000,000,000.00  double
            bytes   â–’â”‚              â”‚ 4987 â–’
                    â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’
                    â–’â”‚              â”‚ 4986 â–’
                    â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’
                    â–’â”‚              â”‚ 4985 â–’
                    â–’â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤      â–’
                    â–’â”‚              â”‚ 4984 â–’
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 3-3. Storing information in memory.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* varsize.c -- shows amount of memory */
    /*              by various types       */

    main()
    {
        printf("Size of a char in bytes is %d\n", sizeof(char));
        printf("Size of an int in bytes is %d\n", sizeof(int));
        printf("Size of a long in bytes is %d\n", sizeof(long));
        printf("Size of a float in bytes is %d\n", sizeof(float));
        printf("Size of a double in bytes is %d\n", sizeof(double));
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-3.  The VARSIZE.C program.

    Here's the output of VARSIZE.C:

    Size of a char in bytes is 1
    Size of an int in bytes is 2
    Size of a long in bytes is 4
    Size of a float in bytes is 4
    Size of a double in bytes is 8

Declaring Variables

    To declare a variable, specify the data type and then the variable name.
    Here are some examples:

    int account_no;
    float balance;
    double budget;
    char acct_type;

    The first statement declares account_no as an integer (int) variable. The
    remaining statements declare variables as floating-point decimal (using
    the keyword float), "jumbo" 8-byte floating-point (double), and 1-byte
    character (char) data types.

    When you declare a variable, QuickC sets aside the appropriate number of
    bytes and notes the variable's starting address. The next program,
    VARADDRS.C (Listing 3-4), declares several types of variables and then
    prints out their starting addresses.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* varaddrs.c -- uses & operator to get   */
    /*               addresses of variables   */

    main()
    {
        char c1, c2;
        int i;
        long l;
        float f;
        double d;

        printf("Address of c1 %d\n", &c1);
        printf("Address of c2 %d\n", &c2);
        printf("Address of i  %d\n", &i);
        printf("Address of l  %d\n", &l);
        printf("Address of f  %d\n", &f);
        printf("Address of d  %d\n", &d);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-4.  The VARADDRS.C program.

    Although the output of this program varies with different system
    configurations, it should look something like this:

    Address of c1 6146
    Address of c2 6144
    Address of i  6142
    Address of l  6138
    Address of f  6134
    Address of d  6126

    VARADDRS.C obtains the addresses of the variables by using an ampersand
    (&) prefix with each variable name. The ampersand is the "address
    operator," and it returns the starting address for each variable
    specified. Compare the output of VARADDRS.C with Figure 3-3 to see how
    variables declared with different data types require different amounts of
    memory. When QuickC allocates the required number of bytes for a declared
    data type, the last byte allocated (moving downward in memory) is the
    variable's starting address. For example, the integer variable i has an
    address of 6142, indicating that it uses two bytes (6144 - 6142 = 2); the
    double type variable d uses eight bytes (6134 - 6126 = 8). Note that the
    compiler allocates two bytes for char values c1 and c2, although each
    value requires only one byte. The extra byte is convenient for
    manipulating (2-byte) words in memory.

Rules for Naming Variables

    In C, the names of variables and functions are called "identifiers." An
    identifier can contain any uppercase or lowercase alphabetic characters
    (A-Z or a-z), digits (0-9), and the underscore character (_). However, the
    name must begin with a letter or underscore. Below are some examples of
    legal and illegal names:

    bignumâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Legal
    BigNumâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Legal, and distinct from bignum
    _videoâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Legal, can begin with an underscore
    bal_dueâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Legal, underscore used to separate words
    player2â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Legal, number in variable name
    8ballâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Illegal, can't begin with a number
    tally-ho!â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Illegal, contains hyphen and exclamation point
    intâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Illegal, keyword reserved for name of integer type

    As you can see, you have considerable flexibility in choosing names for
    your variables. Because QuickC can distinguish the first 31 characters of
    a variable name, you can use long, descriptive names that help make the
    program easier to understand and modify. (You might want to use shorter
    names if your program must run a compiler that does not support long
    names.) C distinguishes between uppercase and lowercase characters, so
    that BigNum and bignum are different variables. Note that you can't begin
    a variable name with a number, use punctuation marks such as ! or $, or
    use C-language keywords as variable names. (You can embed a keyword in a
    variable name, however: interest is a legal name even though it contains
    the keyword int.) Fortunately, C has few keywords compared to languages
    such as BASIC: Most specify data types (such as int) or control and
    decision-branching operations (such as while and if).

    We use specific conventions for naming variables and functions. (See
    "Conventions and Style" in Chapter 1.) These are not required by QuickC,
    but are used here to differentiate among types of variables and functions.
    We also begin our variable names with a character other than an
    underscoreâ”€â”€Microsoft uses the underscore as the initial character for its
    QuickC library functions.

Assignment Statements

    How do you assign values to variables? In C, the simplest assignment
    statement consists of a variable name followed by an equal sign (=) and
    the value to be assigned. Below are some examples:

    a = 5;
    b = a + 5;
    c = a + b;

    In these assignment statements, the value to the right of the equal sign
    is assigned to the variable on the left. The value can be a number or an
    expression involving variables and/or numbers, such as a + 5 or a + b. If
    the value is an expression, QuickC determines the result and then assigns
    it to the variable.

    You can also assign the same value to several variables at once. Usually,
    you do this to initialize variables by setting them all to 0 or 1:

    line_count = word_count = 0;
    line_no = page_no = 1;

Initializing Variables

    Many languages (including most versions of BASIC) automatically initialize
    numeric variables to 0 and character variables to blank or, perhaps,
    "null." C does not. For example, if your program has the following two
    lines:

    int length;
    printf("The length is %d\n", length);

    and you do not initialize length, it might produce the following output:

    The length is -25480

    The default value of a C variable is whatever pattern of bits happens to
    be in the memory locations of the variable when the compiler assigns them.
    Therefore, if you want to use a variable called total, for example, in a
    program that keeps track of some quantity, you should assign that variable
    an initial value of 0. You might modify the declaration above as follows:

    int length = 0;

    Because C is a concise language, it lets you combine the declaration and
    assignment of a variable. That is, you can declare the data type, the
    variables, and their values in the same statement:

    int a = 10, b = 50, c = 100;

Type int

    Now that you know how to declare numeric variables and assign values to
    them, let's look at the int, or integer, data type more closely. An
    integer is a whole number, such as 30, -5, or 93,000,000. In QuickC, an
    int variable can hold numbers in the range of -32,768 through 32,767. This
    rather odd-looking range is established because the int type uses two
    bytes (16 bits) of memory. Two bytes can actually hold a range of 0
    through 65,535. But, in the regular int type, the high (leftmost) bit of
    the 2-byte combination stores the integer's sign (positive or negative),
    leaving only 15 bits for the number.

    If your variable will never store negative integers, use the unsigned int
    type. Because the sign bit is not used, you can use the full two bytes to
    store values from 0 through 65,535.

    Now let's look at the INTVARS.C program (Listing 3-5), which declares
    three integer variables, assigns values to them, and then prints out
    values that describe the World War II German battleship Bismarck.

    We declare the variables length and beam as int types because the length
    and beam (width) of the ship are less than 32,767 feet. For the
    displacement variable (the "weight" of the ship), we use the unsigned int
    type because we need a larger number (41,676) than 32,767 (the int limit)
    but a smaller number than 65,535 (the unsigned int type limit).

    The next three lines assign the values to the variables, and the three
    printf() statements print the values out. Notice that the printf()
    statements use two arguments within the parentheses: a string, such as
    "The battleship Bismarck was %d feet long", followed by a comma and the
    variable name whose value is to be printed. The %d in the string is a
    printf() "format specifier," and the value of the variable is printed in
    its place. (The %d specifier denotes a decimal [base 10] integer. C uses a
    variety of specifiers for different types and formats of numbers and
    characters. We'll discuss them when we look at printf().) When you run
    INTVARS.C, it generates the output that appears below the listing (on the
    following page).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    ANSI C lets you specify any basic variable type as unsigned. It also lets
    you specify signed types. Therefore, although QuickC considers the int
    type to be signed by default, the C language doesn't guarantee that all C
    compilers do so. To write portable programs, you need to specify all
    variables as either signed or unsigned types.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* intvars.c -- declares, defines, and prints */
    /*              some integer variables        */

    main()
    {
        /* declare variables */
        int length, beam;
        unsigned int displacement;
        /* assign values to variables */
        length = 824;
        beam = 118;
        displacement = 41676;

        /* print out values */
        printf("The battleship Bismarck was %d feet long",
                length);
        printf(" with a beam of %d feet,\n", beam);
        printf("and displaced %u tons.\n", displacement);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-5.  The INTVARS.C program.

    The battleship Bismarck was 824 feet long with a beam of 118 feet,
    and displaced 41676 tons.

Long Integer Type

    We've seen that unsigned int variables can hold values to 65,535. But what
    if you must use larger numbers? Type long uses four bytes (32 bits) of
    memory (1 bit is reserved for the sign), and can store numbers from -2^31
    to +2^31, or -2,147,483,648 to 2,147,483,647 in base 10. Once again, if
    your variable will contain only positive numbers, you can double the high
    end of this range by specifying unsigned long. This lets you assign your
    variable a whole number value in the range 0 through 4,294,967,295.

    The SCORE.C program (Listing 3-6 on the following page) combines the
    declaration and assignment of the int variables home, visitors, inning,
    and attendance. Because total_attendance is a different data type, long,
    you must declare it in a separate statement. Again, the printf()
    statements display the values assigned to the variables and produce the
    following output:

    The score after 7 innings is
    Home team 5, Visitors 2.

    The attendance today is 31300.
    Attendance this year to date is 1135477.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* score.c -- defines and prints   */
    /*            int and long vars    */
    main()
    {
        /* declare some int variables and assign values */
        /* to them in the same statement                */

        int home = 5, visitors = 2, inning = 7, attendance = 31300;
        long total_attendance = 1135477;  /* long int */

        /* print out the values */

        printf("The score after %d innings is \n", inning);
        printf("Home team %d, Visitors %d.\n\n", home, visitors);
        printf("The attendance today is %d.\n", attendance);
        printf("Attendance this year to date is %ld.",
                total_attendance);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-6.  The SCORE.C program.

Floating-Point Types

    You should store whole numbers as integers wherever possibleâ”€â”€integers use
    the least amount of memory and integer arithmetic is fast. However, many
    numbers (such as dollars-and-cents amounts) require decimal fractions. In
    computers, these types of numbers are stored in "floating-point format."

    Consider the number 22.95. This number can be stored by dividing it into
    two parts: the digits themselves and an exponent showing the magnitude of
    the number in terms of powers of ten. Thus, 22.95 could be represented as
    22.95 * 10^0. For uniformity in performing operations, however, C always
    expresses the digits with only one digit to the left of the decimal point.
    Therefore, the above number is actually stored as 2.295 * 10^1 (the same
    as 22.95 * 10^0). C represents this notation with the expression
    2.295e+001. The first element, 2.295, is the number's digits (the
    "mantissa"), and the e+001 represents "exponent 1," or 10^1.

Type float

    The most commonly used floating-point type in C is float. In QuickC, type
    float uses three bytes to store digits (the mantissa) and one byte to
    store the exponent. Because exponents can be negative (for example,
    1.4e-002 = .014), one bit of the exponent byte stores the sign. Converted
    into decimal terms, this means you can store a mantissa with seven
    significant digits and an exponent ranging from -38 to +38. In fact, with
    QuickC's float type, you can store numbers as large as 3.4e+038, or 34
    with 37 zeros after it.

    The FLOATS.C program (Listing 3-7) displays three float values, each
    printed in both traditional decimal and exponential notation.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* floats.c  -- shows floating values in regular */
    /*              and exponential format           */

    main()
    {
        float f1 = 2500.125, f2 = 0.0033, f3 = -50.99;

        printf("%f\t %e\n\n", f1, f1);
        printf("%f\t %e\n\n", f2, f2);
        printf("%f\t %e\n", f3, f3);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-7.  The FLOATS.C program.

    The following is the output of the FLOATS.C program:

    2500.125000      2.500125e+003
    0.003300         3.300000e-003
    -50.990002       -5.099000e+001

    Notice that because 0.0033 is less than 1, it has a negative exponent
    (represented by the minus sign after the e). -50.99, on the other hand, is
    a negative number, but because its absolute (unsigned) magnitude is
    greater than 1, it has a positive exponent. FLOATS.C prints each variable
    first in decimal notation and then in exponential notation by varying the
    format specifier in the printf() statement: The %f produces traditional
    decimal format, and the %e produces exponential format.

Type double

    For numbers larger than

    340,000,000,000,000,000,000,000,000,000,000,000,000

    QuickC provides a "jumbo" floating-point type called double (double
    float). It uses eight bytes of storage and has a range of (plus or minus)
    1.7e-308 to 1.7e+308. That's 308 decimal places before or after the
    decimal point, thus accommodating even the most expansive physicist or
    astronomer.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Type Variations on Different Machines
    The C language doesn't define the number of bytes used by the int and
    unsigned int types. Instead, the number of bytes is based on the size of
    number a particular processor can handle in a single operation. This way,
    C compilers can always take advantage of a machine's architecture. Because
    the IBM PC uses the Intel 8086, 8088, or 80286 processor, an int uses two
    bytes, or 16 bits, and this is the implementation QuickC uses. However, on
    larger personal computers, such as those using the Intel 80386 processor,
    and on many minicomputers and mainframes, an int uses four bytes, or 32
    bits. Even if you write your program in "standard" C, you must be aware of
    these differences in implementation and machine architecture when you
    "port" the program to another machine.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Precision for Floating-Point Numbers

    You must consider more than size, however, when storing numbers in a
    computer. We referred to a trillion-dollar budget ($1,000,000,000,000.00)
    earlier in the chapter. If size were the only consideration, we could use
    float to store this number. (A float can handle about 10^38, and a
    trillion is merely 10^12.)

    However, you also must consider the precision available to each data type
    in order to choose the right type for a given variable. Precision refers
    to the number of digits guaranteed to be exactly correct after a
    calculation. The float type has a precision of seven digits. Consider the
    following statements and the resulting output:

    float trillion = 1000000000000.00;
    printf("%f\n", trillion);

    999999995904.000000

    We lost $4,096.00 in this operation. Although we might be happy if the
    government lost only that much of a trillion-dollar budget, we must expect
    full precision in financial calculations and probably an even higher
    precision in most scientific calculations. With its seven-digit precision,
    float can't accurately represent a trillion dollars. We attain the
    required precision by declaring:

    double trillion = 1000000000000.00;

    Because double has 15-digit precision, the result is completely accurate.

Type char

    Let's look at one last data type, char (character). Characters include the
    uppercase and lowercase letters, numerals, punctuation marks, and
    nonprinting control characters. Characters on most computers, including
    the IBM PC, are represented by numbers between 0 and 127, according to the
    ASCII code. The CHARS.C program (Listing 3-8) shows some examples.

    Running CHARS.C produces the following output:

    The character A has ASCII code 65
    If you add ten, you get K
    The character a has ASCII code 97

    The first line of the main() function declares two char type variables,
    ch1 and ch2, and assigns them the values of `A' and `a' respectively. The
    `A' and `a' are called "character constants" or "character literals," and
    you assign them to char variables the same way you assign numeric
    constants. (Note that you must use single quotes around the character
    constant.)

    Consider the first printf() statement in the program:

    printf("The character %c has ASCII code %d\n", ch1, ch1);

    The variable ch1 is specified twice at the end of the argument list. The
    first format specifier, %c, prints the value of ch1 as a character. Then
    the %d specifier prints ch1 as an integer. A character is actually stored
    as a 1-byte version of int, and unless you specify that QuickC treat it as
    a character, it is treated as an integer. This enables us to use the
    expression ch1 + 10 in the second printf() statement. The variable ch1
    contains an integer value (the ASCII code for `A', or 65), so adding 10 to
    it produces 75. When the %c specifier then prints this value, it displays
    the character with the ASCII value of 75, or `K'.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* chars.c -- shows some variables of type char */
    /*            as both characters and integers   */

    main()
    {
        char ch1 = 'A', ch2 = 'a';

        printf("The character %c has ASCII code %d\n", ch1, ch1);
        printf("If you add ten, you get %c\n", ch1 + 10);
        printf("The character %c has ASCII code %d\n", ch2, ch2);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-8.  The CHARS.C program.

Type unsigned char

    A char value is a signed, 1-byte value that stores values in the range of
    -128 to +127. However, the IBM PC's version of ASCII uses the values 0 to
    255 as character codes. The first half of extended ASCII contains the
    regular ASCII character set. Codes from 128 to 255, however, consist of
    special characters and graphics shapes, which together are called the
    "extended character set." You can use the extended character set by
    declaring variables as the unsigned char type. For example:

    unsigned char box = 178;
    printf("%c\n", box);

    displays a rectangular box, or extended ASCII character number 178. (Note
    that two QuickC general help screens show the complete extended ASCII
    character set.)

Using typedef

    C lets you rename any data type with the typedef statement. For example,
    if you use unsigned char type variables to hold characters from the full
    256-character extended set, you could define an easily remembered
    mnemonic:

    typedef xchar unsigned char;
    xchar highlight_char, border_char;

    The typedef statement tells QuickC that the word xchar now represents
    unsigned char. Next, we declare two variables as type xchar. Note that you
    can still declare variables as unsigned char at any time. Also note that
    typedef does not create new data types, it merely provides synonyms for
    existing ones.

    The HARDWARE.C program (Listing 3-9) ends our survey of QuickC data
    types.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* hardware.c -- shows a mixture of int, */
    /*               float, and char types   */

    main()
    {
        int threads    = 8;       /* threads per inch */
        float length   = 1.25,    /* length in inches */
            diameter = 0.425,   /* diameter in inches */
            price    = 0.89;    /* price per hundred */
        char bin = 'A';           /* kept in bin A */
        long quantity = 42300;    /* number in bin */

        printf("Screws: %d threads/inch\n %f inches long\n",
                threads, length);
        printf ("%f diameter\n\n", diameter);
        printf("Price per 100: %f\n", price);
        printf("Stored in bin: %c\n Quantity on hand: %ld",
                bin, quantity);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-9.  The HARDWARE.C program.

    Be sure you understand why we declared the different types. The printf()
    statements display the values of the variables and some descriptive text:

    Screws: eight threads/inch
    1.250000 inches long
    0.425000 diameter

    Price per 100: 0.890000
    Stored in bin: A
    Quantity on hand: 42300

    Although the program works correctly, it would look better if the output
    were formatted more neatly. Also, QuickC printed several extra decimal
    places and filled them with zeros. To gain more control over the
    appearance of program output, we need to study printf() in more detail.

Summary of Data Types

    You don't need to memorize the precise numbers associated with each data
    type; one of QuickC's help screens lets you check which data type you
    should use in a given situation. Display this summary of QuickC data types
    by pressing the F1 key and then proceeding to the appropriate screen. As
    you work with various data types in this chapter, you can always consult
    this chart, shown in Figure 3-4, to refresh your memory.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 3-4 can be found on p.67 of the printed version of the book.    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 3-4. Data types help screen.


The Power of printf()

    Thus far we've used printf() statements merely to display values. But
    printf() is actually quite versatile for formatting numbers and character
    strings.

Using Escape Sequences

    Let's look at the parts of the printf() statement from our first program,
    QCHELLO.C:

    printf ("Hello, and welcome to QuickC!\n");

    This is the simplest printf() statement: It merely prints out a string; no
    variables are involved. Earlier, we briefly discussed the one unusual
    feature of this printf() statement, the \n at the end of the string. This
    combination of backslash and following character is called an "escape
    sequence." Escape sequences tell printf() to print special characters as
    part of the given string. The \n, for example, adds the newline character,
    which moves the cursor or printer head to the beginning of the next line.
    Many languages use two kinds of statements for printing: one to print some
    information, and one to print some information and then start a new line.
    With typical conciseness and versatility, C lets you use one function to
    print any ASCII character, including newline, Tab, and carriage-return
    characters, giving you complete control of the position of the cursor or
    printer head.

    One QuickC help screen, shown in Figure 3-5 on the following page, lists
    all of the escape sequences. The newline \n and tab \t sequences are the
    most frequently used. The \a escape sequence causes an "alert," or beep,
    at the terminal.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 3-5 can be found on p.68 of the printed version of the book.    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 3-5. Character escape sequences.

    The ONELINE.C program (Listing 3-10) shows what happens when you don't
    use the newline escape sequence. When you run the program, the output is
    all on one line as follows:

    All displayed onthe same line, with no space unless specified.

    Not only do the strings from all three printf() statements end up on the
    same line, the word "on" at the end of the first string runs into the word
    "the" at the start of the second string. To print two strings on the same
    line with a space between them, you must include the space in the string.
    In the third string of ONELINE.C, we added a space before the word
    "unless."

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* oneline.c -- shows how printf() continues */
    /*              on the same line             */

    main ()
    {
        printf("All displayed on");
        printf("the same line, with no space");
        printf(" unless specified.");
                /* note added space in line above */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-10.  The ONELINE.C program.

    The program STRINGS.C (Listing 3-11) demonstrates the two basic ways to
    print strings with printf().

    The first printf() statement has only one argument, the string to be
    printed, and the newline escape sequence. The second statement has two
    arguments, the format specifier %s (for "string") and the string to be
    printed. It replaces the specifier with the string and prints it. This is
    the same procedure we used to print numeric variables and literals with
    specifiers such as %d. The STRINGS.C program produces the following
    output:

    This uses a string literal by itself
    This plugs the literal into %s

    TABS.C (Listing 3-12) illustrates the use of the tab escape sequence \t.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* strings.c -- shows two ways to print */
    /*              a string with printf()  */

    main()
    {
        printf("This uses a string literal by itself\n");
        printf("%s", "This plugs the literal into %s\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-11.  The STRINGS.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* tabs.c -- shows formatting with the \t */
    /*           tab escape sequence          */

    main()
    {
        int    q1 = 338, q2 = 57, q3 = 1048, q4 = 778,
                /* quantity in bin */
                t1 = 6, t2 = 8, t3 = 12, t4 = 16;
                /* threads per inch */

        float  s1 = 0.250, s2 = 0.500, s3 = 0.750, s4 = 1.0;
                /* size in inches */

        /* print table header */
        printf("number\t\t size\t\t threads\n");
        printf("in bin\t\t (inches)\t per inch\n\n");

        /* print lines of table */
        printf("%d\t\t %f\t %d\n", q1, s1, t1);
        printf("%d\t\t %f\t %d\n", q2, s2, t2);
        printf("%d\t\t %f\t %d\n", q3, s3, t3);
        printf("%d\t\t %f\t %d\n", q4, s4, t4);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-12.  The TABS.C program.

    This program prints four sets of data in a neat table. The program prints
    the table headers first, using \t to tab to the next field. Using \t to
    position each item at the next tab stop causes the output to be left-
    justified in each field. To make the table easier to read, we added a
    blank line between the header and the data by including an extra \n in the
    second printf() statement. The program then prints the values of the
    variables in the same tab fields as the headers. The result of all this is
    as follows:

    number          size             threads
    in bin          (inches)         per inch

    338             0.250000         6
    57              0.500000         8
    1048            0.750000         12
    778             1.000000         16

Formatting Numbers with printf()

    The printf() function can also print numbers in a variety of formats.
    Let's look at a printf() statement from SCORE.C, which is analyzed in
    Figure 3-6.

    String to print is
    enclosed in quotes         â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
            â”‚                  â”‚                             â”‚
            â”‚                â”Œâ”€â–¼â”€â”€â”            â”Œâ”€â”€â”€â”€â”    â”Œâ”€â”€â”€â–¼â”€â”€â”€â”€â”
    printf ("The score after â”‚ %d â”‚ innings is â”‚ \n â”‚ ", â”‚ inning â”‚ );
                            â””â”€â”€â”€â”€â”˜            â””â”€â”€â”€â”€â”˜    â””â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                â”‚                 â”‚           â”‚
                                â”‚                 â”‚           â”‚
                        Format specifier       Newline     Variable whose
                        for an int value       escape      value is to be
                                            sequence    printed

    Figure 3-6. The printf() statement from SCORE.C.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Return and Newline Are Different
    If you program in other languages on MS-DOS machines, you might expect \r
    (carriage return) to move the cursor to the start of a new line. Change
    the \n in TABS.C to \r and run the program again. What happens? Each line
    prints over the preceding one. Although many languages on MS-DOS machines
    incorporate a line feed in a carriage return, C treats newline and return
    as distinct operations. Return moves the cursor to the beginning of the
    current line but does not advance it to a new line. Newline causes output
    to start on the next line. It commences with output at the beginning of
    the next line (rather than directly below the old position) because MS-DOS
    interprets it as though it contains a carriage return as well.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Notice the %d in our example, SCORE.C. This, as we have already mentioned,
    is the format specifier for a decimal integer. The string "The score after
    %d innings is" is followed by a comma and the variable inning. Thus, when
    the printf() statement executes, the string is printed with the value of
    inning. You can also print more than one value in the same string. For
    example, if you define int apples = 12, oranges = 9, pears = 3;, then
    execute the following printf() statement:

    printf("I have %d apples, %d oranges, and %d pears. \n", apples, oranges,

    you see the following output:

    I have 12 apples, 9 oranges, and 3 pears.

Specifying Formats with printf()

    Variables are printed according to their type and the format specifiers
    used. One of the QuickC General help screens (Figure 3-7) shows format
    specifiers and additional symbols that can specify formats.

    The program SPECS.C (Listing 3-13 on the following page) prints different
    types of variables with their appropriate specifiers.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 3-7 can be found on p.71 of the printed version of the book.    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 3-7. Format specifiers.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* specs.c -- shows printf()format   */
    /*            specifiers for numbers */

    main()
    {
        int    i = 122;       /* ASCII code for 'z' */
        long   l = 93000000;  /* distance to Sun (miles) */
        float  f = 192450.88; /* someone's bottom line */
        double d = 2.0e+030;  /* mass of Sun (kg.) */

        printf("%d\n", i);  /* integer as decimal */
        printf("%x\n", i);  /* integer as hex */
        printf("%ld\n", l); /* long */
        printf("%f\n", f);  /* float as decimal */
        printf("%e\n", f);  /* float as exponential */
        printf("%f\n", d);  /* double as decimal */
        printf("%e\n", d);  /* double as exponential */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-13.  The SPECS.C program.

    Compare the following output with the printf() statements in the SPECS.C
    program:

    122
    7a
    93000000
    192450.875000
    1.924509e+005
    2000000000000000000000000000000.000000
    2.000000e+030

    The first printf() statement prints the value of the int variable i, 122,
    as an ordinary decimal integer, using the now familiar %d specifier. The
    next statement prints the same value with the %x specifier, which prints
    values in hexadecimal. Next, we print the long integer value 93000000.
    Notice that this specifier, %ld, combines the %l (long) and %d (integer)
    specifiers.

    The SPECS.C program then prints the value of the variable f, 192450.88,
    using the %f floating-point specifier. In the next statement, we use %e to
    print the same number in exponential notation. Which is better? If the
    value represents money, the regular decimal format is more appropriate,
    but remember that both representations are slightly inaccurate because the
    original value, 192450.88, has eight places and float has a maximum
    precision of seven places. (If you want absolute accuracy, use the double
    specifier.)

    We print the final value, 2,000,000,000,000,000,000,000,000,000,000, two
    ways: as a double (note that you can use %f for double as well as for
    float) and as exponential notation with %e. Clearly, the latter is easier
    to read and understand.

Format Specifiers and Data Types

    Remember, the format specifier merely controls how a value is displayed.
    The data type of the value represents how it is actually stored in the
    computer. The program FORMATS.C (Listing 3-14) displays the comedy of
    errors that can occur if you carelessly use the wrong format specifier
    with a data type. The following is the output of the program; compare it
    with the printf() statements in the program.

    As integer:      5
    As long integer: 8519685
    As exponential:  7.084198e-309
    As float:        0.000000

    The program uses four different specifiers to print the value of the int
    variable i, which we set to 5. Only the first representation, using %d, is
    correct. The other results vary widely (even from one run to another). How
    can the last three methods be so far off the mark? Consider the second
    printf() statement, in which we told QuickC to print the value of i as a
    long integer %ld. A long integer uses four bytes of memory, but this
    variable, as an int type, uses only two. When you specify a long integer,
    QuickC takes four bytes starting at the address of i and converts them
    into a long integer. Two of these bytes, however, have nothing to do with
    the variable i. You can see how similar problems arise when we try to
    interpret an integer variable as a float. All of this demonstrates that
    the format specifier must be compatible with the data type being handled.
    Table 3-1 correlates the most commonly encountered specifiers and data
    types.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* formats.c -- shows what happens when format */
    /*              doesn't match data type        */

    main()
    {
        int i = 5;
        printf("As integer:      %d\n", i);
        printf("As long integer: %ld\n", i);
        printf("As exponential:  %e\n", i);
        printf("As float:        %f\n", i);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-14.  The FORMATS.C program.

    Table 3-1. Compatibility of Specifiers and Data Types
    Specifier          Types
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    %d                 int (signed or unsigned); char (ASCII value)
    %ld                long
    %f                 float or double (decimal format)
    %e                 float or double (exponential format)
    %c                 char (as character)
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Field Width Specifiers

    We can also improve the appearance of printf() output by controlling how
    many decimal places are printed and how the number is aligned in the
    output field. To do this, C lets us precede the format specifier with a
    "field specifier." The field specifier takes the following form:

    <field width>.<decimal places>

    The "field width" is the total number of character positions that will be
    printed, and "decimal places" is the number of places printed after the
    decimal point. (Use the decimal place specifier only for float and double
    values.) Following are two examples of field specifiers:

    "5.2f"â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€float; 5 places, 2 of which are decimal places
    "8d"â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€integer; 8 places (no decimal places)

    The program FIELDS.C (Listing 3-15) shows how field width specifiers
    work.

    The program prints a single variable with varying field specifiers:

        123.456001â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€12.6f (field specifier)
    123.4560â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€8.4f
        123.456â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€8.3f
        123.46â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€8.2f

    In the first printf() statement, the field specifier %12.6f sets up a
    12-character-wide field, 6 characters of which are decimal places. Because
    the variable has only 10 characters to be printed (9 digits and a decimal
    point), printf() indents the number two spaces. By default, numbers are
    right-justified (printed starting in the rightmost position of the
    specified field width). To print numbers that start at the left side of
    the field (left-justified), put a minus sign in front of the field width
    specifier, "%-4.2f".

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* fields.c -- shows the same number with different */
    /*             field widths and number of decimals  */

    main()
    {
        float f = 123.4560;

        printf("%12.6f\n", f);
        printf("%8.4f\n", f);
        printf("%8.3f\n", f);
        printf("%8.2f\n", f);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-15.  The FIELDS.C program.

    Note also in the first printf() statement that we asked for six decimal
    places, even though the variable number contained only the first four
    places. Although printf() prints these extra places, they add nothing to
    the precision of the number, and, in fact, give a misleading impression of
    precision. You should specify decimal places only to the expected
    precision of the value. For example, if you know that a value will range
    between 0 and 9999 with decimal places, you might specify %4.3f because
    the value can have as many as four places to the left of the decimal
    point, and a float has only seven places of precision. Thus, a total of
    seven places (4.3) displays an accurate value. Specifying %8.6 for this
    example would give a false impression of precision.

    In the second statement, the specifier establishes a field width of 8
    (with 4 decimal places). The third statement specifies the same field
    width of 8, but with only 3 decimal places. Notice that the variable's
    fourth decimal place, the zero, is dropped, and that the number is
    indented one space because the variable has only 7 characters. The last
    statement specifies the same field width of 8, but with only 2 decimal
    places. The printf() function not only drops the third decimal place, it
    also rounds up the second decimal place to 6. Also, because the number has
    one fewer digit to fit in the 8-character field, printf() indents the
    number another space.


Arithmetic Operators

    Like most languages, C offers a complete set of arithmetic operators: +
    (addition), - (subtraction), * (multiplication), and / (division). C also
    provides a fifth operator that is not quite as common in other languagesâ”€â”€
    %, the remainder operator, sometimes called the "modulus" operator. This
    operator returns only the remainder of a division operation. For example,
    5 % 2 is 1 (5 divided by 2 has a remainder of 1), and 9 % 3 is 0 (9
    divided by 3 has no remainder).

    The modulus operator has many uses: You can use it for creating counters
    that cycle within counters or for resetting variables such as line counts
    by checking for a remainder of zero (if line_cnt % page_length = 0, then
    you know that you must start a new page).

    Operators are used with values to form expressions that yield new values.
    Below are some examples:

    10 * 5â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Multiply two literals
    a / 5â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Divide value of a by 5
    count + 1â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Add 1 to value of count
    (a * 80) + bâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Multiply value of a by 80, then add value of b

    In a program, you combine expressions with other elements to form
    statements. The MATH.C program (Listing 3-16 on the following page)
    contains statements that use expressions involving arithmetic operators.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* math.c -- shows arithmetic and       */
    /*           precedence via expressions */

    main()
    {
        int a = 10, b = 4, c = 2;

        /* simple arithmetic expressions */
        printf("99 + 2 = %d\n", 99 + 2);  /* ints */
        printf("5 - 12 = %d\n", 5 - 12);
        printf("7.25 + 3.5 = %f\n", 7.25 + 3.5);
                                            /* floats */

        /* compare precedence on these */
        printf("20 * 20 + 40 = %d\n", 20 * 20 + 40);
        printf("20 * (20 + 40) = %d\n", 20 * (20 + 40));
        printf("a * a - c + b =  %d\n", a * a - c + b);
        printf("a * (a - (c + b)) = %d\n",
                a * (a - (c + b)));

        /* compare integer and float division */

        printf("Integers: 5 / 2 = %d\n", 5 / 2);
        printf("Floats: 5.0 / 2.0 = %f\n", 5.0 / 2.0);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-16.  The MATH.C program.

    Each printf() statement prints the expression and then its value, as
    follows:

    99 + 2 = 101
    5 - 12 = -7
    7.25 + 3.5 = 10.750000
    20 * 20 + 40 = 440
    20 * (20 + 40) = 1200
    a * a - c + b =  102
    a * (a - (c + b)) = 40
    Integers: 5 / 2 = 2
    Floats: 5.0 / 2.0 = 2.500000

    The first three statements simply add and subtract literal numbers and
    print the results. Notice in the third statement that when QuickC sees a
    number with a decimal point, it assumes a float type and prints the answer
    accordingly (10.750000).

Operator Precedence

    The next set of statements in MATH.C illustrates "precedence," or the
    rules that determine the order in which operators are applied. Generally,
    QuickC performs multiplication and division first, then addition and
    subtraction. When operators have equal precedence (such as division and
    multiplication), QuickC performs them from left to right. The following
    QuickC help screen, Figure 3-8, lists all the operators in the language
    (including many covered in later chapters) and arranges them in groups
    from highest to lowest precedence.

    Thus, in Listing 3-16 the first printf() statement in the second group of
    statements multiplies 20 by 20, then adds 40, resulting in 440. However,
    you can use parentheses to impose a different order of precedence, as
    shown in the next statement. To evaluate the expression 20 * (20 + 40),
    QuickC performs the addition first (resulting in 60) and then multiplies
    20 by 60 to produce a value of 1200.

    The next two statements use combinations of variables. As an exercise,
    perform the calculations on paper before you run the program. Remember to
    observe the rules of precedence. Did your answers agree with QuickC's?

    The final two statements in MATH.C illustrate a common problem for the
    unwary beginning C programmer. QuickC divides integer and floating-point
    types differently. When you specify numbers as integers, as in the first
    statement, integer division is performed. Accordingly, 5 divided by 2 is 2
    because this type of division discards any remainder. (A remainder in
    division is a fraction, and int types cannot represent fractions.)
    However, when you specify numbers with decimal points, QuickC treats them
    as float types, resulting in the expected answer of 2.5. Variables of int
    and float types are handled the same way as the literals above.

    The RECEIPTS.C program (Listing 3-17 on the following page) performs
    practical calculations with QuickC's math operators. Notice that we
    declare the units variable as an int type (you can't sell half a unit!)
    and the price and tax rates as float types.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 3-8 can be found on p.77 of the printed version of the book.    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 3-8. Operator precedence help screen.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* receipts.c -- calculates gross and net */
    /*               receipts on sales        */

    main()
    {
        int units = 38;       /* number sold */
        float price = 149.99, /* price per item */
        rate = 0.06;          /* sales tax rate */

        /* variables to hold calculated totals */
        float gross, tax, net;

        /* perform calculations */
        net = units * price;
        tax = net * rate;
        gross = net + tax;

        /* print results */
        printf("\tSales Report\n");
        printf("Net sales: \t%6.2f\n", net);
        printf("Tax:\t\t %5.2f\n", tax);
        printf("Gross sales:\t%6.2f\n", gross);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-17.  The RECEIPTS.C program.

    The "calculations" section uses expressions to generate values for the
    variables net, tax, and gross. The printf() statements combine tab escape
    sequences \t and field width specifiers to align the output. Specify only
    two decimal places for money amounts. (Makes cents, doesn't it?) The
    program produces the following report:

            Sales Report
    Net sales:      5699.62
    Tax:             341.98
    Gross sales:    6041.60

Arithmetic with Mixed Types

    The accuracy of a number generated by QuickC depends on its data type and
    the format in which it is printed. An additional problem arises when you
    perform arithmetic operations on literals (constants) or variables of
    different data types: For example, what happens when you divide an int by
    a float?

    For calculations with mixed data types, C ranks data types roughly
    according to the number of bytes of storage they require. From highest to
    lowest, they are:

    double  8 bytes
    float   4 bytes
    long    4 bytes
    int     2 bytes
    char    1 byte

    Generally, QuickC converts the lower-ranking type to the higher-ranking
    one before it performs the calculation. Thus, when QuickC divides 49 by
    12.5, it first converts 49 to 49.0 (a float), then performs the division.
    (If QuickC chose a lower-ranking type, the calculation would lose
    precision. The above calculation, for example, would be 49 / 12 = 4 in
    integer division.) Although the long and float types both use four bytes,
    a float can contain a fractional part that would be lost when converted
    "down" to a long: Therefore, float is ranked as the "higher" type.
    Finally, QuickC converts float types to double types before it calculates
    the result.

    Although it's convenient that QuickC performs conversions for you, some
    real problems can occur if you assign the results of a calculation to a
    variable of an incorrect data type. The following example illustrates such
    a mistake:

    int sales, units = 50;
    float price = 1.99;
    sales = units * price;
    printf("Total sales are %d\n", sales);

    QuickC calculates price * units correctly by converting units from 50 to
    50.0 (to make it a float), and then multiplying it by the float value of
    price (1.99). The value of the expression is now the float value of 99.50.
    So far, so good. However, we assigned this value to the variable sales,
    which we declared as an int type. As a result, the fractional part of the
    value (.50) is dropped, making the value of sales an incorrect 99.00. The
    solution to this problem is simpleâ”€â”€consider all of the potential values
    for a variable before you declare it. In this case, you need to declare
    the variable sales as a float.

    QuickC can help remind you of potential problems with data type
    conversions. When you select the Compile option from the Run menu, the
    left side of the dialog box lists four levels of compiler warning messages
    (levels 0 through 3). If you select level 2 before you compile programs,
    QuickC sends a warning message for each program statement that causes a
    data type conversion. A typical message follows:

    warning C4051: (1 of 4)
    data conversion

    When you see this type of message, note the statement the cursor is on,
    examine the data types involved, and look up the meaning of warning (4051)
    in the Microsoft QuickC Programmer's Guide. There you will note that this
    is an advisory message, and QuickC issues it for perfectly legitimate
    conversions, such as the int to float conversion in our earlier division
    example.

    The MIXED.C program (Listing 3-18 on the following page) shows more
    examples of operations with mixed data types.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* mixed.c -- shows the effects of mixing */
    /*            data types in an expression */

    main()
    {
        int     i = 50, iresult;
        long    l = 1000000, lresult;
        float   f = 10.5, fresult;
        double  d = 1000.005, dresult;

        fresult = i + f;         /* int + float to float */
        printf("%f\n", fresult);

        fresult = i * f;         /* int * float to float */
        printf("%f\n", fresult);

        lresult = l + i;         /* long + int to long */
        printf("%ld\n", lresult);

        printf("%f\n", d * f);   /* double * float */
                                    /* to double */
        fresult = d * f;         /* assigned to a float */
        printf("%f\n", fresult); /* loses some precision */

        /* debugging a division problem */

        iresult = i / l;          /* int / long to int*/
        printf("%d\n", iresult);  /* whoops! loses result */
        printf("%ld\n", iresult); /* this won't fix it */
        fresult = i / l;          /* store in float result */
        printf("%f\n", fresult);  /* doesn't work */
        dresult = i / l;          /* try a double */
        printf("%f\n", dresult);  /* doesn't work */
        fresult = (float) i / l;  /* try type cast */
        printf("%f\n", fresult);  /* correct result */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-18.  The MIXED.C program.

    Compare this output to the program statements:

    60.500000
    525.000000
    1000050
    10500.052500
    10500.052734
    0
    8519680
    0.000000
    0.000000
    0.000050

    The first set of statements adds an int and a float value and prints the
    result, which is 60.5, a float value. This shows QuickC's default type
    conversion at work. The second set of statements shows the same conversion
    with a multiplication operation. The third pair of statements adds a long
    to an int. Note that the result is correct (100,000 + 50 = 100,050), and,
    from its size, you can guess that it must be a long. QuickC converts the
    value 50 to a long before it does the calculation.

    Next, the program works with double and float types. When we specify d * f
    in the printf() statement, QuickC converts the float value f to a double
    and calculates a double result, which we print. (Remember, you can use the
    %f format specifier with either float or double types.) Because the answer
    requires nine places of precision, converting from float to double
    preserves the accuracy of the value.

    Next, we perform the same calculation, but we assign the result to a float
    value, f. Notice that the result, 10,500.052734, becomes inaccurate
    starting at the fourth decimal place. Converting from double to float can
    produce both large and subtle errors, depending on the numbers involved.
    To be safe, use a double variable to hold the result of this type of
    calculation.

    The last lengthy set of statements illustrates various approaches for
    dividing an int value i by a long value l. Only the last method produces
    the correct result.

    Assigning the result of the division to an int variable returns a 0,
    because the result is a very small decimal fraction (50 / 1,000,000), and
    integer division does not recognize remainders.

    In the next statement we assume that the result of the division is a
    decimal fraction and that we can store it in a float. But this doesn't
    work either. When we add more decimal places by using a double variable
    for the result, we still get a result of 0. The problem here is that when
    the two integer variables i and l are divided, the integer portion of the
    result, 0.000050, is 0. At this point, we can't retrieve the decimal
    fraction. Assigning it to a float or a double merely gives you a
    floating-point representation of 0!

Type Casting

    C provides a solution to our division dilemma with a construction called a
    "type cast." A type cast explicitly converts a value to a specified type
    before any operations are done on that value. Consider the following
    example:

    int i1 = 10, i2 = 3;
    printf("%d\n", i1 / i2);
    printf("%f\n", (float) i1 / i2);

    In the first printf() statement, we divide the two integers and produce
    the integer result of 3. In the second printf() statement, we add (float)
    before i1. This is the type cast: It converts the value of i1 to a float.
    Because a type cast has a higher precedence than the arithmetic operators,
    it converts i1 to a float before the division operation. Now the division
    operation contains a float and an int! QuickC's default type conversion
    then converts i2 to a float as well, and the result is the float value
    3.33333. If you look at the last two statements of the MIXED.C program,
    you can see we used a type cast in the same way, with the correct result
    of 0.000050.

    Type casts are useful for handling variables of lower-ranking data types
    (int, for example) that must occasionally be used in calculations to
    produce a result of a "higher" type (such as float). It is more efficient
    in terms of both storage and processing time to declare such variables as
    the lower type and to use type casts when necessary. Later, you will find
    type casts valuable when you must convert values to a specific type.


Getting Input with scanf()

    In order to write programs that have real-world utility, we must first
    understand how a C program gets input from the user. The all-purpose C
    function for getting input and storing it in a variable is called scanf().
    (Like printf(), scanf() is a "built-in" QuickC core library function.)
    Figure 3-9 shows how it works.

    Let's assume we have a program with a declared integer variable named
    acct_no. When the scanf() statement executes, the program waits for input
    from the user. After the user types the number and a carriage return, the
    input is stored in the variable acct_no, as if it had been assigned by an
    assignment statement. Notice that the acct_no variable in the scanf()
    argument list is preceded by an ampersand (&). Do you remember when we
    placed ampersands in front of variable names in the VARADDRS.C program
    (Listing 3-4 on p. 57) to retrieve the storage addresses of the
    variables? The scanf() function requires as its second argument an address
    at which it can store the input. The & returns the address of the
    following variable. If you omit the address operator from the front of the
    variable name, the value of the variable is interpreted as though it were
    an address, and the input is stored at that address. This can produce
    frightful results if it overwrites information that your program needs!

    Format specifier for
    type of value wanted
            â”‚
            â”Œâ”´â”
    scanf ("%d", &acct_no);
                â”‚â””â”€â”€â”€â”€â”¬â”€â”˜
                â”‚     â”‚
        "address of"   Variable name
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                    â”‚
        Variable to store input in

    Figure 3-9. Parts of a scanf() statement.

    The first argument in the scanf() statement in Figure 3-9 is "%d". This
    looks and works like the format specifiers we used with printf()â”€â”€it
    specifies the type of the value that the program expects. As with
    printf(), the "%d" specifies an integer. You can also use most of the
    other specifiers you used with printf(). For example:

    scanf("%f", &deposit);

    gets a value for the float variable deposit.

    Notice that scanf(), by itself, does not print a prompt for the user; it
    merely presents the user with a blinking cursor. Therefore, you should
    precede a scanf() statement with a printf() statement that tells the user
    what information to supply. In the example above, we might precede the
    scanf() statement with:

    printf("How much is your deposit?");

    The cursor now appears following a space after the prompt. You don't need
    to include a newline character: The cursor will move to the next line when
    the user presses Enter after typing the input.

    You can also use scanf() to get values for more than one variable at a
    time:

    printf("What is your age and weight?");
    scanf("%d %d", &age &weight);

    In this example, the user types an age, a space (to separate the values),
    and then a weight. Note that the user can substitute an Enter or a Tab for
    the space.

    The CONVERT.C program (Listing 3-19) uses scanf() to prompt a user for a
    temperature in Fahrenheit and then converts the temperature to Centigrade.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* convert.c  -- converts Fahrenheit temperature     */
    /*               to Centigrade; gets value from user */

    main()
    {
        float ftemp, ctemp;

        printf("What is the temperature in Fahrenheit? ");
        scanf("%f", &ftemp);
        ctemp = (ftemp - 32.0) * 5 / 9.0;

        printf("The temperature in Centigrade is %5.2f", ctemp);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-19.  The CONVERT.C program.

    A sample user dialog with CONVERT.C follows:

    What is the temperature in Fahrenheit? 87
    The temperature in Centigrade is 30.56

    We print the prompt with a printf() statement, then use a scanf()
    statement with a floating-point specifier %f to get the input value for
    the float variable ftemp.

    The AVGTEMP.C program (Listing 3-20) averages the daily high temperatures
    for a week. When you run the program, it prompts for the high temperature
    for each day of the week, beginning with Monday.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* avgtemp.c -- finds average temperature */
    /*              for the week              */

    main()
    {
        int t1, t2, t3, t4, t5, t6, t7;
        float avg;

        printf("Enter the high temperature for:\n");
        printf("Monday: ");
        scanf("%d", &t1);
        printf("Tuesday: ");
        scanf("%d", &t2);
        printf("Wednesday: ");
        scanf("%d", &t3);
        printf("Thursday: ");
        scanf("%d", &t4);
        printf("Friday: ");
        scanf("%d", &t5);
        printf("Saturday: ");
        scanf("%d", &t6);
        printf("Sunday: ");
        scanf("%d", &t7);

        /* calculate and display average */
        avg = (t1 + t2 + t3 + t4 + t5 + t6 + t7) / 7.0;
            /* divide by 7.0 to ensure float result */
        printf("The average high temperature for");
        printf(" this week was %5.2f degrees.\n", avg);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-20.  The AVGTEMP.C program.

    The int variables t1 through t7 store the daily high temperatures, which
    are obtained by a series of scanf() statements. The program then
    calculates an average and prints it out. A sample dialog with this program
    might look as follows:

    Enter the high temperature for:
    Monday: 82
    Tuesday: 91
    Wednesday: 97
    Thursday: 104
    Friday: 95
    Saturday: 88
    Sunday: 78
    The average high temperature for this week was 90.71 degrees.

    Note: It is important to note that scanf() does not check to make certain
    that the input is compatible with the data type of the variable in which
    it is stored.


Shortcut Assignments, Increments, and Decrements

    Now that you know how to assign a value to a variable with the assignment
    operator = and how to use arithmetic operators to calculate new values, we
    can show you a few tricks and shortcuts. In the course of a program, it is
    often useful to add a value to a variable repeatedly or to subtract a
    value from a variable repeatedly. For example, a program that counts lines
    needs to add one to a variable (such as total_lines) each time it counts a
    new line. We could do this as follows:

    total_lines = total_lines + 1;

    That's the way most languages do it. However, because changing the value
    of a variable is such a common occurrence in programming, C provides
    special, concise "arithmetic assignment operators" for the purpose.

Arithmetic Assignment Operators

    The arithmetic operators are the +, -, *, /, and %, and the assignment
    operator is the =. The arithmetic assignment operator, as the name
    suggests, is a combination of an arithmetic operator and the assignment
    operator: for example, +=. When a statement executes, QuickC performs the
    specified arithmetic on the variable's value and then assigns the result
    of the calculation to the variable as its new value. Using an arithmetic
    assignment operator, we can write a shorter version of the statement that
    increases the value of total_lines by one:

    total_lines += 1;

    Below are more examples that use arithmetic assignment operators:

    count -= 1;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Subtract 1 from the value of count
    fare += 0.75;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Add 0.75 to value of fare
    value *= 10;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Multiply value by 10

    You can use any arithmetic operator in an arithmetic assignment operation.
    Table 3-2 lists the five possible arithmetic assignment operators. The
    addition and subtraction assignment operators are the most commonly used.

    The OPEQUAL.C program (Listing 3-21) demonstrates the use of arithmetic
    assignment statements. The printf() statements print several arithmetic
    assignment expressions and their results.

    Be sure that when you read the printf() statements in the program you can
    correctly predict the following output:

    Starting values: m = 10 n = 5
    m += 2 makes m 12
    m -= n makes m 7
    m *= 2 makes m 14
    m = m + 1 makes m 15
    m += 1 makes m 16

    Table 3-2. Arithmetic Assignment Operators
    Operator           Meaning
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    +=                 Add to value and assign
    -=                 Subtract from value and assign
    *=                 Multiply by value and assign
    /=                 Divide by value and assign
    %=                 Get remainder from division and assign
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* opequal.c -- shows combination math/assignment */
    /*              operators and increment operators */
    main()
    {
        int m = 10, n = 5;
        printf("Starting values: m = %d n = %d\n",
                m, n);

        /* combination of arithmetic and assignment */
        printf("m += 2 makes m %d\n", m += 2);
        printf("m -= n makes m %d\n", m -= n);
        printf("m *= 2 makes m %d\n", m *= 2);

        /* two ways to increment m */
        printf("m = m + 1 makes m %d\n",
                m = m + 1);
        printf("m += 1 makes m %d\n",
                m += 1);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-21.  The OPEQUAL.C program.

Increment and Decrement Operators

    As the last program demonstrated, both m = m + 1 and m += 1 added one to
    the value of m. If you've done any programming, you know how frequently
    the value of a variable must be increased or decreased by one. This is
    especially true when you create a "counter" variable that keeps track of
    the number of times a statement in a loop executes. C provides an
    ultra-concise operator, the increment operator ++, to add one to the value
    of a variable. Similarly, --, the decrement operator, subtracts one from
    the value of a variable. Consider the following examples:

    count++ ;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Add 1 to value of count
    index-- ;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Subtract 1 from value of index

    Note that these increment and decrement operators are really arithmetic
    assignment statements. They add (or subtract) one and assign the resulting
    value to the variable.

    count++;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€is equivalent toâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€count += 1;
    index--;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€is equivalent toâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€index -= 1;

    (Most programmers do not use a space between the increment [or decrement]
    operator and the variable name. However, in C it is perfectly legal to use
    intervening spaces, as in count + +.) INCDEC.C (Listing 3-22) shows how
    the increment and decrement operators change the value of a variable.
    Compare the program statements to the following output:

    a is 10
    ++a is 11
    --a sets a back to 10

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* incdec.c -- shows effect of            */
    /*             increments and decrements  */

    main()
    {
        int a = 10;

        printf("a is %d\n", a);
        printf("++a is %d\n", ++a);
        printf("--a sets a back to %d\n", --a);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-22.  The INCDEC.C program.

Pre-increment vs Post-increment

    In the INCDEC.C program we put the increment or decrement operator in
    front of the variable name. However, you also can use it after the
    variable name. In either case the variable is incremented or decremented;
    but there is one important difference. When you use the operator in front
    of a variable name, the incrementing or decrementing is done immediately.
    When you use the operator after the variable name, the incrementing or
    decrementing is not done until the next use of the variable. The PREPOST.C
    program (Listing 3-23) shows how this works. The output of the program
    illustrates how incrementing is delayed:

    b is 100
    b++ is still 100
    but after it's used, b is incremented to 101

    ++b, on the other hand, is immediately 102

    Notice what happens to b when we use the increment operator after it,
    rather than before it. The first printf() statement with the value b++
    prints the original value of 100, showing that it has not yet been
    incremented. The next printf() statement, however, prints 101.

    As a practical matter, the distinction between pre-increments and
    post-increments (or decrements) is usually important only when the
    variable is incremented or decremented while it is being used with other
    operators in a single expression. For example, suppose you want to
    increment counter and also assign it to total in the same statement.
    Assuming counter is currently 10:

    total = counter++;

    assigns 10 to total, because counter is assigned to total but not
    incremented until the next time it is used. On the other hand:

    total = ++counter;

    assigns 11 to total, because counter is incremented immediately and then
    assigned.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* prepost.c -- shows effect of pre- */
    /*              and post-increments  */
    /*              and decrements       */

    main()
    {
        int b = 100;

        printf("b is %d\n", b);
        printf("b++ is still %d\n", b++);
        printf("but after it's used, ");
        printf("b is incremented to %d\n\n", b);

        printf("++b, on the other hand, ");
        printf("is immediately %d\n", ++b);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-23.  The PREPOST.C program.


Relational Operators

    If you have some programming experience, you know that most programs must
    make decisions based on the values of certain variables. Variables are
    tested or compared, and the result of the test determines which program
    statement will execute next. The next two chapters cover the variety of
    "control structures" that C provides for this purpose. Let's build the
    foundation for those discussions by looking at the operators that C uses
    for testing or comparing values.

    A relational operator compares two values, which can be variables, literal
    numbers, or whole expressions. A combination of relational operators and
    values is called a relational expression. An example is count > 10, which
    translates as "is the value of count greater than 10?" The > in this
    expression is the "greater than" relational operator. The expression is
    true or false depending on the current value of the variable count. If
    count is 8, for example, the expression is false.

    Table 3-3 illustrates the ways we can compare two values, a and b. In
    reality, the values can be constants, variables, or expressionsâ”€â”€anything
    that expresses a numeric value. (Remember from our discussion of ASCII
    that characters, too, are essentially numeric values.)

    We described the value of a relational expression as being "true" or
    "false." These terms are useful ways for us to follow the logic of a
    program, but the actual value of a relational statement, like everything
    else in the computer, is numeric. When a statement is true, its value is
    1; when a statement is false, its value is 0. On the following page, the
    RELATION.C program (Listing 3-24) uses printf() statements to show the
    values of some statements that use relational operators.

    The program generates the following output:

    a = 5    b = 3   c = 4
    Expression a > b has a value of 1
    Expression a == c has a value of 0
    Expression a > (b + c) has a value of 0

    Because a is 5 and b is 3, the expression a > b has a value of 1, or true.
    Because c is 4, a == c has a value of 0, or false. The third expression
    combines relational and arithmetic operators: It first calculates the
    quantity (b + c), and then it compares the value to a.

    Table 3-3. Relational Operators
    Expression               Meaning
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    a < b                    Is a less than b?
    a > b                    Is a greater than b?
    a == b                   Is a equal to b?
    a != b                   Is a not equal to b?
    a <= b                   Is a less than or equal to b?
    a >= b                   Is a greater than or equal to b?
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* relation.c  -- shows effect of      */
    /*                relational operators */

    main()
    {
        int a = 5, b = 3, c = 4;
        printf("a = %d\t b = %d\t c = %d\n", a, b, c);

        printf("Expression a > b has a value of %d\n",
                a > b);
        printf("Expression a == c has a value of %d\n",
                a == c);
        printf("Expression a > (b + c) has a value of %d\n",
                a > (b + c));
        printf("Expression a = b has a value of %d\n",
                a = b); /* what happened here? */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-24.   The RELATION.C program.

Relational == vs Assignment =

    Here's a pitfall to watch out for: In C, a single equal sign = is the
    assignment operator, but a double equal sign == is the relational "equals"
    operator. In some languages (such as BASIC), a single operator, =, serves
    both purposes. So, if you are familiar with the BASIC usage, you might
    make errors with these operators until you get used to the difference. A
    common symptom of this error is a test that always appears to be either
    true or false. For example, if you type the assignment count = 10 instead
    of the relational count == 10 and then use the result in a control
    structure (such as a loop or if statement), QuickC always sees the result
    of the test as "true." Why? Because although relational expressions return
    a value of 1 for "true," QuickC considers any nonzero value to be "true"
    in this type of test. Because the sample statement with = is actually an
    assignment, its value is 10 (the number assigned), which QuickC interprets
    as "true" during a relational test.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Assignment and "Equals" Relation
    The following table lets you compare the assignment and relational
    "equals" operators in C to those in other common languages:

    Language               Assignment              Relation
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    C
    =
    ==
    BASIC                  =                       =
    Pascal                 :=                      =
    FORTRAN                =                       .EQ.
    Logo                   make                    =
    COBOL                  MOVE                    EQUAL TO
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Precedence of Relational Operators

    In RELATION.C, we used parentheses in the expression a > (b + c). If you
    check QuickC's operator precedence help screen (Figure 3-8 on p. 77), you
    will see that relational operators have a lower precedence than arithmetic
    operators. Therefore, even if you don't use parentheses, b + c is
    calculated first, and only then is the result compared to a. Nevertheless,
    it is a good programming practice to use parentheses to visually clarify
    an expression.


Logical Operators

    Sometimes it is necessary or useful to test for more than one thing in the
    same expression or statement. For example, you might want to test to see
    if either the temperature or pressure in a boiler has exceeded the safety
    limit. Let's assume the test for temperature is (temp < 900) and the test
    for pressure is (pressure < 5000). We can combine the two tests as
    follows:

    (temp < 900) && (pressure < 5000)

    The && is called the AND logical operator. It compares the results of two
    relational values and returns a value of true (1) only if both are true.
    QuickC first makes the temp test, then it makes the pressure test (testing
    is from left to right). Then the && operator checks to see if both tests
    were true.

    The OR logical operator, ||, works like the AND operator, except that it
    returns a value of true (1) if either or both of the tests are true. Thus,
    the statement

    (ch == 'q') || (turn > last_turn)

    is true if either the current value of ch is `q' or the current value of
    turn is greater than that of last_turn, or both. You could use this
    statement to check if a game is over.

    Using two relational operators, && and ||, and two possible results of a
    test (true and false), there are four possible results for a relational
    statement involving two tests. The TRUTH.C program (Listing 3-25 on the
    following page) prints these out by making comparisons using ones and
    zeros that represent the result of already completed relational tests.
    Recall that QuickC regards a value of 1 to be "true" and a value of 0 to
    be "false." Thus, 1 AND 1 is 1 means "True and true is true."

    1 AND 1 is 1
    1 AND 0 is 0
    0 AND 0 is 0
    1 OR 1 is 1
    1 OR 0 is 1
    0 OR 0 is 0

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* truth.c -- shows logical operators */
    main()
    {
        printf("1 AND 1 is %d\n", 1 && 1);
        printf("1 AND 0 is %d\n", 1 && 0);
        printf("0 AND 0 is %d\n", 0 && 0);
        printf("1 OR 1 is %d\n",  1 || 1);
        printf("1 OR 0 is %d\n",  1 || 0);
        printf("0 OR 0 is %d\n",  0 || 0);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 3-25.  The TRUTH.C program.

    Once again, if you check the QuickC operator precedence help screen, you
    will notice that logical operators, such as && and ||, have a lower
    precedence than the relational operators, such as < or ==. Therefore, we
    didn't need parentheses around the relational expressions in our examples
    because QuickC evaluated them before it checked the logical operators.
    Again, we used parentheses because they make these complex expressions
    easier to read.

    The last operator we need to discuss is the !, or "not" operator. Its
    function is simple enoughâ”€â”€it reverses the truth value of a relational
    expression. For example, if a is 10, a > 5 is true, but !(a > 5) is false.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€