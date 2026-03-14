Chapter 6  Functions and Function Calls

    One of the great advantages that C offers a programmer is its huge variety
    of library functions, which cover everything from manipulating text to
    controlling memory allocation. The seasoned C programmer soon learns that
    the C library contains most of the tools needed to perform a given task.
    However, the real power of C derives from the ease with which you can
    design customized C functions that perform the specific and unique
    operations your program requires. In this chapter, we will show you how to
    create and use these functions.


Functions and Program Design

    Every C program must have at least one user-defined function, namely
    main(). Most real-world C programs, however, consist of many user-written
    functions, because the procedure for processing data usually involves many
    different steps. A program that calculates statistics, for example, might
    have to ask the user for data, check the data for validity, store the data
    in memory or on disk, process the data (often according to several
    criteria), and report the results, possibly in a variety of formats. If
    all of this program code were in the main() function, the resulting jumble
    would hamper a programmer trying to visualize where one step ends and the
    next one begins. Debugging the program would be nearly impossible because
    you would have difficulty figuring out which of the intertwined parts
    worked correctly and which ones did not. And if you decided to revise the
    program to add new capabilities, you could not easily find the appropriate
    place to add new code.

    Most experienced programmers design programs using a "top-down" approach.
    This method resembles writing an outline for a report. First, list the
    principal ideas or steps. Then divide those ideas or steps into subtopics,
    and continue subdividing until you feel ready to write the actual
    sentences. Using a similar approach, the main() function for our
    statistics program might read:

    main()
    {
    data_menu();
    while (more_data)
        {
        get_data();
        check_data();
        store_data();
        }
    process_data();
    report_menu();
    do_report();
    }

    Each of the names followed by parentheses in the definition of main() is a
    call to a user-defined function. Notice how this "outline" clearly shows
    the overall flow of the program. First, the program offers the user
    choices in a data-entry menu; then it enters a loop that receives,
    validates, and stores data as long as more data is entered. The data is
    then processed. Another menu lets the user generate a specific type of
    report, and finally the program prints that report.

    Note that using separate functions does more than merely keep the parts of
    a program conceptually separate; it also provides an orderly way of
    communicating information between different sections of the program. Each
    function receives information, such as the values of certain variables,
    and after it finishes executing, returns the transformed information to
    another section of the program.

    In a C program, any function can call any other function. This means that
    your user-defined functions can call other user-defined functions as well
    as C library functions. For example, the definition of do_report(), shown
    on the opposite page, might call other user-defined functions, each of
    which prints a different kind of report, corresponding to the choices
    offered in the report_menu() part of the program.

    do_report()
        {
        switch (choice)
            {
            case 'b' :
                bar();
                break;
            case 'p' :
                pie();
                break;
            case 'l' :
                line();
                break;
            case 't' :
                table();
                break
            }
        }

    Normally, you declare each user-defined function in main() before the
    program calls it. The definitions of these user-defined functions usually
    follow the end of the definition of main(). (You also can define groups of
    functions in separate files: We will discuss this in Chapter 12.) Figure
    6-1 proposes a general outline for a program that declares and uses three
    user-defined functions.

    Dividing a program into logically organized user-defined functions also
    lets you develop the program one piece at a time. You can start by putting
    "stub" definitions in the functions, such as:

    pie()
        {
        printf("executing pie()\n");
        }

        Function
        declarations
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”                Function definitions
    â”‚ main ( )       â”‚    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ {              â”‚  â”Œâ”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”                â”‚
    â”‚   func1 ( );   â”‚ â”€â”¼â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”                 â”‚                â”‚
    â”‚   func2 ( );   â”‚ â”€â”˜ â”‚â”Œâ”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”   â”Œâ”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”  â”Œâ”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”
    â”‚   func3 ( );   â”‚ â”€â”€â”€â”˜â”‚  func1 ( )  â”‚   â”‚  func2 ( )  â”‚  â”‚  func3 ( )  â”‚
    â”‚   â”€â”€â”€â”€â”€â”€â”€â”€â”€    â”‚     â”‚  {          â”‚   â”‚  {          â”‚  â”‚  {          â”‚
    â”‚   â”€â”€â”€â”€â”€â”€â”€â”€â”€    â”‚     â”‚  â”€â”€â”€â”€â”€â”€â”€    â”‚   â”‚  â”€â”€â”€â”€â”€â”€â”€    â”‚  â”‚  â”€â”€â”€â”€â”€â”€â”€    â”‚
    â”‚   â”€â”€â”€â”€â”€â”€â”€â”€â”€    â”‚     â”‚  â”€â”€â”€â”€â”€â”€â”€    â”‚   â”‚  â”€â”€â”€â”€â”€â”€â”€    â”‚  â”‚  â”€â”€â”€â”€â”€â”€â”€    â”‚
    â”‚   â”€â”€â”€â”€â”€â”€â”€â”€â”€    â”‚     â”‚  â”€â”€â”€â”€â”€â”€â”€    â”‚   â”‚  â”€â”€â”€â”€â”€â”€â”€    â”‚  â”‚  â”€â”€â”€â”€â”€â”€â”€    â”‚
    â”‚ }              â”‚     â”‚  }          â”‚   â”‚  }          â”‚  â”‚  }          â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜   â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜  â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 6-1. Outline for a C program with functions.

    These let you test the overall control structures of the program (the
    loops, branches, and switches) before you write the actual routines that
    perform the various tasks. Then you can replace functions one at a time
    with their real definitions. After you are certain that a function works
    properly, you can move to the next function. The basic philosophy of this
    type of programming is "divide and conquer."


Declaring and Defining a Function

    Now that we've discussed the advantages of user-written functions in
    program development, let's look at the mechanics of declaring, defining,
    and using your own functions. Always remember that you must declare your
    functions before you use them. In earlier chapters, when you used the
    #include directive to allow calling C library functions in your program,
    QuickC inserted function declarations and definitions into the program.
    For functions you create yourself, however, you must provide the
    declaration and a definition.

Declaring a Function

    Let's declare and define a function that prints an error message. The
    general format of a simple function declaration is as follows:

    return_type name();

    In the declaration, return_type refers to the data type (int, float, etc.)
    of the value that the function returns. Because our first example is a
    function that does not return a value, we must use the special word void
    as the return type. (The word void, in this instance, doesn't mean
    "invalid," but rather "empty.")

    The function nameâ”€â”€error, in our exampleâ”€â”€must be followed by parentheses,
    which hold the parameters the function is designed to use. In the case of
    an error message function, parameters might include a string to print and
    values that would indicate that the message be printed in high-intensity
    text, accompanied by a beep, and so on. You must always include
    parenthesesâ”€â”€even if, as in the case of our error() example, you use no
    parameters. (The compiler uses the parentheses to distinguish a function
    from a variable.) Note also that you must use a semicolon at the end of
    the line. Thus, we declare our error messageâ”€printing function as follows:

    void error();

    As with variable declarations, you can declare several functions of the
    same type on one line, as in the following declaration:

    void error(), greeting(), warning();

    Usually, programmers place the declarations for user-defined functions in
    the definition of main(), before any other statements (except possibly
    comments).

    main()
    {
        void error(); /* function declaration */
        other function declarations;
        ...
        other statements;
        ...
    }

    However, if a program has many user-defined functions, you might want to
    put the declarations before main(). This enables you to see the
    declarations more easily and separates them from the code of main()
    proper.

Defining a Function

    After you declare a function, you must define it with statements that will
    execute when the program calls the function. The first line of the
    function definition essentially repeats the original function declaration:

    void error()

    However, remember that, with a definition, you use no semicolon at the end
    of the line. The next line should contain an opening brace ({ ); then come
    the statements that define the function; and finally, the definition ends
    with a closing brace (} ). Thus, we write our error() function definition
    as follows:

    void error()
        {
        printf("Error!\a\n");
        }

    When a statement calls this function, it prints the word Error! and sounds
    a beep. (Notice the \a [alert] escape sequence, which is listed in Figure
    3-5 on p. 68.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    ANSI and Function Declarations
    QuickC and other current versions of C do not require you to declare
    functions that return no value or an int value. The new ANSI standard and
    modern programming practice encourage you to declare all functions,
    however. This is to help the reader see how the functions work and to
    allow the compiler to check for inconsistencies between the definition of
    a function and the way it is called. For these reasons, which we explain
    in greater detail later, we declare all functions in our example programs.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Calling the User-defined Function

    We call our user-defined error() function the same way we call a library
    function like printf()â”€â”€by naming it in a statement in main() or in the
    body of another function. Consider the following example:

    main()
    {
    ...
        if ((number < 1) || (number > 9))
            error();  /* function call */
    }

    The if statement calls the error() function only if number is either less
    than 1 or greater than 9. Again, note that the function call must include
    the parentheses with the function name.

    The DBLBAR.C program (Listing 6-1) calls the user-defined function line()
    to print a double bar before and after a program title. Note that we
    declare line() before the statements in main(), that we call line() twice
    from within main(), and that we define line() following the end of main().
    Figure 6-2 shows the flow of control in this program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* dblbar.c -- prints header using */
    /*             line() function     */

    #define DOUBLE_BAR 205

    main()
    {
        void line();       /* declare line() function */

        line();            /* call line() function    */
        printf("dblbar.c -- prints header using\n");
        printf("line() function\n");
        line();            /* call line() again        */
    }

    void line()            /* function definition      */
    {
        int pos;
        for (pos = 1; pos <= 40; pos++)
            putch(DOUBLE_BAR);
        printf("\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-1.  The DBLBAR.C program.

                                â”Œâ”€â”€First call
        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â” â”‚  and return
        â”‚ main ( )          â”‚ â”‚           â”Œ - - - - - - - - - - - - -
        â”‚ {                 â”‚ â”‚           |                           |
        â”‚ void line ( );    â”‚ â”‚           |   â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”   |
        â”Œâ”€â”¼â–ºline ( ); â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€|â”€â”€â”€â”¼â–ºvoid line ( )â—„- - - -
        â”‚ â”‚ printf ("...);    â”‚             |   â”‚ {                 â”‚
        â”‚ â”‚ printf ("...);    â”‚             |   â”‚ int pos;          â”‚
    - -â”‚â–ºline ( );- - - - -â”‚- - - - - - -    â”‚ for (     )       â”‚
    |  â”‚ â”‚ }                 â”‚ â”‚               â”‚ printf ("...);    â”‚
    |  â”‚ â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜ â”‚           â”Œâ”€â”€â”€â”¼â”€}- - -            â”‚
    |  â”‚                       â”‚           â”‚   â”‚       |           â”‚
    |  â”‚           Second callâ”€â”˜           â”‚   â”‚       |           â”‚
    |  â”‚           and return              â”‚   â””â”€â”€â”€â”€â”€â”€â”€|â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    |  â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜           |
    |                                                  |
    â”” - - - - - - - - - - - - - - - - - - - - - - - -  â”˜

    Figure 6-2. Flow of control in DBLBAR.C.

    You can also follow the flow of this program by using QuickC's debugger.
    Select the Debug option in the Compile dialog box, and then select Trace
    On from the Debug window. When you recompile the program, you see the
    highlighted statement move through main() until it reaches the first call
    to line(). The debugger then highlights the statements in line().
    Highlighting returns to main() with the statement following the call to
    line(). Control shifts in the same manner when the program encounters the
    second call to line().

A Disadvantage in Using Functions

    The double-bar program demonstrates the advantage of using functionsâ”€â”€they
    reduce the size of the program. Any time we need to draw a line, we simply
    call line() rather than repeat the whole for loop. However, using
    functions has a potential disadvantage. At the machine-code level, each
    time the program calls a function, the current status of the calling
    program (including the contents of CPU registers) has to be saved,
    information must be passed to the function via a memory area called the
    "stack," and various other housekeeping operations must be performed to
    return control to the calling statement. Therefore, calling a function
    involves a lot more "overhead" than merely using a copy of the desired
    code wherever you need it in your program. (The performance difference is
    not noticeable with only a few function calls, but you might notice it
    when you execute a function call thousands of times within a loop.) The
    loss of efficiency is not critical in most cases and usually is far
    outweighed by the benefits of using functions. But keep in mind that the
    more function calls you use, the more important the overhead factor
    becomes.


Local and Automatic Variables

    A defined function, such as line(), can contain its own variable
    declarations within its definition. Variables declared within a function
    definition are called local variables, and they are accessible only within
    the function in which they are declared. Outside the function braces, the
    variables don't exist. To be accessible to all the functions in your
    program, a variable must be declared globallyâ”€â”€outside of any function.
    The extent of a variable's accessibility, or "visibility," is called the
    "scope" of a variable.

    In Figure 6-3, note that variables defined in func1() cannot be accessed
    from main(). They are "invisible" to main(), func2(), or anywhere else
    outside of the definition of func1(). For example, the definition of
    line() in DBLBAR.C declares an int variable pos, which is used in the for
    loop. (See Listing 6-1 on p. 152.) Suppose the main() function in
    DBLBAR.C contained the following line:

    printf("The variable pos in line() has a value of %d\n", pos);

    This line would produce a compiler error, because main() doesn't "know"
    that a variable called pos existsâ”€â”€pos is the private property of the
    line() function.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”                        ADDRESS
    â”‚  main  ( )  â”‚
    â”‚  {          â”‚
    â”‚   int n;â—„- - - - - -Visible only     8706
    â”‚   func1 ( );â”‚       in main ()       (remains
    â”‚   func2 ( );â”‚                        until end
    â”‚  }          â”‚                        of program)
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚  func1 ( )  â”‚
    â”‚  {          â”‚
    â”‚   int n;â—„- - - - - -Visible only     8694
    â”‚   â”€â”€â”€â”€â”€â”€â”€   â”‚       in func1 ()      (reused)
    â”‚   â”€â”€â”€â”€â”€â”€â”€   â”‚
    â”‚  }          â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚  func2 ( )  â”‚
    â”‚  {          â”‚
    â”‚   int n;â—„- - - - - -Visible only     8694
    â”‚   â”€â”€â”€â”€â”€â”€â”€   â”‚       in func2 ()      (reused)
    â”‚   â”€â”€â”€â”€â”€â”€â”€   â”‚
    â”‚  }          â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 6-3. Local variables.

    Similarly, if you declare a variable called pos within main(), it is
    private to main() and not accessible from within a function called by
    main().

    Because variables defined inside functions are local in C, you can use
    variables with the same name in different functions. Thus, many of your
    program functions can use a variable named count, yet QuickC maintains and
    refers to each one separately.

Variables Used in Functions Are Automatic

    Another important characteristic of a local variable is that it is
    "automatic": The variable is created (meaning that internal storage is
    allocated and the address recorded) each time its function is called.
    Conversely, the variable is destroyed and its internal storage released
    when the function ends and control returns to the calling statement. Only
    a local variable can be automatic (and temporary) because the compiler
    knows that it is valid only while the function executes. (A global
    variable must be stored permanently, because the compiler must always
    assume that the program will need its value again.) Automatic variables
    permit more efficient storage allocation because the same block of memory
    can store many temporary variables as the program executes. C programs
    that use local, automatic variables also are smaller than comparable
    programs that make the same variables global.

    The LOCAL.C program (Listing 6-2 on the following page) illustrates the
    way local variables work. (Again, refer to Figure 6-3.) The main()
    function declares an int variable, n, and prints its value and internal
    address. The program then calls the func1() and func2() functions. Each of
    these functions also defines a variable called n and prints its value and
    address.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    The Scope of Variables
    In Pascal, you can "nest" function or procedure definitions within each
    other. A variable defined in a function or procedure is not only
    accessible to that function or procedure, but also to any definitions
    nested within the outer definition. This can make questions of the scope
    of certain variables rather complex. In C you cannot nest function
    definitions; therefore, a variable defined within a function is accessible
    only within that function.

    If you've programmed in older versions of BASIC, you probably expect all
    variables to be global, that is, accessible throughout the program. You
    also might remember times that this "feature" created nasty bugs. For
    example, you might have used count as the control variable of a loop in
    one subroutine and then days later used another variable called count in a
    different subroutine. Depending on the order in which BASIC called the
    subroutines, hard-to-trace bugs probably resulted because BASIC remembered
    the last value in count when it started the new count. If you are a BASIC
    programmer coming to C, rest assured that QuickC will never confuse the
    count of one function with the count of another.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* local.c -- local variables defined */
    /*            within functions        */

    main()
        {
        int n = 12;
        int func1(), func2();
        printf("n in main(): val %d ", n);
        printf("address %d\n", &n);

        printf("Calling func1()\n");
        func1();
        printf("Calling func2()\n");
        func2();
        }

    int func1()
        {
        int n = 8; /* local variable */
        printf("n in func1(): val %d ", n);
        printf("address %d\n", &n);
        }

    int func2()
        {
        int n = 20; /* local variable */
        printf("n in func2(): val %d ", n);
        printf("address %d\n", &n);
        }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-2.  The LOCAL.C program.

    The program's output (which may vary from setup to setup) demonstrates
    that QuickC recognizes each variable's correct value and address without
    any confusion:

    n in main(): val 12 address 8706
    Calling func1()
    n in func1(): val 8 address 8694
    Calling func2()
    n in func2(): val 20 address 8694

    Also notice that n in func1() and n in func2() use the same address. This
    occurs because when func1() ends, it discards its reference to the now
    useless local variable n. When the program calls func2(), QuickC reuses
    the same address for the new func2() local automatic variable n.

    Note that the address of the n in main() wasn't reused when the n in
    func1() or func2() was created. Variables declared in main() have no
    special statusâ”€â”€the n in main() is as automatic and local as the variable
    in the other functions. Remember, however, that QuickC discards an
    automatic variable only when the function in which it is defined
    terminates. Because main() doesn't end execution until the program itself
    ends, its variables (including n) are not destroyed and reused.

The auto Storage Class

    All variables declared within function definitions are, by default,
    automatic. Consider the following example:

    void plot_object()
        {
        auto int length, width;
        ...
        }

    The variables length and width are automatic because they are declared
    within a function. The auto designation merely reminds us of this. Note
    that auto is not a data type. Rather, it (and the keywords register,
    static, and extern) is what is called a "storage class." It refers to how
    QuickC manages the variable as the program runs. Specify the storage class
    before and in addition to the variable's data type (int in the previous
    example).


Static Variables

    Occasionally you will need a variable to retain its value after its
    function terminates. To do this, you must declare the variable used in the
    function with the static storage type, as follows:

    static int total;

    Now the value of total calculated during a previous call is still there
    when you call the function again. You use this storage class to keep
    running totals, for example. Note that a static variable is still local
    and accessible only within the function in which it is defined.

    The STATIC.C program (Listing 6-3 on the following page) uses the
    function countline() to count the words and characters in a line of text.
    (It simply counts a word whenever it encounters a space.) The static
    variables chars and words accumulate the counts. Because the variables are
    static, they retain the previous total each time the function is called.

    A sample of the program's output follows:

    Type some lines of text.
    Start a line with a . to quit.

    By now you should be able to
    Words so far 7. Chars. so far 28
    function very well in C!
    Words so far 12. Chars. so far 52
    .

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* static.c -- demonstrates a static variable */
    /*             that holds count of lines,     */
    /*             words, and characters          */

    main()
        {
        void countline();
        printf("Type some lines of text.\n");
        printf("Start a line with a . to quit.\n\n");

        while (getche() != '.')
            countline();  /* accumulate word and */
                        /* line counts         */
        }

    void countline()
        {
        static int words = 0; /* static variables */
        static int chars = 0;
        char ch;
        ++chars; /* count char typed when */
                /*function was called   */

        while ((ch = getche()) != '\r')
            {
            ++chars;
            if (ch == ' ')
                ++words;
            }
            ++words; /* count last word */

        printf("\nWords so far %d. Chars. so far %d\n", words, chars);
        }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-3.  The STATIC.C program.


External Variables

    You can declare global variables in C when you want two or more functions
    to share relevant values or to communicate with each other by periodically
    changing the value of a common variable. A global variable in C is
    referred to as external because it is defined outside the function
    definitions in the program.

    To declare an external variable, simply put its declaration outside of any
    function definition. External variables are usually placed after any
    #includes and #defines, but before the definition of main(). In the
    following example, we declare scale and palette outside of the function,
    making them external (global) and accessible throughout the program. The
    variables length and width, on the other hand, are local and accessible
    only within main().

    #include <stdio.h>
    #define VERSION 1.0

    int scale = 1.5,        /* global variables */
        palette = 1;        /* go here          */

    main()
        {
        int length, width;  /* local variables */
        ...                /* go here         */

    The EXTERNAL.C program (Listing 6-4) shows how you might use an external
    variable. We declare the variable length before main() to make it an
    external variable. After the user supplies a value for length, main()
    calls three functions: square(), triangle(), and circle(). Each of these
    functions accesses and uses the value of length to calculate the
    appropriate area.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* external.c -- shows an external variable */

    #define PI 3.14159
    int length; /* external (global) variable */
                /* declared before main()    */

    main()
        {
        void square(), triangle(), circle();

        printf("What length do you want to use? ");
        scanf("%d", &length);

        square();   /* calculate areas */
        triangle();
        circle();
        }

    void square()
        {
        float area;
        area = length * length;
        printf("A square with sides of %d has an area of %f\n",
            length, area);
        }

    void triangle()
        {
        float area;
        area = (length * length) / 2;
        printf("A right triangle with sides of %d has an area %f\n",
            length, area);
        }
    void circle()
        {
        float area;
        area = (length * length * PI);
        printf("A circle with radius of %d has area of %f\n",
            length, area);
        }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-4.  The EXTERNAL.C program.

    Try to resist the temptation to make all your variables external; this
    invites the problems we discussed earlier. Variables used in only one
    function should remain local. Variables used by only two or three
    functions might be better handled as parameters passed from one function
    to another. (We will discuss function parameters shortly.)


Register Variables

    Let's look at one more storage type for variables, the register type.
    Microprocessors such as the 8088 and 80286 have several built-in storage
    locations called registers. A program can store and retrieve data from a
    register more quickly than from a location in regular memory, where C
    usually stores variables. As a result, you gain a performance advantage by
    assigning a register to a frequently used variable in a time-sensitive
    application.

    The only problem with using registers is that usually there aren't enough
    registers to store all the data of a given operation. As shown in Figure
    6-4, the IBM family of Intel microprocessors (8088, 8086, and 80286) have
    four general-purpose, 16-bit registers that hold data being manipulated at
    the machine level.

                16 bits
            (2 bytes)
                â”‚
    â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚     AH      â”‚     AL      â”‚ AX
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚     BH      â”‚     BL      â”‚ BX
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚     CH      â”‚     CL      â”‚ CX
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚     DH      â”‚     DL      â”‚ DX
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
        8 bits        8 bits
        (1 byte)      (1 byte)

    Figure 6-4. General-purpose registers for the Intel 8086 family.

    In other languages, the compiler software determines which variables, if
    any, will be assigned registers. In C, however, you can tell the compiler
    to assign a register to a specific variable when you declare that
    variable, as follows:

    register int count;

    This declaration tells QuickC to store the count variable in a CPU
    register. (You can't specify which physical register to use, however.)
    Because registers in the 8088, 8086, and 80286 cannot store variables with
    values larger than two bytes, only char and int variables can be
    accommodated. Additionally, you cannot declare external or static
    variables as register variables, because registers cannot serve as
    permanent storage locations. Finally, QuickC assigns only two variables
    per function as register variables: You can make more declarations, but
    only the first two are honored. In fact, depending on the CPU workload,
    there is no guarantee that both, or even one, of the registers will be
    available. If speed is important to your program, try the declarations to
    see if they help.

    Which variables should you declare to be register variables? Obvious
    candidates include loop control variables or variables that are part of
    statements performed in a loop. But even though most loops execute many
    times, you shouldn't specify these variables as register storage type.
    QuickC uses optimization techniques to try to produce the fastest machine
    code possible from your program, and one of its basic speedup techniques
    is the assigning of registers to variables in loops. Thus, you gain little
    by specifying these as register variablesâ”€â”€in fact, you might even confuse
    the compiler and end up with less efficient code. The best variables to
    specify as register type are variables that are not involved with loops
    yet are used three or more times each time the function is called.


Passing Information to a Function

    Thus far, our user-defined functions have not required that any
    information be passed when we called them. Most functions, however,
    require one or more items of information, called arguments, or parameters.
    This is often true of the QuickC core library functions: printf() needs to
    know what to print and how to print it; scanf() needs to know what
    information to get from the user and where to store it; and so on. Indeed,
    because it uses no parameters, the line() function in Listing 6-1 on p.
    152 is extremely limited. As it stands, it always prints a line of 40
    characters. However, suppose we want 20 or 60 characters. Let's define
    this function so that when you call it, a parameter tells it how long the
    line should be:

    void line (length)   /* length is parameter      */
        int length;      /* declaration of parameter */
        {
        int pos;
        for (pos = 1; pos <= length; pos++)
            putch(DOUBLE_BAR);
        }

    When you call this function, the length parameter (placed in parentheses
    in the function definition) receives the current value of the variable
    length. The items named in the definition of a function are called "formal
    parameters." The definition of the line() function includes one formal
    parameter, length. When you call a function, you must include an actual
    value, such as a constant or a variable, for each formal parameter the
    function requires. Thus, if we use the statement line(10); to call the
    line() function, the value 10 is the "actual parameter" corresponding to
    the formal parameter, length. Inside the line() function, length becomes a
    variable of type int with the value 10.

    Notice that we declare the parameter length as an int in the function
    definition for line(). This declaration serves the same purpose as the
    declaration of an ordinary variable: It tells the compiler what type of
    data the parameter represents. Notice also, however, that unlike the
    declaration of an ordinary variable, which follows the opening brace of
    the function definition body, the declaration of a function parameter
    precedes the opening brace. An alternative syntax, favored by many
    programmers, places the parameter type before the name within the
    parentheses, as in the following:

    void line (int length)

    Note that when a function uses parameters, the parameter should also be
    put in the declaration of the function in or before main(). Thus, in a
    program that uses line(), the declaration would be:

    main()
    {
    void line (length);
    ...
    }

    or:

    void line (int length);

    It's easiest to use the same form for the function declaration and for the
    first line of the function definitionâ”€â”€but remember that the declaration
    ends with a semicolon, whereas the definition does not.

    Once you declare the parameter length, the line() function refers to it as
    though it had been declared and initialized as an ordinary variable. In
    our example, length sets the limit for the loop condition, thus
    controlling the length of the line.

    Parameters make functions versatile. The program now can call line() and
    set the length of the line with any appropriate value: a number, a
    variable name, a #define constant, or an expression.

    By the way, you can call the line() function using a variable with the
    same name as the parameter (length). The variable in the function that
    calls line() belongs to the calling function, and the parameter "belongs"
    to the called function. They are, in effect, separate local variablesâ”€â”€the
    only connection between them is the value.

    Let's look at the ALERT.C program (Listing 6-5), which uses a function
    with a parameter. The beep() function uses a parameter named times to
    control the number of times a beep is sounded. When the function executes,
    the if statement checks to see if times has a value in the range of 1 to
    4. If it doesn't, the program prints an error message. Notice that the
    error message prints the name of the function and the value that length
    passed to it. Including this type of information helps you debug your
    programs.

    If the value of times is in the correct range, a for loop with the limit
    of times generates the correct number of beeps. Try changing the calling
    statement in main() to beep(0) or beep(100).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* alert.c -- sounds alarm by calling a        */
    /*            beep() function with a parameter */

    main()
    {
        void beep(times);  /* function declaration */
        printf("*** Alert! Alert! ***\n");
        beep(3);     /* call beep() with parameter */
    }

    void beep(times)
        int times;   /* declare function parameter */
    {
        int count;

        /* check that parameter is between 1 and 4 */
        if ((times < 1) || (times > 4))
            {
            printf("Error in beep(): %d beeps specified.\n",
                times);
            printf("Specify one to four beeps");
            }
        else /* sound the beeps */
            for (count = 1; count <= times; count++)
                printf("\a");  /* "alert" escape sequence */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-5.  The ALERT.C program.

How Parameters Work

    Now that you know how to use parameters, let's take a detailed look at how
    they work. Figure 6-5 on the following page shows what happens when a
    program calls a function that has a parameter. When it executes the
    function call line(short), QuickC places the value of the variable short
    in an internal memory area called the "stack" and passes control to the
    line() function. The line() function "knows" from its definition that it
    should expect one parameter, called length. It also knows that it is an
    int value. Thus, the function reads two bytes (an int) from the stack and
    creates a temporary storage location for them. This value can now be
    accessed by length within the line() function. It is basically a local,
    automatic variable that behaves as if it had been declared and initialized
    within the function definition.

            Caller
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚  main ( )            â”‚     â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºDiscarded when
    â”‚  int short=10;       â”‚     â”‚          function terminates
    â”‚  {         â”‚â”‚        â”‚     â”‚
    â”‚â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜â””â”€â”€â”€â”€â”€â”€â”€â”â”‚     â”‚
    â”‚â”‚   line (short);    â”œâ”¼â”€â”€â”€â–º10 â”€â”€â”€â”
    â”‚â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜â”‚   â”€â”€â”€â”€   â”‚       Called function
    â”‚    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ â”‚   â”€â”€â”€â”€   â”‚   â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ â”‚   â”€â”€â”€â”€   â”‚   â”‚ void line (length)   â”‚
    â”‚  }                   â”‚   â”€â”€â”€â”€   â””â”€â”€â–ºâ”‚ int length; (=10)    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜  Stack       â”‚ {                    â”‚
                                        â”‚  â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€          â”‚
                                        â”‚  â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€          â”‚
                                        â”‚  â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€          â”‚
                                        â”‚ }                    â”‚
                                        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 6-5. Function parameters and the stack.

    Note that the parameter in a function call is not normally affected by the
    operation of the function. The function operates with a local variable it
    creates, not with the variable in the calling statement.

Multiple User-written Functions

    The TIMER2.C program (Listing 6-6) uses a callable custom function,
    delay(), to improve the timer program we used in Chapter 4. The main()
    function asks the user for the number of seconds to be timed and the
    interval by which the program should count off the time, beeping once at
    each interval. The while loop repeatedly calls delay(interval) to wait for
    interval seconds; then it sounds the beep (by calling the beep() function)
    and prints the elapsed seconds. Be sure you understand the positions and
    components of the function declarations, the function definitions, and the
    parameter declarations for the delay() and beep() functions.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Passing Parameters in Pascal and C
    In Pascal, you can pass either the value of a variable or its address in a
    parameter. (The first is a "call by value," the second is a "call by
    reference.") In C, function parameters are always passed by value: The
    variable itself is never passed. The value can, however, represent the
    address of a variable. In this case the variable itself, and not merely
    the value, can be accessed and changed by the called function. (This is
    called a "pointer," which we discuss in Chapter 8.)
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* timer2.c -- interval timer                */
    /*             calls delay(), uses beep      */

    main()
    {
        /* function declarations */
        void beep (times);
        void delay (seconds);

        /* variable declarations */
        int seconds, interval, tick;

        printf("Set for how many seconds? ");
        scanf("%d", &seconds);
        printf("Interval to show in seconds? ");
        scanf("%d", &interval);
        printf("Press a key to start timing\n");
        getch();

        tick = 0;                /* run "clock" for */
        while (tick < seconds)   /* time specified  */
            {
            delay(interval); /* wait interval seconds */
            tick += interval;
            printf("%d\n", tick);
            beep(1);
            }
        beep(3);
    }

    void delay(seconds)
                    /* wait for number of seconds specified */
                    /* See TIMER.C in chapter 4 for details */
                    /* on the library function time().      */

    int seconds;   /* parameter declaration */
    {
        /* variable declarations */
        long start, end, /* starting and ending times */
                        /* measured in seconds since */
                        /* Jan. 1, 1970 */
            ltime;      /* used to get value from time function */

        start = time(&ltime);  /* get system-elapsed seconds */
                                /* since 1-1-70 */
        end = start + seconds; /* calculate alarm time */

        do
            {;}                       /* null statement for loop body */
        while (time(&ltime) < end);   /* wait for end of time  */
    }

    void beep(times)
        /* parameter declaration */
    int times;
    {
        /* variable declaration  */
        int count;


        /* check that parameter is between 1 and 4 */
        if ((times < 1) || (times > 4))
            {
            printf("Error in beep(): %d beeps specified.\n",
                times);
            printf("Specify one to four beeps\n");
            }
        else /* sound the beeps */
            for (count = 1; count <= times; count++)
                printf("\a");  /* "alert" escape sequence */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-6.  The TIMER2.C program.

    The delay() function has the same code as the TIMER.C program in Chapter
    4, except that it adds the parameter seconds to the current time to
    determine what time should be compared with the system time in the do
    loop. A sample run follows:

    Set for how many seconds? 30
    Interval to show in seconds? 5
    Press a key to start timing
    5â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Beeps after each number
    10
    15
    20
    25
    30

    Putting User Functions in an Include File

    Notice in TIMER2.C that the definition of the beep() function follows that
    of delay(). We've used the beep() function before, and we will use it
    again in several other programs. You would save program space if you put
    the definitions of beep() and related functions (perhaps line(), another
    function that prints characters in reverse video, a function that draws a
    box around a string, and so on) in a header file. Then you could include
    these functions in any program without typing or pasting them in by hand.
    Simply save the definitions in a file that uses the traditional .h
    extension (hilite.h, for example). Then insert the line #include
    "hilite.h" at the beginning of your program. (You can use the existing
    INCLUDE subdirectory, but your file system would be better organized if
    you created a subdirectory called INCLUDE\USER to hold these user-written
    include files.)


Functions with Many Parameters

    Functions can use any number of parameters. The actual parameters
    specified in the function call parentheses are assigned, in order, to the
    corresponding formal parameters in the function definition.

    As a general rule, however, functions that use more than five parameters
    become cumbersome to use. If you must use more than this number,
    reconsider the operations your function performs and try to do the
    operations in two or more simpler functions. After all, one of the chief
    benefits of using functions is that they keep each piece of a program at a
    manageable size. The LINES.C program (Listing 6-7) uses five parameters
    in its line() function, which draws a colored line on the screen. (To run
    this program, you need a CGA, EGA, or Hercules board.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* lines.c -- calls line() with */
    /*            five parameters   */

    #include <graph.h>

    main()
    {
        void line (x1, y1, x2, y2, color);

        int x1, x2, y1, y2, i, color;

        _setvideomode(_MRES16COLOR); /* 320-by-200  16 col. */
        srand(2);                    /* new random seed    */
        for (i = 0; i < 100; i++)
            {
            x1 = rand() % 319;       /* random coordinates */
            x2 = rand() % 319;
            y1 = rand() % 199;
            y2 = rand() % 199;
            color = (rand() % 14) + 1; /* random color 1-15 */
            line(x1, y1, x2, y2, color); /* draw a line   */
            }
        while(!kbhit()); /* wait for key to be hit */

        _setvideomode(_DEFAULTMODE); /* restore video mode */
    }

    void line (x1, y1, x2, y2, color)
    int x1, y1, x2, y2, color;
    {
        _moveto(x1, y1); /* position at first endpoint   */
        _setcolor(color);
        _lineto(x2, y2); /* draw line to second endpoint */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-7.  The LINES.C program.

    The line() function draws a line between the points (x1,y1) and (x2,y2)
    using a specified color. As you learned from PIXELS.C in Chapter 5, you
    must use a system of coordinates to specify pixel locations on the
    graphics screen. This program uses the 320-by-200, 16-color mode, with
    coordinates starting at (0,0) in the upper-left corner of the screen and
    ending with (319,199) in the lower-right corner.

    After the program sets the video mode and initializes the random number
    generator with the QuickC library function srand(2), a for loop executes.
    The body of the loop generates random sets of endpoints for lines. (The
    QuickC random number function rand() generates random integers between 0
    and 32,767. To produce a random number between 0 and a number n, we use
    the expression rand() % n. Because the modulus operator gets the remainder
    by dividing the first number by the second, the result is a number greater
    than or equal to 0 [no remainder] and less than the second number.) A
    similar expression generates a random color between 1 and 15. (We can't
    use color 0 because that is the background colorâ”€â”€a line drawn in that
    color would be invisible.)

    Finally, the program calls line() and passes five parameters: the two
    pairs of endpoint coordinates and the color number. Notice that commas
    must separate the parameters. The line() function draws the line by first
    calling the QuickC graphics function _moveto() to position the cursor at
    the randomly specified point (x1,y1). Another graphics function,
    _setcolor(), sets the current drawing color to the value of color.
    Finally, the QuickC _lineto() function draws the line to the second
    endpoint (x2,y2). The for loop in main() then repeats the process to draw
    100 random lines in random colors.


Functions That Return Information

    Sending values to a function is only one way that information flows
    between a calling program and a function in C. A function can also send
    information to the program. For example, in the expression

    ch = getche()

    getche() returns a value (the character) to the calling statement, which
    in turn assigns the value to the variable ch. To have a function return a
    value to its caller, add a statement to the function definition that
    consists of the keyword return with the value to be returned enclosed in
    parentheses, as follows:

    return (value);

    Replace value with any information you want the function to returnâ”€â”€the
    value of a variable, the result of a calculation, a character the function
    has read, or anything else that can be expressed using one of C's data
    types. When the flow of execution reaches a return statement, the function
    immediately terminates, returning the specified value to the calling
    statement. (A function can have several return statements to return
    different values under different conditions, such as in the branches of an
    if or switch statement. However, the function always terminates at the
    first return statement it encounters.) In the calling statement, the
    returned value replaces the function call, and execution of the statement
    continues.

    Let's look at a very simple example, a function that accepts a quantity in
    yards, converts it to feet, and returns the result:

    int ytof(yards)
        int yards;
        {
        return(yards * 3);
        }

    This function takes the number of yards passed to it through its formal
    parameter yards. The return statement calculates the number of feet with
    the expression yards * 3 and returns the value to the caller. Suppose the
    calling program uses the following statement:

    distance = ytof(course_length);

    and assume that the user supplies a course_length of 750 yards. When the
    statement calls ytof(), it passes the value of course_length to the ytof()
    function. The function returns 2250 (750 * 3), which replaces the function
    call in the statement. The statement now reads:

    distance = 2250;

    and the assignment operator assigns this value to distance.

    Also note that the definition of the ytof() function begins not with the
    type void but rather with the type int. The return type void signifies
    that the function does not return a value. (We also must declare the
    parameter yards to be an int in the definition of ytof().)

    Now let's look at a more useful example. Some languages have a built-in
    exponentiation operator; C does not. However, the math.h include file
    contains a function called pow() that you can call as pow(x,y). It raises
    the first parameter (x) to the power specified in the second parameter
    (y). Because this function uses double values, it can handle both integer
    and floating-point values with great precision. The EXPO.C program
    (Listing 6-8 on the following page) creates an integer version of this
    function that can respond to various types of input.

    The expo() function takes two parameters (the number to be raised to a
    power and the power to raise it to) and returns a value to the calling
    statement. However, part of designing functions that return values is
    deciding how to handle special cases. This program must be able to handle
    three special cases: an exponent less than 0 (negative), an exponent equal
    to 0, and an exponent equal to 1. Thus, we designed EXPO.C to respond to
    valid inputs, special inputs, and error conditions with appropriate
    messages and return values.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* expo.c -- uses exp() function to  */
    /*            calculate powers       */

    main()
    {
        int expo(number, power);
        int number, power;

        printf("Enter a number: ");
        scanf("%d", &number);
        printf("Raise to what power? ");
        scanf("%d", &power);

        printf("Result: %d", expo(number, power));
    }

    int expo(number, power)
    {
        int count, value;
        int total = 1;      /* store value of calculation */
        if (power < 0)      /* reject negative exponents  */
            {
            printf("Error in expo(): negative exponent\n");
            return(0);
            }

        if (power == 0) /* any number to 0 power is 1 */
            return(1);

        if (power == 1) /* any number to 1 power is itself */
            return(number);

        /* calculate for power > 1 */
        for (count = 1; count <= power; count++)
            total *= number;
        return(total);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-8.  The EXPO.C program.

    A negative exponent results in a fraction that is less than 1. For
    example, 2 to the -3 power is the same as:

        1                     1
    â”€â”€â”€ which is equal to â”€â”€â”€ or 0.125
    2^3                    8

    This function handles only positive powers because it uses int type
    variables that can't handle fractions. The first if statement tests the
    power parameter and prints an error message if it is less than zero. The
    return statement returns a value of zero to the calling program, and the
    function terminates.

    Now let's look at the remaining two cases in expo(). If the power
    specified in calling expo() is 0, a return statement returns 1 (any number
    to the zero power is one). If the power specified is 1, expo() returns the
    number itself.

    Finally, a for loop calculates all other cases (positive powers greater
    than 1). Because we initialized total to 1 at the beginning of the
    function, the expression total *= number in the for loop multiplies number
    by itself power times.

    The main() function simply lets you test the expo() function by assigning
    it a number and a power.


Recursion

    Thus far, calling functions and returning values from them has been a
    simple and straightforward matter. However, you can use function calls in
    a way that disturbs these rules slightlyâ”€â”€with amazing results. Recursion
    is an idea that some find difficult to grasp at first, yet a little
    perseverance will lead you to a programming tool of great beauty,
    elegance, and power. Here's how it works: In C, any function can call any
    other function. In fact, a function can call itselfâ”€â”€and that is the
    essence of recursion.

    A classic example of recursion is the calculating of the factorial of a
    number. Recall that the factorial of a number is the product of all the
    integers between 1 and that number, inclusive. For example, the factorial
    of 4 (written by mathematicians as 4!) is 1 * 2 * 3 * 4, or 24.

    A program could calculate a factorial by the "brute force" method, using a
    for loop and multiplying the loop control variable by the previous total.
    But there is another way to calculate factorials. Consider that 4! = 4 * 3
    * 2 * 1, and 3! = 3 * 2 * 1. From this we can deduce that 4! = 4 * 3!, or
    in general terms, that the factorial of a number n is equal to n * (n -
    1)!, which in turn is equivalent to n * (n - 1) * (n - 2)!, and so on.
    Eventually we get to 0!, which, by definition, is equal to 1.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Special Return Values and Error Numbers
    Why return a value if an error occurs? Because the value returned can warn
    the caller that an error has occurred. The warning value selected is a
    value that the function will not return by normal operation. If normal
    operation of the function returns a positive number, a number such as 0 or
    -1 sometimes indicates an error. For functions that don't normally return
    a number, the return value usually indicates something relevant about the
    function's operation: For example, the return value of scanf() is the
    number of data fields read, and a 0 indicates an error. Other functions
    return 0 if their operation was successful; a nonzero return value not
    only indicates an error but also represents an error number that specifies
    the precise problem. As you continue to work with QuickC, you will become
    familiar with how library functions handle errors and what the return
    values mean.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Figure 6-6a depicts the calculation of 4! and then generalizes the
    calculation of a factorial in Figure 6-6b. Note that you keep breaking
    down the expression by subtracting 1 from the current value of n, taking
    its factorial, and multiplying it by the preceding value. Eventually the
    expression becomes equal to n - n, or 0. But 0! = 1, so we no longer need
    to break down n any further. Multiplying all the values together gives the
    factorial of the original number n.

    The RECURSE.C program (Listing 6-9) demonstrates how to use this
    recursive method to calculate factorials.

                    4!
                / \
                4 * 3!
                    / \
                    3 * 2!
                    / \
                    2 * 1!
                        / \
                        1 * 0!
                        â”‚
                        â”‚
                        1
                    4! = 24

    (A)           BREAKING DOWN 4!


                    n!
                /  \
                n * (n-1)!                     â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                /      \           â–’â–’â–’â–’â–’â–’â–’â–’â–ºâ”‚ (n-(n-1) * (n-n)! â”‚
                (n-1) * (n-2)!       â–’        â”‚   = 1 * 0!        â”‚
                        /      \      â–’        â”‚   = 1 * 1 = 1     â”‚
                    (n-2) * (n-3)!  â–’        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                .     â–’
                                .     â–’
                                .     â–’
                            (n-(n-1) * (n-n)!

    (B)                       BREAKING DOWN n!

    Figure 6-6. Breaking down factorial expressions.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* recurse.c -- demonstrates recursion */

    int level = 1; /* recursion level */
    main()
    {
        int num, result;

        printf("Factorial of what number? ");
        scanf("%d", &num);
        result = factorial(num);
        printf("Result is: %d\n", result);
    }

    factorial(int number)
    {
        int result;
        printf("entering: ");
        printf("level %d. number = %d. &number = %d\n",
                level++, number, &number);

        if (number == 0)
            result = 1;
        else
            result = number * factorial(number - 1);

        printf("exiting : ");
        printf("level %d. number = %d. &number = %d. ",
                --level, number, &number);
        printf("result = %d\n", result);

        return(result);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-9.  The RECURSE.C program.

A Recursive Function at Work

    Let's examine how the factorial(number) function in RECURSE.C works. An if
    statement terminates the function and returns 1 if number is 0 (because 0!
    is 1). For any other value of number, the else branch executes

    result = number * factorial(number - 1);

    This is a recursive call because factorial() is actually calling itself.

    Now let's follow execution from start to finish. The main() function makes
    the first call to factorial() with the value of number. Because number
    initially is not 0, factorial() executes the else branch and calls itself
    with number - 1. In this new call, execution again encounters the else
    branch, and another call to factorial() results. Although this call also
    uses number - 1, the number here is actually the value factorial()
    received from its previous call, or number - 2.

    As a result of the repeated calls of factorial() to itself, the decreasing
    values passed with each call accumulate on the stack (because the values
    passed to a function call are not removed from the stack until the call
    terminates). Also, remember that each call to factorial() creates a new
    set of the automatic variables number and result. These variables
    accumulate (one set for each call) until the function terminates. It is as
    though QuickC places a "bookmark" in each function call when the next call
    executes so that the compiler can keep track of what remains to be done in
    each.

    The printf() statements in the program record the above process, as
    follows:

    Factorial of what number? 4
    entering: level 1. number = 4. &number = 8720
    entering: level 2. number = 3. &number = 8706
    entering: level 3. number = 2. &number = 8692
    entering: level 4. number = 1. &number = 8678
    entering: level 5. number = 0. &number = 8664
    exiting : level 5. number = 0. &number = 8664. result = 1
    exiting : level 4. number = 1. &number = 8678. result = 1
    exiting : level 3. number = 2. &number = 8692. result = 2
    exiting : level 2. number = 3. &number = 8706. result = 6
    exiting : level 1. number = 4. &number = 8720. result = 24
    Result is: 24

    Notice the new address for each call's version of the number variable:
    This proves that separate automatic variables are being created. (The
    actual addresses the program returns may vary from setup to setup.)

    The "turning point" in the recursive process occurs when number decreases
    to 0, the call factorial(0) is made, and the if branch finally executes.
    Finally the function returns to the caller (the preceding version of
    factorial()), after assigning the value 1 to result. Now the preceding
    call can "pick up its bookmark" and replace factorial(number - 1) with 1,
    multiply it by the value of number that was saved in its automatic
    variable, and then return this value to its preceding caller. You can see
    this happening in the second half of the output listing: The calls move
    back through the recursion levels, back through the addresses of the
    accumulated automatic variables, with each result being multiplied by the
    preceding one, until the function returns to main() with the correct
    result, 24.

Recursion and Stack Size

    Some problems are naturally recursiveâ”€â”€searching through directories and
    their subdirectories, parsing commands into subcommands, or working with
    tree structures. One thing to keep in mind, however, is that recursion
    uses a lot of memory for storing automatic variables and the stack. (The
    stack holds not only the parameters passed for each call but also the
    register values and return addresses.) Try running RECURSE.C with larger
    input numbers. You can only use numbers to 7 before type int, which stores
    the result, overflows. If you rewrite the program to use long, you can use
    numbers to 16. With type double, you can generate some truly impressive
    factorials, but trying to generate 62! causes a stack overflow error. The
    stack, which by default can store 2048 bytes, simply cannot hold any more
    recursions. (You can specify a larger stack size by selecting Set Runtime
    Options from the Run menu. Still, there is a limit in our medium memory
    model because the stack and the program data share one 64 KB segment. In
    Chapter 11, we also will show you how to use a compiler command-line
    switch to use memory models in which the stack has an entire 64 KB segment
    to itself.)


Noninteger Functions

    The value returned by a function does not have to be an integer type.
    Functions can return a float, a char, or any other standard C data type.
    So far, we have declared and defined functions using a return data type,
    such as:

    int expo(number, power)

    An older style of C programming omits the return type when the function
    returns an int, because the compiler defaults to int if no type is
    specified. We base our style on the new ANSI standard, which encourages
    declaring return types for all functions and using void for functions that
    do not return values. For example, we might define a function that
    calculates the cube root of a number as:

    float cube_root(number)

    This specifies that the cube_root() function returns a value of type
    float. Remember that we also must declare this function in or before
    main():

    main()
        {
        char response;
        int x, y;
        float result;
        float cube_root(number);   /* function declaration */

    The GETYN.C program (Listing 6-10 on the following page) demonstrates the
    declaration and use of a noninteger function. It defines a function,
    getyn(), that prompts for a "yes or no" answer, checks to make sure the
    character entered by the user is either a y or an n, and returns the
    entered character. We declare the function at the start of main() and
    define it as follows:

    char getyn()

    because it returns a value of type char. Notice that this function does
    not use a parameter. Although many functions that return values, such as
    the expo() function, require parameters, some functions receive their
    information not from the calling statement but from some other source. In
    the case of getyn(), and indeed with the standard functions that read
    characters (getch(), getche(), and so on), the user supplies the value.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* getyn.c -- calls char function getyn()    */
    /*               with error checking         */

    #define TRUE 1

    main()
    {
        char ch;
        char getyn();

        printf("Do you want to continue? ");
        if ((ch = getyn()) == 'y')
            printf("Answer was y\n");
        else
            printf("Answer was n\n");
        printf("Value of ch was %c\n", ch);
    }

    char getyn()
    {
        char ch;
        while (TRUE)
            {
            printf(" (y or n) ");
            ch = getche();
            printf("\n");
            if ((ch == 'y') || (ch == 'n'))
            /* valid response, break out of loop */
                break;
            /* give error message and loop again */
            printf("please enter ");
            }
        return(ch);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-10.  The GETYN.C program.

    In the getyn() function, a while loop prompts the user to enter a y or n,
    a getche() gets a character, and an if statement checks to see if the
    character is a y or an n. If it is, a break statement exits the loop, and
    the return statement returns the character. If the character is something
    other than y or n, a prompt asks the user to reenter a value, and then the
    loop repeats. Putting an input-type statement in a loop provides a
    framework for error checking.

    The getyn() function is a handy tool that you can use in place of getch()
    or getche() whenever you want the user to enter a valid response to a
    yes/no question.


Function Prototypes

    We've seen that you can declare the return type for a function at the
    beginning of your program, such as:

    float distance(x1, y1, x2, y2);

    This declaration tells QuickC that your function returns a float value.
    That takes care of the value coming out of the function. But what about
    the values going into the functionâ”€â”€the function parameters?

    As it stands, this definition does not specify a data type for the
    parameters. Consequently, we might design the function to work with
    integer values and then accidentally give it some double values as real
    parameters. If you don't specify the data type of the function parameter,
    QuickC isn't even aware of the potential problem.

    The MIXTYPES.C program (Listing 6-11) shows what can happen when the type
    of data passed to the function does not match the expected type.

    We wrote this program in the older C style: It has no function declaration
    and only the minimum function definition. After all, the examine()
    function merely prints its parameter. (It expects a parameter of the
    default int type, hence the "%d" format specifier in the printf() control
    string.)

    In main() we incorrectly declare the variable n as float and call
    examine() with it.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* mixtypes.c -- shows problem with calling           */
    /*               a function with wrong type parameter */

    main()
    {
        /* didn't bother to declare int function */
        float n = 5.0;
        int i;

        printf("n in main() is %f\n", n);
        i = examine(n);    /* pass float to function */
        printf("examine() returned n as %d\n", i);
    }

    examine(num)  /* function didn't declare return type */
    {
        printf("examine() says n is %d\n", num);
        return(num);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-11.  The MIXTYPES.C program.

    What happens when you run MIXTYPES.C?

    n in main() is 5.000000
    examine() says n is 0
    examine() returned n as 0

    The printf() statement in main() verified a float type. But when we try to
    print the value of this parameter inside examine(), we see that its value
    is now 0. Because we didn't specify a type for the num parameter in
    examine(), the float passed to the function without comment. However,
    because the function expects num to be an int (the default), the float is
    fetched from the stack as if it were an int. (Treating the 4-byte value
    5.0 as a 2-byte int returns two zero bytes, or 0.) Finally, examine()
    returns this incorrect value to main().

    How can we avoid this problem? In Chapter 3, we discussed strategies for
    ensuring sensible type conversions, such as using type casts. Here we need
    to tell QuickC the data type of the function's parameters. You do this by
    providing a complete declaration called a function prototype.

    A function prototype declares the name of the function, its return type,
    the data type of each parameter, and, optionally, the parameter's name.
    Below are some sample declarations:

    int factorial(int number);
    int expo(int number, int power);
    void line(int x1, int y1, int x2, int y2, int color);
    char getyn(void);

    These are all functions we used earlier in this chapter. Although you have
    already used return type declarations, the full ANSI prototypes add an
    additional specificationâ”€â”€the data type for each formal parameter. The
    prototype for factorial() indicates that it returns a value of type int
    and accepts one parameter of type int. The prototype for expo() specifies
    that it returns an int and accepts two int parameters.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Type Checking in Pascal and C
    In the type-mixing situation described above, a Pascal compiler would show
    an error. Pascal checks actual parameter types against the expected
    parameter types and is very strict about making you define types for
    everything. The traditional C philosophy, on the other hand, expects the
    programmer to anticipate problems carefully, so the compiler permits the
    mixing of function parameter types. Thus, because C does not force you to
    declare types for function parameters, it often cannot tell you that
    anything is wrong when the types of the actual and expected parameters
    don't match. If you follow modern C programming practice and define
    function return and parameter types, the compiler will alert you to many
    potential problems.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    The line() function uses a return type of void because it does not return
    a value; it does, however, take five int parameters. Finally, getyn()
    returns a char but has a parameter of void, which signifies that the
    function takes no parameters. In addition, the prototypes specify the
    names of the parameters. (Although the names are optionalâ”€â”€you could say,
    for example, int factorial(int)â”€â”€we recommend using the parameter names in
    the declaration so that all the information is in one place.)

    The beginning of the function definition should also contain the function
    return type, function name, and the list of formal parameters (the
    parameter names), as in the following:

    int factorial(int number)
    int expo(int number, int power)
    void line(int x1, int y1, int x2, int y2, int color)
    char getyn(void)

    You also could declare the parameter types separately on the following
    lines. (Again, the void in parentheses after getyn signifies that the
    function takes no parameters. Also, notice that the function definitions
    do not end with semicolons.)

Advantages of Using Prototypes

    Using prototypes might involve a little more thought and a little more
    typing, but it offers many advantages, which is why the ANSI C standard
    and QuickC support it. First, the complete prototype contains all of the
    information you need to use the function: what you can put in and what you
    can expect to get out. Indeed, if you look up a library function using the
    on-line help, you will find the complete prototype prominently displayed.

    It is important to note that if you use prototypes, QuickC will check both
    the type and number of the parameters in your function calls against the
    type and number of the parameters you specify in the prototype. In cases
    where types are mixed, QuickC will try to promote smaller to larger types.
    (See the examples in Chapter 3.) If you use the wrong number of
    parameters, QuickC will display an error message.

    The PROTO.C program (Listing 6-12 on the following page) is a revision of
    the problem program MIXTYPES.C, rewritten to use function prototypes. This
    program produces more reasonable output than that produced by MIXTYPES.C:

    n in main() is 5.000000
    examine() says n is 5
    examine() returned n as 5

    With the prototype, QuickC knew that examine() needed an int. When the
    program tried to pass it a float, QuickC converted the value to an int
    before passing it to the function. (Some conversions can cause variables
    to lose precision, but the resulting value will be much more likely to be
    acceptable.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* proto.c -- demonstrates function prototyping */
    /*            and parameter checking           */

    main()
    {
        float n = 9995.997;
        int i;
        int examine(int num);  /* declare function */
                                /* with prototype   */

        printf("n in main() is %f\n", n);
        i = examine(n);    /* pass float to function */
        printf("examine() returned n as %d\n", i);
    }

    int examine(num)
    {
        printf("examine() says n is %d\n", num);
        return(num);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-12.  The PROTO.C program.


Putting It All Together: A Larger Program

    To sum up our work with functions and function calls, we present the
    number game GETCLOSE.C (Listing 6-13), which uses 10 functions (counting
    main()). Although this program is much longer than previous programs,
    notice how the use of functions breaks this large, more complex program
    into manageable pieces. Look at the following listing; then we'll see how
    easy to understand this program actually is.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* getclose.c -- a number game using */
    /*               random numbers      */

    #define TRUE 1
    #define FALSE 0

        /* external variables */
        int number,     /* total number in current game   */
            moves,      /* number of moves in current game*/
            target,     /* target number to reach         */
            done,       /* true if game is over           */
            score,      /* score of current game          */
            wins = 0,   /* number of games won            */
            losses = 0, /* number of games lost           */
            total = 0;  /* total score                    */

        char move;
        /* function prototype declarations */
        void intro(void);       /* tell player about game   */
        char getyn(void);       /* get yes/no response      */
        int  random(int num);   /* random between 1 and num */
        void new_target(void);  /* target number for game   */
        char get_move(void);    /* get player's move        */
        void do_move(void);     /* generate num from move   */
        void check_move(void);  /* won, lost, or continue?  */
        void show_score(void);  /* show score for game      */
        void show_total(void);  /* show total score         */
    main()
    {
        intro();         /* print instructions */

        while (TRUE)     /* new games until user quits */
            {
            printf("\nDo you want to continue? ");
            if (getyn() != 'y')
                break;   /* exit program */

            done = FALSE;
            number = moves = score = 0;
            new_target();  /* target number for this game */
            while (!done)  /* play one game */
                {
                get_move();/* user selects random number  */
                do_move(); /* generate random number      */
                            /* and add                     */
                check_move();  /* win, lose, or continue? */
                }
            show_score();  /* score for this game */
            show_total();  /* total score         */
            }
    }

    void intro(void)
    {
        printf("Welcome to Getclose\n\n");
        printf("The object of this game is to\n");
        printf("try to get as close to the target\n");
        printf("number as possible in as few\n");
        printf("moves as possible by choosing from\n");
        printf("various ranges of random numbers.\n");
        printf("You score if you get within 4 of the\n");
        printf("target. You get a 100-point bonus for\n");
        printf("hitting the target, but you get no score\n");
        printf("if you go over.\n\n");
        }
    char getyn(void)
                        /* get yes or no answer      */
                        /* repeats until valid entry */
    {
        char ch;  /* character to read and return */
        while (TRUE)
            {
            printf(" (y or n) ");
            ch = getche();
            printf("\n");
            if ((ch == 'y') || (ch == 'n'))
            /* valid response, break out of loop */
                break;
            /* give error message and loop again */
            printf("please enter ");
            }
        return(ch);
    }

    int random(int num)
        /* generate random number between 1 and num     */
        /* doesn't use library function srand() because */
        /* we don't want the same seed each time        */
    {
        long seconds, result;
        time(&seconds);   /* randomize with system time */
        return(abs ((int)seconds * rand() % num) + 1);
    }

    void new_target(void)
                /* generate a new target number */
                /* between 50 and 99            */
    {
        target = 50 + random(49);
        printf("\nYour target for this game is %d\n",
            target);
    }

    char get_move(void)
    {
        while (TRUE)
            {
            printf("\nPick a random number from 1 to\n");
            printf("a) 5  b) 10  c) 25  d) 50  e) 100 ");
            move = getche();
            if ((move >= 'a') && (move <= 'e'))
                {
                ++moves; /* count the move */
                break;   /* valid response */
                }
            /* invalid response, try again */
            printf("\nPlease type a, b, c, d, or e\n");
            }
    }

    void do_move(void)
    {
        int num = 0;  /* random value to obtain */
        switch (move)
            {
            case 'a' :
                num = random(5);
                break;
            case 'b' :
                num = random(10);
                break;
            case 'c' :
                num = random(25);
                break;
            case 'd' :
                num = random(50);
                break;
            case 'e' :
                num = random(100);
                break;
            }
        number += num;  /* add new number to total */
        printf("\n\nYou got a %d. Number is now: %d ", num, number);
        printf("(Target is %d)\n", target);
    }

    void check_move(void)
    {
        int temp;
        if (number > target)
            {
            printf("\nYou went over! ");
            printf("No score this game.\n");
            losses++;
            done = TRUE; /* to break out of loop */
            }
        if (number == target)
            {
            printf("\nYou hit the target ");
            printf("for 100 bonus points!\n");
            score = (100 / moves) + 100;
            total += score;
            wins++;
            done = TRUE;
            }
        if ((number >= (target - 4)) && (number < target))
            {
            temp = 100 / moves;
            /* does player want to go for broke? */
            printf("\nTake %d points (y) or continue (n)? ",
                temp);
            if (getyn() == 'y')
                {
                score = temp;
                total += score;
                wins++;
                done = TRUE;
                }
            }
    }

    void show_score(void)
    {
        printf("\nYou scored %d points in %d moves.\n",
            score, moves);
    }

    void show_total(void)
    {
        printf("You have won %d game(s) ", wins);
        printf("and lost %d.\n", losses);
        printf("Your total score is %d\n", total);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 6-13.  The GETCLOSE.C program.

Overview of the Game

    GETCLOSE.C is a number game in which you try to reach a randomly generated
    target number between 50 and 99 in as few moves as possible. Each "move"
    consists of choosing one of five possible ranges of random numbers: 1â”€5,
    1â”€10, 1â”€25, 1â”€50, and 1â”€100. You start at zero, and each number you choose
    is added to your total. Thus, each move brings your total closer to the
    target number. If you get within 4 of the target, you can settle for a
    score that depends on the number of moves you've made, or you can continue
    to try to hit the target exactly. If you actually hit the target number,
    you get a 100-point bonus. If you go over, however, you lose and score
    nothing. The program lets you play new games, and it keeps track of your
    total score and the number of games you have won and lost.

    The strategy of the game involves deciding how large a range from which to
    pick the next random number. If you pick from the larger ranges, you can
    reach the target number in only a few moves, gaining you a high score. But
    the big ranges also present you with a greater chance of overshooting the
    target, giving you no points at all. (Playing the game is a little like
    playing blackjack, except that you have five different decks from which to
    choose cards.)

Playing the Game

    Type in the program, run it, and play a few games to get an idea of the
    different operations the program performs. Then read the next section to
    explore the program's inner workings. The following is a sample game:

    Welcome to Getclose

    The object of this game is to
    try to get as close to the target
    number as possible in as few
    moves as possible by choosing from
    various ranges of random numbers.
    You score if you get within 4 of the
    target. You get a 100-point bonus for
    hitting the target, but you get no score
    if you go over.


    Do you want to continue?  (y or n) y

    Your target for this game is 93

    Pick a random number from 1 to
    a) 5  b) 10  c) 25  d) 50  e) 100 e

    You got a 31. Number is now: 31 (Target is 93)

    Pick a random number from 1 to
    a) 5  b) 10  c) 25  d) 50  e) 100 d

    You got a 13. Number is now: 44 (Target is 93)

    Pick a random number from 1 to
    a) 5  b) 10  c) 25  d) 50  e) 100 d

    You got a 19. Number is now: 63 (Target is 93)

    Pick a random number from 1 to
    a) 5  b) 10  c) 25  d) 50  e) 100 d

    You got a 13. Number is now: 76 (Target is 93)

    Pick a random number from 1 to
    a) 5  b) 10  c) 25  d) 50  e) 100 c

    You got a 16. Number is now: 92 (Target is 93)

    Take 20 points (y) or continue (n)?  (y or n) y

    You scored 20 points in 5 moves.
    You have won 1 game(s) and lost 0.
    Your total score is 20

The main() Function

    As you have seen, the main() function of a C program controls the overall
    flow of the program, while calls to various functions do the actual work.
    To explore GETCLOSE.C, look at the structure of main(). Even without
    knowing how the functions work, you can see the general structure of the
    program. First, it calls the intro() function to explain the game briefly.
    (Notice that we commented each of the function prototype declarations in a
    block before main(). This quickly lets you understand the purpose of every
    function.)

    The outer while loop permits unlimited games until the user decides to
    quit. At the start of each game, new_target() generates a new target
    number, and then the inner while loop processes the player's moves until
    the game ends. In this loop, getmove() prints a menu and lets the user
    select a range of random numbers for the next move. The do_move() function
    gets the random number and adds it to the player's current total;
    check_move() then compares the current total and the target number and
    decides if the player has won, lost, or can continue playing.

    Finally, when the inner loop (which represents one game) ends,
    show_score() displays the score of the last game, and show_total()
    displays the total score and the games won and lost thus far.

    You can also use the QuickC Calls menu to help you understand how the
    function calls work. First, compile GETCLOSE.C with Debug selected, and
    then move the cursor to the body of a function you want to examine. Use
    the Debug menu to set a breakpoint there, then run the program. When the
    program stops at the breakpoint, pull down the Calls menu to see a list of
    all called functions. Then display the text of any listed function by
    selecting it. The Calls menu is especially useful for examining programs
    that nest function calls.

Modifying GETCLOSE.C

    One of the best ways to improve your knowledge of C is to take a program
    such as GETCLOSE.C and try to add features to it. You might already have
    some ideas in mind from playing and studying the game. Here are some
    possibilities:

    1.  Give points for how close the player gets to the target number.

    2.  Generate a "poison number" between 1 and the target number minus 10.
        If the player gets within 4 of this number without going over, he or
        she loses.

    3.  Similarly, you could specify a "free number" that, when reached, is
        not counted as a turn, thus potentially increasing the player's score.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€