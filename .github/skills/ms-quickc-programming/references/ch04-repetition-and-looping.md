Chapter 4  Repetition and Looping

    In all of our programs so far, QuickC has executed the program statements
    sequentially, from the first statement to the end of the program. However,
    most of a program's important work involves controlled repetition, in
    which a group of statements repeatedly does a particular job until the
    work is done. For example, consider the data-entry routine of a database
    program. This group of statements (used to receive, validate, and store
    data) must be repeated as long as the user wants to enter new data
    records. This set of repeating statements is called a loop because it is
    executed as though the statements were arranged in a circle. However, when
    the user wants to stop entering data, the program must be able to
    recognize a "quit" command and stop repeating the data-entry statements.

    As you study C, you will find many other examples of the need for
    controlled repetition. For example, a program that retrieves data from a
    file must repeatedly read and process data items until it reaches the end
    of the file. If you program in another language, you probably use loops
    regularly to initialize and access elements of an array or a set of
    variables.

    C uses three types of loops: the for loop, the while loop, and the do
    loop. Although these loops are fundamentally similar, they let you control
    the looping action in different ways to suit different needs. This chapter
    focuses on how to use these three types of loops and some of their common
    variations.


The for Loop

    The for loop repeats a group of program statements as long as a specified
    condition is true. Generally, you use it to specify a fixed number of
    repetitions: for example, processing the accounts for each month of the
    year.

    The anatomy of a for loop is as follows:

    for (start; condition; update)
        {
        statements;
        }

    In this generalized for loop, start is one or more statements that
    initialize the variables used by the loop; condition is a relational
    expression that is tested to see whether the loop should continue to run;
    and update is one or more statements that change the values of variables
    in the loop. The group of statements between the braces that follow the
    for line is called the "body" of the loop. These statements execute as
    long as the condition in the parentheses is true. (The body can also
    consist of only one statement, in which case the braces are optional. We
    tend to use braces for even a single statement, however, because they make
    the body of the loop easier to distinguish.)

    The FORLOOP.C program (Listing 4-1) uses a for loop to count from 1 to
    10. After we declare the variable i, we begin the loop structure with the
    keyword for. The parentheses that follow the for contain the control
    statements for the loop. Note that semicolons separate the control
    statements.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* forloop.c -- a simple for loop that   */
    /*              counts to ten            */

    main()
    {
        int i;
        for (i = 1; i <= 10; i++)
            {
            printf("%d\n", i); /* body of loop */
            }
        printf("All done!\n");  /* executed when i > 10 */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 4-1.  The FORLOOP.C program.

    The start statement establishes the variable i as the loop's control
    variable. This is the variable whose value is tested to determine when the
    loop will stop running. (Many people use i, j, or k for loop control
    variables. This tradition owes its roots to FORTRAN. However, any legal
    name will do.)

    The next statement, i <= 10, is the loop's test, or condition. It
    specifies that the body of the loop execute repeatedly as long as the
    value of i is less than or equal to 10. The test condition is a relational
    statement that compares the loop control variable to an assigned value and
    returns a value of 1 (true) or 0 (false).

    The last statement in the for loop parentheses is i++. This update
    statement changes the value of the loop control variable each time the
    loop body executes. Here we use the ++ increment operator to increase i by
    one each time it executes, and, in fact, most for loops use update
    statements that either increment or decrement the control value by one.
    Using values other than one, however, is almost as easy: The statement
    value += 10, for example, adds 10 to value each time it executes. You can
    also use multiplication or division rather than addition or subtraction.

    Let's step through FORLOOP.C one statement at a time to see how it works:

    â–   Set i to 1.

    â–   Check i to see if it is less than or equal to 10.

    â–   Because the result of this test is true, execute the body of the loop.
        (The body consists of a printf() statement that prints the value of i.)

    â–   Execute the update statement, i++. (Set i to i + 1, or 2.)

    â–   Check the test statement again to see if i is still less than or equal
        to 10. If it is, execute the body of the loop again. Continue the cycle
        until the test condition is false (when the value of i increases to
        11).

    Figure 4-1 on the following page shows this program as a flowchart. You
    can follow the arrows to trace the flow of execution.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Choosing a Control Variable
    If you are used to writing loops in BASIC, remember that with C, you must
    declare the loop control variable before you use it in the loop. Select a
    data type for the control variable that can accommodate the full range of
    values the variable will hold when the loop is run.

    For example, a loop that will run 50,000 times requires a control variable
    of type unsigned int because a signed int value cannot exceed 32,767.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
        â”‚  Initialize    â”‚â—„â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’
        â”‚     i = 1      â”‚                          â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â–’â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
        â””â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”˜                          â”‚Â° for (i = 1; i <= 10; i++Â°
                â”‚                                   â”‚Â°               â–’       â–’ Â°
                â–¼           â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’{â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’       â–’ Â°
                /\          â–’         â–¬  â–¬  â–¬       â”‚Â°     printf("%d\n", i);â–’ Â°
            /    \ â—„â–’â–’â–’â–’â–’â–’â–’      â–¬           â–¬    â”‚Â°     }        â–’        â–’ Â°
            /  TEST  \    No     â–¬               â–¬  â”‚Â°              â–’        â–’ Â°
    â”Œâ”€â”€â”€â–º/  i <= 10   \ â”€â”€â”€â”€â”€â”€â–º â–¬      END      â–¬  â”‚Â°              â–’        â–’ Â°
    â”‚    \     â–¬      /         â–¬               â–¬  â”‚Â°              â–’        â–’ Â°
    â”‚      \ â–¬ ? â–¬  /             â–¬           â–¬    â”‚Â°              â–’        â–’ Â°
    â”‚        \ â–¬  /                  â–¬  â–¬  â–¬       â”‚Â°              â–’        â–’ Â°
    â”‚          \/                                  â”‚Â°              â–’        â–’ Â°
    â”‚          â”‚ Yes                               â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–’â”€â”€â”€â”€â”€â”€â”€â”€â–’â”€â”€
    â”‚  â”Œâ”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”                                          â–’        â–’
    â”‚Do body of loop â”‚                                          â–’        â–’
    â”‚  â”‚  print f...    â”‚â—„â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’        â–’
    â”‚  â””â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”˜                                                   â–’
    â”‚          â”‚                                                            â–’
    â”‚  â”Œâ”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”                                                   â–’
    â”‚  â”‚  Add 1 to i    â”‚â—„â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’
    â”‚  â””â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    â”‚          â”‚
    â””â”€â”€â”€â—„â”€â”€â”€â”€â”€â”€â”˜

    Figure 4-1. The for loop.

    Why does the loop stop running? Let's look at the situation when i = 10:
    The printf() statement in the body of the loop prints the number 10. The
    update statement then increments the loop by 1 and the test statement
    executes. Because the value of i is now 11, the test fails (returns a
    value of "false"). This causes the program to skip the loop body and
    execute the next statement, which prints the message All done!

for Loop Style

    As with other C statements, the statements within the parentheses of a for
    loop can extend to more than one line if necessary. As noted in our
    discussion of conventions, we align the braces vertically for the loop
    body, as shown in FORLOOP.C. An older style aligns the braces as follows:

    for (i = 1; i <= 10; i++) {
        printf("%d\n",i);
    }

    With this style, the braces can get lost in a long listing, making it
    difficult to find where the body of the loop begins and ends. Aligning the
    braces vertically makes them easier to spot and highlights the body of the
    loop.

    Also note that we indent the body of a C loop to the right of the line
    that specifies it. To indent text in the QuickC editor, simply press the
    Tab key. The default indention in QuickC is eight characters, but you can
    change this value at the Options box of the View menu. We use a tab of
    four characters in our listings.

    Pitfalls to Avoid in for Loops

    An easy mistake to make when writing for loops is to put a semicolon after
    the closing parenthesis:

    for (i = 1; i <= 10; i++);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Semicolon added

    This does not cause a compiler error: In C, a semicolon by itself is a
    "null statement." Such a statement does nothing, but it counts as a legal
    statement. Using a semicolon after the parenthesis makes the null
    statement the body of the loop. Adding the semicolon to FORLOOP.C causes
    the loop to do "nothing" 10 times; the program then prints the value of i
    (which is 11 after the loop exits) and All Done!

    Also, always remember to put braces before and after a loop body that
    consists of more than one statement. If you do not use braces, only the
    first statement following the parentheses executes as the body of the
    loop. The remaining statements will execute only once, after the loop
    terminates. (This is another reason for adopting the practice of always
    putting braces around the statements in a loop body, even when the body
    has only one statement.)

Multistatement for Loops

    FORLOOP.C has only one statement in the body of the loop, but most
    programs are much more complex. Let's develop a program that will print a
    table of square roots, squares, and cubes for the integers from 1 through
    9. Because this program must calculate and print three values for each
    number, it needs several statements in the body of the for loop.

    Using QuickC Library Functions

    To write such a program, we need a means of producing the square root of a
    number. Although C does not have operators for calculating squares or
    cubes directly, we can get these values simply by multiplying a variable
    by itself two and three times respectively. To get the square root,
    however, we must call on QuickC's sqrt() function. This function returns
    the square root of any value you pass to it. For example, if i = 4, then
    sqrt(i) = 2.

    The square root function, sqrt(), is an example of a QuickC library
    function (sometimes called a "library routine"). We've already used
    several QuickC "core" functions, such as printf() and scanf(). Because
    these functions are part of the QuickC environment, you can use them
    without any special commands. (Appendix B lists all the built-in core
    functions.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    Sometimes it is convenient to break out of a loop during its execution.
    Perhaps you recognize a problem with its output, or perhaps you find
    yourself in a runaway loopâ”€â”€one whose test will not or cannot fail. To
    break out of a loop, press Ctrl-Break.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    However, sqrt() is not on this list. It is one of many library routines
    that are defined in the header files (often called "include files") of the
    \INCLUDE directory. One of the early tasks in learning QuickC is becoming
    familiar with its external library functions. Fortunately, QuickC makes it
    easy to explore the function library.

    QuickC's extensive on-line help screens let you call up a summary of any
    function to find out whether it is a core function or an external library
    function. To find out about sqrt(), select Topic from the Help menu. Next,
    select the appropriate topic, math; this produces a list of library
    functions that include the sqrt() function. When you select this function,
    a small help window appears at the top of the QuickC screen. (See Figure
    4-2.) The first entry in this window informs you that sqrt() resides in
    both the float.h and math.h include files.

    QuickC also lets you browse through include files while you are working on
    a program. Simply select Include from the View menu, select the \INCLUDE
    directory from the window (if necessary), and then select the include file
    you want to view. When you finish, select Open Last File from the File
    menu, and QuickC returns you to the program you were working on.

    Of course, the preferred reference for all QuickC library functions is the
    Microsoft QuickC Run-Time Library Reference, one of the manuals that come
    with QuickC. It introduces the library functions by category.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 4-2 can be found on p.98 of the printed version of the book.    â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 4-2. Library function help window.

    Using an Include File in a Program

    To use functions or other definitions from an include file in your
    program, you must specify the name of the file you want to call before the
    start of main(). For example:

    #include <graph.h>

    includes the file that contains graphics functions and definitions in your
    program. (The angle brackets that enclose the filename tell QuickC to look
    for the file in the default \INCLUDE directory, whose pathname the setup
    procedure stored in the environmental variable INCLUDE.) This statement is
    actually a "directive" to the QuickC preprocessor, a program that examines
    your C program code and looks for special commands that tell it to make
    changes in the program text before compilation begins. In this case, the
    #include preprocessor directive reads the contents of the specified
    include file into the program and compiles it as though you had typed it
    in. Only after it reads and compiles all the include files does QuickC
    compile your program statements. Note that preprocessor statements such as
    #include are not actually C language statements and do not end with a
    semicolon.

    Creating a Program List

    We have seen that we need to use a #include statement if we want to refer
    to the sqrt() function in the program we want to run, TABLE.C (Listing
    4-2). In addition, before we compile the program, we need to tell QuickC
    where to find the compiled library code that corresponds to the definition
    of sqrt() in the include file math.h. We can do this by creating what is
    called a "program list." To do this, first select Set Program List from
    the File menu. In the dialog window (Figure 4-3 on the following page),
    type in the name of your program followed by the extension .mak. (Thus,
    for TABLE.C you type table.mak.) Next, select Edit Program List from the
    File menu.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* table.c -- prints square root, square, and cube */
    /*            for the numbers 1 thru 9             */

    #include <math.h> /* include math functions so we  */
                        /*  can do square root       */

    main()
    {
        int i;
        printf("i\t sqrt(i)\tsquare(i)\tcube(i)\n\n");
        for (i = 1; i < 10; i++)
            /* beginning of body of loop */
            {
            printf("%d\t", i);
            printf("%f\t", sqrt(i));
            printf("%d\t\t", i * i);
            printf("%d\n", i * i * i);
            }
            /* end of body of loop */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 4-2.  The TABLE.C program.

    The dialog window, shown in Figure 4-4, lists all the C programs in the
    current directory. Select TABLE.C from the window with the mouse or
    keyboard, and then select the Add/Remove button. Finally, select the Save
    button to save the edited program list. You are now ready to run TABLE.C.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 4-3 can be found on p.100 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 4-3. Set Program List dialog window.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 4-4 can be found on p.100 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 4-4. Edit Program List dialog window.

    We use the #include <math.h> statement before the definition of the main()
    function to tell QuickC to use the math.h include file in the program. A
    printf() statement then prints the table header. Because we only want to
    print the header once, we don't place this statement inside the loop!

    Next comes the for loop. The loop specifications establish the test
    condition as i < 10 and the update as increments of 1.

    The body of the loop consists of four printf() statements: The first
    prints the value of i; the next three print, in order, the square root,
    the square, and the cube for each value. The program results in the
    following neatly formatted table:

    i        sqrt(i)        square(i)        cube(i)
    1        1.000000       1                1
    2        1.414214       4                8
    3        1.732051       9                27
    4        2.000000       16               64
    5        2.236068       25               125
    6        2.449490       36               216
    7        2.645751       49               343
    8        2.828427       64               512
    9        3.000000       81               729

Multiple Initializations and Calculations in for Loops

    An almost universal rule in C states that anywhere you can put a single C
    statement, you can put multiple statements. For example, in a for loop,
    you can initialize two variables in the first part of the loop
    specification, as follows:

    for (count = 1, total = 0; count < values; count++)
        {
        total += count;
        }

    Here we initialize the for loop by setting the loop control variable count
    to 1. At the same time, we set the variable total to zero. This loop adds
    all the integers between 1 and the number specified in values. Note that a
    comma separates the two statements in the initialization: Semicolons
    separate the three parts of the loop specification (start or
    initialization, test, and update); however, commas separate multiple
    statements within each part.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    If you want QuickC to search for a file in the current directory instead
    of the default include directory, enclose the filename in quotes: #include
    "graph.h". If you want QuickC to search another directory, specify the
    full pathname: #include "c:\qc\mydefs\defs.h".
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    You can also use multiple calculations in the update portion of the loop
    specification. For example, we can rewrite the above loop as follows:

    for (count = 1, total = 0; count < values;
        total += count, count++)
        {;}

    Here we moved the statement that added each new value of count to total
    out of the loop body and put it in the update part of the loop
    specification. However, a loop must have a body to be legal, so we added a
    single semicolon (a null statement) as the loop body. (The null statement
    is somewhat dangerous because you might accidentally delete the stray
    semicolon. We try to avoid this by indenting the semicolon to the loop
    body position. We also enclose the semicolon in braces. The braces are
    unnecessary, but they help to emphasize the importance of the semicolon in
    the loop structure.)

    The use of multiple statements and null bodies in loops is a matter of
    programming style. Many C programmers try to be as concise as possible, so
    you will often encounter these usages in C code. We present these variants
    to acquaint you with common C programming practices; you gain no
    performance advantage by doing all initializations and calculations within
    the loop specification.

    The INFLATE.C program (Listing 4-3) is another example that uses multiple
    initializations and calculations. At first glance, you might think that
    the braces in the for loop have been forgotten or misplaced.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* inflate.c -- shows multiple initialization */
    /*              and calculations in for loop  */

    main()
    {
        int year;
        float value, rate;
        printf("What do you think the inflation rate will be?");
        scanf("%f", &rate);
        printf("If the dollar is worth 100 cents in 1987\n");
        printf("and the inflation rate is %2.2f, then:\n", rate);

        for (year = 1988, value = 1.0; year <= 1999;
            value *= (1.0 - rate),
            printf("in %d the dollar will be worth", year),
            printf(" %2.0f cents\n", value * 100), ++ year)
            {;}
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 4-3.  The INFLATE.C program.

    The program asks you to estimate the average inflation rate for the next
    decade or so. (We're sure your guess is as good as ours!) If you enter
    .06, the program generates the following:

    What do you think the inflation rate will be? .06
    If the dollar is worth 100 cents in 1987
    and the inflation rate is 0.06, then:
    in 1988 the dollar will be worth 94 cents
    in 1989 the dollar will be worth 88 cents
    in 1990 the dollar will be worth 83 cents
    in 1991 the dollar will be worth 78 cents
    in 1992 the dollar will be worth 73 cents
    in 1993 the dollar will be worth 69 cents
    in 1994 the dollar will be worth 65 cents
    in 1995 the dollar will be worth 61 cents
    in 1996 the dollar will be worth 57 cents
    in 1997 the dollar will be worth 54 cents
    in 1998 the dollar will be worth 51 cents
    in 1999 the dollar will be worth 48 cents

    The program uses scanf() to obtain the estimated inflation rate. Then it
    prints the introduction to the table and enters a for loop. Because the
    table prints yearly values, we call the loop control variable year. (Note,
    by the way, that control variables need not start at 0 or 1.) The
    initialization part of the loop also sets value to 1.0. (In other words,
    the dollar starts at its full value.) The test part of the loop causes the
    printing of values for the years 1988 through 1999.

    The update part of the loop specification does the work of this loopâ”€â”€the
    loop has a null body. Each year the current value is multiplied by 1.0 -
    rate to show the effects of inflation. The arithmetic assignment operator,
    *=, causes this new amount to become the new value. The printf()
    statements print the amount in cents by first multiplying value by 100;
    the format specifier %2.0f rounds it off to whole cents. Finally, ++year
    increments year, and the loop is ready for another pass.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    A for Loop Using Characters
    Because the PC's ASCII character set is merely a set of integer values
    from 0 to 255, a for loop can process characters as easily as it does
    ordinary integers. For example, the int control variable can be
    initialized by setting it to the character value `a'. There is no problem
    with this, because `a' is simply the integer value 97. Then, by specifying
    a loop test condition such as i <= `m', you determine that the body of the
    loop will be repeated 13 times, once for each letter in the first half of
    the alphabet.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Nesting for Loops

    Sometimes it is useful to have one of the statements in the body of a loop
    be another loop. This is called nesting loops. For example, you might
    design a program to read a disk data file that is arranged so that each
    line contains four data fields. An "outer" loop could process each line,
    and an "inner" loop could process each field. The outline for this program
    might be:

    open_file(name);
    for (line = 1; line <= last_line; line++)
        {
        for (field = 1; field <= 4; field++)
            {
            process_field;
            }
        }
    save_file(name);

    The first, or outer, loop uses the control variable line and the test line
    <= last_line to read each line of the file in turn. (In this example, we
    assume that the number of lines in the file has been previously
    determined.) The inner for loop uses the control variable field to step
    through the four fields of each line. The body of this nested loop calls
    the function process_field to do the actual reading of data. When the last
    field in the line is processed, the inner loop exits. Because we are still
    in the body of the outer loop, the outer loop continues by moving to the
    next line; then the inner loop runs again. Only when the inner loop runs
    for the last line do the nested loop structure and the save_file()
    statement execute.

    Our next sample program, GRAPHBOX.C (Listing 4-4 on page 106), uses
    several for loops, including a pair of nested ones, to draw a box on the
    screen using PC graphics characters.

    As we mentioned earlier, the IBM PC uses the ASCII values from 128 to 255
    to represent the "extended character set," which includes many shapes that
    you can use to create effective graphics. To find the appropriate
    characters for drawing a box, select the help screens for ASCII characters
    from the Help menu (or press the F1 key). The second of the two screens
    contains the extended characters. For example, with character number 201
    you can draw the upper-left corner of the box.

    To display these characters, you must use the QuickC core library function
    called putch(). Call the function by specifying the ASCII code of the
    desired character in parentheses. For example, to draw the corner
    character mentioned above, specify:

    putch(201);

    Using #define

    Our box-drawing program uses many different characters to represent the
    corners and sides of the box, plus the newline, return, and blank
    characters. Remembering the ASCII codes for all these characters is a
    difficult task, and relying on memory could lead to coding mistakes. But C
    has a feature that helps eliminate this problem.

    C provides a mechanism for assigning symbolic names to frequently used
    values in a program. The preprocessor directive #define lets you specify a
    name and assign a value to it, as in the following example:

    #define UPLEFT 201

    Before QuickC compiles your program, the preprocessor finds each
    occurrence of the name UPLEFT and replaces it with the number 201. You
    remember the name; QuickC remembers the number. You can also use #define
    with characters. If you use the definition #define color "green" and you
    use the statement printf(color); in your program, the preprocessor
    translates the statement into printf("green"); before QuickC compiles it.

    Always place #define statements before the definition of main(), and do
    not end them with a semicolon. (If you use a semicolon, the preprocessor
    will treat it as part of the value to be substituted. This often leads to
    a bug that causes a compiler error.)

    You can use #define to make your code more readable by substituting
    easy-to-remember names for numbers. For example, you could use NL for the
    newline character instead of 10, the newline ASCII value. Also, #define
    makes it easy to change many values in a program without having to change
    many individual statements.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    #define vs Variables
    You might ask why you should use #define when you could do the same thing
    more easily with ordinary variables. After all, you could declare int nl =
    10; and then use putch(nl); (to simplify punctuation) and thereby avoid
    the preprocessor step. But there are two reasons why this isn't a good
    idea.

    First, using #define produces more efficient code than does using a
    variable. When your program uses variables, QuickC must compile extra
    machine instructions to store, change, or fetch the needed values. With
    #define, on the other hand, the preprocessor compiles the values directly
    into the compiled code: The program doesn't need any extra instructions.
    As a result, your compiled code is faster and more compact.

    Second, a variable should represent a quantity that is subject to change
    by the program. The ASCII value 10 for a newline character, however, is a
    constant. Using #define guarantees that the value you define cannot
    accidentally be changed while the program is running.

    Incidentally, the new ANSI C standard creates the keyword const to let you
    avoid #define directives. Using the new keyword, you might declare const
    int nl = 10; to define the constant nl.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* graphbox.c -- defined to use PC-specific graphics characters */

    #define NL 10
    #define CR 13
    #define BLANK 32
    #define UPLEFT 201
    #define UPRIGHT 187
    #define LOWLEFT 200
    #define LOWRIGHT 188
    #define LINE 205
    #define SIDE 186

    main()
    {
        int i, j, height, width;

        /* get height and width from user */
        printf("How high a box do you want? ");
        scanf("%d", &height);
        printf("How wide do you want it to be? ");
        scanf("%d", &width);

        /* draw top of box */
        putch(UPLEFT);
        for (i = 0; i < (width - 2); i++)
            putch(LINE);
        putch(UPRIGHT);
        putch(NL);
        putch(CR); /* go to next line */

        /* draw sides of box */
        for (i = 0; i < (height - 2); i++)  /* outer loop */
            {
            putch(SIDE); /* left side */
            for (j = 0; j < (width - 2); j++) /* inner loop */
                    {
                    putch(BLANK);
                    }
            putch(SIDE); /* right side */
            putch(NL);
            putch(CR); /* move to next line */
            }

        /* draw bottom of box */
        putch(LOWLEFT);
        for (i = 0; i < (width - 2); i++)
            putch(LINE);
        putch(LOWRIGHT);
        putch(NL);
        putch(CR); /* box is done, move cursor to new line */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 4-4.  The GRAPHBOX.C program.

    To continue with the previous example, if you convert your program to run
    on a mainframe that uses a non-ASCII character set, you need only to
    change the value of NL in the #define statement to reflect the new
    character value throughout the program.

    When you run the GRAPHBOX.C program, it asks:

    How high a box do you want? 8â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Enter height in lines
    How wide do you want it to be? 20â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Enter width in characters

    Figure 4-5 shows the graphics box that this program generates on your
    screen.

    â•”â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•—
    â•‘                   â•‘
    â•‘                   â•‘
    â•‘                   â•‘
    â•‘                   â•‘
    â•‘                   â•‘
    â•‘                   â•‘
    â•‘                   â•‘
    â•šâ•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•

    Figure 4-5. Character graphics box produced by GRAPHBOX.C.

    The program begins with nine #define statements that name the needed
    characters and their values. The first section of main() prompts the user
    for a height and width. Then a putch() displays the character for the
    upper-left corner of the box. Next, a for loop prints a graphics
    double-line character width - 2 times. (We print two less than width
    characters to leave room for the upper-left and upper-right corner
    characters.)

    The third section of main() draws the sides of the box. After subtracting
    the top and bottom lines, we want to print height - 2 lines: This is
    provided for by the test statement in the next for loop. For each line,
    the program prints the SIDE character (the double bar) and then uses a
    nested for loop to print width - 2 blank characters to position the cursor
    at the right side of the box. Another SIDE character completes the line;
    then an NL and a CR move the cursor to the next line.

    The statements that print the bottom line are the same as those that
    printed the top line, except that they use the special characters for the
    lower-left and lower-right corners of the box.


The while Loop

    C contains another loop structure, called the while loop, which takes the
    following general form:

    while (test)
        {
        statements;
        }

    Structurally, the while loop is a for loop with only the test part of the
    specification, its condition, in parentheses. You initialize loop
    variables in a statement before the while, and you update or increment the
    loop with a statement in the loop body. Thus, although the for loop
    features compactness and holds the entire loop specification in the
    parentheses, the while loop is easier to read because the parentheses
    contain only the test expression. The WHILE.C program (Listing 4-5 at the
    bottom of the page) shows a simple example.

    The program produces the following output:

    1
    2
    3
    4
    5
    6
    7
    8
    9
    10
    Done!

    The statement int count = 1; declares and initializes the loop control
    variable. At the while statement, the condition count < 11 is tested.
    Because it is true, the body of the loop executes. The body consists of a
    printf() statement that prints the current value of count, and the
    statement count++; which increments count. The test condition is then
    checked again, and the loop continues printing numbers until count reaches
    11. At this point the test fails, the loop terminates, and the statement
    printf("Done!\n"); executes. Figure 4-6 shows a flowchart of this while
    loop.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* while.c -- a simple while loop */

    main()
    {
        int count = 1;

        while (count < 11)  /* loop condition */
            /* body of loop */
            {
            printf("%d\n", count);
            count++;
            }
        printf("Done!\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 4-5.  The WHILE.C program.

    At this point you might ask why you need while statements if they are
    merely variant forms of for loops. The answer is simple. A for loop is
    designed to work with a specific series of values (such as numbers from 1
    to 10 or 1 to total_lines), and it usually counts up or down. A while
    loop, however, is designed to run indefinitely as long as some condition
    remains true. It also can test many kinds of conditions.

    For example, suppose you want to write a program that draws endlessly
    changing graphic patterns until the user presses a key to stop it. A while
    loop is ideal for this purpose when used with the QuickC library function
    kbhit(), which returns a 1 (true) if a key is pressed and a 0 (false) if
    no key is pressed. (A loop that waits for some external event to take
    place is called a "polling loop.") The main loop of your graphics program
    might appear as follows:

    while (!kbhit())
        {
        draw statements;
        }

    The draw statements create the graphics while the test part of the while
    loop specification polls the keyboard. As long as the user does not press
    a key, the kbhit() function returns a 0, or false. Notice that we use an
    !, which is the "logical not" operator, in front of kbhit(). "Not false"
    is the same as "true," so the test for the while loop is satisfied and the
    body of the loop executes as long as the user doesn't press a key. If you
    find this reverse logic difficult to understand, try translating the loop
    specification into words:

    whileâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€"As long as"
    !â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€"no"
    kbhit()â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€"key is pressed"

        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”                           â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
        â”‚  Initialize    â”‚â—„â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’int count = 1         Â°â”‚
        â”‚   count = 1    â”‚                           â”‚Â°                       Â°â”‚
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜  â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’while (count < 11)    Â°â”‚
                â–¼           â–’                        â”‚Â° {                     Â°â”‚
                /\          â–’         â–¬  â–¬  â–¬       â–’â–’â–’â–’printf("%d\n", count);Â°â”‚
            /    \ â—„â–’â–’â–’â–’â–’â–’â–’      â–¬           â–¬    â–’â”‚Â°                       Â°â”‚
            /  TEST  \    No     â–¬               â–¬  â–’â–’â–’â–’count++;              Â°â”‚
    â”Œâ”€â”€â”€â–º/count < 11  \ â”€â”€â”€â”€â”€â”€â–º â–¬      END      â–¬  â–’â”‚Â° }                     Â°â”‚
    â”‚    \     â–¬      /         â–¬               â–¬  â–’â”‚Â°                       Â°â”‚
    â”‚      \ â–¬ ? â–¬  /             â–¬           â–¬    â–’â”‚Â°                       Â°â”‚
    â”‚        \ â–¬  /                  â–¬  â–¬  â–¬       â–’â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    â”‚          \/                                  â–’
    â”‚          â”‚ Yes                               â–’
    â”‚  â”Œâ”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”                          â–’
    â”‚Do body of loop â”‚                          â–’
    â”‚  â”‚  print f...    â”‚â—„â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’
    â”‚  â”‚  count++;      â”‚
    â”‚  â””â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    â”‚          â”‚
    â””â”€â”€â”€â—„â”€â”€â”€â”€â”€â”€â”˜

    Figure 4-6. The while loop.

    When the user presses a key, kbhit() returns "true," but the logical not
    operator reverses the result into "not true," or 0, and the loop exits.

    Note that a polling while loop needs no counter variable or incrementing.
    The while loop needs only to test a condition that will eventually change.
    (If the condition never changes, the program never stops.)

Using while to Animate a Character

    We can nest while loops much as we nested for loops. The ANIMATE.C program
    (Listing 4-6) uses a set of nested while loops to produce simple
    animationâ”€â”€making a character appear to move back and forth across the
    screen.

    When you run ANIMATE.C, a "double arrow" graphics character (Â» or Â«) and
    the flashing cursor move back and forth across the screen until you press
    a key.

    ANIMATE.C starts with #define statements that specify the right arrow and
    left arrow PC graphics characters as well as the backspace and blank
    characters, which we use for moving the cursor back and for erasing the
    previously drawn arrow.

    The outer loop uses while (!kbhit()), which keeps the program running
    until you press a key. The inner while() loop moves the arrow to the right
    by repeatedly

    1.  displaying the right arrow character,

    2.  backing up the cursor,

    3.  erasing the previously displayed arrow by overprinting it with a blank
        space character, and

    4.  incrementing pos to display an arrow in the next space.

    (Remember, the blank moves the cursor to the space with the displayed
    arrow.) A while loop then tests pos to stop the arrow when it reaches the
    right side of the screen (position 79).

    Notice the two nested while loops that we use to slow the display so the
    eye can follow it. This loop simply counts to 1000. We often use delay
    loops such as this to slow a program to accommodate human perception or
    peripheral devices that cannot keep up with the CPU. (Sophisticated delay
    loops read and use the system clock.)

    Another set of while loops moves the arrow from the right side of the
    screen to the left side. You should have little trouble figuring out how
    it works. Note that the arrow must move backward, so we decrement (rather
    than increment) pos and test for pos > 1 to see when the arrow reaches the
    left side of the screen.

    What happens when the arrow reaches the left side of the screen? The body
    of the outer loop finishes, and control returns to the test statement in
    the outer loop. Assuming no key has been pressed, the body of the loop
    then executes again.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* animate.c -- animates a graphics character */
    /*              until a key is pressed        */

    /* Special characters */
    #define RTARROW 175
    #define LFTARROW 174
    #define BLANK 32
    #define BACKSPACE 8

    main()
    {
        int pos, i, j = 1;
        while (!kbhit())
            {
            pos = 1;
            while (pos < 79)
                {
                putch(RTARROW);
                i = 1;
                while (i < 1000)
                    {
                    j = i + 10;
                    i++;
                    }
                putch(BACKSPACE);
                putch(BLANK);
                pos++;
                }
            while (pos > 1)
                {
                putch(LFTARROW);
                i = 1;
                while (i < 1000)
                    {
                    j = i + 10;
                    i++;
                    }
                putch(BACKSPACE);
                putch(BLANK);
                putch(BACKSPACE);
                putch(BACKSPACE);
                pos--;
                }
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 4-6.  The ANIMATE.C program.

Combining while and for Loops

    The following program, MIXLOOPS.C (Listing 4-7), accepts a character from
    the user and counts through the alphabet until it reaches the character,
    beeping once for each count. The loop continues to accept characters until
    the user enters a blank. (Note: As written, the program works only with
    lowercase alphabetic characters; you can extend it to accept others by
    changing the starting value of the variable i.)

    A session with MIXLOOPS.C might run as follows:

    câ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€User enters character
    In FOR loop!â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Beeps each time line is printed
    In FOR loop!
    In FOR loop!
        â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€User enters blank to end program

    The outer loop, a while loop, contains the test:

    while ((ch = getche()) != ' ')

    This introduces another noncore QuickC library function called getche(),
    which stands for "get character with echo." This function accepts a
    character from the user and echoes (displays) it on the screen. Because
    this function is located in the conio.h include file, you must add the
    appropriate #include line before the definition of main().

    An important feature of this loop is its use of a function call whose
    value is both assigned to a variable and tested in the loop condition.
    We'll learn more about function calls in the next chapter.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* mixloops.c -- reads characters,       */
    /*               beeps for ASCII count,  */
    /*               uses a while and a for  */
    #include <conio.h>

    main()
    {
        char ch;
        int  i;

        while ((ch = getche()) != ' ') /* get a char. */
            {
            for (i = 'a'; i <= ch; ++i) /* count up to alphabet pos.*/
                    {
                    printf("In FOR loop!\n");
                    printf("\a");  /* sound beep each time */
                    }
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 4-7.  The MIXLOOPS.C program.

    When the user enters a character, the assignment ch = getche() assigns the
    ASCII value of the character to the variable ch. The not equals operator
    != then compares the character value to the ASCII value for the blank
    character, specified as '  '. This results in a true or false value that
    the while loop tests.

    If the user does not enter a space, the for loop, which makes up the body
    of the while loop, executes. The for loop tests for i <= ch. Thus, if the
    user enters the character f, the loop counts from the ASCII value of `a'
    to that of `f': The body of the for loop executes one time each for the
    values `a' through `f', and you hear six beeps.

    MIXLOOPS.C is a good example of the appropriate use of while and for
    loops. The outer, while loop waits indefinitely for a condition to change
    (the user enters a space); the inner loop, the for loop, counts to a
    definite value (the ASCII value of the character entered in the while
    loop).


The do Loop

    The third (and final) C looping structure is the do loop, which takes the
    following general form:

    do
        {
        statements;
        }
    while (test);

    The do loop is very similar to the while loop, with one major exceptionâ”€â”€
    the while loop performs the test and then executes the body of the loop;
    the do loop executes the body of the loop and then performs the test.
    Thus, the body of a do loop always executes at least once, even if the
    result of the first test is false.

    The DO.C program (Listing 4-8) demonstrates a simple do loop that
    performs the now-familiar task of counting from 1 to 10.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* do.c -- a simple do-while loop */

    main()
    {
        int i = 1;
        do
            {
            printf("%d\n", i);
            i++;
            }
        while (i < 11);
        printf("Done!\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 4-8.  The DO.C program.

    Of the three C looping structures, the do loop is by far the least used.
    Usually when you test for a change in condition, a while loop is more
    appropriate because you want the program to react immediately to user
    input, especially a "quit" command.

    Use the do loop to repeat an action until some condition changes only when
    the test need not be made immediately. A good example is the TIMER.C
    program (Listing 4-9).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* timer.c -- uses do loop to    */
    /*            check elapsed time */
    #include <time.h>

    main()
    {
        long start, end, /* starting and ending times */
                        /* measured in seconds since */
                        /* Jan. 1, 1970 */
            ltime;      /* used to get val from time function */
        int seconds;     /* elapsed time to be set */

        printf("QuickC Egg Timer\n");
        printf("Enter time to set in seconds: ");
        scanf("%d", &seconds);
        start = time(&ltime);  /* get system elapsed seconds */
                                /* since 1-1-70 */
        end = start + seconds; /* calculate alarm time */

        do
            {;}                       /* null statement for loop body */
        while (time(&ltime) < end);   /* wait for alarm time  */

        printf("Time's Up!\a\a\a\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 4-9.  The TIMER.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    Pascal programmers should note the similarity of C's do and Pascal's
    repeat until loops. The difference is that the C do loop repeats the body
    until the specified condition is false, whereas the Pascal loop repeats
    the body until the condition is true.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    This program lets you specify a time in seconds, after which the program
    beeps three times and prints Time's Up! The program uses the noncore
    library function time(), which, when given the address of a long type
    variable, stores in that variable the number of seconds that have elapsed
    since Jan. 1, 1970, as measured by your PC's clock. As you would expect,
    the function also returns this value for use in the calling statement.

    After the initial messages are printed and the user enters a number, the
    program calls the time() function. Because this function, like scanf(),
    requires an address as its parameter, you must call the function as
    time(&ltime), using the address operator & to specify the address of the
    long variable ltime. The returned value, the elapsed seconds from Jan. 1,
    1970 to the second the user enters a number, is assigned to the variable
    start. We add the number of seconds specified by the user to this variable
    and store the result in the variable end. This variable thus contains the
    number of elapsed seconds at which the program will terminate.

    The do loop then begins. Because this is a timer program and the user
    wants to wait some period of time, the test does not need to be performed
    before the body of the loop executes, so the do loop is appropriate. The
    body of the loop is a null statementâ”€â”€all we want to do is wait. The test
    while (time(&ltime) < end) repeatedly calls the time() function and checks
    the returned value until the elapsed time exceeds the value in end.


Debugging and Loops

    It's rare for a program to work correctly the first time you run it.
    Debugging is the art of knowing what to look for in a program that has
    errors and of correctly interpreting what you see. Some common errors in C
    programs that involve elements we have already discussed include:

    â–   Syntax errors

    â–   Uninitialized variables

    â–   Wrong or incompatible data types

    â–   Incorrectly specified loops

    Throughout this book we point out common programming errors. Syntax errors
    are the easiest to fix: The compiler enforces the rules of C syntax and
    informs you when and where you have erred. (Sometimes, though, you must
    sort out the real problems from the syntax errors that occur as a result
    of an earlier error!)

    True bugs are much harder to detect and fix because they cannot be
    detected by QuickC. We'll define a "logic bug" as an error that does not
    violate the rules of C but generates program results that are either
    completely or partially incorrect. For example, C contains no rule that a
    variable must be initialized. There is no rule preventing you from
    assigning the result of a double calculation to an int variable. And
    loops, with their sometimes complex conditions and specifications, offer
    plenty of opportunity for bugs, such as the problem that arises when you
    use a semicolon after a for loop specification.

    Until recently, debugging a C program was a tedious process that involved
    putting printf() statements in strategic parts of a program to reveal the
    values of key variables or the order in which program statements executed
    (or both). Then came programs called "debuggers" that could run and report
    on a C program. (If you bought QuickC with Microsoft C 5.0, you also
    received CodeView, a sophisticated debugger.) QuickC represents the next
    step in the evolution of debugging: The debugging features are built into
    the QuickC environment itself. (QuickC's debugger only works in the medium
    model.)

    The BUGS.C program (Listing 4-10) is a bug-ridden program that we will
    fix using the QuickC Debug menu and facilities. It features a while loop
    and is supposed to let the user enter as many as five numbers and get
    their total and average.

    Type this program exactly as shown and run it. (If you spot some bugs
    along the way, give yourself a star. But please type the program as shown
    so you can step through the debugging exercise properly.) When you run the
    program, this is what happens:

    Continue (y/n)? yâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Type `y'
    Enter a number:
    Enter a number:
    Enter a number:
    Enter a number:
    Enter a number:

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* bugs.c -- for practice with debugger */

    main()
    {
        char response;
        int number, max_numbers = 5, count = 0, total = 0;
        float average;

        printf("Continue (y/n)? ");
        response = getche();
        while ((response != 'n') && (count < max_numbers))
            printf("\nEnter a number: ");
            scanf("%d", &number);
            total += number;
            printf("Continue (y/n)? ");
            response = getche();
        average = total / count;
        printf("\nTotal is %d\n", total);
        printf("Average is %f\n", average);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 4-10.  The BUGS.C program.

    The program is running out of control. To break out of it and return to
    the QuickC environment, press Ctrl-Break. Now the screen displays the
    following messages:

    Enter a number:
    Enter a number:
    E^C

    run-time error R6014 : (1 of 1)
    - control-BREAK encountered

    Program returned (255).  Press any key

    Press a key to return to QuickC. (You can ignore this error message.)

    Now you need to figure out which bug or bugs caused the program to fail.
    Because the program uses a while loop, it seems likely that something is
    causing one statement of the loop to be repeated endlessly. To debug the
    program, you must first select the Compile menu and then select the Debug
    option. (The Debug menu is shown in Figure 4-7.) This tells QuickC to
    gather debugging information as it compiles the program. Now select Build
    Program from the bottom of the Compile menu to recompile the program with
    debug information. Then go to the Debug menu and select Trace On. (This is
    a toggle settingâ”€â”€select it to turn it on, denoted by a check mark to the
    left of Trace On; select it again to turn it off.) Trace On highlights the
    statement currently being executed (in color if you have a color display).
    This lets you easily follow the flow of the program as it executes.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 4-7 can be found on p.117 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 4-7. The Debug menu.

    Another option in this menu is Screen Swapping. When you turn on Screen
    Swapping, QuickC alternates between the output screen and the QuickC
    environment screen as every statement executes. This causes a flickering
    effect that can be annoying. Even with Screen Swapping off, QuickC shows
    the output screen whenever any statement produces output or requests
    input. We suggest you leave Screen Swapping off. Finally, select Start
    from the Run menu to run the program.

    As the program runs, notice that the statement currently being executed is
    highlighted. (If you have a color monitor, you can change colors by
    selecting Options from the View menu.) The first printf() statement
    executes and is followed by the scanf() statement that solicits a
    response. Type y to continue.

    After that, the program runs away. Notice that the loop specification line
    and the next printf() line execute continually. Do you see why? We didn't
    use braces to mark the beginning and end of the loop body. Therefore, the
    printf() line is executed as the body of the loop. Because this statement
    doesn't get or change values for either of the loop's two control
    variables, response and count, the loop test never becomes false, and the
    loop never terminates. Now you can stop the program (with Ctrl-Break) and
    insert the braces before and after the indented lines.

    This example illustrates how easy it is to use the QuickC debugger. You
    simply turn on the debugging features, observe the problem, and go back to
    the program to fix it. Because everything is done in the same QuickC
    environment, you don't have to save or reload any files.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Controlling the Debugger from the Keyboard
    It is often easier to use keyboard commands rather than menu selections to
    debug a running program. You can use the following QuickC keyboard
    commands while debugging a program:

    Function Key      Result
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    F8                Execute next statement, trace through function
    F10               Execute next statement, trace around function
    F7                Execute until current cursor position is reached
    F4                Display the output screen
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    (When a statement calls a function you have defined elsewhere, F8 traces
    through the definition of the function. F10, on the other hand, does not
    detour to trace a called function.)
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Now run the program again. As the highlight moves on the screen, notice
    that the whole body of the loop executes. That's an improvement. You now
    can run BUGS.C and enter a series of numbers to be totaled and averaged.
    Let's say you enter three numbersâ”€â”€8, 12, and 10. This is what happens:

    Continue (y/n)? y
    Enter a number: 8
    Continue (y/n)? y
    Enter a number: 12
    Continue (y/n)? y
    Enter a number: 10
    Continue (y/n)? n
    run-time error R6003
    - integer divide by 0

    Program returned (255).  Press any key

    Clearly the program still doesn't work right. A look at the listing shows
    that the program is supposed to add each new number to total and, after
    the last number is entered, divide total by count to get average.
    Apparently count is still zero when the loop exits, thus triggering the
    divide by zero error. Why? To find out, let's use another feature of the
    QuickC debugger, "watch variables."

    Move the cursor in the text area to the variable name count. Select the
    Debug menu again, and then select Add Watch. The window shown in Figure
    4-8 appears. The Watch window is a device that lets you designate program
    variables for QuickC to monitor. When the value of one of these variables
    changes, QuickC displays its new value in a window at the top of the
    screen. This eliminates the need to put extra printf() statements in your
    program to monitor variables.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 4-8 can be found on p.119 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 4-8. Adding a watch variable.

    Because you already selected it with the cursor, the word count appears in
    the window. Simply select OK to add count to the list of watch variables.
    (To remove watch variables later, select Delete Last Watch or Delete All
    Watch from the Debug menu.)

    You can also specify another display format for the value of the watch
    variable by adding a comma and a format specifier to the variableâ”€â”€for
    example, count,dâ”€â”€which specifies an integer format display for count. The
    format specifiers are similar to those you used with printf() and scanf().

    Next, select Add Watch twice and add the variables number and total to the
    watch list. (Either position the cursor on the names or type them in the
    dialog box.)

    Finally, let's set a breakpoint. This is a place in the program at which
    execution will stop. This lets you examine the status of the watch
    variables. Move the cursor to the last line in the body of the while
    loopâ”€â”€response = getche();â”€â”€and choose Toggle Breakpoint (or press F9)
    from the Debug Menu. (Select the toggle again with the cursor on the same
    line to remove the breakpoint, or choose Clear All Breakpoints. You can
    set any number of breakpoints.)

    Now you're ready to run the program again, so choose Start from the Run
    menu. Again, the program prompts you for numbers, and you can watch the
    statements in the while loop as they execute. The program stops at the
    breakpoint at the end of the body of the loop. At the top of the screen, a
    small window lists the watch variables and their current values. After you
    inspect them, select Continue from the Run menu (or press F5) to resume
    program execution. (Figure 4-9 shows the screen display with the current
    statement and breakpoint highlighted; the watch variable information
    window is at the top.)

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 4-9 can be found on p.120 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 4-9. Debugging in progress.

    As the loop cycles, notice that number accepts the value of the number you
    entered, and total grows as you add new numbers. But count always remains
    zero. Have you figured out why? We forgot to put a statement in the body
    of the loop that increments count. Adding count++; after total += number;
    completes our debugging of the program.

    You can do more complex things with the debugger, so be sure to read
    Chapter 8 of the Microsoft QuickC Programmer's Guide for more information.
    For example, when you learn about arrays and structures, you can use watch
    variables to display them, too. Meanwhile, you also can use the debugger
    as a learning tool for tracing the flow of programs in this book, the
    sample programs provided by Microsoft, or other C programs.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€