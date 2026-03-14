Chapter 9  Strings

    A "string" is a sequence of ASCII charactersâ”€â”€this sentence, for example,
    is a string. Strings give your programs life by enabling them to
    communicate with the user. Nearly all programsâ”€â”€from our simple printf()
    statements to the sophisticated dialogues of complex interactive
    programsâ”€â”€use strings of one type or another.

    Unlike BASIC and Pascal, the C language has no built-in string-type
    variable. Instead, C uses the convention that a string is an array of type
    char whose final, or terminating, value is the special character '\0'â”€â”€a
    one-byte zero value. Figure 9-1 on the following page illustrates such an
    array.

    We refer to this arrangement as a convention because nothing in C prevents
    you from handling strings in another manner. For example, you might store
    strings as arrays of short variables, using one byte to hold the character
    and the other to hold the character's attributes (more on this in Chapter
    13). Or you might store strings as a value length followed by length
    number of characters. However, because you will most often handle strings
    in the conventional way, we will emphasize that method in our discussion
    of strings.

    Address of bytesâ”€â”€  9876   9877  9878  9879  9880  9881  9882  9883
    in memory          â”Œâ”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”
                        â”‚ 'H' â”‚ 'e' â”‚ 'l' â”‚ 'l' â”‚ 'o' â”‚'\n' â”‚'\O' â”‚     â”‚
                        â””â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”˜
                        â”‚                             â”‚        
                        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜        â”‚
                                    â”‚                       â”‚
                                ASCII characters        Terminating zero

    Figure 9-1. In C, a string is an array of type char terminated by a zero
    value.


Declaring and Initializing Strings

    A string is merely an array of type char, and you initialize it the same
    way you would any other array. The following example fills the char array
    named phrase with ASCII character constants that spell "Hello" followed by
    the newline character:

    char phrase[] = {'H', 'e', 'l', 'l', 'o', '\n', '\0'};

    We made this array a conventional C string by adding a terminating zero
    value (the character constant '\0'). As with all arrays, string arrays can
    be initialized only if you use the keyword static or declare them
    globallyâ”€â”€outside of all functions.

    The HELLO.C program (Listing 9-1) illustrates the proper way to
    initialize string arrays. It also demonstrates the printf() format command
    %s, which tells printf() to print the next argument as a string.

    Because zero-terminated char arrays so commonly represent strings in C,
    the language provides a built-in shorthand. When C finds text enclosed in
    full quotation marks (called string constants), it immediately stores that
    text as an array of type char and adds the terminating '\0'. This
    characteristic of C provides you an alternate way to initialize arrays.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* hello.c  --  legal ways to initialize strings as */
    /*              arrays of char values               */

    char Gphrase[] = {
        'H','e','l','l','o','\n','\0' };    /* global initialization */

    main()
    {
        static char gphrase[] = {
            'h','e','l','l','o','\n','\0' };    /* local initialization */

        printf("Global: %s", Gphrase);
        printf("Local:  %s", gphrase);

    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-1.   The HELLO.C program.

    For example, you can create the same arrays as those declared in HELLO.C
    by substituting the following lines of code:

    char Gphrase[] = "Hello\n";â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Global initialization

    static char lphrase[] = "Hello\n";â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Local initialization

    As an aid in declaring long string constants, the compiler combines
    adjacent quoted strings into a single string constant. This feature lets
    you easily initialize long strings, as in the following example:

    static char long_phrase[]  = "This is one long "
                                    "sentence that the compiler "
                                    "combines into a single string.";

    C uses the rule that if nothing but white space (spaces, tabs, or
    newlines) separates two quoted strings, those strings are concatenated to
    form a single string. Thus, the above QuickC declaration is equivalent to
    the following:

    static char long_phrase[]  =
    "This is one long sentence that the compiler combines into a single
    string.";

    Under pre-ANSI C, long string initializers can be emulated with the
    #define preprocessor directive. Recall that you can extend #define lines
    by ending each with a backslash and a newline character (that is, type \
    and press Enter). Because this #define technique is portable to all
    compilers, we will use it throughout the rest of the book:

    #define PHRASE \
    "This is one long sentence that the compiler \
    combines into a single string."

    static char long_phrase = PHRASE;

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    A Constant Reminder
    When you declare string constants, remember that it is illegal for a
    newline character to appear anywhere between full quotation marks. The
    following example is illegal:

    static char long_phrase = "This is one
    long sentence that the...";

    and results in the following QuickC error message:

    error C2001:
    newline in constant

    If you want to insert a newline character into a string constant, use the
    escape sequence for a newline character (\n) instead:

    static char long_phrase[] = "This is one \n long sentence that the ..."

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€


The String Pool and String Addresses

    QuickC copies all of a program's quoted strings into a common area of
    memory called the string pool. They are copied there, one after the other,
    in the order that they occur in the program. (Figure 9-2 illustrates this
    process.)

    The STRPOOL.C program (Listing 9-2) dumps the contents of the string pool
    to your terminal screen. Note in STRPOOL.C that any char array that ends
    with a zero value, such as Cent_string, is placed into the string pool.

    We place nonprinting characters into quoted strings as we did with
    printf()â”€â”€that is, a newline character, with \n; a carriage return, with
    \r; and a tab, with \t. Other special characters that you can place in
    string constants are the full quotation mark, with \"; the formfeed
    character, with \f; the backspace character, with \b; and the bell (beep)
    character, with \a.

    You can include any character from the PC's extended character set in a
    string constant by using a \x followed by a two-digit hexadecimal number.
    For example, \x9B is used to represent the Â¢ character. (QuickC's General
    help screens include a handy table that lists these escape sequences.)

    Note also in the program that we assigned the address of a string to a
    pointer (cp = Start). Nowhere are pointers used more heavily than with
    strings.

            Your program                              String pool
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”     â”Œâ”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€
    â”‚Â°char phrase [ ] = "Hello\n";â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â–º'H' â”‚ 'e' â”‚ 'l' â”‚ 'l' â”‚ 'o' â”‚'\n'
    â”‚Â°main ( )                      Â°â”‚     â”œâ”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€
    â”‚Â°{                             Â°â”‚  â”Œâ”€â”€â”¼'\O'â”€â”¼â–º'T' â”‚ 'y' â”‚ 'p' â”‚ 'e' â”‚ ' '
    â”‚Â°  printf("Type in a line of");â”€â”¼â”€â”€â”˜  â”œâ”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€
    â”‚Â°  printf(" text and I will");â”€â”€â”¼â”€â”€â”  â”‚ 'i' â”‚ 'n' â”‚ ' ' â”‚ 'a' â”‚ ' ' â”‚ 'l'
    â”‚Â°  .                           Â°â”‚  â”‚  â”œâ”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€
    â”‚Â°  .                           Â°â”‚  â”‚  â”‚ 'i' â”‚ 'n' â”‚ 'e' â”‚ ' ' â”‚ 'o' â”‚ 'f'
    â”‚Â°  .                           Â°â”‚  â”‚  â”œâ”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€
    â”‚Â°                              Â°â”‚  â””â”€â”€â”¼'\O'â”€â”¼â–º' ' â”‚ 't' â”‚ 'e' â”‚ 'x' â”‚ 't'
    â”‚Â°                              Â°â”‚     â”œâ”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     â”‚ ' ' â”‚ 'a' â”‚ 'n' â”‚ 'd' â”‚ ' ' â”‚ 'I'
                                            â”œâ”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€
                                            â”‚ ' ' â”‚ 'w' â”‚ 'i' â”‚ 'l' â”‚ 'l' â”‚'\O'
                                            â”œâ”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€
                                            |     |     |     |     |     |
                                            |     |     |     |     |     |

    Figure 9-2. Quoted string constants are placed one after the other into
    the string pool.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* strpool.c  -- dumps the string pool to show how    */
    /*               quoted strings are stored            */

    #define PHRASE \
    "This is one long sentence that the compiler \
    combines into a single string."

    char Start[]        = "start";
    char Long_phrase[]  = PHRASE;
    char Short_phrase[] = "This is a short phrase";
    char Cent_string[]  = "\x9B";

    main()
    {
        static char local_phrase[] = "This is local";
        char *cp;

        printf("Dump of the string pool:\n");
        printf("-----------------------\n");

        printf("\"");                /* print leading quote */

        /*
        * Note that the address of a string can be
        * assigned to a pointer: cp = Start
        */
        for (cp = Start; *cp != '^'; ++cp)
            {
            if (*cp == '\0')        /* print '\0' as a quote */
                printf("\"\n\"");
            else if (*cp == '\n' )  /* print '\n' as '\' 'n' */
                printf("\\n");
            else
                printf("%c", *cp);
            }
        printf("^");                /* marks end */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-2.  The STRPOOL.C program.


Pointers and Initialized Strings

    In the last chapter we assigned the address of an array to a pointer. We
    can also initialize a pointer to char with the address of a quoted string
    constant, as follows:

    char *str = "This is a phrase";

    This example initializes the char pointer *str to contain the address of
    the quoted string constant. Because the compiler places all string
    constants into the "string pool," the address in *str is that of the
    letter "T" (the first character of the char array) in the string pool.

    Recall that an array declaration creates an rvalue and a pointer
    declaration creates an lvalue. Consider the following declarations:

    char ary[] = "This is a phrase";
    char *str = "This is another";

    The ary[] declaration creates an rvalue (an address reference, such as a
    label) that cannot be changed with calculations.

    The *str declaration, on the other hand, creates an lvalue (a pointer
    variable whose value is an address), which can be changed with
    calculations. You can, for example, increment the pointer as follows:

    ++str;

    The distinction between lvalue and rvalue can be a confusing one for
    beginning C programmers. Remember that an array name (such as ary[]) is a
    fixed location and cannot be changed; a pointer (such as *str) is a
    variable and can be changed.

    The BIFFRED.C program (Listing 9-3) demonstrates that you can use
    pointers to manipulate strings in the string pool. Examine the program
    before you run it. Can you predict what it will do?

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* biffred.c  --  strings in the string pool can be */
    /*                manipulated via pointers          */

    char Start[] = "start";

    main()
    {
        char *cp;
        int pass;

        for (pass = 0; pass < 2; ++pass)
            {
            printf("My name is FRED\n");

            cp = Start;

            while (*cp != 'F')
                ++cp;

            *cp   = 'B';
            *++cp = 'I';
            *++cp = 'F';
            *++cp = 'F';
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-3.  The BIFFRED.C program.


Formatting Strings with printf()

    So far, we've used printf() to print and format numbers (int with %d and
    float with %f, for example), individual characters with %c, and quoted
    strings with %s. The ability of printf() to print strings, however, goes
    far beyond the mere echoing of quoted string constants. In the following
    example:

    printf("%s\n", ary);

    the expression ary can be the address of any char type array that ends
    with the character constant value '\0'. It can be a quoted string constant
    such as

    printf("%s\n", "This is a phrase");

    or the address of a string from either a char array or a value in a
    pointer, as in the following examples:

    char *str, ary[] = "This is a phrase";

    str = ary;

    printf("%s\n", ary);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Address of an array
    printf("%s\n", str);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Value in a pointer

    Because all quoted strings are placed into the string pool and replaced
    with their starting address in that string pool, it follows that the
    format specification in the control string of this example:

    printf("%s\n", str);
            â””â”€â”€â”¬â”€â”˜
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Control string

    can also be expressed as either an array address or the value in a
    pointer, as follows:

    char *str, ary[] = "This is a phrase.";
    char *cp,  ctl[] = "%s\n";

    str = ary;
    cp  = ctl;

    printf(ctl, ary);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Addresses of arrays
    printf(cp, str);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Pointer values
    printf(ctl, str);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Mixture of the two

    The CONTROL.C program (Listing 9-4 on the following page) demonstrates
    this equivalence. This program asks you to type either an l or an r, and
    then it prints out a string with the corresponding left or right
    justification.

    CONTROL.C lets you see how the printf() format specifier %s is used to
    format strings. The various options you can use with %s are summarized in
    Table 9-1 on the following page. You can also combine them as in the
    following statement, which prints the first four letters of computer
    right-justified in a 25-character field.

    printf("%25.4s\n", "computer");

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* control.c  --  demonstrates string justification */
    /*                using printf()                   */

    char Some_text[] = "Some Text";
    char Left_control[] =    "<<%-15s>>";
    char Right_control[] =    "<<%15s>>";

    main()
    {
        char ch;

        while (1)
            {
            printf("Select l)eft r)ight or q)uit: ");
            ch = getch();
            putch(ch);

            printf("\n\n");
            switch((int) ch)
                {
                case 'l':
                case 'L':
                    printf(Left_control, Some_text);
                    break;
                case 'r':
                case 'R':
                    printf(Right_control, Some_text);
                    break;
                case 'q':
                case 'Q':
                    exit (0);
                default:
                    printf("Huh?");
                    break;
                }
            printf("\n\n");
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-4.  The CONTROL.C program.

    Note: In these format specifiers, num must be a decimal integer. You can
    combine the last option, %.nums, with any of the others, producing, for
    example, %25.5s.

    Table 9-1 Variations of the printf() %s Specifier
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    %s          Prints the string exactly as it is
    %nums       Prints the string right-justified in a field of width num
    %-nums      Prints the string left-justified in a field of width num
    %.nums      Prints num characters of string
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€


String Input and Output

    The standard C Library contains several functions specifically designed to
    facilitate input and output of strings. Here we discuss some that read
    from your keyboard or print to your screen. The next chapter ("Managing
    Files") deals with file-handling counterparts to these functions. In
    Chapter 13, we will present additional routines that directly access the
    keyboard and screen hardware.

String Input with scanf()

    We've already used scanf() several times: Now let's discuss it in detail.
    The scanf() function uses the same % specifiers that printf() does, but it
    uses them to read values, not to print them. Unfortunately, scanf()
    handles strings a little differently than does printf(). Where printf()
    prints the entire string to a terminating '\0', scanf() reads only
    space-delimited words of text. That is, for each %s in its control string,
    scanf() reads all characters up to, but not including, space, tab, or
    newline. Therefore, scanf() is best used for reading words rather than
    lines of text.

    The scanf() routine, when used with %s to read words of text, takes the
    form

    scanf("%s", buf);

    where buf is the address of a char array (buffer) into which scanf()
    places the text it reads from the keyboard. The array buf can be either a
    char array or a pointer to memory created by malloc(). (Note that you do
    not need to use an ampersand with an array name.) The scanf() function
    appends a terminating '\0' to the text in buf.

    The short SCANLINE.C program (Listing 9-5 on the following page)
    illustrates a simple way to use scanf() for reading words of text from the
    keyboard. It asks you to type in a line of text and then uses scanf() to
    print the words of that text, one word per line.

    When you run SCANLINE.C, notice that it prints nothing until you press the
    Enter key. This is because scanf() is a "buffered I/O" routine. It reads
    from the standard input (the keyboard), but it "sees" nothing until you
    "flush the standard input buffer" by pressing the Enter key. (We discuss
    this concept of buffered versus unbuffered I/O in the next chapter.)

    The scanf() function provides two variations for the %s specifier. (See
    Table 9-2.) These let you read more than individual words.

    Table 9-2 Variations of the scanf() %s Specifier
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    %nums       Reads num characters including space, tab, or newline
                characters (Specify num as a decimal integer.)
    %[range]    Reads a specified range of characters
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* scanline.c  -- demonstrates how scanf() reads  */
    /*                the individual words of a line  */

    #define INTRO \
    "Type in lines of text. They will be printed out\n\
    one word per line, thus demonstrating scanf().\n\
    (Type Ctrl-Z to Quit)\n"

    main()
    {
        char buf[512];    /* should be big enough */

        printf(INTRO);

        /*
        * scanf() returns the number of items
        * its control string matched
        */
        while (scanf("%s", buf) == 1)
            {
            printf("%s\n", buf);
            }

    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-5.  The SCANLINE.C program.

    The following example reads 127 characters from the keyboard and places
    them into the array buf:

    char buf[128];

    scanf("%127s", buf);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€%nums form
    buf[127] = '\0';

    This form of scanf() has two disadvantages. First, because newline
    characters can be read into buf, you can't easily tell whether buf
    contains a complete line or a partial line or a number of lines. Second,
    because this form does not append a terminating '\0' to the text, you must
    add it yourself.

    For better control, use the more complex scanf() %[range] directive. Here
    range is any list of characters that you want to include in buf. The
    following example:

    scanf("%[0123456789]", buf);

    reads in only the digits 0 through 9. Anything else causes scanf() to stop
    reading and terminate buf with a '\0'.

    A more useful variation of the %[range] directive can be constructed using
    the ^ character. When you use a ^ as the first character in range, scanf()
    reads all characters up to, but not including, any characters in range and
    stops reading at the first excluded character. This version of scanf()
    also appends a terminating '\0' to the characters it reads. The following
    example shows how to use this variation:

    scanf("%[^\n]", buf);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Read all but a newline
    scanf("%[\n]", dummy);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Read only a newline

    The first line tells scanf() to read all characters up to, but not
    including, the newline character and to place those characters into buf.
    The second line tells scanf() to read only a newline character (the one
    that terminated the first scanf()) and to place it into dummy. The scanf()
    function can be tricky to use (witness the need for the second statement),
    but with practice, you will find it a valuable and powerful programming
    tool.

    The SCRANGE.C program (Listing 9-6) summarizes the scanf() function. It
    prompts for, and reads in, several lines of text, displaying exactly what
    scanf() reads as it executes.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* scrange.c  --  illustrates scanf()'s control */
    /*                directives                    */

    main()
    {
        char buf[512],    /* should be big enough */
            dummy[2];    /* for \n and \0        */
        int  num;

        do
            {
            printf("Running:\n");
            printf("\tscanf(\"%%d\", &num);\n");
            printf("\tscanf(\"%%[^\\n]\", buf);\n");
            printf("\tscanf(\"%%[\\n]\", dummy);\n");

            printf("\nType enough to satisfy this:\n");
            printf("(Set num equal to zero to quit)\n");

            scanf("%d", &num);
            scanf("%[^\n]", buf);
            scanf("%[\n]", dummy);

            printf("\n\tnum = %d\n", num);
            printf("\tbuf[] = \"%s\"\n", buf);
            printf("\n\n");

            } while (num != 0) ;

    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-6.  The SCRANGE.C program.

Lines of Text with gets() and puts()

    Although we can use variations of scanf() to read lines of text, the
    QuickC library contains a pair of routines specifically tailored for
    reading and writing strings as lines of text. A line of text, in this
    case, is any string that includes a terminating newline. This is the most
    natural form of text entry because it corresponds to a line of text on the
    screen.

    Although the newline, '\n', is used throughout C to represent the end of a
    line of text, it does not correspond to the characters produced or
    expected by your hardware. The Enter key, for example, actually produces
    the '\r' character. And printing a '\n' to your screen moves the cursor
    down but not to the left on the screen. Fortunately, scanf() and gets()
    convert an Enter keypress ('\r') to a newline ('\n'), and both printf()
    and puts() convert a newline ('\n') into a carriage return/linefeed
    combination ('\r' '\n') when writing to your screen.

    The gets() (pronounced "get s") function reads all typed characters up to
    and including a newline (generated when you press Enter) and places those
    characters into a char array. The newline is then replaced with a '\0' to
    form a C string. The puts() (pronounced "put s") function prints a string
    on the screen and adds a newline to the end.

    The DIALOG.C program (Listing 9-7) uses gets(), puts(), and printf() to
    carry on a simple conversation. Note that because the gets() function
    returns NULL if it fails, we must use the directive #include <stdio.h> to
    incorporate the definition of NULL.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* dialog.c  -- a conversation using gets() and puts()  */

    #include <stdio.h>        /* for NULL and BUFSIZ */

    #define THE_QUESTION \
    "And what is your view on the current price of corn\n\
    and the stability of our trade import balance?"

    main()
    {
        char name[BUFSIZ],
            buf[BUFSIZ];
        extern char *gets();

        name[0] = '\0';        /* clear the name */

        puts("\n\nHi there. And what is your name?");

        if (gets(name) != NULL && name[0] != '\')
            {
            printf("\nPleased to meet you, %s.\n", name);
            puts(THE_QUESTION);
            /*
            * force an extra <enter> before replying
            */
            do
                {
                if (gets(buf) == NULL)
                    break;

                } while (*buf != '\0');        /* wait for empty line */

            puts("Sorry. I needed to think about that.");
            printf("Nice talking to you, %s.\n", name);
            }
        else
            puts("How rude!");

        puts("Goodbye.");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-7.  The DIALOG.C program.


String Manipulation Routines

    As you can see, the string I/O routines in DIALOG.C are not very
    sophisticated. Fortunately, the QuickC library contains a host of
    functions that permit more complex string manipulations. We won't describe
    all of the functions hereâ”€â”€each has its own page in the Microsoft QuickC
    Run-Time Library Referenceâ”€â”€but we do list many of them in Table 9-3 on
    page 279. We will, however, use many of these functions in one large
    program and then discuss those selected string-handling routines.

    The ACME.C program (Listing 9-8) asks the user to fill out an employment
    application for a fictional company. It isn't particularly user friendly,
    and it terminates if you type something it can't understand.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* acme.c  --     illustrates an assortment of the    */
    /*                C library string-handling routines  */

    #include <stdio.h>        /* for NULL */
    #include <string.h>        /* for strchr(), et al */

    #define NAME_PATTERN \
    "first<space>last  or\n\
    first<space>middle<space>last"

    #define ADDRESS_PATTERN \
    "number<space>street<comma><space>city"

    char Buf[BUFSIZ];        /* global I/O buffer */
    main()
    {
        char *ocp, *cp, *first, *last, *street, *city;
        void Prompt(), Cant();

        printf("Acme Employment Questionnaire\n");

        /*
        * Expect first<space>last or
        *        first<space>middle<space>last
        */
        Prompt("Full Name");

        /* search forward for a space */
        if ((cp = strchr(Buf,' ')) == NULL)
            Cant("First Name", NAME_PATTERN);
        *cp = '\0';
        first = strdup(Buf);
        *cp = ' ';

        /* search back from end for a space */
        if ((cp = strchr(Buf,' ')) == NULL)
            Cant("Last Name", NAME_PATTERN);
        last = strdup(++cp);

        /*
        * Expect number<space>street<comma><space>city<comma>
        */
        Prompt("Full Address");

        /* search forward for a comma */
        if ((cp = strchr(Buf,',')) == NULL)
            Cant("Street", ADDRESS_PATTERN);
        *cp = '\0';
        street = strdup(Buf);

        /* Search forward from last comma for next comma */
        if ((ocp = strchr(++cp,',')) == NULL)
            Cant("City", ADDRESS_PATTERN);
        *ocp = '\0';
        city = strdup(++cp);

        printf("\n\nYou Entered:\n");
        printf("\tFirst Name: \"%s\"\n", first);
        printf("\tLast Name:  \"%s\"\n", last);
        printf("\tStreet:     \"%s\"\n", street);
        printf("\tCity:       \"%s\"\n", city);

    }

    void Cant(char *what, char *pattern)
    {
        printf("\n\n\bFormat Error!!!\n");
        printf("Can't parse your %s.\n", what);
        printf("Expected an entry of the form:\n\n");
        printf("%s\n\nAborted\n", pattern);
        exit(1);
    }

    void Prompt(char *str)
    {
        while (1)
            {
            printf("\n%s: ", str );
            if (gets(Buf) == NULL || *Buf == '\0')
                {
                printf("Do you wish to quit? ");
                if (gets(Buf) == NULL || *Buf == 'y')
                    exit (0);
                continue;
                }
            break;
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-8.  The ACME.C program.

The strchr() String Function

    The first new function in ACME.C is strchr() (for "string character").
    This routine requires two argumentsâ”€â”€a string to search and a character to
    look for in that string:

    strchr(Buf, ' ')
            â””â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Search string for a space character

    If strchr() finds the character in the string, it returns the address of
    that character. If it doesn't find the character, it returns NULL. Thus,
    we can handle the error as follows if the character is not in the string:

                        â”Œâ”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Search Buf for a space character
    if ((cp = strchr(Buf, ' ')) == NULL)
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Save address
                                        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Then test for an error

    In the example, cp is a pointer to char into which we assign the address
    returned by strchr(). If the result of that assignment (the value of cp)
    is NULL, the string Buf contains no space character.

    Because strchr() returns the address of a string, you must either declare
    it in your program as char *strchr(); or use the statement #include
    <string.h> (as we did in ACME.C), to supply the declaration for strchr().

The strdup() String Function

    The second new function in ACME.C is strdup(). This is a Microsoft QuickC
    function that does not exist in other C libraries. When passed a string,
    strdup() makes a copy of that string and returns the address of the copy.
    Because this type of "string duplication" is not portable, we'll show you
    a version (Listing 9-9) that is. The implementation of this portable
    version of strdup() introduces two new string-handling functions, strlen()
    and strcpy().

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    #include <stdio.h>  /* for NULL  */
    #include <malloc.h> /* malloc    */

    char *
    strdup(str)
    char *str;
    {
        char *newstr;
        int  bytes;

        bytes = strlen(str);
        if ((newstr = malloc(bytes + 1)) == NULL)
            return (NULL);
    88     (void)strcpy(newstr, str);
        return (newstr);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-9.  The strdup() function.

The strlen() String Function

    The strlen() function counts the number of characters in a string
    (excluding the terminating '\0') and returns that count. For example, the
    assignments

    static char word[] = "Biff";

    bytes = strlen(word);

    cause bytes to be assigned the value 4 because the string word contains
    four letters.

The strcpy() String Function

    The strcpy() function copies its second argument (a string) into its
    first, a buffer large enough to hold that copy. The value returned by
    strcpy() is the address of its first argument. Because we wanted to ignore
    that return value in our version of strdup(), we typecast the call as type
    void:

    if ((newstr = malloc(bytes + 1)) == NULL)
            return (NULL);
    (void)strcpy(newstr, str);

    To create the space for the copy, we call malloc() with an argument of
    bytes + 1, which creates room for both the copy of the string and the
    appended terminating '\0'. (Remember strlen(), which gave us the value in
    bytes, does not count the terminating '\0'.)

    Table 9-3 QuickC Library String Manipulation Functions
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    strlen(str)          Returns the length of a string str, not counting the
                        terminating '\0'
    strcat(s1, s2)       Concatenates the second string (s2) to the end of the
                        first (s2)
    strcmp(s1, s2)       Compares two strings (s1 and s2); returns 0 if they
                        are the same, otherwise returns the arithmetic
                        difference of the first two nonmatching characters
    stricmp(s1, s2)      Compares two strings without regard to case
    strncmp(s1, s2, n)   Compares n characters in the two strings (s1 and s2)
    strcpy(buf, str)     Copies a string (str) into a char buffer buf, which
                        must be large enough to hold both the string and its
                        terminating '\0'
    strncpy(buf, str, n) Copies n characters of the string str into the buffer
                        buf
    strchr(str, ch)      Finds a character (ch) in a string (str); returns the
                        address of ch if found, otherwise returns NULL
    strcspn(s1, s2)      Finds a substring in s1 that begins with anything
                        other than one of the characters in s2; returns the
                        address of that substring if found, otherwise returns
                        NULL
    strstr(s1, s2)       Finds the first occurrence of the substring s1 in the
                        larger string s2; returns the address of that
                        substring if found, otherwise returns NULL
    strrev(str)          Reverses the characters in the string str; returns
                        the address of that reversed string
    strupr(str)          Converts a string (str) to uppercase characters
    strset(str, ch)      Clears a string (str), converting all its characters
                        to the character ch
    strdup(str)          Duplicates a string (str), returning the address of
                        the new copy
    sprintf(str, cntl,   Formatted print into a string (str), converting args
    args,...)            based on the control string cntl
    sscanf(str, cntl,    Formatted convert, like scanf(), but converts from
    addrs,...)           the string rather than from the keyboard
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    You should be aware that although stricmp(), strcspn(), and strupr() are
    supplied with the Microsoft QuickC library, they are not a part of ANSI C.
    Do not use them if you want your programs to be portable to other
    compilers and computers.

C vs BASIC String Functions

    As you have seen, sophisticated C string handling can require complicated
    programming. Although the C library string-handling routines can emulate
    much of BASIC, the following example demonstrates that such emulation is
    usually less straightforward:

    A$ = B$â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€BASIC
    first = strdup(Buf);â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€C

    Some functions common to BASIC are missing from C. Among them are LEFT$,
    MID$, and RIGHT$. Listing 9-10 shows a C version of LEFT$. We leave it as
    an exercise for you to write C versions of the other two BASIC commands.

    C offers two principal advantages over BASICâ”€â”€it permits the programmer to
    extend string-handling library routines with customized routines, and it
    allows easy access to strings from pointers.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    #include <stdio.h>   /* for NULL     */
    #include <string.h>  /* for strdup() */

    char *
    leftstr(str, cnt)
    char *str;
    int  cnt;
    {
        char *cp;

        if (strlen(str) < cnt || cnt <= 0)
            return (NULL);
        if (strlen(str) == cnt)
            return (strdup(str));
        cp = strdup(str);
        cp[cnt - 1] = '0';
        return (cp);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-10.  The leftstr() function.


Arrays and Strings

    Because a string is nothing more than an array of type char, you can use a
    two-dimensional array of type char as an array of strings. However, you
    must be sure to terminate each row (string) with a '\0' character, as
    follows:

    char names[3][6] = {
            { 'J','o','e','\0' },
            { 'D','u','k','e','\0' },
            { 'O','z','z','i','e','\0' }
    };

    You also can take the easier route of using string constants (quoted
    strings) as array initializers:

    char names[3][6] = { "Joe", "Duke", "Ozzie" };

    Both forms create identical arrays, as illustrated in Figure 9-3. Also
    notice that underinitializing rows sets the trailing characters in rows 0
    and 1 to '\0'.

        char names [3] [6] = {"Joe", "Duke", "Ozzie"};

                                    Columns
                                        â”‚
                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                â”‚                                      â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”
            â”Œâ”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â–¼â”¬â”€â”€â”€â”€â”€â”€â”€â” â”‚
            â”‚ â”‚  'J'  â”‚  'o'  â”‚  'e'  â”‚  '\O' â”‚  '\O' â”‚  '\O' â—„â”€â”¼â”€ Auto-initia
            â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤ â”‚  trailing ze
    Rows of â”€â”¤ â”‚  'D'  â”‚  'u'  â”‚  'k'  â”‚â”‚ 'e'  â”‚  '\O' â”‚  '\O' â—„â”€â”˜
    strings  â”‚ â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”¼â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤
            â”‚ â”‚  'O'  â”‚  'z'  â”‚  'z'  â”‚â”‚ 'i'  â”‚â”‚ 'e'  â”‚  '\O' â”‚
            â””â”€â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”¼â”€â”€â”€â”€â”€â”€â”´â”¼â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”˜
                                        â”‚       â”‚       â”‚
                                        â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ String-
                                                                    terminating
                                                                    zeros

    Figure 9-3. A two-dimensional array of char values as an array of strings.

    As we've already seen, strings can be easily manipulated by pointers.
    Because of this, arrays of pointers to strings are often used in place of
    the two-dimensional arrays of char. The previous sample arrays, declared
    and initialized as an array of pointers, appear as follows:

    char *names[3] = { "Joe", "Duke", "Ozzie" };
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Array of pointers

    This pointer form also uses storage space more efficiently than the
    two-dimensional array. Compare the memory use of this form, depicted in
    Figure 9-4, with that of the preceding approach (shown in Figure 9-3).

        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”       â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
        â”‚          â”‚â”€â”€â”€â”€â”€â”€â–ºâ”‚  'J'  â”‚  'o'  â”‚  'e'  â”‚  '\O' â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤       â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”
        â”‚          â”‚â”€â”€â”€â”€â”€â”€â–ºâ”‚  'D'  â”‚  'u'  â”‚  'k'  â”‚  'e'  â”‚  '\O' â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤       â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”
        â”‚          â”‚â”€â”€â”€â”€â”€â”€â–ºâ”‚  'O'  â”‚  'z'  â”‚  'z'  â”‚  'i'  â”‚  'e'  â”‚  '\O' â”‚
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜       â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜
        â””â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”˜
            â”‚
    Array of 3 pointers
            â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”
    char *names[3] = {"Joe", "Duke", "Ozzie"};

    Figure 9-4. Arrays of pointers to strings use memory efficiently.

    The L2WORDS.C program (Listing 9-11) illustrates one application for an
    array of pointers to strings. It asks you to enter a line of text, then it
    breaks that line into individual words and returns an array of pointers to
    the substrings that form those words. Line2words() assumes that spaces
    separate words, but it can take multiple words as a single word if you
    surround them with full quotation marks. A routine like Line2words() is
    useful for writing your own command-line interpreter (COMMAND.COM).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* l2words.c  --  employs an array of pointers to  */
    /*                strings to break a line of text  */
    /*                into its component words         */

    #include <stdio.h>        /* for NULL and BUFSIZ */

    main()
    {
        char **Line2words();    /* declare function type */
        char **list;            /* pointer to pointer    */
        char buf[BUFSIZ];       /* buffer for input      */
        int  count, i, quote_flag;

        printf("Enter a line of text and I will break\n");
        printf("it up for you.\n");

        if (gets(buf) == NULL)
            exit(1);

        list = Line2words(buf, &count);

        for (i = 0; i < count; i++)
            {
            quote_flag = 0;
            printf("<");
            if (list[i] != buf)
                {
                if( list[i][-1] == '"')    /* negative subscript */
                    {
                    ++quote_flag;
                    printf("\"");
                    }
                }
            printf("%s", list[i]);

            if (quote_flag)
                printf("\"");

            printf(">\n");
            }
    }
    #define MAXW 64

    char **Line2words(char *line, int  *count)
    {
        static char *words[MAXW];
        int  index;

        index = 0;        /* zero internal index */

        while (*line != '\0')
            {
            /* turn spaces and tabs into zeros */
            if (*line == ' ' || *line == '\t')
                {
                *(line++) = '\0';
                continue;
                }
            words[index] = line++;    /* found a word */

            /* is it quoted? */
            if ( *(words[index]) == '"')
                {
                /* Yes, advance pointer to just past quote. */
                ++words[index];

                /* find next quote. */
                while (*line && *line != '"')
                    {
                    ++line;
                    }

                /* and turn it into a '\0'. */
                if (*line)
                    *(line++) = '\0';
                }
            else
                {
                /* otherwise skip to next space */
                while (*line && *line != ' ' && *line != '\t')
                    {
                    ++line;
                    }
                }
            if (++index == MAXW)
                break;
            }
        *count = index;        /* set count via pointer   */
        return (words);        /* return address of array */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-11.  The L2WORDS.C program.

    L2WORDS.C does a few tricky things: First, notice that we declare the
    function Line2words() as char **. This means that it returns a pointer to
    a pointer. That pointer contains the address of the first element of our
    array of pointers. The first element in that array points to the first
    word.

    Second, notice that when the program prints words, it checks lines[i][-1]
    (negative subscripting) to see if the string has full quotation marks
    around it. If it does, the program replaces them when it prints the word.


The Arguments to main()â”€â”€argv and argc

    When you run a program from the command interpreter (COMMAND.COM under
    MS-DOS, or sh or csh under UNIX), you can specify arguments for the
    program on the command line. For example, when you run QuickC by typing

    C> qc file.c

    QuickC starts with the file named file.c already loaded. All C programs,
    including QuickC, retrieve arguments from the command line in the same
    way. That is, every C program begins execution with the function named
    main(), and that function, like any other, can receive arguments.
    Traditionally called argc and argv, these arguments are received by main()
    as follows:

    main(argc, argv)
    int argc;
    char *argv[];

    These arguments to main() contain all the information that you need to
    access the command-line arguments: argc is the number of command-line
    arguments, and argv is an array of pointers to those arguments.

    The SHOWARGS.C program (Listing 9-12) shows how to access and use the
    arguments passed to main(). To run this program from within QuickC, you
    must first set the command-line arguments with Set Runtime Options on the
    Run menu.

    When you run SHOWARGS.C with the following command-line preset in the Set
    Runtime Options dialog box:

    kit makes lovely paper

    the program prints the following:

    argc = 5â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Five pointers in argv

    argv[0] -> "C"
    argv[1] -> "kit"
    argv[2] -> "makes"
    argv[3] -> "lovely"
    argv[4] -> "paper"
    argv[5] -> NULL

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* showargs.c  --  shows how to access the arguments  */
    /*                 passed to main()                   */

    #include <stdio.h>        /* for NULL */

    main(argc, argv)
    int argc;
    char *argv[];
    {
        int i;

        printf("argc = %d\n", argc);
        printf("\n");

        for (i = 0; i < argc; ++i)
            {
            printf("argv[%d] -> \"%s\"\n", i, argv[i]);
            }
        printf("argv[%d] -> NULL\n", i);
        printf("\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-12.  The SHOWARGS.C program.

    The first string that argv points to (an array of pointers to strings) is
    usually the name of your program. (Under QuickC, your program will always
    be named C when you run it from the Run menu, but argv[0] is correct when
    you run your program later as a .EXE file.)

    Because argv is an array of pointers to char, you often will see it
    alternatively declared as follows:

    main(argc, argv)
    int argc;

    main(argc, argv)
    int argc;
    char **argv;
    {    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ A pointer to a pointer

    Recall that this pointer to a pointer and the declaration char *argv[] are
    interchangeable.

    The main() function is actually passed three arguments, but the third
    argument, called envp, is seldom used. Like argv, it is an array of
    pointers to strings and must be declared as follows:

    main(argc, argv, envp)
    int argc;
    char *argv[], *envp[];
    {

    The strings that envp points to are your system's environmental variables,
    such as PATH.

    Take a moment to modify SHOWARGS.C so that it matches the SHOW2.C program
    (Listing 9-13). After you run this program, choose DOS Shell from the
    File menu and type set. Compare the output produced by the MS-DOS SET
    command to that produced by this program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* show2.c  --     shows how to use main()'s envp */

    #include <stdio.h>        /* for NULL */

    main(argc, argv, envp)
    int argc;
    char *argv[], *envp[];
    {
        int i;

        printf("argc = %d\n", argc);
        printf("\n");

        for (i = 0; i < argc; ++i)
            {
            printf("argv[%d] -> \"%s\"\n", i, argv[i]);
            }
        printf("argv[%d] -> NULL\n", i);
        printf("\n");

        for (i= 0; envp[i] != NULL; ++i)
            {
            printf("envp[%d] -> \"%s\"\n", i, envp[i]);
            }
        printf("envp[%d] -> NULL\n", i);

    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-13.  The SHOW2.C program.


Character Classification and Transformation

    You often need to be able to classify individual characters of a string
    (such as uppercase versus lowercase) and then transform them (such as
    converting uppercase to lowercase). QuickC includes a standard C header
    file called ctype.h, which defines many character classifications and
    transformation routines. (Use the View Include menu to examine it.) To
    access ctype.h, merely use #include to include it at the head of your
    program.

    The routines in ctype.h are not true functions: They are #define macros.
    We'll describe #define macros in detail in Chapter 12. In the meantime,
    you can use these routines because they work like function calls.

The Character Classification Routines

    Each of the character classification routines in Table 9-4 takes a single
    argumentâ”€â”€the character to classifyâ”€â”€and returns a 1 for true or a 0 for
    false.

    The WHATCHAR.C program (Listing 9-14) prints all possible classifications
    for each character in a line of entered text. The program limits the line
    of text to 20 characters so that the display doesn't scroll off the
    screen.

    Table 9-4 The Character Classification Routines in ctype.h
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    isalnum()   Tests for alphanumeric ('A' through 'Z,' 'a' through 'z,' and
                '0' through '9')
    isalpha()   Tests for a letter ('A' through 'Z' and 'a' through 'z')
    isascii()   Tests for an ASCII character (0x00 through 0x7F)
    iscntrl()   Tests for a control character (less than ' ' or equal to 0x7F)
    isdigit()   Tests for a digit ('0' through '9')
    isgraph()   Tests for printable character (inverse of iscntrl() but
                excludes space)
    islower()   Tests for lowercase letter ('a' through 'z')
    isprint()   Tests for printable character (inverse of iscntrl())
    ispunct()   Tests for punctuation character
    iswhite()   Tests for white space ('\t,' '\n,' '\f,' and ' ')
    isupper()   Tests for uppercase letter ('A' through 'Z')
    isxdigit()  Tests for a hexadecimal digit ('A' through 'F,' 'a' through
                'f,' '0' through '9')
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* whatchar.c  --  demonstrates the character         */
    /*                 classification routines in ctype.h */

    #include <stdio.h>        /* for NULL and BUFSIZ */
    #include <ctype.h>        /* for iscntl(), et al */
    #define MAXL 20

    main()
    {
        char buf[BUFSIZ];
        int i;

        printf("Enter a line of text (20 chars max):\n");
        if (gets(buf) == NULL)
            exit(1);

        for (i = 0; i < MAXL; ++i)
            {
            if (buf[i] == '\0')
                break;
            printf("'%c' ->", buf[i]);
            if (isalpha(buf[i]))   printf(" isalpha");
            if (isascii(buf[i]))   printf(" isascii");
            if (iscntrl(buf[i]))   printf(" iscntrl");
            if (isgraph(buf[i]))   printf(" isgraph");
            if (isprint(buf[i]))   printf(" isprint");
            if (isdigit(buf[i]))   printf(" isdigit");
            if (isupper(buf[i]))   printf(" isupper");
            if (islower(buf[i]))   printf(" islower");
            if (ispunct(buf[i]))   printf(" ispunct");
            if (isspace(buf[i]))   printf(" isspace");
            if (isalnum(buf[i]))   printf(" isalnum");
            if (isxdigit(buf[i]))  printf(" isxdigit");
            printf("\n");
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-14.  The WHATCHAR.C program.

    The include file ctype.h also defines routines to transform characters.
    Each of the routines in Table 9-5 takes a single argument, the character
    to transform, and returns the transformed character, as in the following
    example:

    ch = toupper('a');

    Here toupper() is given a lowercase 'a'. Because 'a' is lowercase,
    toupper() transforms it to an uppercase 'A' and assigns that value to the
    variable ch.

    The INVERT.C program (Listing 9-15) uses both the character
    classification and transformation routines to reverse a line of entered
    text. That is, it prints the line backward and inverts the case of each
    character.

    Table 9-5 The Character Transformation Routines in ctype.h
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    toascii()   Converts a non-ASCII character to an ASCII character (clears
                all but the low-order seven bits)
    toupper()   Converts a lowercase character to an uppercase character
    tolower()   Converts an uppercase character to a lowercase character
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* invert.c  --  combines character classification and */
    /*               transformation to invert text        */

    #include <stdio.h>         /* for NULL           */
    #include <ctype.h>        /* for toupper, et al. */

    main()
    {
        char buf[BUFSIZ];
        int i;

        printf("Type in a line of text and I will invert it.\n");

        if (gets(buf) == NULL)
            exit(1);
        /* Print the string backward. */
        for (i = (strlen(buf) - 1); i >= 0; --i)
            {
            if (isupper(buf[i]))            /* upper to lower */
                putchar(tolower(buf[i]));
            else if (islower(buf[i]))       /* lower to upper */
                putchar(toupper(buf[i]));
            else
                putchar(buf[i]);
            }
        putchar('\n');

    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 9-15.   The INVERT.C program.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€