Chapter 7  Arrays

    In programming, it is often advantageous to collect variables into sets or
    lists, so that many values can be stored and manipulated as a single
    conceptual unit. Such a collection of variables, when all those variables
    are the same type, is called an array. Arrays are used to organize values
    in applications that range from the "top ten" scores in a video game to
    the payroll records for thousands of employees.

    To visualize the advantage of arrays over simple variables, imagine that
    you run a business and that you want to store each employee's working
    hours in your computer. If you have even two employees, a year's worth of
    variables might look like this:

    int emp1_jan_1, emp2_jan_1;
    int emp1_jan_2, emp2_jan_2;
    ...â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€And so on for 362 intervening lines
    int emp1_dec_31, emp2_dec_31;


    Clearly, even the typing is a monumental undertaking. You can express the
    same number of variables as an array in C in a single line of code:

    int employees[2][365];

    Without a doubt, arrays let you organize data more concisely than do
    simple variables. This is convincingly illustrated in Figure 7-1.

    Although the details of declaration, storage, and retrieval differ from
    language to language, the basic nature of an array does not. In its
    simplest form, an array consists of one or more variables of the same
    storage type (size and number of bytes), arranged one after the other,
    continuously upward in memory. All variables in an array are referenced by
    a single name, called an identifier.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 7-1 can be found on p.190 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 7-1. Arrays provide superior organization over simple variables for
    many common C programs.


How Arrays Are Stored in Memory

    The elements in an array are stored consecutively in memory. An array
    consisting of only four int values, for example, is stored in memory as
    shown in Figure 7-2. Four int values (of two bytes each on the IBM PC)
    are arranged together in ascending order in memory. That is, the array
    begins with the leftmost intâ”€â”€the one lowest in memoryâ”€â”€and continues
    upward in memory with one or more adjoining int values.

                â”Œâ”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”
    Array of â”€â”€â”€â”€ â”‚     int     â”‚     int     â”‚     int     â”‚     int     â”‚
    4 ints        â””â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”˜

    Memory â”€â”€â”€â”€â”€â”€â”€â”€â”€ 46     47     48     49     50     51     52     53
    location

    Figure 7-2. An array of four int values as stored in memory.


How to Declare Arrays

    When you declare an array, you must tell the compiler how many items of
    which data type to set aside in memory for storage and the name to use
    when referencing that storage.

    The rules for declaring an array in C are relatively straightforward:

    â–   First, declare the type (char, float, int, etc.).

    â–   Second, declare the name. Array names use the same naming conventions
        as variable names.

    â–   Third, declare the number of items in the array by placing an integer
        constant expression inside square brackets; for example, [15].

    You recall, of course, that an "integer constant expression" is any
    integer constant value or any combination of integer constant values and
    arithmetic operators. Thus, 15 is an integer constant value, and so are 3,
    0x0F, and `a'. The last is a character constant that C views as an integer
    constant. But 3.0 is a floating-point constant and thus illegal for
    specifying the array size. The expression 15 * 2 is an integer constant
    expression because it is one integer constant value multiplied by another.

    Remember, you cannot specify the number of elements in an array with a
    variable. The following array declaration, for example, is illegal:

    int line_num = 15;
    int widths[line_num];

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    BASIC and Pascal Array Declarations
    Declaring an array in C is similar to declaring an array in BASIC and
    Pascal. In BASIC, an array is declared as widths%(15); in Pascal, the same
    array is declared as widths : ARRAY [1...15] OF INTEGER. In C, we declare
    this array as:

    int widths[15];

    All three of these declarations identify an array named widths composed of
    15 integer variables. Each sets aside room in memory for 15 int values (30
    bytes on the IBM PC because each int occupies two bytes). As you can see,
    declaring an array in C retains the simplicity of BASIC but is clearer
    than BASIC.

    The 1...15 expression in the Pascal declaration tells the compiler that
    the elements in the array are represented by the numbers 1 through 15. In
    C, array elements are always numbered beginning with 0 and ascending to
    the specified number.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    You cannot use the expression line_num to declare the number of elements
    in the array widths. The C compiler looks at only one small piece of a
    program at a time. It first sees int line_num = 15 and generates code to
    store the value 15 into the variable line_num. When it reaches the array
    declaration, all it knows of line_num is that it currently contains the
    value 15; QuickC has no idea how that value will change as the program
    executes.

    In C, a constant variable, that is, one declared with the ANSI keyword
    const, is not considered a constant value. Therefore, the following
    example is illegal:

    const int line_num = 15;
    int widths[line_num];

    Using the const keyword declares to the compiler that you do not intend to
    change the value of line_num. It does not prevent a bug in your program
    from accidentally changing that value.

    If you attempt to declare the size of an array with a variable, even a
    const variable, QuickC will print the following error message:

    Error C2057:
    expected constant expression

    Examine the ARRAY1.C program (Listing 7-1). This "do-nothing" program
    demonstrates the correct way to declare arrays.

    In this program, SIZEOARRAY is specified using #define as 26. The number
    of items in ages is therefore declared with 26 * 2, which is legal.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* array1.c -- how to declare arrays legally        */

    #define SIZEOARRAY 26

    main()
    {
        char  initials[26];
        int   num_men[26], num_women[SIZEOARRAY];
        float ages[SIZEOARRAY * 2];
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-1.  The ARRAY1.C program.


Referencing and Using Array Items

    The way you reference the items in an array (whether to store values in
    them or to fetch values from them) looks very much like the declaration.
    You merely state the identifier for the array and place the offset of the
    item within square brackets. The offset is always measured from the
    beginning of the array, with the first item having an offset of 0.

    For example, the expression

    widths[1] = 3;

    stores the value 3 in the second item of the array named widths; that is,
    the item whose offset from the beginning of the array is 1.

    Conversely, the expression

    this_width = widths[1];

    retrieves the value of the second item of the array widths and assigns
    that value to the variable this_width.

    In C, the offset into an array can be the result of any expression that
    returns a value. It can be the value of a variable, the result of a
    computation or logical test, or even the returned value of a function
    call. The only restriction is that the array offset must be specified with
    an integer value. The following are legal specifications:

    widths[1]â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Offset is a constant
    widths[i]â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Offset is an int variable
    widths[i++]â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Offset is a computation
    widths[getnum()]â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Return value of function call
    widths['a']â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Offset is a char constant

    However, the following float type offset causes a compiler error:

    widths[fltval]â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€float offset (error)

    Because there are no fractional memory locations, specifying an array's
    offset with a float causes the following QuickC error:

    error C2108:
    non-integral index

    With a legal offset specification, an array element is no different from
    an ordinary variable of that type. You can perform the same operations
    with an array item as you can with any ordinary variable. Consider, for
    example:

    widths[1] = 3;
    total  = widths[0] + widths[1] + widths[2];

    In the first operation, the value 3 is stored in the second element of the
    array named widths. In the second, values stored in three array elements
    are added together. Notice that we use the same notation to access eachâ”€â”€
    an offset in brackets.

An Example

    Now that you have the basic rules for declaring arrays and accessing items
    in those arrays, examine the XMAS.C program (Listing 7-2).

    In XMAS.C, we declare the array widths to contain 20 items of the type
    int. That array is then filled with values by the for loop; this is one
    way to store values in an array. Finally, each item in the array widths is
    passed to the function Center_out(); this is one way to access the values
    in an array.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* xmas.c -- fills an array with values, then passes */
    /*           each of those values to a function      */

    main()
    {
        int i, j, widths[20];
        void Center_out();

        for (i = 0, j = 1; i < 18; ++i, j += 2)
            {
            widths[i] = j;
            }
        widths[i++] = 3;
        widths[i] = 3;

        for (i = 0; i < 20; i++)
            {
            Center_out('X', widths[i]);
            }

    }

    void Center_out(char character, int width)
        {
        int i;

        for (i = 0; i < ((80 - width) / 2); ++i)
            {
            putch(' ');
            }
        for (i = 0; i < width; ++i)
            {
            putch(character);
            }
        putch('\r');
        putch('\n');
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-2.  The XMAS.C program.

    Whenever you reference an array element, the value of that element becomes
    available for useâ”€â”€you can assign the value to other variables or pass it
    to a function. Note, however, that passing an array element by giving its
    name and an offset merely passes a copy of that element, not the element
    itself. This is the method for passing ordinary variables.


Bounds Checking Arrays in Your Code

    In XMAS.C, the for loop prevents your specifying an offset beyond the end
    of the array widths:

    for (i = 0; i < 20; ++i)

    In many programs, however, the ability to exceed an array's bounds is not
    prevented by your code but is controlled by the user. For example, the
    SADD.C program (Listing 7-3) is a simple adding machine that lets the
    user enter as many as three numbers, one per line, and terminate entry
    with any non-numeric character such as an x.

    Now run SADD.C and enter (on separate lines) the numbers 1, 2, and 3,
    followed by an x character. The program displays the correct sum,
    which is 6:

    1
    2
    3
    x
    ----------
    6

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* sadd.c -- a small adding machine that illustrates  */
    /*            the need for array bounds checking      */

    main()
    {
        int offset = 0, i, result = 0;
        int stack[3];

        while (scanf("%d", &stack[offset]) == 1)
            {
            ++offset;
            }
        for (i = 0; i < offset; ++i)
            {
            result += stack[i];
            }
        printf("----------\n");
        printf("%d\n", result);

    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-3.  The SADD.C program.

    Now run the program again, but this time enter four numbers:

    1
    2
    3
    4
    x
    ----------
    20

    The result shown is 20, which is wrong. But QuickC doesn't recognize that
    an error occurred and prints no error message. The C language itself,
    unlike Pascal and BASIC, contains no provisions to prevent offsets beyond
    the end of an array.

    To understand why SADD.C referenced stack[3], even though no fourth item
    exists (remember that arrays begin with item 0), let's look again at the
    way arrays are arranged in memory. As a bonus, we'll find out where the
    value 20 came from. Figure 7-3a shows how the compiler translates into
    memory the declarations from SADD.C (shown on the next page).

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚Â°                                        Initialized         Â°â”‚
    â”‚Â°       int offset=0, i, result=0;â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’  Â°â”‚
    â”‚Â°       int stack[3];                                     â–’  Â°â”‚
    â”‚Â°  â–’â–’â–’â–’â–’while (scanf("%d", &stack [offset]) == 1)         â–’  Â°â”‚
    â”‚Â°  â–’          ++offset;                 â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’  Â°â”‚
    â”‚Â°  â–’                                    â–’                 â–’  Â°â”‚
    â”‚Â°  â–’    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â–¼â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â–¼â”€â”€â”€â”¤
    â”‚Â°  â–’    â”‚    ?   â”‚    ?   â”‚    ?   â”‚    0   â”‚    ?   â”‚    0   â”‚
    â”‚Â°  â–’    â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚Â°  â–’     stack[0] stack[1] stack[2]  result      i     offsetâ—„â”œâ”€â”€â”€â”€â”€â”
    â”‚Â°  â–’                                                     Â°â”‚     â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–’â”€â”€â”€â”€â”€â”€â”€â”€â–’â”€â”€â”€â”€â”€â”€â”€â”€â–’â”€â”€â”€â”€â”€â”€â”€â”€â–’â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     â”‚
        â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’1â–’â–’â–’â–’â–’â–’â–’â–’2â–’â–’â–’â–’â–’â–’â–’â–’3â–’â–’â–’â–’â–’â–’â–’â–’4                           â”‚
                â”‚                            â”‚                          â”‚
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜                          â”‚
                                â”‚                                        â”‚
                    Stores these input values                          â”‚
                    while incrementing offsetâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    (A)


    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚    1   â”‚    2   â”‚    3   â”‚    4   â”‚    ?   â”‚    4   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    stack[0] stack[1] stack[2]â”‚ result      i     offset
                                â”‚    
            Array ends hereâ”€â”€â”€â”˜    â”‚
                                    â”‚
                            Position of stack[3]

    (B)

    Figure 7-3. Consequence of referencing beyond the end of an array.

    int offset = 0, i, result = 0;
    int stack[3];

    First, the variables offset and result are set to 0. Then the while loop
    fills out the items in the 3-element array stack. The last value entered
    was 4, which was the fourth value placed into stack. But stack contains no
    fourth item (that is, no stack[3] ), so the fourth value is placed into
    result because result occupies the place in memory that follows the stack
    array.

    The arrangement depicted in Figure 7-3a occurs because QuickC places auto
    variables into memory from the top down, but it places static and global
    variables into memory from the bottom up.

    Now look closely at Figure 7-3b. Because result begins with a value of 4
    instead of 0, the for loop adds 1, 2, and 3 to it, resulting in a sum of
    10. The for loop continues (because offset is 4) by adding stack[3] to
    result (both reference the same address and the same value, 10), thus
    yielding the erroneous value of 20.

    To make programs less sensitive to improper user input, always provide
    code that detects array out-of-bounds conditions. You can do this by
    simply terminating the program when an error is detected, but writing your
    program so that it can recover from errors is better. The SADD2.C program
    (Listing 7-4) shows a common approach to array bounds checking that
    corrects the previous program's weakness.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* sadd2.c -- a small adding machine that includes */
    /*            array bounds checking                */

    #define MAXSTAK 3

    main()
    {
        int offset = 0, i, result = 0;
        int stack[MAXSTAK];

        while (scanf("%d", &stack[offset]) == 1)
            {
            if (++offset >= MAXSTAK)
                {
                printf("Stack Full\n");
                break;
                }
            }
        for (i = 0; i < offset; ++i)
            {
            result += stack[i];
            }
        printf("----------\n");
        printf("%d\n", result);

    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-4.  The SADD2.C program.

    In this revision of SADD.C, we use the preprocessor #define directive to
    create an alias for the size of the array stack. Thus, you can later
    easily change the number of items in stack by changing a single #define
    and then recompiling.

    Next, we insert an if statement that checks a preincremented offset to be
    sure it does not exceed the number of items in stack, that is, MAXSTAK. If
    offset becomes too large, the if statement first causes a warning message
    to be printed and then breaks out of the while loop. The user gets an
    accurate sum for the numbers entered, despite the error, and any
    out-of-range numbers are simply ignored.


How to Initialize Arrays

    When you declare an auto array (an array declared inside a function and
    without the keyword static), it is initially filled with garbage values,
    regardless of its type and size. (This also occurs when you create auto
    variables.) On the other hand, static arrays and arrays declared outside
    of functions always have their initial values set to zeroâ”€â”€again just like
    ordinary variables. For example:

    char Letters[26];â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Initialized to zeros

    main()
    {
        char vowels[5];â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Starts with garbage
        static char consonants[21];â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Initialized to zeros

    When zero is not an appropriate initial value, you can give static and
    global variables starting values of your choice. To initialize an array:

    â–   Follow the right square bracket (]) in the array identifier with an
        assignment operator (=) and a left brace ({).

    â–   Then state each initializing value, followed by a comma.

    â–   Finally, terminate your comma-separated list of initializers with a
        right brace (}) and the usual semicolon.

    For example, to initialize the array Letters with the letters of the
    alphabet, you need simply declare it as:

    char Letters[26] = { 'a', 'b', 'c', 'd', 'e',
                            'f', 'g', 'h', 'i', 'j',
                            'k', 'l', 'm', 'n', 'o',
                            'p', 'q', 'r', 's', 't',
                            'u', 'v', 'w', 'x', 'y',
                            'z', };

    Or, for an array of numbers you could declare:

    int Values[5] = { 12, 2, 44, 19, 7 };

    In both of the above examples, the type of the initializing values matches
    the type of the array and is a constant value. This is mandatory. Values
    in array initializing

    lists must be constant values or constant expressions, and those values
    must fit in the number of bytes declared for each array item. The array
    Letters is initialized with the type char, and `a' is a char constant. The
    array Values is initialized with type int, and 12 is an integer constant.
    A float array would have to be initialized with the type float, such as
    76.98, which is a floating-point constant.

    The ASIMOV.C program (Listing 7-5) contains in the initialized array
    Letters the name of a famous Isaac Asimov character. By entering the
    correct series of numbers, you can reveal that name.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* asimov.c -- illustrates how to initialize an      */
    /*             array with starting values            */

    #define MAXL 16
    char Letters[MAXL] = {
        'e', 'I', 'a', 'N', 'o', 'R', 'O', 'o',
        'u', 't', 'o', 'R', 'l', 'o', 'B', 'b', };

    main()
    {
        int num, i;

        printf("Guess my identity with numbers.\n");
        printf("(any non-number quits)\n\n");

        while (scanf("%d", &num) == 1)
            {
            if (num <= 0)
                {
                printf("Guesses must be above zero\n");
                continue;
                }
            for (i = 1; i <= num; ++i)
                {
                printf("%c", Letters[(i * num) % MAXL]);
                }
            printf("\n");
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-5.  The ASIMOV.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    The list of initializers for Letters ends with a trailing comma. That is
    not an error. Trailing commas in initializer value lists are optional but
    enable long lists to be rearranged easily with your text editor.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Letting the Compiler Supply the Size

    When you declare the values for an initialized array, it is not always
    possible, or necessary, to state explicitly the number of items in the
    array. C provides an alternative. For example, the following declaration
    omits the size of the array:

    int  Primes[ ] = {1, 2, 3, 5, 7, 11,};
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Number of items omitted

    Whenever you omit the size, the C compiler counts the number of
    initializers and dimensions the array to the correct size for that count.
    Because the preceding example contains six initializers, that declaration
    is equivalent to declaring:

    int  Primes[6] = {1, 2, 3, 5, 7, 11,};

    When the size of an array is omitted, you might expect bounds checking in
    your code to be difficult. Fortunately, you can use the sizeof operator to
    find the number of bytes in an array and thus specify, using #define, a
    bounds-checking value. When used with the preceding declaration, the
    expression

    #define MAXL (sizeof(Primes)/sizeof(int))

    gives MAXL a value of 6.

    The sizeof keyword, when given the name of an array, yields the number of
    bytes in that array. The #define, then, is the number of bytes in the
    array Primes (12 bytes) divided by the number of bytes in an int (2
    bytes).

Overinitializing and Underinitializing

    One good reason to omit the size of an array is that C permits a mismatch
    between the number of initializing values and the size you declare. When
    there are fewer initializers, the compiler silently fills the remainder
    with zero values. When there are too many initializers, the compiler
    complains and stops. Some compilers (especially under UNIX) will issue a
    warning and truncate the array.

    The UNDOVER.C program (Listing 7-6) demonstrates this behavior. As the
    program stands, it prints the following message:

    The first 6 primes are: 1 2 3 5 7 11

    Now change Primes[6] to Primes[8] in the declaration and run the program
    again. This time it prints:

    The first 8 primes are: 1 2 3 5 7 11 0 0

    The new result shows that underinitializing causes the compiler to fill
    the leftover items with zero values. Now change the declaration again,
    this time from Primes[8] to Primes[3]. This time the QuickC compiler stops
    and issues the message:

    error C2078:
    too many initializers

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* undover.c -- illustrates the effect of underinitializing and */
    /*              overinitializing arrays                         */

    int Primes[6] = { 1, 2, 3, 5, 7, 11 };
    #define NUMP (sizeof(Primes) / sizeof(int))

    main()
    {
        int i;

        printf("The first %d primes are: ", NUMP);
        for (i = 0; i < NUMP; ++i)
            {
            printf("%d ", Primes[i]);
            }
        printf("\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-6.  The UNDOVER.C program.


Arrays and Functions

    As you saw earlier in XMAS.C, passing one of an array's elements to a
    function is like passing an ordinary variable to a function. That is, a
    copy of the value of that element is passed, not the element itself.

    However, when you pass whole arrays to functions, the situation changes.
    Although you are still passing by value, what you are actually passing is
    the address of the array (its location in memory). The effect of this is
    that you appear to be passing the array itself and that the array itself
    will be changed. (See the next chapter for further details.) For now,
    we'll simply show you how to pass arrays to functions and how to use those
    arrays when they get there.

Passing Arrays to Functions

    To pass an array to a function, merely state the array's name (minus the
    offset) in the function call. For example, if you have declared an array
    as follows:

    static int list[7] = { 5, 1, 3, 7, 2, 4, 6 };

    you would pass that array to a function, called Bub_sort() for example, by
    stating its name, as follows:

    Bub_sort(list);

    This tells the compiler to send the entire array named list to Bub_sort().

    At the receiving end, in Bub_sort(), you need to declare the type of the
    received array. To do so, declare an array in the normal C manner and
    leave the square brackets empty:

    Bub_sort(vals)
    int vals[];
    {

    This declares that a function named Bub_sort() will receive one argument,
    the int array vals. Because Bub_sort() is receiving an arrayâ”€â”€via the
    array's addressâ”€â”€it receives the array itself and not a copy of that
    array. This allows Bub_sort() to change the original array.

    The BUBSORT.C program (Listing 7-7) demonstrates the differences between
    passing array elements to functions and passing entire arrays.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* bubsort.c  --  passing an array to a function  */
    /*                affects the original array      */

    #define NUMINTS 6

    extern void Bub_sort();
    extern void Triple();
    main()
    {
        int num = 2, i;
        static int list[NUMINTS] = { 6, 5, 4, 3, 2, 1 };

        printf("num before Triple = %d\n", num);
        Triple(num);
        printf("num after Triple = %d\n", num);
        printf("list[0] before Triple = %d\n", list[0]);
        Triple(list[0]);
        printf("list[0] after Triple = %d\n", list[0]);
        printf("Before sorting -> ");
        for (i = 0; i < NUMINTS; ++i)
            {
            printf("%d ", list[i]);
            }
        printf("\n");

        Bub_sort(list);
        printf("After sorting ->  ");
        for (i = 0; i < NUMINTS; ++i)
            {
            printf("%d ", list[i]);
            }
        printf("\n");

    }
    void Triple(int x)  /* function doesn't affect original */
    {
        x *= 3;
    }

    void Bub_sort(int vals[NUMINTS]) /* function changes original */
    {
        int i, j, temp;

        for (i = (NUMINTS - 1); i > 0; --i)
            {
            for (j = 0; j < i; ++j)
                {
                if (vals[j] > vals[j+1])
                    {
                    temp      = vals[j];
                    vals[j]   = vals[j+1];
                    vals[j+1] = temp;
                    }
                }
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-7.  The BUBSORT.C program.

    This program first calls the Triple() function, passing it both an
    ordinary variable and one of the elements in the array list. The value of
    the original isn't changed in either case; only the value (a copy) of what
    is sent is changed.

    Next, we pass the array list to the function Bub_sort() (a simple bubble
    sorting function). The program prints the array before and after the
    function call to demonstrate that the Bub_sort() function changes the
    values in the original array; it does not sort a copy.

Variations

    When a function receives an array, the number of elements in the
    declaration of that array is usually omitted because the size
    specification is optional:

    Bub_sort(vals)
    int vals[ ];
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Size of array omitted

    Restating that size in the function declaration, however, is often a good
    idea. As we have seen, C does no array bounds checking on your behalf, so
    restating the size of the received array helps to clarify and document
    your program:

    Bub_sort(vals)
    int vals[NUMINTS];
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Restated for clarity

    The type of the received array should also match that of the original. If
    the types do not match, your program might not work properly. The reason
    we say "might not" is that you might want to mismatch types intentionally.
    The HEXOUT.C program (Listing 7-8) demonstrates such a planned mismatch.
    This program asks you to enter a floating-point number and then prints out
    that number, one byte at a time, in hexadecimal notation.

    HEXOUT.C first reads a floating-point value into the array faryâ”€â”€a float
    type array consisting of only one element. That array is then passed to
    Hexout(). In Hexout(), we declare the type of the received array as
    unsigned char. This "deception" causes Hexout() to handle the array fary
    as if it were an array of single unsigned bytes, whereas the original was
    actually a 4-byte float type. We will explain this shortly. This deception
    illustrates one of C's primary strengths, the freedom of the programmer to
    change types in midstream.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* hexout.c --  prints a floating-point variable in */
    /*              hexadecimal format                  */

    extern void Hexout();
    main()
    {
        float fary[1];

        printf("Enter a floating-point number\n");
        printf("(Any non-numeric entry quits)\n\n");
        while (scanf("%f", &fary[0]) == 1)
            {
            Hexout(fary);
            }
    }

    void Hexout(unsigned char chary[])
    {
        int i;

        for (i = 0; i < sizeof(float); ++i)
            {
            printf("%02X ", chary[i]);
            }
        printf("\n\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-8.  The HEXOUT.C program.


How Array Offsets Advance

    When you reference an array element with an array name and an offset,
    QuickC invisibly converts the element offset to a bytes-in-memory offset.
    To illustrate this, let's look at how two different type arrays are
    organized in memory. Figure 7-4 shows that an array of char type occupies
    one byte of memory for each element and that an array of float type
    occupies four bytes of memory for each element.

    For the char array, chary[4], each element occupies one byte, so each
    element offset specification corresponds to the bytes-in-memory offset.
    For the float array fary[2], however, each element occupies four bytes, so
    each element offset specification corresponds to a bytes-in-memory offset
    of 4 bytes. In the latter case, when you specify

    fary[1]

    you are really telling the compiler to reference a value that is four
    bytes into the array fary[]. Because a float value occupies four bytes of
    memory, your element offset of 1 becomes a bytes-in-memory offset of 4
    bytes.

    This explains how, in the preceding program, HEXOUT.C, it is possible to
    print out a float one byte at a time. Inside the function Hexout(), the
    compiler thinks it is handling an array of unsigned char type, in which
    each element occupies a single byte. Thus, i increments in unmultiplied
    steps of single bytes.

                    char chary[4] = {'t', 'e', 's', 't'};

                        â”‚ 1 byte â”‚
                        â”‚        â”‚
                        â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”
                        â”‚   't'  â”‚   'e'  â”‚   's'  â”‚    't' â”‚
                        â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    (A)                        ARRAY OF char VALUES


    float fary [2] = {1.2, 4.3};

    â”‚ 1 byte â”‚
    â”‚        â”‚
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚                1.2                â”‚                4.3                â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                    fary[0]                             fary[0]

    (B)                        ARRAY OF float VALUES

    Figure 7-4. How offsets differ by number of bytes based on the type of the
    array.


Multidimensional Arrays

    In C you can easily create and use arrays of two, three, or many
    dimensions. Two-dimensional arrays correspond to such useful items as
    calendars, spreadsheets, and maps. We begin with the rules for
    two-dimensional arrays and then apply them to arrays of three and more
    dimensions. Three-dimensional arrays find application in items such as 3-D
    graphics, layered indexes, and solid topology. Many-dimensioned arrays
    delve into the arcane worlds of higher math and complex games.

Two-dimensional Arrays

    Two-dimensional arrays represent rectangular grids of data. As illustrated
    in Figure 7-5, they are organized in rows first and then columns. Because
    computer memory is linear, those rows and columns are stored in memory one
    row after the other.

    The rules for declaring a two-dimensional array are similar to those for
    declaring a one-dimensional array. They take the following form:

    type name[rows][columns];

    As with one-dimensional arrays, you must specify the number of rows and
    the number of columns as integer constant expressions. Thus, the
    expression

    int week[7][8];

    declares a two-dimensional array of type int, named week, with 7 rows (for
    7 days) and 8 columns (for 8 working hours per day). You can fill it with
    any number of useful items, for example, the number of lines of code
    written per hour per day.

                                    Columns
                                        â”‚
                            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                            â”‚                       â”‚
                            â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â” â”€â”€â”€â”
                            â”‚   1   â”‚   2   â”‚   3   â”‚    â”‚
                            â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤    â”‚
                            â”‚   4   â”‚   5   â”‚   6   â”‚    â”œâ”€â”€ Rows
                            â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤    â”‚
                            â”‚   7   â”‚   8   â”‚   9   â”‚    â”‚
                            â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜ â”€â”€â”€â”˜
                                        â”‚
                                        â”‚  Arranged in memory as
                                        â–¼
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
    â”‚   1   â”‚   2   â”‚   3   â”‚   4   â”‚   5   â”‚   6   â”‚   7   â”‚   8   â”‚   9   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜
    â”‚                       â”‚                       â”‚                       â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚                       â”‚                       â”‚
            Zeroth row               First row              Second row

    Figure 7-5. Two-dimensional arrays are arranged in memory row by row.

    Referencing two-dimensional array elements is as simple as referencing
    elements of one-dimensional arrays. Specify the row and column with
    integer expressions:

    int day  = 6, /* Saturday */
        hour = 2; /* 10:00 A.M. */

    printf("Wrote %d lines of code.\n", week[day][hour]);

    Initializing Two-dimensional Arrays

    Before we go into the somewhat more complex rules for initializing
    two-dimensional arrays, enter the MAGIC.C program (Listing 7-9). This
    program initializes an array of type int with scrambled numbers and then
    asks the user to rearrange those numbers into the correct order by
    continually swapping squares adjacent to the 0 with the 0. The object is
    to rearrange the numbers into ascending order, with 0 at the top left,
    counting up row by row.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* magic.c  --  demonstrates use of a two-dimensional  */
    /*              array of type int                      */

    main()
    {
        static int square[3][3] = { 5, 8, 3, 4, 2, 0, 7, 1, 6 };
        int zrow = 1, zcol = 2;  /* location of the zero */
        int num, row, col, i, j, rowdist, coldist;

        while (1)
            {
            printf("Swap what with zero?\n");
            printf("(Q to quit)\n");

            /* Print the square. */
            for (i = 0; i < 3; ++i)
                {
                for (j = 0; j < 3; ++j)
                    {
                    printf(" %d ", square[i][j]);
                    }
                printf("\n");
                }

            /* Enter the user number. */
            if ((num = getch()) == 'Q')
                exit(0);
            num -= '0';
            if (num < 1 || num > 9)
                {
                printf("Not a legal number.\n\n");
                continue;
                }
            /* Find that square. */
            for (row = 0; row < 3; ++row)
                {
                for (col = 0; col < 3; ++col)
                    {
                    if (num == square[row][col])
                        {
                        goto GOTIT;
                        }
                    }
                }
    GOTIT:
            /* Check for a legal move. */
            if (row > 2 || col > 2)
                {
                printf("Bad Box Specification\n\n");
                continue;
                }
            rowdist = zrow - row;
            if (rowdist < 0)
                rowdist *= -1;
            coldist = zcol - col;
            if (coldist < 0)
                coldist *= -1;
            if (rowdist > 1 || coldist > 1)
                {
                printf("Not a Neighbor\n\n");
                continue;
                }

            /* Make the move. */
            square[zrow][zcol] = square[row][col];
            square[row][col] = 0;
            zrow = row;
            zcol = col;

            /* See if done, and solved. */
            for (i = 0; i < 3; ++i)
                {
                for (j = 0; j < 3; ++j)
                    {
                    if (square[i][j] != ((i * 3) + j))
                        {
                        break;
                        }
                    }
                }
            if ((i * j) == 9)
                break;
            }
        printf("\n\aYOU GOT IT !!!\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-9.  The MAGIC.C program.

    We initialize the two-dimensional array in MAGIC.C by filling it row by
    row. When, for clarity, you want to specify where one row ends and the
    next begins, you can enclose each row's initializers in another set of
    braces:

    static int square[3][3] = {
        {5, 8, 3},â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Row 0
        {2, 4, 0},â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Row 1
        {7, 1, 6}â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Row 2
    };

    This amounts to specifying each row as its own subset of initializers,
    clearly a more readable arrangement.

    To underinitialize a 3-by-3 array, we could use the following:

    static int square[3][3] = {
        5, 8, 3, 2, 4, 7, 1, 6 };
                                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ One initializer short

    Here the last column of the last row is omitted and thus is 0 by default.
    We also could underinitialize by a selected row, as follows:

    static int square[3][3] = {
        {5, 8, 3},
        {2, 4},â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Row 1 short
        {7, 1, 6}
    };

    Here we omit the third column of the second row, thus setting the value to
    0.

    Two-dimensional Arrays and Functions

    As with one-dimensional arrays, you pass a two-dimensional array to a
    function by merely stating its name:

    Make_move(board);

    Again, this passes the two-dimensional array itself, not a copy.

    For the receiving function, Make_move(), you must always declare the size
    of the columns. The number of rowsâ”€â”€as with one-dimensional arrays that
    have only one rowâ”€â”€is optional, as shown in the following legal example:

    Make_move(field)
    int field[][3];

    The TTT.C program (Listing 7-10 on the next page) is a somewhat
    unsophisticated tic-tac-toe game that will help you understand how to use
    two-dimensional arrays. It's an easy game to win. Forcing a tie, however,
    is difficult. For clarity, the declaration for field in Make_move()
    includes the number of rows.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* ttt.c    --  a tic-tac-toe game demonstrates  */
    /*              passing two-dimensional arrays   */
    /*              to functions                     */

    main()
    {
        static char board[3][3] = {
            { '-', '-', '-' },
            { '-', '-', '-' },
            { '-', '-', '-' },
        };
        int row, col, ch;
        extern char Check_winner();
        extern void Make_move(), Draw_field();

        printf("You are X and make the first move.\n");
        while (1)
            {
            printf("Specify coordinate for your X.\n");
            printf("(For example, a2, or Q to quit)\n");

            /* Print the square. */
            Draw_field(board);

            /* Enter the user's coordinates. */
            if ((row = getch()) == 'Q')
                exit(0);
            row -= 'a';
            col = getch() - '1';

            /* Check for a legal move. */
            if (row < 0 || row > 2 || col < 0 || col > 2)
                {
                printf("Bad Square Specification\n\n");
                continue;
                }
            if (board[row][col] != '-')
                {
                printf("Sorry, Square Occupied\n\n");
                continue;
                }

            /* Make the move. */
            board[row][col] = 'X';
            if ((ch = Check_winner(board)) != '-' || ch == 't')
                break;
            Make_move(board);
            if ((ch = Check_winner(board)) != '-' || ch == 't')
                break;
            }
        Draw_field(board);
        if (ch == 't')
            printf("It's a tie!\n");
        else if (ch == 'X')
            printf("You win!\n");
        else
            printf("I win!\n");
        }

    char Check_winner(char field[][3])
        {
        int row, col;

        for (row = col = 0; row < 3; ++row, ++col)
            {
            if (field[row][0] != '-'             /* horizontal */
                    && field[row][0] == field[row][1]
                    && field[row][1] == field[row][2])
                {
                return(field[row][0]);
                }
            if (field[0][col] != '-'             /* vertical */
                    && field[0][col] == field[1][col]
                    && field[1][col] == field[2][col])
                {
                return(field[0][col]);
                }
            }
        if (field[0][0] != '-'         /* right diagonal */
                && field[0][0] == field[1][1]
                && field[1][1] == field[2][2])
            {
            return(field[0][0]);
            }
        if (field[0][2] != '-'         /* left diagonal */
                && field[0][2] == field[1][1]
                && field[1][1] == field[2][0])
            {
            return(field[0][2]);
            }

        for (row = 0; row < 3; ++row)        /* any moves left */
            {
            for (col = 0; col < 3; ++col)
                {
                if (field[row][col] == '-')
                    {
                    return('-');
                    }
                }
            }
        return ('t');
    }

    void Make_move(char field[3][3])
    {
        int row, col;

        for (row = 2; row >= 0; --row)
            {
            for (col = 2; col >= 0; --col)
                {
                if (field[row][col] == '-')
                    {
                    field[row][col] = 'O';
                    return;
                    }
                }
            }
    }

    void Draw_field(char field[][3])
    {
        int row, col;

        printf("\n   1  2  3\n\n");
        for (row = 0; row < 3; ++row)
            {
            printf("%c ", 'a' + row);
            for (col = 0; col < 3; ++col)
                {
                printf(" %c ", field[row][col]);
                }
            printf("\n");
            }
        printf("\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-10.  The TTT.C program.

Arrays of Three and More Dimensions

    In C you can give an array an unlimited number of dimensions, but remember
    that the more dimensions an array has, the more unmanageable it becomes.
    You have already seen how two-dimensional arrays are declared,
    initialized, and passed to functions. The rules for using more dimensions
    are a simple extension of those same concepts.

    Declaring Multidimensional Arrays

    The general rule for declaring multidimensional arrays is as follows:

    type name[exp][exp][exp][exp] ...
                â”‚    â”‚    â”‚    â”‚    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Etc.
                â”‚    â”‚    â”‚    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Fourth dimension
                â”‚    â”‚    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Third dimension
                â”‚    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Second dimension
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ First dimension

    First, specify the type that will be stored in each array item, and then
    name the entire array. Each exp is an integer constant expression that
    specifies the number of elements in that dimension. Each succeeding
    square-bracketed [exp] defines another dimension.

    Think of a three-dimensional array as a cube. Figure 7-6 shows a
    conceptualization of a cube that corresponds to the following declaration:

    #define DEPTH  3
    #define ROWS   3
    #define COLS   3

    int cube[DEPTH][ROWS][COLS];
                â”‚   â””â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”˜
                â”‚         â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Size of each two-dimensional array
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Number of two-dimensional arrays (depth)

    You can also think of this three-dimensional array as an array of three
    two-dimensional arrays.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 7-6 can be found on p.213 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 7-6. Three-dimensional arrays can be thought of as a cube.

    Initializing Multidimensional Arrays

    When you use a list of values to initialize a multidimensional static or
    global array, the compiler reads that list from left to right, filling the
    array row by row for each plane of the depth. The following declaration
    places the initializing values into cube, beginning with the value 1, as
    shown in Figure 7-7.

    int cube[3][3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9,
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
        22, 23, 24, 25, 26, 27};

    To specify the order for initializing, you can enclose any group with
    braces. Those braces correspond to the depth first, then to the rows and
    columns. You can therefore rewrite the above declaration more clearly as
    follows:

    int cube[3][3][3] =
    {
        { {1,  2,  3},  {4,  5,  6},  {7,  8,  9} },
        { {10, 11, 12}, {13, 14, 15}, {16, 17, 18} },
        { {19, 20, 21}, {22, 23, 24}, {25, 26, 27} }
    };

    Here each inner set of braces encloses a given row's list of initializers.
    Use this technique when you need to underinitialize a given row, column,
    or depth. Clearly, as you progress beyond three dimensions, initializing
    can become very confusing. Just remember the general rules, or, in
    despair, simplify your algorithm.

            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€\
            â”‚\â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€\
            â”‚ â”‚  19   â”‚  20   â”‚  21   â”‚ \
            â”‚\â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤   \
            â”‚ â”‚  22   â”‚  23   â”‚  24   â”‚     \
            â”‚\â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤       \
            â”Œâ”€\ â”‚  25   â”‚  26   â”‚  27   â”‚         \
            â”‚  \â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜           \
            â”‚     \           â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€\
            â”‚       \         â”‚\â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€\
            â”‚         \       â”‚ â”‚  10   â”‚  11   â”‚  12   â”‚ \
            â”‚           \     â”‚\â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤   \
            â”‚             \   â”‚ â”‚  13   â”‚  14   â”‚  15   â”‚     \
            â”‚               \ â”‚\â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤       \
            â”‚                 â”‚ â”‚  16   â”‚  17   â”‚  18   â”‚         \
    Depthâ”€â”€â”¤                  \â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜           \
            â”‚                     \          â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€\
            â”‚                       \        â”‚\â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”â”€â”€â”
            â”‚                         \      â”‚ â”‚   1   â”‚   2   â”‚   3   â”‚  â”‚
            â”‚                           \    â”‚\â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚
            â”‚                             \  â”‚ â”‚   4   â”‚   5   â”‚   6   â”‚  â”œâ”€â”€Row
            â”‚                               \â”‚\â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚
            â”‚                                \ â”‚   7   â”‚   8   â”‚   9   â”‚  â”‚
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€\â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜â”€â”€â”˜
                                            â”‚                       â”‚
                                            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                                        Columns

    Figure 7-7. Initializing a three-dimensional array.

    Using Multidimensional Arrays in Functions

    To pass a multidimensional array to a function, you need specify only the
    name of that array as an argument:

    Draw_planes(cube);

    On the receiving endâ”€â”€in the function Draw_planes()â”€â”€you must specify the
    sizes of all but the leftmost dimension. That size is optional, as in the
    following:

    int
    Draw_planes(box);
    int box[][3][3];
    {

    The BOX.C program (Listing 7-11) shows the initialization of a
    three-dimensional array and then prints out the result.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* box.c  --  demonstrates the result of initializing  */
    /*            a three-dimensional array                */

    main()
    {
        static int cube[3][3][3] = {
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
            13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
            23, 24, 25, 26, 27 };
        int plane;
        extern void Draw_plane();

        for (plane = 0; plane < 3; ++plane)
            {
            Draw_plane(cube, plane);
            }
    }

    void Draw_plane(int box[3][3][3], int slice)
    {
        int row, col;

        printf("Plane[%d] =\n", slice);
        for (row = 0; row < 3; ++row)
            {
            for (col = 0; col < 3; ++col)
                {
                printf( "%2d ", box[slice][row][col]);
                }
            printf("\n");
            }
        printf("\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-11.  The BOX.C program.


Advanced Topics and Tricks

    In this section we discuss three advanced techniques that can be very
    handy:

    â–   Negative subscripting

    â–   Large and huge arrays

    â–   Passing pieces of arrays

Negative Subscripting

    Recall that unless you include code to perform bounds checking, C lets you
    reference items both beyond the end and before the beginning of an array.
    You have already seen the consequences of referencing beyond an array's
    end. Referencing before its beginning is something new, as Figure 7-8
    demonstrates.

    If you declare three consecutive arrays such as the following:

    int first[3], second[3], third[3];

    and then reference with a negative subscript:

    second[-1]

    you actually reference either third[2] or first[2], depending on whether
    the arrays are auto or static, as shown in Figure 7-8. QuickC places auto
    arrays into memory from right to left (top down) and static arrays from
    left to right (bottom up).

                    second [-1]
                        â”‚
                        â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
    â”‚   7   â”‚   8   â”‚   9   â”‚   4   â”‚   5   â”‚   6   â”‚   1   â”‚   2   â”‚   3   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜
    â”‚                       â”‚                       â”‚                       â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚                       â”‚                       â”‚
            third [3]              second [3]              first [3]

    (A)                         ARRAY DECLARED auto


                    second [-1]
                        â”‚
                        â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
    â”‚   1   â”‚   2   â”‚   3   â”‚   4   â”‚   5   â”‚   6   â”‚   7   â”‚   8   â”‚   9   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜
    â”‚                       â”‚                       â”‚                       â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚                       â”‚                       â”‚
            first [3]               second [3]             third [3]

    (B)                          ARRAY DECLARED static

    Figure 7-8. Effect of negative subscripting on auto and static arrays.

    The L2WORDS.C program (Listing 9-11 on pp. 282â”€83) illustrates this
    technique.

Large and Huge Arrays

    On the IBM PC an integer is 2 bytes long, so you have to be careful when
    declaring arrays larger than 32,767 elements. That is because 32,767 is
    the highest positive value a 2-byte integer can hold. If you successively
    reference the elements in an array with the following loop:

    int i;
    for (i = 0; i < 40000; i++)
        printf("%dn", array[i]);

    the 0th through 32,767th elements print out correctly, but the 32,768th
    element prints out as array[-32768].

    Integers are signed variables, so they wrap to negative numbers when they
    exceed their highest positive value. Therefore, to reference elements in
    large arrays, use either unsigned int or long offsets.

    Another problem occurs when arrays grow to more than 65,536 bytes total on
    the IBM PC. In this case, use the huge keyword in the array declaration,
    as follows:

    int huge bigbox[100][100][100];

    Here the keyword huge is required because the total size of the array
    bigbox is 100 x 100 x 100 times 2 (two bytes per int), or 2,000,000 bytes
    total. This tells the compiler to set aside more space for this array than
    the space reserved for ordinary variables. Whenever you use large arrays
    that require the huge keyword, compile with the large memory model. That
    model will be discussed in greater detail in Chapter 12. (Of course, you
    will need lots of memory in your computer, too.)

Passing Pieces of Arrays

    When you reference array elements with fewer dimensional offsets than were
    present in that array's declaration, you are actually referencing the
    address of a subarray. If, for example, you declare:

    int square[3][3];

    and then later reference that array without specifying the second
    dimension:

    Print_row(cube[1]);

    you would pass the address of cube's second row (a one-dimensional
    subarray) to Print_row(). Then declare Print_row() to receive a
    one-dimensional array:

    Print_row(row)
    int row[];
    {


The Bitwise Operators, Tiny Arrays

    Just as arrays can get larger and larger and more and more complex, it is
    also possible to go the other direction and store data in the individual
    bits of a single byte. You can manipulate individual bits of a byte using
    the bitwise operators. Those operators are:

    Operator           Description
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    &                  The bitwise AND operator
    |                  The bitwise OR operator
    ^                  The bitwise exclusive-OR operator
    ~                  The unary inversion operator (ones-complement)
    >>                 The unary right-shift operator
    <<                 The unary left-shift operator
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Each of these affects the individual bits in the bytes of a value, which
    can be either a constant or a variable. Remember, a char uses 8 bits, an
    int 16 bits, and a long 32 bits. First, we demonstrate the application of
    the bitwise operators, and then discuss the logic of each.

    The BITWISE.C program (Listing 7-12) lets you enter values interactively
    and then apply the bitwise operators to them. By running this program, you
    will better understand the discussion that follows. (Note that a set bit
    is represented with a 1 and a clear bit is represented with a 0.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* bitwise.c -- demonstrates the bitwise operators */

    #include <stdio.h>

    main()
    {
        unsigned int val1, val2, result;
        int ch;
        extern void show();

        while(1)
            {
            printf("\nval1: ");
            if (scanf("%d", &val1) != 1)
                break;

            printf("val2: ");
            if (scanf("%d", &val2) != 1)
                break;
            printf("\tval1   = ");
            show(val1);
            printf("\tval2   = ");
            show(val2);

            printf("Bitwise Operator: ");
            while ((ch = getchar()) == '\n')
                {
                continue;
                }
            if (ch == EOF)
                break;
            switch (ch)
                {
                case '&':
                    result = val1 & val2;
                    printf("Executing: result = val1 & val2;\n");
                    break;
                case '|':
                    result = val1 |= val2;
                    printf("Executing: result = val1 | val2;\n");
                    break;
                case '^':
                    result = val1 ^= val2;
                    printf("Executing: result = val1 ^ val2;\n");
                    break;
                case '~':
                    result = ~val1;
                    printf("Executing: result = ~val1;\n");
                    printf("\tresult = ");
                    show(result);
                    result = ~val2;
                    printf("Executing: result = ~val2;\n");
                    break;
                case '<':
                    result = val1 <<= val2;
                    printf("Executing: result = val1 <<val2;\n");
                    break;
                case '>':
                    result = val1 >>= val2;
                    printf("Executing: result = val1 >>val2;\n");
                    break;
                case 'q':
                case 'Q':
                    return(0);
                default:
                    continue;
                }
            printf("\tresult = ");
            show(result);
            }
    }
    void bitout(unsigned char num[])
    {
        int bytes = 2, i, j;

        /* IBM PC stores ints low/hi. */
        for (i = bytes-1; i >= 0; --i)
            {
            for (j = 7; j >= 0; --j)
                {
                putchar((num[i]&(1<<j))?'1':'0');
                }
            }
    }

    void show(unsigned int val)
    {
        extern void bitout();

        printf("(%05u decimal)", val);
        bitout(&val);
        printf(" binary\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 7-12.  The BITWISE.C program.

The Binary Bitwise Operators

    The bitwise AND, the bitwise OR, and the bitwise exclusive-OR are binary
    operators. That is, like the addition operator, they operate on two
    valuesâ”€â”€not one. You can invoke them as follows:

    result = val1 & val2;     /* bitwise AND          */
    result = val1 | val2;     /* bitwise OR           */
    result = val1 ^ val2;     /* bitwise exclusive-OR */

    Or you can invoke them with the op= form:

    result &= val1;    /* bitwise AND          */
    result |= val1;    /* bitwise OR           */
    result ^= val1;    /* bitwise exclusive-OR */

    The Bitwise AND Operator

    The bitwise AND operator, &, compares the bits in two values and produces
    a value based on the comparison of the same bits in each:

    var1           &              var2          yields         result
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    1                             1                            1
    0                             1                            0
    1                             0                            0
    0                             0                            0
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    For the bitwise AND, the result bit is set only if the same bit in both
    values is set. Otherwise, the result bit is cleared.

    The bitwise AND operator is useful for turning off (clearing) a selected
    bit in a variable. A typical application for the & operator is to turn off
    a blinking cursor when you are accessing screen memory directly:

    var1 =  3;
    var1 &= 0xFFFE;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Turn off low bit

    This results in the following calculation:

                    0000000000000011 â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ var1
                & 1111111111111110 â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ OxFFFE
                â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Yields â”€â”€â”€â”€â”€ 0000000000000010
                                
                                â”‚
                                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Low bit cleared

    The Bitwise OR Operator

    The bitwise OR operator, |, compares the bits in two values and sets the
    result bit for any bit that is set in either of the values:

    var1           |              var2          yields         result
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    1                             1                            1
    0                             1                            1
    1                             0                            1
    0                             0                            0
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    For the bitwise OR, the result bit is set if either or both corresponding
    bits in both values are set. Otherwise, the result bit is cleared.

    The bitwise OR operator is useful for turning on (setting) a selected bit
    in a variable. A typical application for the | operator is to turn on the
    high bit of a character variable before sending that character to the
    printer:

    var1 =  0;
    var1 |= 1;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Turn on low bit

    This results in the following calculation:

                    0000000000000000 â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ var1
                | 0000000000000001 â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Equivalent to 1 decimal
                â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Yields â”€â”€â”€â”€â”€ 0000000000000001
                                
                                â”‚
                                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Low bit set

    The Bitwise exclusive-OR Operator

    The bitwise exclusive-OR operator, ^, compares the bits in two values and
    produces a set bit only if one bit or the other is set, but not both:

    var1           ^              var2          yields         result
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    1                             1                            0
    0                             1                            1
    1                             0                            1
    0                             0                            0
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    For the bitwise exclusive-OR, ^, the result bit is set if one or the other
    of the corresponding bits in the values is set, but not both.

    The bitwise exclusive-OR operator is useful for toggling (setting,
    clearing, setting, etc.) a selected bit in a variable. A typical
    application for the ^ operator is to toggle a flag in a game, thereby
    determining which of two players is to make the next move:

    var1 =  0;
    var1 ^= 1;
    var1 ^= 1;

    This results in the following calculations:

                    0000000000000000 â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ var1
                ^ 0000000000000001 â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Equivalent to 1 decimal
                â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Yields â”€â”€â”€â”€â”€ 0000000000000001
                                
                            â–“      â”‚
                            â–“      â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Low bit set (Player 2)
                            â–“
                            â–“
                            â–¼

                    0000000000000001 â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ New value of var1
                ^ 0000000000000001 â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Equivalent to 1 decimal
                â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Yields â”€â”€â”€â”€â”€ 0000000000000000
                                
                                â”‚
                                â””â”€â”€â”€â”€â”€â”€â”€ Low bit toggled to clear (Player 1)

The Unary Bitwise Operators

    The unary bitwise operators affect the bits of a single value. These
    operators are:

    Operator       Description
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    ~              The unary ones-complement operator
    >>             The unary right-shift operator
    <<             The unary left-shift operator
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    The Unary Ones-Complement Operator

    The ones- complement of a variable is derived by inverting all the bits in
    that value. If a bit is set, that bit changes to clear, and vice versa. In
    C, the ~ causes the bits in a value to be inverted, as follows:

    var1    0000000000000111

    ~var1   1111111111111000â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Result

    Two applications are common for the ones-complement operator. One is to
    set selected bits in a variable regardless of the number of bytes occupied
    by that variable. Suppose you have an int and you want all but the zeroth
    bit set. One way to do this is by:

    number = 0xFFFE;

    This does the job, but pays the price of assuming an int always occupies
    two bytes of storage. Although that is true on the IBM PC, it is not the
    case on most 32-bit machines. The correct way to set all but the zeroth
    bitâ”€â”€and the portable wayâ”€â”€is to use the ones-complement operator:

    number = ~1;

    The second common application for the ones-complement operator is turning
    off selected bits. One way to turn off the zeroth bit, while leaving all
    the other bits in a variable unchanged, is:

    masks &= 0xFFFE;

    But again, the ones-complement operator should be used for portability:

    masks &= ~1;

    The Unary Shift Operators

    The shift operators move all the bits in a variable right or left by the
    number of bit positions specified. The shift operators are used as
    follows:

    result = value <<bits;
    result = value >>bits;

    Here the first line shifts the value in value leftâ”€â”€from the low toward
    the high bitâ”€â”€by the number of bit positions specified by bits. The second
    line shifts value in the opposite directionâ”€â”€right, or from the high
    toward the low bit. For example:

    val1       0000000000111000
    val1 <<3   0000000111000000â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Left shift
    val1 >>3   0000000000000111â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Right shift

    When shifting left, the bits on the right are filled with clear bits. With
    QuickC, the fill bits for a right shift are always set. For portability,
    however, always use unsigned variables when right-shifting.

    The shift operators are useful for aligning a bit prior to ORing it into a
    variable. Shifting also provides a quick way to multiply or divide by 2.
    Each bit you shift to the left multiplies a number by 2; each bit you
    shift to the right divides it by 2.

    int val = 1;

    val <<= 1;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€val now equals 2
    val <<= 1;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€val now equals 4
    val <<= 1;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€val now equals 8

Summary of Bitwise Operators

    If you haven't already done so, enter, compile, and run the BITWISE.C
    program (Listing 7-12 on p. 218). Watching the actions of bits as the
    program applies each bitwise operator will give you a feel for bits and
    will lead you to develop sophisticated applications of your own. You will
    find the bitwise operators used a great deal in the hardware-specific
    chapters at the end of this book.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€