Chapter 8  Addresses and Pointers

    One of the chief strengths of C is its ability to manipulate individual
    areas of memory with almost the same precision that assembly language
    provides. This chapter discusses this ability in detail by showing you a
    new kind of variable called a "pointer"â”€â”€a variable whose contents
    identify a memory address. Using pointers can greatly increase the speed
    at which your programs execute, lets you access your computer's hardware
    directly, and allows you to write subroutines that manipulate variables
    directly (via the address).


Addresses Reviewed

    The concept of memory addresses is vital to C programming. Recall, for
    example, that all arguments passed to scanf() must be preceded by an
    ampersand (&). In the following expression:

    scanf("%d", &num);

    the & tells scanf() to read an integer from the keyboard and to place that
    input value into the variable num, whose address is passed with the
    expression &num.

    You also used addresses with arrays. In the previous chapter we mentioned
    that when an entire array is passed to a function, it is passed as
    addresses. For example, the code fragment

    char choices[4] = {'Q', 'E', 'S', 'L'};

    Get_move(choices);

    passes the address of the choices array to the function Get_move(), rather
    than the individual elements of that array. When you use an array name
    without specifying an element in square brackets, the compiler uses the
    internal starting memory address of that array as its value.

    One of C's strengths is the ease with which it lets you manipulate the
    values of variables by way of their addresses. This type of address
    manipulation, known as indirection, is accomplished with pointers.


What Is a Pointer?

    A pointer, in its simplest form, is a variable whose value (contents) is
    an address, or a number corresponding to a specific location in memory.
    That is, if address_var is a pointer-type variable, and num is an integer
    variable, the expression

    address_var = &num;

    causes the address of the variable num to be placed into the pointer
    variable named address_var. This assignment ignores the actual value of
    num.

    You can use pointers in your programs to:

    â–   Save information from functions that return addresses

    â–   Indirectly return more than one value from a function

    â–   Speed up execution by manipulating pointers rather than large blocks of
        data

    â–   Access and modify text screen memory

    â–   Call functions using their addresses, thus creating more flexible code

    â–   Access and manipulate strings

    Before you can use a pointer, also called a "pointer to," you must declare
    it. Declaring a pointer is much like declaring an ordinary variable, the
    only difference being that you must always precede the pointer's name with
    the * character.

    The following example declares two variables: an integer called num and a
    pointer called address_var.

    int num, *address_var;

    The * before address_var tells the compiler that address_var is a pointer
    whose contents will be an address. Because address_var is declared as type
    int, the compiler knows that address_var will contain the address of an
    integer variable. Figure 8-1 illustrates this process.

    In this example, we declare two variables and two pointers (Figure 8-1a).
    The variables are num (an int) and fval (a float). We also declare two
    pointers, address_var and faddress_var.

    The pointer address_var contains the address of an int type of variable;
    pointer faddress_var contains the address of a float type of variable. The
    two assignment statements in Figure 8-1b store the addresses in the
    appropriate pointers. The result of the assignment is that address_var now
    holds num's address (and thus points to num), and faddress_var holds
    fval's address (and thus points to fval).

        int num/ *address_var;   â”€â”€â”€â”
                                    â”‚â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’ These declarations
        float fval, *faddress-var;â”€â”€â”˜         â–’ create...
                                                â–¼

    Memoryâ”€â”€  4096   4097  4098  4099  4050  4051  4052  4053  4054  4055
    locations â”Œâ”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”
    in bytes  â”‚           â”‚           â”‚           â”‚           â”‚           â”‚
            â””â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”˜
                    â”‚           â”‚     â”‚                       â”‚     â”‚
                    â”‚           â”‚     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     â”‚
                    â”‚           â”‚                 â”‚                 â”‚
                    num     address-var          fval          faddress-vars

    (A)


            address_var = &num; â”€â”€â”€â”
                                â”‚â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’ These assignments
            faddress-var = &fval; â”€â”˜         â–’ yield...
                                            â–¼

                â”Œâ”€â”€â”€â”€â–º&numâ”€â”€â”€â”€â”€â”€â”        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–º&fvalâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                â”‚               â”‚        â”‚                          â”‚
    Memoryâ”€â”€  4096   4097  4098 â”‚4099  4050  4051  4052  4053  4054 â”‚4055
    locations â”Œâ”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”
    in bytes  â”‚           â”‚   4096    â”‚           â”‚           â”‚   4050    â”‚
            â””â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”˜
                    â”‚           â”‚     â”‚                       â”‚     â”‚
                    â”‚           â”‚     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     â”‚
                    â”‚           â”‚                 â”‚                 â”‚
                    num     address-var          fval          faddress-var
                                â–’                                  â–’
                    â–’           â–’                 â–’                 â–’
                    â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’                 â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’
                    Points to                         Points to

    (B)

    Figure 8-1. Result of assigning an address to a pointer.


Accessing Variables with Pointers

    The * operator (pronounced "star"), when used to signify a pointer, is
    called the indirection operator because it lets you access variables
    indirectly. When you use the * operator in front of a pointer (other than
    in its declaration) you tell the compiler to fetch or store the value that
    the pointer points to. For example, in the fragment

    int num, *address_var;

    address_var = &num;
    *address_var = 3;

    you first declare an int variable (num) and a pointer to an int
    (address_var). Next, the value you store in address_var is the address of
    the variable num. Finally, the * in front of address_var tells the
    compiler to store the value 3 in the variable whose address is stored in
    address_var. Because address_var contains the address of num, that value
    is stored in num. (See Figure 8-2 on p. 234.)

    The POINTER.C program (Listing 8-1) illustrates the procedure for
    declaring, assigning a value to, and using pointers.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* pointer.c  --  demonstrates pointer declaration,   */
    /*                assignment, and use                 */

    #define WAIT printf("(press any key)"); getch(); \
                printf("\n\n")

    main()
    {
        int num, *address_var;

        num = 0;
        address_var = &num;

        printf("The address of the variable ");
        printf("\"num\" is:  0x%04X\n", &num);
        printf("The value in the pointer ");
        printf("\"address_var\" is:  0x%04X\n", address_var);
        printf("The value in the variable ");
        printf("\"num\" is: %d\n", num);
        WAIT;
        printf("Since \"address_var\" points to \"num\"\n");
        printf("the value in ");
        printf("\"*address_var\" is: %d\n", *address_var);
        WAIT;
        printf("To verify this, let's store 3 in\n");
        printf("\"*address_var\", then print out ");
        printf("\"num\" and \"*address_var\"\n");
        printf("again.\n");
        WAIT;
        printf("Doing: *address_var = 3;\n\n");
        *address_var = 3;

        printf("The address of the variable ");
        printf("\"num\" is:  0x%04X\n", &num);
        printf("The value in the pointer ");
        printf("\"address_var\" is:  0x%04X\n", address_var);
        printf("The value in the variable ");
        printf("\"num\" is: %d\n", num);
        WAIT;
        printf("Since \"address_var\" points to \"num\"\n");
        printf("the value in ");
        printf("\"*address_var\" is: %d\n", *address_var);
        WAIT;

        printf("Now we will add 15 to \"num\" and print\n");
        printf("\"num\" and \"*address_var\" again.\n");
        WAIT;

        printf("Doing: num += 15;\n\n");
        num += 15;

        printf("The address of the variable ");
        printf("\"num\" is:  0x%04X\n", &num);
        printf("The value in the pointer ");
        printf("\"address_var\" is:  0x%04X\n", address_var);
        printf("The value in the variable ");
        printf("\"num\" is: %d\n", num);
        WAIT;
        printf("Since \"address_var\" points to \"num\"\n");
        printf("the value in ");
        printf("\"*address_var\" is: %d\n", *address_var);
        WAIT;

        printf("Doing: return (*address_var);\n\n");
        return (*address_var);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-1.  The POINTER.C program.

    The output of this program follows. Compare it to the listing.

    The address of the variable "num" is:  0x1388
    The value in the pointer "address_var" is:  0x1388
    The value in the variable "num" is: 0
    (press any key)

    Since "address_var" points to "num"
    the value in "*address_var" is: 0
    (press any key)
    To verify this, let's store 3 in
    "*address_var", then print out "num" and "*address_var"
    again.
    (press any key)

    Doing: *address_var = 3;

    The address of the variable "num" is: 0x1388
    The value in the pointer "address_var" is: 0x1388
    The value in the variable "num" is: 3
    (press any key)

    Since "address_var" points to "num"
    the value in "*address_var" is: 3
    (press any key)

    Now we will add 15 to "num" and print
    "num" and "*address_var" again.
    (press any key)

    Doing: num += 15;

    The address of the variable "num" is:  0x1388
    The value in the pointer "address_var" is: 0x1388
    The value in the variable "num" is: 18
    (press any key)

    Since "address_var" points to "num"
    the value in "*address_var" is: 18
    (press any key)

    Doing: return (*address_var);

    In the POINTER.C program, the pointer address_var contains the address of
    num (as a result of the assignment address_var = &num) and therefore
    yields the value stored in num. That is, we indirectly access num via its
    address (*address_var = 3). Because address_var contains num's address,
    you can use *address_var anywhere you would use num. For example, we could
    have ended the program with return (num) to produce the same result.


Passing Pointers to Functions

    Until now, with the exception of arrays, we have passed arguments to
    functions by value. Thus, you might think we could write a function that
    squares the argument passed to it as follows:

    square(int num)
        {
        num *= num;
        }

    This doesn't work, however, because the variable num is a local variable
    to the function square(), and the result is not accessible by other
    functions. Thus, calling square() with

    main()
    {
        int val = 5;

        square(val);
    }

    does not result in main()'s variable val being squared, because main()
    doesn't "see" the variable num.

    You can get around this by having square() return a value, as follows:

    main()
    {
        int val = 5;

        val = square(val);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Value returned by square()
    }

    square(int num)
    {
        num *= num;
        return (num);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€square() returns value
    }

    Another approach is to use pointers. When you pass a pointer to a
    function, you still pass a copy of its value, but the value you pass is an
    address. Therefore, in square(), you must declare num as a pointer because
    it will receive an address:

    square(int *address_var) â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Pointer receives an address
    {

        *address_var *= *address_var;
    }                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Multiplication operator

    This form of square() receives an address as its argument. The pointer to
    hold that address, address_var, is declared as int *address_var because it
    receives the address of an int variable.

    To use this new square() function, we must pass it an address. We can do
    this in either of two ways. We can use the & operator, as follows:

    main()
    {
        int val = 5;

        square(&val);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Pass an address
    }

    Or we can pass a pointer:

    main()
    {
        int val = 5, *here;

        here = &val;
        square(here);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€The value of here is val's address
    }

    After making our declarations, we place the address of val into the
    pointer here. When we pass here to square(), its valueâ”€â”€the address of
    valâ”€â”€is what is actually passed. This results in val being squared.

    The SQUARE.C program (Listing 8-2) summarizes this passing of pointers
    and addresses in an interactive quiz. In it, we've expanded on our
    original square() subroutine. In the new Square(), we return two values
    from a single function! The first, returned by return, is an error
    statusâ”€â”€zero for a successful square and -1 for any attempt to square a
    number larger than 181 or less than -181 (the square root of 32,767, the
    largest signed int on the IBM PC). We return the second value with the
    pointer *where.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* square.c  --  a quiz to demonstrate passing        */
    /*               pointers and addresses in functions  */

    main()
    {
        int val, count, guess;

        for (count = 1; count < 255; ++count)
            {
            val = count;
            printf("What is the square of %d?\n", val);
            if (scanf("%d", &guess) != 1)
                return(0);        /* non-number exits   */

            if(Square(&val) != 0)    /* pass val's address */
                {
                printf("Range Error\n");
                exit(1);
                }
            if (val != guess)
                printf("Wrong. It is %d.\n", val);
            else
                printf("Right!\n");
            printf("Continue? ");
            if (getche() != 'y')
                break;
            }
    }
    int Square(int *where)
    {
        if (*where > 181 || *where < -181)
            return (-1);
        *where = (*where) * (*where);
        return (0);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-2.  The SQUARE.C program.

    In this program, we use a separate variable, count, in the for loop
    because the value of val is indirectly changed by the call to Square(). If
    we had used val as follows:

    for (val = 1; val < 255; ++val)

    you would be prompted only for the numbers 1, 2, 5, and 26, and then you
    would receive a Range Error.


Pointers and Arrays

    Pointers let you manipulate strings and arrays more succinctly and
    efficiently. We'll learn about strings in the next chapter. Here we will
    discuss the relationship between arrays and pointers, detailing potential
    pitfalls along the way.

    Recall from the previous chapter that referencing an array by name,
    without an offset, yields that array's address. What we didn't tell you
    was that the address of an array is the same as the address of the array's
    first element. For example, in the following array declaration:

    int coins[4] = {25, 10, 5, 1};

    the reference

    Find_change(coins, amount);

    actually causes the address of the array coins[4] to be passed to the
    function Find_change(). Because the address of an array is the location in
    memory of its beginning, we can also reference that array with the
    expression

    &coins[0]

    Here the address operator & yields the address of the first item in the
    array coins and, therefore, the address of the array itself.

    You can assign the address of another variable to a pointer with the &
    operator (address_var = &num[1]). Because each item in an array is a
    variable, the assignment

    address_var = &coins[0];

    results in address_var containing the address of the first integer in the
    array coins.

    Because &coins[0] and coins are equivalent, the following expression is
    the same as the one above:

    address_var = coins;

    Now here comes the exciting part. When a value, say 1, is added to a
    pointer, it increments the address in that pointer by the number of bytes
    in the type to which it points. For example, in Figure 8-2 the variable
    address_var begins with a value that is the address of coins. Notice what
    happens when we add 1 to address_var. Because address_var is a pointer to
    the type int, and because an int occupies two bytes (on the IBM PC), the
    value in address_var is increased by 2. The new value in address_var is
    thus the address of coins[1] (the next element in the array).

                                Points to
                                â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’
                                â–’        â–’
                        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â” â–’
                        â”‚             â”‚ â–¼
    Memory locationsâ”€â”€  4392   4393  4394  4395  4396  4397  4398  4399
    in bytes           â”Œâ”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”
                        â”‚   4394    â”‚           â”‚           â”‚           â”‚
                        â””â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”˜
                            â”‚           â”‚           â”‚           â”‚
                            â”‚           â”‚           â”‚           â”‚
                            â”‚           â”‚           â”‚           â”‚
                        address-var   coins[0]    coins[1]    coins[2]
                            â€¢                                  
                            â€¢                       â–’           â–’
                            â€¢                       â–’           â–’
                        4392   4393                  â–’           â–’
                        â”Œâ”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”                 â–’           â–’
                        â”‚   4394    â”‚â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’           â–’
                        â””â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”˜   Next points to            â–’
                            â”‚                                   â–’
                            â”‚                                   â–’
                            â”‚                                   â–’
    Increment valueâ”€â”€â”€address_var += 1;                          â–’
    of pointer               â€¢                                   â–’
                            â€¢                                   â–’
                            â€¢                                   â–’
                        4392   4393                              â–’
                        â”Œâ”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”                             â–’
                        â”‚   4398    â”‚â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’
                        â””â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”˜    Then points to
                            â”‚
                            â”‚
                            â”‚
    Increment pointerâ”€â”€â”€address_var += 1;
    again

    Figure 8-2. The value of a pointer increases by multiples of the number of
    bytes in the data type to which it points.

    The CHANGE.C program (Listing 8-3) demonstrates how the pointer coin_ptr
    advances through the array coins, each step determined by the number of
    bytes for the type int. Compile the program with the Debug option set
    because we want to trace its execution.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* change.c  -- a change-making program demonstrates   */
    /*              how pointers advance the correct       */
    /*              number of bytes based on type          */

    #define NCOINS (4)
    #define CENT (0x9b)  /* IBM PC cent character */
    #define WAIT printf("(Press any key to continue)"); \
                getch(); printf("\n\n")

    main()
    {
        static int coins[NCOINS] = {25, 10, 5, 1};
        int *coin_ptr, i = 0;
        int pennies1, pennies2, count;
        float amount;

        printf("Enter an amount and I will ");
        printf("give you change.\nAmount: ");
        if (scanf("%f", &amount) != 1)
            {
            printf("I don't know how to change that!\n");
            exit(1);
            }
        pennies2 = pennies1 = (int)(amount * 100.0);

        coin_ptr = coins;
        for (i = 0; i < NCOINS; ++i)
            {
            WAIT;
            count = 0;
            while ((pennies1 -= coins[i]) >= -1)
                ++count;
            if (count > 0)
                {
                printf("%4d %2d%c", count, coins[i], CENT);
                printf(" coins by array offset.\n");
                }
            if (pennies1 == 0)
                break;
            pennies1 += coins[i];

            count = 0;
            while ((pennies2 -= *coin_ptr) >= 0)
                ++count;
            if (count > -1)
                {
                printf("%4d %2d%c", count, *coin_ptr, CENT);
                printf(" coins by pointer indirection.\n");
                }
            if (pennies2 == 0)
                break;
            pennies2 += *coin_ptr;
            ++coin_ptr;
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-3.  The CHANGE.C program.

    After you compile CHANGE.C, turn off screen swapping and specify the
    following four watch variables:

    coin_ptr
    *coin_ptr
    i
    coins[i]

    (See pp. 119-20 if you forgot how to specify watch variables. You don't
    need to specify the types with a comma; the defaults are correct.) Now
    step through the program with the F8 function key. Observe that as ++i
    followed by coins[i] steps through the array, so does ++coin_ptr followed
    by *coin_ptr. Figure 8-3 shows the screen as the program is being traced.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 8-3 can be found on p.236 of the printed version of the book.   â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 8-3. Incrementing a pointer moves it through an array in steps
    that correspond to the number of bytes in the data type.

    This equivalence between arrays and incrementing pointers is one of C's
    chief strengths. It can also be confusing and can lead to some unexpected
    bugs. In the CHANGE.C program, we perform bounds checking with the for
    loop. If we rewrite that loop without i, we need to do one of two things.
    One option is to put some stop value into our array, such as the last
    element (0) in the following:

    int coins[5] = {25, 10, 5, 1, 0};

    This approach is often used with string variables.

    The other option requires that we add some means of detecting when the
    address in coin_ptr becomes too large, as follows:

    for (coin_ptr = coins; coin_ptr < &coins[4]; ++coin_ptr)

    This approach is more common for situations where a stop value is not
    practical. In a database, for example, you might have 32 bytes available
    and want to use all 32 for a mailing address, with none reserved for a
    terminating value.


Pointer Arithmetic

    QuickC permits fewer arithmetic operations on pointers than on other kinds
    of variables. Because pointers contain addresses as their values, whenever
    you change one, you reference a new location inside your computer's
    memory. Obviously, you don't want to reference random locationsâ”€â”€not only
    would they be meaningless, but they might overwrite crucial memory
    locations and crash your PC.

    To help avoid such meaningless addresses, C permits only a handful of
    mathematical operations to be performed on pointers. They are:

    Addition  You can add values to addresses (like incrementing with ++).
    This is most useful with arrays.

    Subtraction  You can subtract values from addresses (decrementing with --
    and subtracting with -).

    Comparison  You can compare one address to another to see if it is greater
    than, less than, equal to, or not equal to the other.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    C does not provide many safeguards against referencing incorrect
    addresses. QuickC, however, lets you compile with Pointer Check turned on.
    Although this provides a measure of safety (by verifying that pointer
    values address program data), it results in slower-executing programs.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    The operations allowed on pointers are a small set when compared to the
    operations allowed on numeric variables and array items. Let's examine why
    you cannot use the other arithmetic operations:

    Multiplication  Doubling an address or even multiplying it by, let's say,
    523 would yield a new address value that, at best, would be somewhere in
    your data and at worst would be beyond the end of your program, possibly
    in the code of another memory resident program (like QuickC or
    COMMAND.COM).

    Division  Halving an address or even dividing it by, let's say, 10 would
    yield a new address value that, at best, would be somewhere inside your
    own code and at worst would be inside the MS-DOS interrupt vectors.

    Bitwise operators  You cannot manipulate the bits in an address. This
    would result in a totally random address.

    Unary negation  You can't reverse the sign of an address because addresses
    are always unsigned.

    Now let's look at the CHANGE2.C program (Listing 8-4). This rewrite of
    CHANGE.C illustrates the incrementing of pointers and the comparison of
    two pointers.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* change2.c -- modified to demonstrate passing       */
    /*              an address to a function              */

    #define NCOINS (4)
    #define CENT (0x9B)  /* IBM PC cent character */

    main()
    {
        static int coins[NCOINS] = {25, 10, 5, 1};
        int pennies;
        float amount;

        printf("Enter an amount and I will ");
        printf(" give you change.\nAmount: ");
        if (scanf("%f", &amount) != 1)
            {
            printf("I don't know how to change that!\n");
            exit(1);
            }
        pennies = (int)(amount * 100.0);

        Show_change(coins, &coins[NCOINS], pennies);

        }
    Show_change(int amts[], int *end, int due)
    {
        int count;

        while (amts < end)    /* compare pointers */
            {
            count = 0;
            while ((due -= *amts) >= -1)
                {
                ++count;
                }
            if (count > 0)
                printf("%4d %2d%c\n", count, *amts, CENT);
            if (due == 0)
                break;
            due += *amts;

            ++amts;                /* increment a pointer */
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-4.  The CHANGE2.C program.

    The function Show_change() receives addresses of the array coins and the
    fourth element in that array (one past its end). This introduces some new
    concepts: the interchangeability of the declaration coins[] with the
    declaration *coins and the importance of left versus right values.


The Interchangeability of *amts and amts[]

    In the following declaration:

    Show_change(int amts[]);
    {

    the expression int amts[] tells the compiler to pass this array to the
    function Show_change(). However, you can also use an array declaration of
    the form *amts interchangeably with amts[]. The two are equivalent. In
    fact, if you declare an array as amts[], you can use that array's name as
    though it were a pointer:

    Show_change(int amts[])
        {             â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Declared as an array
        ...
        due = *amts;
                â””â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ but used as a pointer

    and vice versa:

    Show_change(int *amts[])
        {              â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Declared as a pointer
        ...
        due = amts[i];
                â””â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ but used as an array

    Note, however, that this interchangeability works only when the array is
    declared as one of a function's received arguments. An attempt to use that
    singular equivalence elsewhere results in either a Syntax or an lvalue
    error.


lvalue vs rvalue

    An lvalue is any variable whose value can change (have a new value
    assigned to it). An rvalue is a variable whose value cannot change. The
    easiest way to differentiate between the two is to remember that rvalues
    go to the right of the assignment operator and lvalues go to the left. Why
    is this important?

    Arrays are usually rvalues because of the way C generates its intermediate
    code. C treats an array as a label (like the target of a goto is a label).
    As an address of a location, an array is a constant value much like the
    number 3 is a constant.

    Confusing lvalues and rvalues with array names is a common source of
    errors for the beginning C programmer. Always remember that array names
    cannot be assigned to, incremented, or decremented, except when they are
    declared as one of the received arguments of a function, as follows:

    char *Amount;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Global pointer or lvalue
    int   Bills[4] = {20,10,5,1};â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Array or rvalue

    some_function(char amts[];)â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Equivalent to a pointer
        {
        char *address_var,â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Local pointer or lvalue
                old_coins[];â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Syntax error

        ++Amounts;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Legal
        ++Bills;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Illegal operation on rvalue
        ++amts;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Legal
        ++address_var;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Legal
        ++old_coins;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Legal
        }

    In this sample program, *Amount and *address_var are pointers, values that
    can be incremented. Although amts[] is declared as an array, the
    interchangeability we discussed earlier permits us to increment it as
    though it were a pointer. On the other hand, because Bills is not a
    function's argument (it is a global array), it is an rvalue that cannot be
    incremented. Finally, old_coins[] generates a syntax error because only
    arrays in function argument declarations can be used without specifying
    the size of their leftmost dimension.


Type Casting Pointers and Addresses

    Occasionally you will need to perform an arithmetic operation on a pointer
    other than addition, subtraction, or comparison. Fortunately, C is very
    flexible, and it permits you to perform those other operations on pointers
    by using type casts (also called "casts"). In Chapter 3 you used a type
    cast to convert one type to another: You can also use that technique with
    pointers. For example, suppose you need to divide a pointer's value by 2.
    You could use the method:

    unsigned long temp;
    int *point = some_address;

    temp = (unsigned long)point;
    temp /= 2;
    point = (int *)temp;

    First, we assign the address some_address to the pointer int *point. Next,
    we type cast the value in point (the address of some_address) to force a
    change to unsigned long, and then we store the resulting value in temp.
    Because it is legal to divide an unsigned long, we divide temp by 2. Then
    we cast that result, still an unsigned long, to the type int * (meaning
    pointer to an int). Finally, we place the correctly typed new value in
    point.

    The PEEK.C program (Listing 8-5) illustrates this use of type casting.
    PEEK.C asks the user for a number, then treats that number as an address
    and shows you the value stored at that address.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* peek.c    -- demonstrates how to cast an int to a  */
    /*              pointer                               */

    main()
    {
        char *mem_ptr;
        unsigned int address;

        while (1)
            {
            printf("Examine what memory location?\n");
            printf("Enter location in decimal: ");
            if (scanf("%u", &address) != 1)
                break;

            mem_ptr = (char *)address;   /* cast  */

            printf("The value in %u is 0x%02X\n",
                    address, (unsigned char)*mem_ptr);
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-5.  The PEEK.C program.


far Pointers

    So far, we've assumed that all pointers occupy two bytes of memory. Two
    bytes can represent only addresses in the range 0 through 65535, howeverâ”€â”€
    not nearly enough to reference every location in the latest PCs.
    Fortunately, QuickC provides a 4-byte pointer, called a far pointer, that
    can address more than four billion bytes of memory.

    In particular, far pointers are useful for directly accessing the text
    screen's memory and for producing sophisticated graphics programs. In this
    section we'll show you how to manipulate the text screen of a graphics
    adapter.

    To declare a far pointer, merely add the keyword far to the pointer
    declaration, as follows:

    int far *screenp;

    We must use a far pointer to access screen memory because that memory is
    located at 0xB000000 (for machines with CGA) or 0xB800000 (for machines
    with EGA or VGA), locations that clearly will not fit into a 2-byte
    pointer (two bytes can hold only four hex digits, not eight). To place
    this hexadecimal constant into a far pointer, use the following type cast:

    screenp = (int far *)0xB000000;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€CGA
    screenp = (int far *)0xB800000;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€EGA or VGA

    This tells the compiler to handle the constant 0xB000000 (or 0xB800000) as
    a far address and to assign that address to the far pointer variable
    screenp.

    The SCRINV.C program (Listing 8-6) demonstrates a simple technique for
    manipulating text screen memory. Every time you press a key, the screen
    flips over. (Type Q to quit.) In the listing, adjust the constant assigned
    to screenp to suit your hardware: For EGA or VGA, replace 0xB000000 with
    0xB800000.

    This program uses a pointer as if it were an array. Although we declare
    screenp as a far pointer:

    int far *screenp;

    we reference its elements using an offset in square brackets, as follows:

    temp = screenp[i];

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    Be careful when casting pointers to integers. You should always type cast
    to an unsigned long because that type will be large enough to hold all
    addresses. Specifying unsigned will prevent addresses from being (wrongly)
    considered negative, which could lead to incorrect results.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* scrinv.c  --  using a far pointer to access text   */
    /*               screen memory                        */

    #define ROWS 25
    #define COLS 80

    main()
    {
        int far *screenp;
        int temp, i;

        do
            {
            /* use 0xB800000 for EGA or VGA */
            screenp = (int far *)0xB000000;

            for (i = 0; i < ((ROWS*COLS)/2); ++i)
                {
                temp = screenp[i];
                screenp[i] = screenp[(ROWS*COLS)-i-1];
                screenp[(ROWS*COLS)-i-1] = temp;
                }
            } while (getch() != 'Q');

    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-6.  The SCRINV.C program.


Functions That Return Addresses

    In Chapter 6, we demonstrated that functions can return values and that
    those values are of type int unless you declare otherwise. You can also
    declare functions that return addresses. The C library contains many
    functions of this type, and your functions can also take advantage of the
    speed and compactness this procedure offers.

    You declare a function that returns an address the way you declare a
    pointer variableâ”€â”€with a type, a *, and a name. For example, the following
    function returns the address of a char type:

    char *function(int arg)
    {

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    We declared screenp as a pointer to an int because each character on your
    PC text screen is represented by two bytes of informationâ”€â”€one byte is the
    character and the other is that character's attribute (normal, blinking,
    inverse, etc.). (We will discuss this organization and the various
    attributes in Chapter 14.)
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    This is like using a function as a pointer. Let's try another example.
    Examine the function Range() in the following fragment from an upcoming
    program.

    char *Range(int key)
    {
        static char  k2[]   = {'a', 'b', 'c'},
                        k3[]   = {'d', 'e', 'f'},
                        k4[]   = {'g', 'h', 'i'};
        char *kp;

        if (key == 2)
            {
            return (k2);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Address of k2
            }
        else if (key == 3)
            {
            return (&k3[0]);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Address of k3
            }
        kp = k4;
        return (kp);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Return value of a pointer, an address
    }

    This example demonstrates that you can return an address in three ways: as
    an array name (k2), as the address of the first element in an array
    (&k3[0]), or as a pointer (kp).

    Now let's call the above function from another named main():

    main()
    {
        char *keys;
        extern char *Range();â”€â”€â”€â”€â”€â”€â”€â”€Range will return the address of a char

    Notice that you can only use the return value of Range() after you
    correctly declare it, both in its own declaration and in (or before) any
    functions that call it.

    You can use a pointer value returned by a function the same way you use a
    pointerâ”€â”€with one exception. The address returned by a function is an
    rvalue: Thus, you can neither place it to the left of the assignment
    operator nor change it by computation. The following examples illustrate
    three correct ways to use the value returned by Range():

    keys = Range(2);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Address assigned to keys (a pointer)

    printf("%cn", Range(2)[1]);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Address used as an array

    printf("%cn", *(Range(2)+1));â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Address used as a pointer

    The first example assigns the address value returned by Range() to a
    pointer variable (keys). The second example uses the address returned by
    Range() as if it were an array, printing the second element. The third
    example uses the address returned by Range() as if it were a pointer,
    printing the value stored in that address plus one.

    The PHWORD.C program (Listing 8-7) asks the user for a telephone number
    and then, using the letters of the telephone dial, prints out all the
    possible words that can be made from that number.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* phword.c   --  generates all the possible words     */
    /*                in a phone number; demonstrates      */
    /*                functions that return addresses      */

    #define MAXD (7)    /* 7 digits max */

    main()
    {
        int digits[MAXD], ndigits = 0, line = 0;
        char *letters;
        signed char digit;
        int a, b, c, d, e, f, g;
        extern char *Range();

        printf("Enter Phone Number (7 digits): ");
        do
            {
            digit = getch() - '0';
            if (digit == ('-' - '0'))
                continue;
            if (digit < 0 || digit > 9)
                {
                printf("\nAborted: Nondigit\n");
                return(1);
                }
            digits[ndigits++] = digit;
            printf("%d", digit);
            } while (ndigits < 7);
        printf("\n");

        for( a = 0; a < 3; ++a)
        for( b = 0; b < 3; ++b)
        for( c = 0; c < 3; ++c)
            for( d = 0; d < 3; ++d)
            for( e = 0; e < 3; ++e)
            for( f = 0; f < 3; ++f)
            for( g = 0; g < 3; ++g)
                {
                printf("%c", Range(digits[0])[a]);
                printf("%c", Range(digits[1])[b]);
                printf("%c", Range(digits[2])[c]);
                printf("%c", Range(digits[3])[d]);
                printf("%c", Range(digits[4])[e]);
                printf("%c", Range(digits[5])[f]);
                printf("%c", Range(digits[6])[g]);
                printf("\n");
                if (++line == 20)
                    {
                    printf("Press any key for more");
                    printf(" (or q to quit): ");
                    if (getch() == 'q')
                        return (0);
                    printf("\n");
                    line = 0;
                    }
                }
    }

    char *Range(int key)
    {
        static char keys[10][3] = {
            {'0', '0', '0'},
            {'1', '1', '1'},
            {'a', 'b', 'c'},
            {'d', 'e', 'f'},
            {'g', 'h', 'i'},
            {'j', 'k', 'l'},
            {'m', 'n', 'o'},
            {'p', 'r', 's'},
            {'t', 'u', 'v'},
            {'w', 'x', 'y'}
        };

        return (keys[key]);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-7.  The PHWORD.C program.

    The PHWORD.C program also illustrates another point about arrays. When you
    reference a multidimensional array with only a partial list of offsets,
    the value generated is the address of the portion you referenced. Thus,
    although keys in Range() is a two-dimensional array, referencing with only
    a single dimension, as follows:

    return (keys[key]);

    yields the address of only the row specified. In other words, it yields
    the address of a one-dimensional array that is a subset of the
    two-dimensional array.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    The extern keyword tells QuickC that the variable or function named will
    be found elsewhere, either later in the current file or in another file
    that you plan to compile separately. It can also be used to tell QuickC
    that you plan to use a variable found in a library routine.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Notice in PHWORD.C that main() screens your telephone number for illegal
    characters. The function Range() would be more portable if we checked for
    illegal values inside of it and returned an error code. The trick is to
    return an error address that is always illegal. Defined in the standard
    header file stdio.h is the perfect value to convey address errorsâ”€â”€NULL.
    This special zero address value is guaranteed to be illegal. By using NULL
    rather than 0, you ensure the portability of your programs.

    The following is a rewrite of Range() that uses NULL:

    #include <stdio.h>       /* for NULL */

    char *Range(int key)
    {
        static char keys[10][3] = ...

        if (key < 0 || key > 9)
            {
            return (NULL);
            }

    Now Range() does its own error checking. It can return NULL, even though
    it is declared char *, because NULL is a special address value that is
    illegal regardless of the expected return type.


Dynamic Arrays

    In the previous chapter, we explained that arrays in C must be
    dimensioned with integer constant expressions, and therefore you cannot
    change the size of a declared array. But now that you have pointers at
    your disposal, the situation is somewhat different. By using standard C
    Library routines, you can allocate memory while the program is running
    (that is, "dynamically") and thus create arrays "on the fly." You can also
    use other C library routines to change the size of dynamically allocated
    arrays, again while the program is running.

    The ability to create, change the size of, and discard arrays from within
    your running program opens a host of new programming possibilities. It
    frees your program from having to know ahead of time how many lines of
    text a user will type, for example, or how many characters it will receive
    via a modem. When you design a database, it is clearly better to allow
    users to add fields at will, rather than restricting them to a
    predetermined record structure. Games are generally more interesting when
    players can add characters at any time. Text editors are more powerful
    when the user can interactively define keyboard macros.

    The standard library routines for the dynamic allocation and reallocation
    of memory are listed in Table 8-1 on the following page. The return types
    for these functions are declared in the header file <malloc.h>. If you
    look at those declarations (using the Include option on the View menu),
    you will see that they are all declared as pointer type void *. This new
    type, when applied to a function's return value, permits the returned
    address to be legally assigned to any type of pointer. This makes it very
    easy for us to create dynamic arrays of any type.

    Table 8-1 Memory Allocation Library Routines
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    malloc()           Memory allocate
    calloc()           Computed memory allocate
    realloc()          Reallocate memory
    free()             Free allocated memory
    sbrk()             Request memory from system
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

The malloc() Memory Allocation Function

    The malloc() function is the most frequently used library allocation
    function. It takes a single argument, the number of bytes of memory you
    wish to allocate (reserve), and returns the address of that memory. If
    malloc() cannot find as much free memory as you specify, it returns a NULL
    value. The correct form for using malloc() (including a check for failure)
    follows:

    #include <stdio.h>â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€For NULL
    #include <malloc.h>â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€For malloc() declaration
    ...
    int *iptr;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€To receive address
    size_t bytes = 100;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Number of bytes

    if ((iptr = malloc(bytes)) == NULL)
        {
        /* handle error here */
        }
    printf("Now let's fill the array iptr[]\n");

    The parentheses in the malloc() expression force the result of the
    assignmentâ”€â”€the value of iptrâ”€â”€to be compared to NULL. If malloc succeeds
    in allocating memory, iptr contains the address of that dynamically
    allocated memory.

    Because the value of iptr evaluates as an address, you can use iptr as if
    it were an array. For example, the following expression is perfectly
    legal:

    iptr[5]

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    Note in the above example that we declare bytes as type size_t. This type
    is defined in <malloc.h> as an unsigned int for QuickC. Because the type
    size_t is a part of the ANSI standard, you should use it rather than
    unsigned int to ensure the portability of your programs.

    However, to transport programs written with size_t to different machines,
    you might need to use #define to make size_t an unsigned int.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    The TOTAL.C program (Listing 8-8) asks you to type numbers, one per line,
    and dynamically builds an array of those numbers. When you enter a
    non-numeric character, the program displays your list of numbers from the
    array and totals them.

    This program introduces two new elements to our memory allocation
    routines: free() and realloc(). The free() function releases memory that
    you reserve with malloc() or realloc(). The realloc() function copies
    memory into a larger or smaller block of memory.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* total.c  -- how to build an array on the fly     */

    #include <stdio.h>         /* for NULL   */
    #include <malloc.h>        /* for size_t */

    main()
    {
        int *iptr, count = 0, i, total;
        size_t bytes = sizeof(int);

        /* Start the array with room for one value. */
        if ((iptr = malloc(bytes)) == NULL)
            {
            printf("Oops, malloc failed\n");
            exit(1);
            }

        printf("Enter as many integer values as you want.\n");
        printf("I will build an array on the fly with them.\n");
        printf("(Any non-number means you are done.)\n");

        while (scanf("%d", &iptr[count]) == 1)
            {
            ++count;
            /* Enlarge the array. */
            if ((iptr = realloc(iptr,bytes*(count+1))) == NULL)
                {
                printf("Oops, realloc failed\n");
                exit(1);
                }
            }
        total = 0;
        printf("You entered:\n");
        for (i = 0; i < count; i++)
            {
            printf("iptr[%d] = %d\n", i, iptr[i]);
            total += iptr[i];
            }
        printf("\nTotal: %d\n", total);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-8.  The TOTAL.C program.

    The free() function takes a single argument, the address returned by
    malloc() or realloc(), and uses it to release that memory. Note that if
    you pass free() an address other than one returned by one of these
    functions, your program may crash.

    The realloc() function takes two arguments: first, the address returned by
    malloc() or one returned from a previous call to realloc(); and second, a
    new size in bytes. The function copies the contents of the old memory to
    the new memory (truncating if the new size is smaller) and returns the
    address of the new memory. Like malloc(), realloc() returns a NULL address
    if it fails.

The calloc() Memory Allocation Routine

    QuickC supplies a companion routine to malloc() called calloc() (for
    "calculated allocate"). The calloc() function also allocates memory, but
    with a twist that makes it ideal for arrays. Instead of merely allocating
    a number of bytes, it takes a pair of arguments: the number of items and
    the number of bytes (sizeof) of each item. The form for using calloc() is
    as follows:

    address = calloc(items, sizeof(item));

    Like malloc(), calloc() returns the address of successfully allocated
    memory or NULL if not enough memory is available.

    The advantage offered by calloc() is that it initializes allocated memory
    to zero values, whereas malloc() can leave memory that is filled with
    garbage. The free() function also releases memory reserved by calloc().

The sbrk() Memory Extension Function

    The malloc() family of routines keeps track of all the memory you
    allocate. These routines use extra bytes to keep a list of allocated
    memory and still more bytes to ensure that all addresses are even. If your
    program is short on space, those pieces of memory might be too valuable to
    waste on mere housekeeping. These functions also need to search through
    lists of available memory to find blocks of the requested size. If you
    have allocated many chunks of memory, that search slows the execution of
    your program.

    QuickC's sbrk() function offers a quick and efficient way to allocate
    memory when you don't need to keep track of how much has been allocated.
    When you load a program into memory, it is arranged as shown in Figure
    8-4. The address of the end of the data segment serves to record the
    highest memory location you can legally access. The sbrk() function
    requests that the highest location be extended by a specified number of
    bytes, as follows:

    address = sbrk(bytes);

    The value returned by sbrk() is the address of the old limit before it was
    extended (in other words, the address of the first byte of the newly
    acquired memory). The address of the first byte beyond the new memory
    allocation then replaces the previously stored value.

                â”Œ- - - - - - - - - - -â”€â”â—„â”€â”€â”€New highest after sbrk()
                |                      |
                |                      |
                â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤â—„â”€â”€â”€Offset from DS
                â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€Highest memory location
                â”‚                      â”‚    your program can use
                â”‚                      â”‚
                â”‚        DATA          â”‚â”€â”€â”€â”€Uninitialized data
                â”‚                      â”‚
                â”‚                      â”‚
                â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚                      â”‚
                â”‚        DATA          â”‚â”€â”€â”€â”€Initialized data
                â”‚                      â”‚
                â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚                      â”‚
        â”‚       â”‚                      â”‚
        â”‚       â”‚        CODE          â”‚â”€â”€â”€â”€Your program's code
        â”‚       â”‚                      â”‚
        â”‚       â”‚                      â”‚
    Increasing  â”‚                      â”‚
    memory      â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜â—„â”€â”€â”€DS

    Figure 8-4. The sbrk() function lets you extend the limit of accessible
    memory.

    Because sbrk() returns an address of -1 on failure, the full call to
    sbrk(), including an error check, is as follows:

    #include <malloc.h> /* for size_t */
    ...
    int *iptr;
    size_t bytes = 100;
    ...
    if ((iptr = sbrk(bytes)) == (int *)-1)
        {
        /*handle error here */
        }
        /* you have 100 bytes at the address in iptr */

    Note that we must typecast the -1 to (int *) so that the comparison will
    be to the same type as iptr.

    The TOTAL2.C program (Listing 8-9 on the following page) uses sbrk() to
    transform the earlier TOTAL.C program into an adding machine of unlimited
    capacity. We can use sbrk() in TOTAL2.C because we only take memory and
    never release or exchange any. Because sbrk() extends memory continuously,
    our array always remains intact. With malloc(), on the other hand, memory
    may not be allocated continuously, so you must call realloc() to enlarge
    and possibly move your array.

    Unfortunately, giving back pieces of memory that you acquired with sbrk()
    requires advanced programming expertise. If you need to juggle memory
    (taking, then giving back part, and so on), malloc() and realloc() are
    much easier to use. Do not, however, mix sbrk() and the malloc() routines
    in the same program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* total2.c -- how to build an array on the fly       */
    /*             using sbrk()                           */

    #include <stdio.h>        /* for NULL   */
    #include <malloc.h>       /* for size_t */

    main()
    {
        int *iptr, count = 0, i, total;
        size_t bytes = sizeof(int);

        /* Start the array with room for one value. */
        iptr = sbrk(0);
        if (sbrk(bytes) == (int *)-1)
            {
            printf("Oops, sbrk failed\n");
            exit(1);
            }

        printf("Enter as many integer values as you want.\n");
        printf("I will build an array on the fly with them.\n");
        printf("(Any non-number means you are done.)\n");

        while (scanf("%d", &iptr[count]) == 1)
            {
            ++count;
            /* Enlarge the array. */
            if (sbrk(bytes) == (int *)-1)
                {
                printf("Oops, sbrk failed\n");
                exit(1);
                }
            }
        total = 0;
        for (i = 0; i < count; i++)
            total += iptr[i];
        /* just print the total this time */
        printf("%d\n", total);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-9.  The TOTAL2.C program.


Advanced Pointer Techniques

    Perhaps you've heard horror stories about C pointers and incomprehensible
    code. Well, some of those stories are true. Reading and understanding
    poorly written code is like trying to untangle a plate of spaghetti. C
    gives you the freedom to design many types of strange but useful
    constructs. But C also gives you the freedom to design the
    incomprehensible. This section discusses some of C's magnificent but
    potentially arcane constructsâ”€â”€those dealing with the more elaborate and
    sophisticated uses of pointers.

Arrays of Pointers

    C lets you create arrays of any type of elements. Thus, you can even
    create an array whose elements are pointers. For example, to create an
    array of 10 pointers, in which each item is a pointer to a float, simply
    declare the following:

    float *array_name[10];

    The * preceding the array name in this declaration tells the compiler that
    the array is an array of pointers; therefore, each element holds an
    address. The float signifies that all pointers will point to float
    variables.

    You can use this technique for speeding up sorting routines, for example.
    Because an address on a PC occupies only two bytes (except for far
    pointers), while the data it points to occupies four bytes (for a float),
    it's faster to exchange two 2-byte addresses than to exchange the data.
    The advantage offered by arrays of pointers becomes even more evident when
    we use them with strings in the next chapter.

    The REVERSE.C program (Listing 8-10 on the following page) reads in lines
    of characters. The addresses of those lines are stored in an array of
    pointers to char. (See Figure 8-5.) An empty input line causes the lines
    of text pointed to by the array of pointers to be printed in reverse
    order.

                            cptrs[]
                            â”Œâ”€â”€â”€â”€â”€â”
    Pointer to first lineâ”€â”€â”€â”€â”‚     â”‚â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºThis is the text
                            â”œâ”€â”€â”€â”€â”€â”¤
    Pointer to second lineâ”€â”€â”€â”€â”‚     â”‚â”€â”€â”€â”€â”€â”    that we typed in.
                            â”œâ”€â”€â”€â”€â”€â”¤     â”‚
                    etc.    â”‚     â”‚â”€â”€â”€â” â””â”€â”€â”€â”€â”€â–ºIt will be reve
                            â”œâ”€â”€â”€â”€â”€â”¤   â”‚
                            â”‚     â”‚â”€â”€â”â””â”€â”€â”€â”€â”€â–ºrsed. Line 3 is
                            â”œâ”€â”€â”€â”€â”€â”¤  â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                            â”‚     â”‚â”€â”€â”€â”€â”€â”    here. Line 4 is
                            â”œâ”€â”€â”€â”€â”€â”¤     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                            â”‚     â”‚â”€â”€â”€â”€â”€â”    here. Line 5 is
                            â”œâ”€â”€â”€â”€â”€â”¤     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                            â”‚     â”‚â”€â”€â”€â”€â”€â”    Here. And so on...
                            â”œâ”€â”€â”€â”€â”€â”¤     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                            â”‚     â”‚
                            â”œâ”€â”€â”€â”€â”€â”¤           Continuous memory
                            â”‚     â”‚           allocated with srbk()
                            â””â”€â”€â”€â”€â”€â”˜
                            Array of
                            pointers

    Figure 8-5. An array of pointers, each element of which contains a line of
    text in allocated memory.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* reverse.c -- demonstrates an array of pointers     */
    /*              by reversing lines of text            */

    #include <stdio.h>        /* for NULL   */
    #include <malloc.h>       /* for size_t */

    #define MAXL 20

    main()
    {
        char *cptrs[MAXL];            /* array of pointers */
        char *cp;
        int count, i, j, ch;
        extern char *Getbyte();

        printf("Type in several lines of text, and I will\n");
        printf("print them back out in reverse order.\n");
        printf("(Any blank line ends input):\n");

        for (i = 0; i < MAXL; ++i)
            {
            cp = Getbyte();
            cptrs[i] = cp;        /* assign address to pointer */
            count = 0;
            while ((ch = getchar()) != '\n')  /* gather line */
                {
                *cp = ch;
                cp = Getbyte();
                ++count;
                }
            *cp = '\0';
            if (count == 0)        /* all done if blank line */
                break;
            }
        printf("---------<reversed>---------\n");
        for (j = i-1; j >= 0; --j)
            {
            printf("%s\n", cptrs[j]);
            }
    }

    char *Getbyte(void)
    {
        char *cp;

        if ((cp = sbrk(1)) == (char *)-1)
            {
            printf("Panic: sbrk failed\n");
            exit(1);
            }
        return (cp);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-10.  The REVERSE.C program.

    The fact that we can print an array of characters with printf()
    illustrates the correspondence between arrays of char and strings. We will
    discuss that relationship in detail in the next chapter.

Pointers to Pointers

    As you have seen, a pointer is a variable whose value is an address, and
    that address is usually the location in memory of another variable.
    However, in C, that other variable can also be a pointer. There is no
    limit to how far you can extend this "pointer-to-a-pointer" relationshipâ”€â”€
    you can have pointers to pointers to pointers and so on, ad infinitum.
    Here, however, we'll minimize the danger of creating "spaghetti code" by
    restricting ourselves to pointers to pointers, sometimes referred to as
    "handles."

    Figure 8-6 illustrates the relationship of a pointer to a pointer. The
    variable pp contains as its value the address of p. The variable p in turn
    contains as its value the address of num, an ordinary integer. Because p
    points to an int, pp is a pointer to a pointer to an int.

    The following example shows how to declare a pointer to a pointer:

    int **pp, *p, num;
        â”‚     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Pointer to an int
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Pointer to a pointer to an int

    The two * characters tell the compiler that pp is a pointer to a pointer
    and holds as its value the address of another pointer.

    When accessing the values pointed to by pp, the number of *s determines
    which value is obtained. Consider the following initialization:

    p = &num;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Address of num
    pp = &p;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Address of p

                                Points to a variable
                    â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’
                    â–’                                              â–’
            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”                                         â–’
            â”‚           â”‚                                         â–¼
    Memoryâ”€â”€   621    622   623   624   625   626   627   628   629   630
    locations â”Œâ”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”
    in bytes  â”‚    629    â”‚           â”‚    621    â”‚           â”‚     3     â”‚
            â””â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”˜
                    â”‚                       â”‚                       â”‚
                    â”‚                       â”‚                       â”‚
                    p                       pp                     num
                                            â–’
                    â–’                       â–’
                    â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’â–’
                        Points to a pointer

    Figure 8-6. Pointer to a pointer: a variable whose value is the address of
    another pointer.

    The following statement yields the value stored in the address that pp
    points to:

    *pp

    Because pp points to p, *pp yields the address stored in p, that of num.
    Placing another * in front of pp:

    **pp

    tells the compiler to fetch the value stored in the pointer pointed to by
    pp. Because pp points to p, and p in turn points to num, **pp fetches the
    value of num. Thus, all three of the following yield the value stored in
    the variable num:

    **pp
    *p
    num

    One useful application for a pointer to a pointer is in traversing arrays
    of pointers. The REVERSE2.C program (Listing 8-11) is a rewrite of the
    previous REVERSE.C. In this version, we replace the final for loop with a
    while loop that decrements pp, a pointer to a pointer.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* reverse2.c -- demonstrates a pointer to a pointer  */

    #include <stdio.h>        /* for NULL   */
    #include <malloc.h>       /* for size_t */

    #define MAXL 20

    main()
    {
        char *cptrs[MAXL];
        char **pp;                    /* pointer to pointer */
        char *cp;
        int count, i, ch;
        extern char *Getbyte();

        printf("Type in several lines of text, and I will\n");
        printf("print them back out in reverse order.\n");
        printf("(Any blank line ends input):\n");

        for (i = 0; i < MAXL; ++i)
            {
            cp = Getbyte();
            cptrs[i] = cp;        /* assign address to pointer */
            count = 0;
            while ((ch = getchar()) != '\n')  /* gather line */
                {
                *cp = ch;
                cp = Getbyte();
                ++count;
                }
            *cp = '\0';
            if (count == 0)        /* all done if blank line */
                break;
            }
        printf("---------<reversed>---------\n");
        pp = &cptrs[i];
        while (pp >= cptrs)
            {
            printf("%s\n", *(pp--));
            }
    }

    char *Getbyte(void)
    {
        char *cp;

        if ((cp = sbrk(1)) == (char *)-1)
            {
            printf("Panic: sbrk failed\n");
            exit(1);
            }
        return (cp);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-11.  The REVERSE2.C program.

    This program shows that a pointer to a pointer is decremented (or
    incremented) by the number of bytes in a pointer:

    printf("%s\n", *(pp--))
                    â””â”€â”€â”¬â”€â”€â”˜
                        â””â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ The same
                    â”Œâ”€â”€â”€â”€â”€â”´â”€â”€â”
    printf("%s\n", cptrs[i--])

    Recall that the address in a pointer changes by a number of bytes that
    corresponds to the type to which it points. A char pointer changes by one
    byte, while a float pointer changes by four bytes. A pointer to a pointer
    changes by the number of bytes in an address because it points to a
    pointer, and thus to an address. Because cptrs[] is an array of pointers,
    and pp points to one of those addresses, decrementing pp causes it to
    point to the immediately preceding element in that array. Figure 8-7 on
    the following page illustrates this process.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Pointer Pointer
    Pointers are so versatile that they can contain the address of almost
    anything. However, you cannot use pointers to obtain the address of the
    following C elements: constants (such as 5); variables declared with the
    keyword register; labels (the targets of goto); and keywords (such as if,
    while, and so on).
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

                            cptrs[]
                            â”Œâ”€â”€â”€â”€â”€â”
                â”Œâ”€â”€â”€endâ”€â”€â”€â”€â”‚     â”‚â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºThis is the text
                â”‚          â”œâ”€â”€â”€â”€â”€â”¤
                â”‚  --ppâ”€â”€â”€â”€â”‚     â”‚â”€â”€â”€â”€â”€â”    that we typed in.
                â”‚          â”œâ”€â”€â”€â”€â”€â”¤     â”‚
        pp       â”‚  --ppâ”€â”€â”€â”€â”‚     â”‚â”€â”€â”€â” â””â”€â”€â”€â”€â”€â–ºIt will be reve
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”   â”‚          â”œâ”€â”€â”€â”€â”€â”¤   â”‚
    â”‚       â”‚ â”€â”€â”¤  --ppâ”€â”€â”€â”€â”‚     â”‚â”€â”€â”â””â”€â”€â”€â”€â”€â–ºrsed. Line 3 is
    â””â”€â”€â”€â”€â”€â”€â”€â”˜   â”‚          â”œâ”€â”€â”€â”€â”€â”¤  â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    Points to   â”‚  --ppâ”€â”€â”€â”€â”‚     â”‚â”€â”€â”€â”€â”€â”    here. Line 4 is
    pointer    â”‚          â”œâ”€â”€â”€â”€â”€â”¤     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚  --ppâ”€â”€â”€â”€â”‚     â”‚â”€â”€â”€â”€â”€â”    here. Line 5 is
                â”‚          â”œâ”€â”€â”€â”€â”€â”¤     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â””â”€startâ”€â”€â”€â”€â”‚     â”‚â”€â”€â”€â”€â”€â”    Here. And so on...
                            â”œâ”€â”€â”€â”€â”€â”¤     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                            â”‚     â”‚
                            â”œâ”€â”€â”€â”€â”€â”¤           Continuous memory
                            â”‚     â”‚           allocated with srbk()
                            â””â”€â”€â”€â”€â”€â”˜
                        Array of
                        pointers

    Figure 8-7. Decrementing a pointer to a pointer moves it down through an
    array of pointers.

Pointers to Functions

    It is often useful to know the address of a function. You declare a
    pointer to a function as follows:

    int (*pointer_name)();

    This declares the variable pointer_name to be a pointer *pointer_name. The
    trailing parentheses tell the compiler that the pointer *pointer_name
    contains the address of a function. The int specifies that the function
    pointed to returns an int.

    To obtain the address of a function, merely state its name. However, be
    sure you declare the function before you take its address:

    int (*funptr)();â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€A pointer to a function
    extern int Quit();â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€A function declared

    funptr = Quit;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Address of Quit() assigned to funptr

    In this example, funptr contains the address of Quit(), and we can call
    Quit() through funptr, as follows:

    *funptr();

    The preceding * tells the compiler to use the value pointed to by funptr
    (the address of Quit()). The trailing parentheses tell the compiler to
    call the function whose address we just fetched.

    The CHOOSE.C program (Listing 8-12) goes one step further by creating an
    array of pointers to functions. First, the program asks you to choose a
    menu item. Then it translates your choice into an array offset and calls
    the function whose address is stored at that offset.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* choose.c   --  an array of pointers to functions   */
    /*                used to create a menu               */

    void Choice1(), Choice2(), Choice3();

    void (*Dochoice[3])() = {Choice1, Choice2, Choice3};

    main()
    {
        int ch;

        printf("Select 1, 2 or 3: ");
        ch = getch(); putch(ch);
        ch -= '1';
        if (ch < 0 || ch > 2)
            printf("\nNo such choice.\n");
        else
            Dochoice[ch]();

    }

    void Choice1(void)
    {
            printf("\nThis is choice 1\n");
    }

    void Choice2(void)
    {
            printf("\nThis is choice 2\n");
    }

    void Choice3(void)
    {
            printf("\nThis is choice 3\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 8-12.  The CHOOSE.C program.

    Arrays of pointers to functions are best applied in interactive programs.
    Believe it or not, you'll find it easier to design word processors and
    complex games once you master this technique.

    The following example illustrates the advantage of using an array of
    pointers to functions instead of a simpler switch statement. Examine the
    following fragment from a hypothetical text processor:

    int (*commands[128])() = {
                ...
                Go_left,     /* l */
                Mark_line,   /* m */
                Next_search, /* n */
                ...
                };

    This array has 128 pointers to functions, each of which corresponds to a
    key on the keyboard. Pressing l causes Go_left() to be called, moving the
    cursor left. If the user wishes to change the meaning of the keys,
    swapping the functions of l and n, for example, you need only use the
    following:

    int (*temp)();â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Scratch pointer
    int from, to;

    from = 'l';
    to   = 'n';
    temp = commands[from];
    commands[from] = commands[to];
    commands[to] = temp;

    Here we first declare a scratch variable to be used in the swap. We
    declare it as a pointer to a function because we will be swapping pointers
    to functions. We then assign to temp the address stored in commands[from],
    where from is the offset that corresponds to the numeric value of the
    letter `n'. Because that array item is a pointer to the function
    Next_search(), we are saving the address of that function. We then copy
    the address in commands[to] into commands[from]. Finally, we assign the
    address saved in temp to commands[to]. The result of this exchange is that
    typing n now causes the Go_left() function to be called, and typing l
    causes the Next_search() function to be called, thereby reversing their
    roles.

    Contrast this flexible form of programming with an inflexible switch
    statement, such as the following:

    switch(key)
        {
        ...
        case 'l':
            Go_left();
            break;

        case 'm':
            Mark_line();
            break;

        case 'n':
            Next_search();
            break;
        ...
        }

    Clearly, a program that a user can customize is more difficult to write,
    yet a versatile program is always worth the extra effort.

Unscrambling the Spaghetti

    In the previous sections of this chapter you've seen some complicated
    declarations. You will see more of them in the chapters to follow, so it
    behooves us to establish some rules that will help us understand complex
    declarations.

    Remember: Always start reading at the inside of a declaration with the
    name (identifier); then work your way outward. For example, to unscramble
    the following declaration:

    int (*name)();

    follow the definition from the inside out: name is a pointer to a function
    of type int. Thus, this declaration is a pointer to a function that
    returns an int.

    Let's try this same technique on a different declaration:

    float (*name)[3];

    In this example, name is a pointer to an array of three float variables.
    Thus, it is a pointer to an array of three floats. Contrast that
    declaration with the following:

    float *name[3];

    Here name is an array of three pointers to float variables. This example
    is an array of three pointers to floats. The difference lies in the
    parentheses. Be sure to obey the order of precedence for operators.

    As an example of using parentheses, try to decipher the following
    declaration from CHOOSE.C:

    int (*funs[4])();

    Here the * operator has a higher precedence than the [] operators, so *
    binds to funs first. Therefore, funs is a pointer, and four such pointers
    exist in an array; these pointers point to functions that return the type
    int. Thus, the declaration is an array of four pointers to functions that
    return int.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€