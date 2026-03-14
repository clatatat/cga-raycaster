Chapter 5  Decisions and Branching

    All programming languages must be able to perform controlled "branching."
    Branching uses the result of a test or condition to determine which
    statement (or group of statements) will execute next. In this chapter we
    discuss the variations of branching in C and learn how to use them with
    looping statements.


The if Statement

    In C, as in most languages, the if keyword introduces a branching
    statement. The following structure is the simplest form of branching:

    if (condition)
        statement(s);

    An if statement, like a while loop, evaluates a condition first. The
    condition can be any combination of values and relational or logical
    operators that yields a true (nonzero) or false (zero) valueâ”€â”€answer ==
    `y', for example. If the condition is true, the following statement (or
    group of statements in braces) executes. (As with loops, the statement or
    statements controlled by the condition are called the "body" of the
    statement.) If the condition is false, the following statement or group of
    statements does not execute, and execution continues with the next
    statement or group of statements. A simple example follows:

    if (balance < 0)
        printf("Your account is overdrawn!\n");
    printf("Your current balance is %8.2f\n", balance);

    If the customer's balance is less than zero, the first printf() statement
    executes, telling the customer the account is overdrawn; then the second
    printf() statement, which prints the current balance, executes. If the
    customer's balance is zero or more, the condition is false, and the first
    printf() statement does not executeâ”€â”€the program skips it. Only the second
    printf() statement executes.

    In the above example, we indent the first printf() statement to show that
    the if controls itâ”€â”€it is the body of the if statement. (In C, we indent
    statements for our benefit only: The compiler doesn't require indention.)
    Always enclose the condition in parentheses, and do not use a semicolon
    directly after the parentheses because the complete if statement includes
    the if, the condition, and the statement body.

    The IF.C program (Listing 5-1) features the if statement.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* if.c -- simple IF statement */

    char ch;
    main()
    {
        printf("Do you want to continue y/n? "); /* prompt */
        if (ch = getche() == 'y')
            printf("\nLet's continue ...\n");    /* if true */
        printf("\nAll done.\n");                 /* always executed */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 5-1.  The IF.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    If you know BASIC or Pascal, note that C does not use the then keyword
    before the body of the if statement. Most other languages use the
    following form for the if statement:

    if (condition)
        then statement(s)

    If you mistakenly use then with if, the QuickC compiler will catch the
    error, of course, and you will soon stop making it.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    IF.C asks the user if he or she wants to continue. The test expression ch
    = getche() == `y' gets the response character, assigns it to ch, and tests
    it. The program generates one of two responses:

    Do you want to continue y/n? yâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€User types y
    Let's continue ...
    All done.

    Do you want to continue y/n? nâ”€â”€â”€â”€â”€User types any character other than y
    All done.

    Note that the program prints Let's continue ... only if the user types y;
    however, it always prints All done.

    The if statement represents a fork in the road: One of two possible
    courses is followed, depending on the result of the test. The flowchart in
    Figure 5-1 depicts such a branch, with the test shown in a diamond-shaped
    box.

                                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                            No â”‚                                 â”‚
        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”         /\          â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”    â”Œâ”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”
        â”‚ printf    â”‚       /    \        â”‚ printf    â”‚    â”‚ printf    â”‚
        â”‚ ("Do you  â”‚     /   if   \      â”‚ ("\nLet's â”‚    â”‚ ("\nAll   â”‚
        â”‚ want to   â”œâ”€â”€â–º/ch=getche() \â”€â”€â”€â–ºâ”‚ continue  â”œâ”€â”€â”€â–ºâ”‚ done.\n");â”‚
        â”‚ continue  â”‚   \   =='y')   /    â”‚ ...\n");  â”‚    â”‚           â”‚
        â”‚ y/n");    â”‚     \        /      â”‚           â”‚    â”‚           â”‚
        â”‚           â”‚       \    /        â”‚           â”‚    â”‚           â”‚
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜         \/          â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 5-1. Flowchart for the if statement.

Comparing if and while

    Notice the structural similarity of the following two statements:

    if (score > 90)
        printf("Excellent!");

    and

    while (question <= total_questions)
        ask_question();

    Both statements test a condition and (if the condition is true) execute
    the following statement. The important difference between the two
    constructions is that the if statement executes the body of the statement
    only once; but the while statement executes the body repeatedly (as long
    as the test continues to be true).

    If you think about the two statements, you can see why each is appropriate
    for its assigned task. A statement that prints the final score of a quiz
    needs to be executed only once. On the other hand, a statement that calls
    a function that asks the next question in the quiz must be executed
    repeatedly.

Using a Group of Statements with an if

    The body of an if statement can contain any number of statements. Consider
    the following example:

    if (choice == 'd')
        {
        printf("How much do you want to deposit? ");
        scanf("%f", &deposit);
        balance += deposit;
        printf("Thank you. Your new balance is ");
        printf("%8.2f", balance);
        }

    When choice is `d', the program executes all five statements between the
    braces. Notice that we use the same indention for the braces and the
    statements.

Nested if Statements

    Just as the body of a loop can contain another loop, the body of an if
    statement can contain another if statement. For example, a simple text
    formatter might use the following code fragment:

    if (pos == line_length)
        if (++line_count > lines_page)
            {
            print_footer;
            putch(FF);
            ++page_number;
            print_header;
            }

    If the first if statement is true (the character position equals the line
    length), the program executes the body of the statement, which is itself
    an if statement. This statement increments line_count by one, and if the
    result is greater than lines_page, the body of the inner if statement
    executes. These statements print a footer, output a "form feed" character,
    add one to the page number, and print a header for the next page. (Because
    we must repeatedly test for the end of line and the end of page, we would
    actually place these if statements inside a while loop. As you might
    expect, you will often use if statements inside loops, and we will show
    you examples of these later in this chapter.)

Providing Alternatives with else

    The if statement has an adjunctâ”€â”€elseâ”€â”€that is useful for executing a
    statement or group of statements only if the given condition is false. The
    general form of the if-else statement is simply an extension of the simple
    if statement:

    if (condition)
        statement(s);
    else
        statement(s);

    Consider the following example:

    if (age >= 18)
        {
        printf("To vote, enter number of candidate: ");
        scanf("%d", &candidate);
        }
    else
        printf("Sorry, you must be at least 18 to vote.\n");

    The first group of statements executes only if age is greater than or
    equal to 18. The statement following else executes only if that condition
    is false. If-else statements let you provide appropriate responses for
    both true and false results.

    Note that we align the else with its corresponding if because together
    they form one if statement of two parts. Correspondingly, we also indent
    the statement(s) controlled by the else to match the statements under the
    if.

    The IFELSE.C program (Listing 5-2) uses an if statement with an else to
    simulate the logon sequence for a bulletin board system.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* ifelse.c -- IF with ELSE */

    char ch;
    int num;
    main()
    {
        printf("Are you a new user? y/n? ");
        if (ch = getche() == 'y')
            {
            /* executed if IF is true */
            printf("\n\nYou must register to use this\n");
            printf("bulletin board. Please read\n");
            printf("Bulletin #1 first. Thank You.\n");
            }
        else
            /* executed if IF is false */
            {
            printf("\n\nEnter your secret number: ");
            scanf("d", &num);
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 5-2.  The IFELSE.C program.

    If the user replies y to the question Are you a new user?, the statements
    following the if execute. If the user types n (or anything else), the
    statements following the else execute instead.

    Here is a sample dialogue:

    Are you a new user? y/n? y

    You must register to use this
    bulletin board. Please read
    Bulletin #1 first. Thank You.

    Are you a new user? y/n? n

    Enter your secret number: 31415

Matching an else to an if

    As you write more advanced programs, you will need to use more complex if
    statements, such as:

    if (temp < 900)
        if (temp > 750)
            printf("Warning! Boiler overheating!\n");
    else
        printf("Start emergency shutdown!\n");

    This program is meant to check the temperature and print a warning if the
    temperature is between 750 degrees and 900 degrees, or print an emergency
    warning if the temperature is greater than 900 degrees. It might look
    correct, but it's not.

    When this if statement actually executes, it prints nothing if the
    temperature exceeds 900, and it prints the emergency warning if the
    temperature is less than 750! We actually want the else to go with the
    outer if to print the emergency warning only if the temperature exceeds
    900. However, although we physically aligned the else so that it appears
    to go with the outer if, the compiler reads the statement differently. It
    considers the else to belong to the inner (nested) if.

    Always remember that QuickC matches a given else with the preceding
    unenclosed if that doesn't already have an else. Now that we understand
    this rule, we can fix the program by enclosing the inner if in braces so
    that the else is not attached to it:

    if (temp < 900)
        {
        if (temp > 750)
            printf("Warning! Boiler overheating!\n");
        }
    else
        printf("Start emergency shutdown!\n");


The Conditional Assignment Statement ?

    Compared to BASIC or even Pascal, C might seem to be a sparse language
    that provides the essential tools for programming but few frills. However,
    we've already seen several elements (such as the special increment and
    decrement operators) by which C provides "shorthand" expressions to
    simplify commonly encountered programming chores. Another such common
    programming task is assigning one of two values to a variable, depending
    on the result of a test. For example, suppose we want to set the variable
    max to the larger of the values of the variables n1 and n2. Of course, we
    can use an if and else, as follows:

    if (n1 > n2)
        max = n1;
    else
        max = n2;

    But we can also use C's conditional assignment statement to do the jobâ”€â”€
    and in one line of code. The general form for the conditional assignment
    statement is:

    variable = (expression) ? value1 : value2;

    QuickC evaluates the expression in parentheses first. In this form of
    assignment statement, if the expression is true (nonzero), value1 is
    assigned to variable; if the expression is false (zero), value2 is
    assigned to variable. Note that a question mark follows (expression) and a
    colon (:) separates the two values.

    We can now rewrite our earlier statement for assigning a value to max as
    follows:

    max = (n1 > n2) ? nl : n2;
        â”‚        â”‚        â”‚    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Assign if false
        â”‚        â”‚        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Assign if true
        â”‚        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Expression to test
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Variable to receive value

    This translates as "If n1 > n2, then assign the value of n1 to max;
    otherwise, assign the value of n2 to max." Although this statement might
    look odd, it's easy to use and quite handy.

Assigning Truth Values

    If the two possible values for a variable are actually "true" and "false,"
    you don't need to use the conditional assignment statement. Simply assign
    the result of the expression to the variable. For example,

    frozen = (temp <= 32)

    sets the value of frozen to true (nonzero) if the temperature is less than
    or equal to 32 and sets it to false otherwise.

    The SHORTIF.C program (Listing 5-3 on the following page) illustrates
    some shorthand and conditional assignments.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* shortif.c -- shows 'shorthand' IF / ELSE   */
    /*           -- gets absolute value of number */

    main()
    {
        int num, pos, abs;
        printf("Enter a whole number: ");
        scanf("%d", &num);

        pos = (num >= 0); /* is number positive? */

        abs = (pos) ? num : -num;  /* assigns negative of */
                        /* number if number is negative */
        if (pos)
            printf ("The number is positive.\n");
        else
            printf("The number is negative.\n");
        printf("Absolute value of number is: %d\n", abs);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 5-3.  The SHORTIF.C program.

    First, the program gets a number from the user. Then it tests the number
    to see if it is positive. Notice we do this by assigning the result of the
    expression (num >= 0) to the variable pos. This value now contains "true"
    if the number is positive, or "false" if it is not. (Remember that these
    are actually numeric values, 1 and 0, that have the logical effects of
    "true" and "false" when used in tests.)

    Next, the program uses a conditional assignment statement to calculate the
    absolute value of the number. (The absolute value of a number is its value
    disregarding its sign. Thus, both 5 and -5 have an absolute value of 5.)
    Recall that a conditional assignment statement assigns one of two values
    to a variable based on the truth result of an expression. However, you can
    also use a single variable that has a truth value instead of an
    expression. Because the variable pos was assigned a truth value earlier,
    we can use it here as the test for the conditional assignment.

    Now let's look at the assignment statement and the if-else branches. If
    the entered number (num) is positive, pos contains "true," and the
    statement assigns num to the absolute value abs. In other words, the
    absolute value of a positive number is simply the number itself.

    If num is negative, however, then pos contains "false," and the statement
    assigns the second value, -num, to abs. The negative of a negative number
    is a positive number and, therefore, the absolute value. The examples on
    the following page demonstrate the output when the program is run twiceâ”€â”€
    first with a positive number and then with a negative number.

    Enter a whole number: 23
    The number is positive.
    Absolute value of number is: 23
    Enter a whole number: -58
    The number is negative.
    Absolute value of number is: 58


Multipath Branching

    Thus far, we've discussed simple branches (the single if) and two-way
    branches (the if and else). Simple branches are most useful for testing a
    condition that can have only one of two valuesâ”€â”€typically "true" and
    "false." But what about those situations in which you must test for one of
    several values? This commonly occurs in a menu from which a user must
    choose one of several items.

    Consider, for example, a program that offers the user a choice of readings
    from a home weather station. Let's say the user can choose among
    temperature, humidity, pressure, and wind velocity. Here's one way we
    could set up the menu:

    printf("Enter reading wanted: t = temp  h = humidity\n");
    printf("p = pressure  w = wind velocity ");
    ch = getche();
    if (ch == 't')
        printf("Current temperature is %5.2\n", temp)
    else
        if (ch == 'h')
            printf("Humidity is %4.2f\n", humidity);
        else
            if (ch == 'p')
                printf("Air pressure is %5.2f\n", pressure);
            else
                if (ch == 'w')
                    printf("Wind velocity is %d\n", wind);
                else
                    {/* default */
                    printf("Invalid choice. Choose ");
                    printf(" t, h, p, or w.\n");
                    }

    This chain of if statements, each hooked to the preceding statement's
    else, will work, but it has many disadvantages. Its many levels of nesting
    are difficult to read. Also, the many indentions run the code off the edge
    of the screen, requiring awkward line breaks.

    This type of code also creates a conceptual problem. The structure of
    these statements suggests that each if statement is dependent on all of
    the preceding if statements. This suggests that we are checking for some
    kind of special case that is true only if all the ifs in the series are
    true. But nothing is further from the truthâ”€â”€we merely want to compare ch
    to four possible values and provide a branch for each value. (We also need
    a default branch to handle invalid user-entry values.)

    We can improve the visual organization of our branches in the following
    manner:

    if (ch == 't')
        printf("Current temperature is %5.2\n", temp)
    else if (ch == 'h')
        printf("Humidity is %4.2f\n", humidity);
    else if (ch == 'p')
        printf("Air pressure is %5.2f\n", pressure);
    else if (ch == 'w')
        printf("Wind velocity is %d\n", wind);
    else { /* default */
            printf("Invalid choice. Choose ");
            printf("t, h, p, or w.\n");
            }

    This arrangement is clearer and more compact. All of the branches now have
    the same level of indention, showing that they are co-equal and not
    dependent on each other. However, it is important to note that else if is
    not a distinct command: Changing indention doesn't change the way the
    compiler handles this code.


The switch Statement

    C offers a special switch statement that makes writing multiple branches
    much easier. The general form of switch follows:

    switch (variable)
        {
        case 'constant1':
            statement(s);
            break;
        case 'constant2':
            statement(s);
            break;
        case 'constant_n':
            statement(s);
            break;
        default:
            statement(s);
        }

    Specify the name of the variable to be tested in parentheses after the
    word switch. As with the other loops and branches, don't use a semicolon
    at the end of the first line: The entire structure comprises one
    statement.

    The body of the switch statement (enclosed in braces) is a list of
    possible branches. Each branch consists of the word case followed by a
    constant value (a number or character) in parentheses. During execution,
    this constant is compared with the switch variable: If they are equal, the
    statements for that case execute. Note that single quotes enclose each
    constant, and the line ends in a colon.

    One or more statements follow each case line. (Do not enclose a group of
    statements in bracesâ”€â”€the compiler handles all statements under a given
    case as a single unit.) The last statement in each branch is the keyword
    break. The break statement immediately ends execution of the switch
    statement; program execution resumes at the statement that follows the
    body of the switch statement. Usually you will conclude each case in a
    switch statement with the keyword break. If a switch statement behaves
    erratically, look for missing break statements in the individual cases.
    Also, include a default: to handle invalid values.

    Sometimes, however, you will want to execute a set of statements if the
    switch variable has any one of several values. You can do this by placing
    the set of statements after a series of switch values, as in the
    following:

    switch (ch)
        {
        case 'q':
        case 'Q':
            show_score();
            end_game();
            break;
        case ...
        }

    No statement is associated with 'q', so execution falls through to the
    code for 'Q', the show_score() and end_game() functions execute, and break
    is encountered.

    A switch statement can contain any number of branches, which is why the
    last branch in our format description uses the notation constant_n. A
    special case, default:, is an optional branch that is usually placed after
    the last explicit case in the switch statement. It specifies the branch
    that executes if none of the conditions for the other cases match the
    value of variable. Although default: is optional, programmers frequently
    use it to respond to erroneous values, such as an invalid choice.

    Let's use the switch statement to rewrite our weather station menu:

    switch (ch)
        {
        case 't':
            printf("Current temperature is %5.2\n", temp)
            break;
        case 'h':
            printf("Humidity is %4.2f\n", humidity);
            break;
        case 'p':
            printf("Air pressure is %5.2f\n", pressure);
            break;
        case 'w':
            printf("Wind velocity is %d\n", wind);
            break;
        default:
            printf("Invalid choice. Choose ");
            printf("t, h, p, or w.\n");
        }

    Figure 5-2 on the following page illustrates this switch statement. The
    multiple branches suggest tracks in a railroad switching yard, the
    probable origin of the name.

                                                â”Œâ”€â”€â”€â”€â”€â”€â”€â”    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”‚  't'  â”‚â”€â”€â”€â–ºâ”‚printf... â”‚
                                â”‚            â”‚       â”‚    â”‚break;    â”‚
                                â”‚            â””â”€â”€â”€â”€â”€â”€â”€â”˜    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                â”‚            â”Œâ”€â”€â”€â”€â”€â”€â”€â”    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                                â”‚    â”Œâ”€â”€â”€â”€â”€â”€â–ºâ”‚  'h'  â”‚â”€â”€â”€â–ºâ”‚printf... â”‚
                                â”‚    â”‚       â”‚       â”‚    â”‚break;    â”‚
            Value of   â–¬  â–¬ â”€â”€â”€â”€â”€â”€â”˜    â”‚       â””â”€â”€â”€â”€â”€â”€â”€â”˜    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”       â–¬ â”€â”€â”€â”€â”€â”€â”€â”€â”˜       â”Œâ”€â”€â”€â”€â”€â”€â”€â”    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
            â”‚        â”‚    â”‚     â–¬ â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”‚  'p'  â”‚â”€â”€â”€â–ºâ”‚printf... â”‚
    switch â”‚ ( ch ) â”‚    *     â–¬               â”‚       â”‚    â”‚break;    â”‚
            â”‚        â”‚          â–¬               â””â”€â”€â”€â”€â”€â”€â”€â”˜    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”˜        â–¬ â”€â”€â”€â”€â”€â”€â”€â”€â”       â”Œâ”€â”€â”€â”€â”€â”€â”€â”    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                        â–¬  â–¬ â”€â”€â”€â”€â”€â”€â”    â””â”€â”€â”€â”€â”€â”€â–ºâ”‚  'w'  â”‚â”€â”€â”€â–ºâ”‚printf... â”‚
                                â”‚            â”‚       â”‚    â”‚break;    â”‚
                                â”‚            â””â”€â”€â”€â”€â”€â”€â”€â”˜    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                â”‚            â”Œâ”€â”€â”€â”€â”€â”€â”€â”    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”‚defaultâ”‚â”€â”€â”€â–ºâ”‚printf... â”‚
                                                â”‚       â”‚    â”‚break;    â”‚
                                                â””â”€â”€â”€â”€â”€â”€â”€â”˜    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 5-2. The switch statement.


The break Statement

    The break statement has other uses than as the last statement in each case
    of a switch statement. A break statement can also be used with the three
    looping statements: (for, while, and do). In all cases, however, break has
    the same effectâ”€â”€it immediately "breaks out of" the enclosing structure
    and causes execution to resume after the end of the switch or loop
    structure. The BREAK.C program (Listing 5-4) uses break to exit from a
    while loop:

    This program uses the rand() library function to generate a series of
    random numbers. On each pass through the while loop, the program generates
    and displays one random number in the range 0 through 32,767. The
    statement

    if (number < 32000)
        break;

    terminates the while loop if the program generates a random number greater
    than 32,000. The output might look something like the following:

    41
    18467
    28145
    16827
    491
    2995
    11942
    5436
    32391
    Broken out of WHILE loop.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* break.c -- shows how to get out of loop with BREAK */

    #include <stdio.h>
    #define TRUE 1

    main()
    {
        int number;
        while (TRUE) /* endless loop */
            {
            /* get a random number between 0 and 32767 */
            number = rand();
            printf("%d\n", number);

            /* break out of loop if random number */
            /* is greater than 32000              */
            if (number > 32000)
                break; /* exit WHILE loop */
            }
        printf("Broken out of WHILE loop.\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 5-4.  The BREAK.C program.

    The last value, 32391, triggered the break statement. The while loop
    terminates, and the printf() statement following the body of the while
    loop executes.

    The SWITCH.C program (Listing 5-5 on the following page) shows you how to
    create a simple menu using a while loop containing a switch statement. The
    program asks the user to select one of four math routines (octal
    representation, hex representation, square, or square root), prompts for a
    number to be converted, and prints the result. The user types q to exit
    the program.

    Following is a sample dialogue with SWITCH.C:

    Select a math routine:
    o = octal  h = hex   s = square
    r = square root  q = quit: o
    Enter a whole number: 30
    Result: 36

    Select a math routine:
    o = octal  h = hex   s = square
    r = square root  q = quit: r
    Enter a whole number: 10
    Result: 3.162278

    Select a math routine:
    o = octal  h = hex   s = square
    r = square root  q = quit: q

    Program returned (113).  Press any key

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* switch.c -- demonstrates switch statement */
    /*             prints values according       */
    /*             to user's choice              */
    #include <math.h> /* for sqrt() */
    #define TRUE 1
    main()
    {
        char choice;   /* routine wanted by user   */
        int number;    /* number entered by user   */

        while (TRUE)   /* endless loop */
        {
            printf("\nSelect a math routine:\n");
            printf("o = octal  h = hex   s = square\n");
            printf("r = square root  q = quit: ");
            choice = getche(); printf("\n");

            if (choice == 'q')
                break; /* exits WHILE loop; ends program */

            /* rest of program executed if choice <> 'q' */
                printf("Enter a whole number: ");
                scanf("%d", &number);

            switch (choice) /* print according to */
                            /* choice requested   */
                {
                case 'o':   /* print octal */
                    printf("Result: %o\n", number);
                    break;  /* break here in each case    */
                            /* exits the switch statement */

                case 'h':   /* print hex */
                    printf("Result: %x\n", number);
                    break;

                case 's':   /* square */
                    printf("Result: %d\n", number * number);
                    break;

                case 'r':   /* square root */
                    printf("Result: %f\n", sqrt(number));
                    break;

                default:
                    printf("Choice must be o, h, s, r, or q\n");
                }
        }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 5-5.  The SWITCH.C program.

    We enclose the menu in an endless while loop because the user will be
    making choices indefinitely. Notice that we use while (TRUE) instead of
    while (1). Both have the same effect, but the code is clearer when we use
    a #define statement to make TRUE equal to 1 and use the descriptive name
    in the program.

    After the program displays the menu and getche() gets the user's choice,
    an if with a break statement tests for the possibility that the user wants
    to quit. If the user quits, the while loop terminates and the program
    ends.

    If the user did not enter q, the program obtains the number to be
    processed. A switch statement then processes the number. The constants in
    the various cases correspond to the menu options so the switch statement
    can match the user's choice with the appropriate case. If the choice is
    `o' or `h', a format specifier returns the appropriate value; if the
    choice is `s' or `r', the value is calculated.

    The default: case handles any value not specified in the menu by printing
    a list of valid values. Note that the default: case needs no break because
    there are no further statements in the switch statement that can be
    executed.

switch vs if-else

    Using switch gives you a structure that is at least as clear as the series
    of else ifs shown earlier, because each case is clearly distinct. The
    switch has the additional advantage that the variable to be compared is
    stated clearly once, at the beginning of the structure, rather than being
    buried inside the individual tests.

    Whether you decide to use switch or the if-else form is a matter of style.
    A good rule of thumb is to use switch whenever four or more possible
    values (including a default) are involved. Some programmers argue that
    switch is clearer for even three possible branches.

    There is, however, one situation in which you cannot use switchâ”€â”€even when
    many branches must be used. A switch statement can be used only to test
    simple constant values. You cannot, for example, do the following:

    switch (expenditure)
        {
        case < 10.00:â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Expression is illegal for switch
            printf("petty cash");
            break;
        case < 100.00:
            printf("see office manager");
            break;
        case < 500.00:
            printf("see district manager");
            break;
        default:
            printf("see head office");
        }

    Unlike many versions of the Pascal case statement and similar structures
    in other languages, the C switch statement cannot compare a value against
    ranges of values. It also cannot be used with relational expressions. For
    these programming tasks, you must use multiple if-else structures.


The continue Statement

    Under some conditions we might need to skip some of the statements in the
    body of a loop and return to the loop's test condition. For example, if a
    program offers a menu operation that has potentially irrevocable
    consequences (such as overwriting the contents of a file), you might want
    to ask Do you really want to overwrite this file? If the user answers no,
    the program must skip the remaining statements and return to the menu. The
    continue statement lets you do this.

    A continue statement takes the following general form. We illustrate it
    here with a while loop, although you can use it in any kind of loop (but
    not a switch).

    while (condition)
        {
        some statements;
        if (condition)
            continue;
        rest of statements;
        }

    The if statement tests a condition as usual: If its condition is true, the
    continue executes. This restarts the loop before the rest of the
    statements in the body of the loop execute, and the while loop condition
    is tested again.

    The CONTINUE.C program (Listing 5-6) uses a simple example of a continue
    statement. The program also illustrates a "toggle switch" variable, sw. A
    toggle switch changes to the opposite of its current value each time you
    use it. If it's "on," the next time you use it you turn it off.

    The body of the endless while loop first prints out the current status of
    the sw switch. Next, the program uses a break statement to give the user
    an opportunity to quit. The program then asks the user whether the switch
    should be toggled. If the answer is not `y,' a continue statement skips
    the last statement in the loop body and the switch is not toggled. If the
    answer is `y,' the continue doesn't execute, and the last statement sw =
    !sw toggles the switch. (Recall that the ! operator reverses the truth
    value of the associated variable.)

    The next program, M.C (Listing 5-7), demonstrates various combinations of
    for loops and if statements and includes a continue statement. The program
    draws a letter M within the dimensions specified in the #define statements
    at the beginning of the program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* continue.c -- shows CONTINUE in a loop */
    main()
    {
        int sw = 0;
        char ch;
        while (1) /* endless loop */
        {
            /* print current status */
            if (sw)
                printf("\nSwitch is ON\n");
            else
                printf("\nSwitch is OFF\n");

            printf("Do you want to quit? ");
            if (ch = getche() == 'y')
                break;    /* exit loop on yes */

            printf("\nDo you want to toggle the switch? ");
            if (ch = getche() != 'y')
                continue; /* restart loop on no */

            sw = !sw;     /* toggle switch */
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 5-6.  The CONTINUE.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* m.c -- draws a letter M        */
    /*        using IF and CONTINUE  */

    /* define characters */
    #define CH 'M'    /* character to "draw" with */
    #define BLANK ' '
    #define NL 10
    #define CR 13
    #define LEFT 20   /* left side of M   */
    #define RIGHT 46  /* right side of M  */
    #define BOTTOM 22 /* last line to use */
    main()
    {
        int pos, line;
        /* space to left side */
        for (line = 1; line <= BOTTOM; line++)
            {
            for (pos = 1; pos < LEFT; pos++)
                {
                putch(BLANK);
                }
            putch(CH); /* draw left side */
            /* are we past midpoint? */
            if (line > ((RIGHT - LEFT) / 2))
                {
                /* yes, so just draw right side */
                for (pos = LEFT; pos < RIGHT; pos++)
                    {
                    putch(BLANK);
                    }
                putch(CH);
                putch(NL);
                putch(CR);
                continue; /* start loop over, do next line */
                }
                /* not past midpoint, check for interior */
            for (pos = LEFT; pos < RIGHT; pos++)
                {
                if ((pos == (LEFT + line)) ||
                    (pos == (RIGHT - line)))
                    putch(CH);
                else
                    putch(BLANK);
                }
            putch(CH);
            putch(NL);
            putch(CR); /* could also use printf("\n"); */
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 5-7.  The M.C program.

    The M.C program generates the following output:

    M M                       MM
    M  M                     M M
    M   M                   M  M
    M    M                 M   M
    M     M               M    M
    M      M             M     M
    M       M           M      M
    M        M         M       M
    M         M       M        M
    M          M     M         M
    M           M   M          M
    M            M M           M
    M             M            M
    M                          M
    M                          M
    M                          M
    M                          M
    M                          M
    M                          M
    M                          M
    M                          M
    M                          M

    Drawing the letter M involves drawing two distinct sectionsâ”€â”€the V-shaped
    inner part and the straight-sided outer part. The overall control for
    drawing all the individual lines resides in the outermost for loop. Each
    line is started by a small for loop that moves to the left side of the M
    and draws the character "M" there.

    What happens next depends on whether the current line number is in the top
    or bottom part of the M. We determine this by testing to see if the
    distance down the screen in lines is greater than half the distance across
    the M in characters. (This test is arbitrary. Feel free to try other
    formulas and to vary the size of the M by changing the #define
    directives.)

    If we are not below the bottom of the V part of the M, the for statement
    in the body of the if moves to the right side, which is then drawn. The
    continue (which doesn't require an if here) then skips the rest of the
    statements, which aren't needed.

    If the if statement is false, we are still in the upper portion of the M:
    The body of the if is skipped, and the rest of the statements in the body
    of the outer loop execute. The if statement works on the principle that
    the inner lines of the M are drawn one space further to the right and to
    the left from the sides of the M for each line further down the screen.
    Thus, the appropriate positioning for the inner lines is found by adding
    and subtracting the current line number.


The goto Statement

    C's goto statement transfers control to the line containing the specified
    label. For example, you might use goto with an if statement, as follows:

    printf("Do you want to continue? \n");
    if (ch = getche() == 'y')
        goto yes;
    printf("Goodbye\n")
        goto end;
    yes: printf("Let's continue ...\n");
    end:

    Here, if the user enters y, the goto immediately causes execution to skip
    to the printf() statement that follows the label yes: (which must end with
    a colon). If the user does not enter y, the second goto skips the "yes"
    branch.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    The Appropriate Use of continue
    The continue statement is rarely used in C programs. Often (in Microsoft
    C, for example), continue's function is handled by an else branch for the
    relevant if statement or by a new if statement. However, if you have a
    complicated, multiple-nested set of if-else statements, using a continue
    statement might simplify things.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    If this looks confusing, that's because it is. You can do the operation
    much more clearly with an if and an else:

    printf("Do you want to continue? \n");
    if (ch = getche() == 'y')
        printf("Let's continue ...\n");
    else
        printf("Goodbye\n");

    Nearly all contemporary computer scientists discourage the use of goto
    because it obscures program logic and makes code difficult to decipher, as
    anyone who has ever tried to debug an old-style BASIC program knows. If
    your programming background is in the older versions of BASIC or FORTRAN,
    resist the impulse to use goto statements. Examine the logic of your
    program: You probably will see, as in the above example, that an if-else
    with appropriate conditions (or a switch, break, or continue) lets you
    express the operation more clearly. That's why you can go for months
    without encountering a goto in C programs. (An occasional exception is the
    goto that breaks out of a multiple-nested loop. You can't use break in
    this situation because it only breaks out of the current loop. But even in
    this case, you can avoid a goto by redesigning the program structure to
    use "flag" variables. We will discuss flag variables later.)


More Complex Conditions for Branching

    Because we have been concentrating on the mechanics of branching, we have
    used only simple test conditions in our branching statements. In the last
    chapter, we showed you how to use logical operators (&& and ||) to create
    multiple conditions for controlling loops. You can also use these compound
    conditions to control the execution of if statements.

    The next program, PIXELS.C (Listing 5-8), introduces the QuickC Graphics
    Library. It generates random positions for pixels (points of light on the
    screen) and uses a compound condition to display only selected pixels.

Running the Program

    We've already included header files in several of our programs. The
    machine code represented by these header files was in the standard library
    (such as MLIBCE.LIB, the medium memory model with floating-point
    emulation), so all you needed to specify was #include and the appropriate
    header file. QuickC knew where to find the default library.

    To use graphics, however, you must specify the graph.h header file. The
    definitions it contains reside in a separate Graphics Library,
    GRAPHICS.LIB. You might need to tell QuickC where to find this library. As
    with the TABLE.C program in the last chapter, you need a program list.
    Create a program list called PIXELS.MAK and add PIXELS.C to it. (If you
    are unsure how to proceed, reread "Creating a Program List" in Chapter
    4.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* pixels.c -- creates shapes       */
    /*             from random pixels   */
    #include <graph.h> /* for graphics  */

    main()
    {
        int pixels, xpos, ypos;
        /* window coordinates */
        int xmin = 100, xmax = 540;
        int ymin = 50,  ymax = 150;

        srand(0);               /* init random nums */
        _setvideomode(_HRESBW); /* CGA 640 x 200    */
        _setcolor(1);           /* white foreground */

        /* generate random pixel locations      */
        for (pixels = 1; pixels < 10000; pixels++)
            {
            xpos = rand() % 639;
            ypos = rand() % 199;

            /* set pixel if within window */
            if ((xpos > xmin && xpos < xmax) &&
                (ypos > ymin && ypos < ymax))
                _setpixel(xpos, ypos);
            }
        getch(); /* freeze screen until key pressed */
                /* restore original video mode */
        _setvideomode(_DEFAULTMODE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 5-8.  The PIXELS.C program.

    You will need to add the Graphics Library (GRAPHICS.LIB) to the program
    list as well unless you specified that the Graphics Library was to be
    included in your standard library when you ran the SETUP program. (See
    Chapter 2.)

    For future programs in this book, we will not remind you to create a
    program list. In general, if the program uses any standard functions that
    are not part of the core library (listed in Appendix :ARB), you must
    create a program list with the name of the program in it before you can
    compile the program to memory. If you wish, you can simply try to compile
    the program and create the program list if you get the error unresolved
    external.

    PIXELS.C starts by including the graph.h header file, which contains
    definitions for graphics at every resolution and color supported by the
    IBM graphics adapters (CGA, EGA, VGA, and so on, each with several modes).
    We discuss graphics modes and graphics routines in Chapter 15. Here,
    simply note that the _setvideomode() statement in PIXELS.C sets the video
    mode to the constant _HRESBW, which represents the two-color
    high-resolution CGA mode having a resolution of 640 pixels by 200 pixels.
    The _setcolor statement sets the foreground color (the color of the
    displayed pixels) to white.

    The values xmin, xmax, ymin, and ymax contain the coordinate positions of
    the screen "window" in which the program plots pixels. Figure 5-3 shows
    the screen and the coordinates of the selected window, as well as some
    sample output for the program.

    The heart of the program is the for loop that plots 10,000 random pixel
    positions. Notice that we use the % (modulus) operator to select values in
    the range 0 through 639 for X, and 0 to 199 for Y. (This corresponds to
    the 640-by-200 resolution for the specified CGA high-resolution mode.)

    The if statement checks for an X and a Y position within the window
    specified by xmin, xmax, ymin, and ymax. Notice that the && logical AND
    operator ensures that each value is greater than or equal to the minimum
    and less than or equal to the maximum. The && between the two expressions
    in parentheses tests the random value to see if it fits in both the X and
    Y ranges.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 5-3 can be found on p.144 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 5-3. Screen coordinates and output for PIXELS.C.

Variations of PIXELS.C

    You can create many interesting shapes by substituting different
    conditions in the if statement. The GALAX.C program (Listing 5-9)
    establishes a center point (center_x, center_y) and a radius. The if
    statement in the for loop uses a formula that determines if a point is
    within the circleâ”€â”€if it is, the program plots the pixel.

    The result of running GALAX.C (Figure 5-4 on the following page) looks
    more like an ellipse than a circle because in the 640-by-200 mode, pixels
    are spaced together more closely horizontally than they are vertically.
    Because the program must calculate many square roots, it runs a little
    slowly. We use an if (kbhit()) to let you stop the program whenever you
    press a key.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* galax.c -- creates an ellipse by selecting */
    /*              from random pixels            */
    #include <graph.h> /* for graphics */
    #include <math.h>  /* for sqrt() */
    #include <conio.h> /* for kbhit() */
    main()
    {
        int pixels, radius = 50;
        double center_x = 320, center_y = 100,
            xpos, ypos;
        srand(0);
        _setvideomode(_HRESBW);
        _setcolor(1);
        for (pixels = 1; pixels < 25000; pixels++)
            {
            /* draws filled ellipse, due */
            /* to dimensions of hi-res screen */
            /* generate random location */
            xpos = rand() % 639;
            ypos = rand() % 199;
            if (sqrt /* is distance within radius? */
                ((xpos - center_x) * (xpos - center_x)
                + (ypos - center_y) * (ypos - center_y))
                < radius)
                _setpixel(xpos, ypos);
            if (kbhit())
                break; /* exit if key pressed */
            }
        getch(); /* freeze screen until key pressed */
        _setvideomode(_DEFAULTMODE);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 5-9.  The GALAX.C program.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 5-4 can be found on p.146 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 5-4. Output of GALAX.C.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€