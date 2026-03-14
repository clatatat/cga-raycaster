Chapter 13  Keyboard and Cursor Control

    Almost every PC program needs to get information from the keyboard and to
    display information on a monochrome or color screen. So far, our programs
    have used the standard C Library functions such as getchar(), scanf(),
    putchar(), and printf(), and occasionally we've used command-line
    arguments. Using these approaches produces portable code. However, it also
    produces a bland interface that fails to take advantage of many PC
    capabilities. If you want your programs to do more than display mere text
    on the screen, study this and the next two chapters, which explore PC I/O.
    You will learn how to use function keys and cursor control keys, how to
    control the location and appearance of text on the screen, how to use
    color in text and in graphics, and how to construct graphic figures.

    In this chapter, we examine the keyboard and cursor control. We look at
    QuickC's numerous I/O functions and provide a more detailed discussion of
    the generic getchar() and the PC-specific getche() and getch(). We
    describe scan codes, show how to use ANSI.SYS to redefine keys and to
    provide cursor control, and discuss BIOS routines. Finally, we use the
    int86() function to create a library of BIOS-based screen-control and
    cursor-control functions.


Keyboard Input Functions

    You use the standard C I/O functions to read and to display a variety of
    input: characters, strings, integers, and floating-point numbers. But the
    standard input functions don't detect non-ASCII keys, such as the function
    keys. And they don't provide many of the input control features typically
    required by programs such as word processors, spreadsheets, and games. To
    get that control, we need to process input at a "lower" level than that of
    standard I/O functions.

    Three QuickC functions read keyboard input character by character:
    getchar(), getche(), and getch(). Each reads one character at a time and
    reports its value to the calling program. (Actually, getchar() is not a
    true function; instead, it is defined as a macro in stdio.h.)

Input Examples

    The programs on the opposite page illustrate how the three input functions
    respond to the same inputâ”€â”€in this case, the input is the word hat
    followed by Enter.

    The GETCHAR.C program (Listing 13-1) produces the following output:

    Please enter a word.
    hat<Enter>
    1.. 2.. 3..â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Counting delayed until you press Enter
    3 characters altogether

    Counting doesn't start until you type the word and press Enter.

    Next, look at GETCHE.C (Listing 13-2), which generates the following
    output:

    Please enter a word.
    h1.. a2.. t3.. <Enter>â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Immediate count
    3 characters altogether

    This time each letter is counted as it is typed.

    Finally, examine GETCH.C (Listing 13-3), which produces the following
    output:

    Please enter a word.
    1.. 2.. 3..â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Input not displayed 3 characters altogether

    This time the input is invisible; only the output is displayed.

    The functions behave differently, and you use them for different purposes.
    The getchar() function buffers and echoes input; getche() does not buffer
    input but echoes it; getch() neither buffers nor echoes input. Buffered
    input goes into a temporary storage area before being transferred to the
    calling program. (Pressing Enter "empties" the buffer.) Echoed input is
    displayed on the screen.

    The getchar() function handles arrow keys or function keys inconsistently
    from one system to another. Try using GETCHAR.C with these keys as input
    and see how your system responds. The getche() and getch() functions do
    read these keys in a consistent manner, however. Try GETCHE.C, for
    example, with an arrow key or function key as input. Each of these keys,
    as you'll see, is counted as two keystrokes, and characters other than
    those you typed are echoed on the screen. This is perfectly proper and
    reasonable behavior, as you'll see when we discuss scan codes.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*      getchar.c -- using getchar()         */

    #include <stdio.h>
    main()
    {
        int count = 1;

        printf("Please enter a word.\n");
        while (getchar() != '\n')       /* here it is */
            printf("%d.. ", count++);
        printf("\n%d characters altogether\n", count - 1);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-1.  The GETCHAR.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*     getche.c -- using getche()             */
    #include <conio.h>     /* note different file included */
    main()
    {
        int count = 1;

        printf("Please enter a word.\n");
        while (getche() != '\r')    /* changed comparison */
            printf("%d.. ", count++);
        printf("\n%d characters altogether\n", count - 1);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-2.  The GETCHE.C program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*     getch.c -- using getch()             */
    #include <conio.h>
    main()
    {
        int count = 1;

        printf("Please enter a word.\n");
        while (getch() != '\r')
            printf("%d.. ", count++);
        printf("\n%d characters altogether\n", count - 1);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-3.  The GETCH.C program.

The getchar() Buffer

    The program using getchar() doesn't receive the generated code until this
    buffer is flushed. This occurs when you press Enter or when the buffer is
    filled. Because the getchar() buffer is 512 bytes, normal keyboard input
    does not fill it. QuickC sets up this input buffer when any input function
    from the stdio.h family is called, and all the input functions of that
    family, such as scanf() and gets(), share it. Thus, when your program uses
    both scanf() and getchar(), they share the same input buffer.

Differences in Usage

    First, getchar() requires the stdio.h include file, while getch() and
    getche() use conio.h, the include file for console I/O functions. Second,
    getch() and getche use \r instead of \n to represent the action of Enter,
    and they do not interpret Ctrl-Z as an end-of-file indicator.

    The reason for these last two differences is that getchar(), by default,
    reads input in the text mode, and getch() and getche() read input in the
    binary mode. In the text mode, as you may recall, the carriage
    return/linefeed combination is converted to a linefeed on input, and the
    linefeed is converted to a carriage return/linefeed on output. The binary
    mode makes no conversions. As a result, getchar() uses \n to detect the
    Enter key, but getch() and getche() must use \r.

    The second difference is that getchar(), when used in the text mode,
    recognizes the Ctrl-Z character as marking the end of a file. This lets
    you simulate the end-of-file condition from the keyboard by entering
    Ctrl-Z. The binary mode used by getche() and getch() does not recognize
    Ctrl-Z (or any other character) to mark the end of a file. As a result,
    constructions such as

    while((ch = getche()) != EOF)     /* NO */

    do not work for keyboard input. When using getch() or getche() in such a
    loop, you must specify a keyboard character to indicate the end of input.
    We've used \r, and in many later examples we'll use the Esc key.

    Although the getchar() function uses text mode by default, you can call
    QuickC's setmode() function to place getchar() in binary mode. (See
    setmode() in the Microsoft QuickC Run-Time Library Reference for details.)
    However, you cannot switch getche() and getch() to text mode.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Reminder
    Don't mix buffered functions such as getchar() and gets() with unbuffered
    functions such as getche() and getch(). The buffered functions transmit
    characters from the input buffer when it is flushed; the unbuffered
    functions read keys as they are pressed. Thus, a program mixing buffered
    and unbuffered input functions might not process the characters in the
    order they were typed.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Table 13-1 summarizes the different behavior of the character input
    functions.

    Table 13-1 Character Input Functions
                                        getchar()   getche()     getch()
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Buffered                             o
    Echoes                               o           o
    Uses \n                              o
    Uses \r                                          o            o
    Uses stdio.h                         o
    Uses conio.h                                     o            o
    Text mode (default)                  o
    Binary mode                                      o            o
    Backspace editing                    o
    Reads ASCII keys                     o           o            o
    Reads non-ASCII keys                             o            o
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Typical Uses for Character Input Functions

    The primary advantage of using the buffered getchar() is that it lets
    users edit input with the Backspace key before they send it to the
    program. The nonbuffered form, on the other hand, requires users to type
    less because they needn't press Enter. For example, suppose your program
    uses the following prompt:

    Continue? <y/n>

    With getchar(), the user must type y and press Enter, while getche()
    requires only a y. Likewise, the getche() function is useful in programs
    that use a typed character to select a menu item. Consider the following
    fragment:

    while ((ch = getchar()) != 'q') /* oops example */
        switch (ch)
        {
            case 'a': ...
            case 'b': ...
            case 'c': ...
            default:  printf("Not a valid choice\n");
        }

    To choose case a, the user types a and presses Enter. The loop processes
    the a, recycles and processes the \n generated by the Enter key, and
    prints the default message. Replacing getchar() with getche() eliminates
    the need to press the Enter key and hence the need to add programming to
    process the extraneous \n.

    The non-echoed, nonbuffered getch() is useful, of course, when you don't
    want to display input on the screen. For example, you might use the k key
    to move an image on the screen. Also, a program that requires a user to
    type a secret password shouldn't display it on the screen.

    Let's use getch() to construct a simple password program. In a real
    application, we would ensure password security by also using encryption
    and periodic updating. In the PASSWORD.C program (Listing 13-4 on the
    following page), we'll build the password into the program and concentrate
    on processing the user's input.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  password.c -- requires a password to complete the   */
    /*                program; illustrates a use of getch() */

    #include <stdio.h>
    #include <conio.h>
    #include <string.h>
    #define GUESS_LIMIT 4
    #define WORD_LIMIT 10  /* maximum length of password */
    #define TRUE 1
    #define FALSE 0
    char *Password = "I'mOk";
    main()
    {
        int g_count = 0;           /* guesses taken    */
        int w_count;               /* letters accepted */
        int in_count;              /* letters entered  */
        char entry[WORD_LIMIT + 1];
        char ch;
        int correct, go_on;

        do
            {
            puts("Enter the secret password.");
            in_count = w_count = 0;
            /* the following loop accepts no more chars */
            /* than entry[] will hold, but keeps track  */
            /* of total number typed                    */
            while ((ch = getch()) != '\r')
                    {
                    if (w_count < WORD_LIMIT)
                        entry[w_count++] = ch;
                    in_count++;
                    }
            entry[w_count] = '\0';
            if (in_count != w_count)
                    correct = FALSE;    /* too many chars */
            else
                    correct = (strcmp(entry, Password) == 0);
            g_count++;
            go_on = !correct && g_count < GUESS_LIMIT;
            if (go_on)
                    puts("\nNo good; try again.");
            } while (go_on);
        if (!correct)
            {
            puts("Sorry, no more guesses.  Bye.");
            return(1);
            }
        puts("Welcome to Swiss bank account 2929100.");
        puts("Your current balance is $10,232,862.61.");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-4.  The PASSWORD.C program.

    Note the following loop:

    while ((ch = getch()) != '\r')
            {
                if (w_count < WORD_LIMIT)
                    entry[w_count++] = ch;
                in_count++;
            }

    It uses an if statement to prevent overflowing the array, yet it continues
    to read additional characters if the limit is exceeded. We could have made
    this loop stop at the character limit, but that would tell the illicit
    user the number of characters in the actual password.

    The structure of the do while loop reflects the two conditions that
    terminate the loop: a correct password or too many attempts. If the loop
    ends and correct is still false, the program knows that the reason for
    termination was too many attempts.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Character and String Input in BASIC and C
    If you are used to BASIC, you know that you can read a character from the
    keyboard (with no echo) using the INKEY$ function. This function is
    similar to C's getch(). C conveniently provides the alternative getche()
    function for character input with echo, while in BASIC you would need a
    separate PRINT statement to echo the input character. Note that neither
    the BASIC function nor the C functions mentioned recognize Ctrl-Z as a
    signal for the end of file.

    Both BASIC and C provide generalized input functions that can handle a
    series of numeric or string variables. In BASIC, the INPUT statement
    allows you to supply a prompt string and accept input into one or more
    variables. For example:

    INPUT "ENTER NAME AND AGE: ",NAME$,AGE

    The scanf() function in C is similar in that it allows you to receive
    input for a series of variables of different types. The scanf() function,
    however, allows you a much greater degree of control over the format of
    each input value, the interpretation of white space, and the characters
    used to separate input values. Unlike the INPUT function, scanf() makes no
    provision for a prompt string, so it is normally preceded by a separate
    printf() statement with the desired string.

    In a typical trade-off for these two languages, BASIC's INPUT statement
    provides very rudimentary error checking and editing of the input line.
    While scanf() will reject any input that does not match the
    specifications, it does not terminate or restart when bad input is
    encountered. The C programmer is responsible for error checking to
    determine whether the values entered are actually reasonable and complete.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€


Reading Non-ASCII Keys

    Some keys, such as the function keys, the cursor control keys, and Alt-key
    combinations, have no ASCII code. How can a QuickC program read them?
    Before answering this question, we need to discuss how the keyboard
    actually works.

The Keyboard Processor and Scan Codes

    Information does not flow directly from the keyboard to a C program.
    Instead, pressing (or closing) a given key generates a "closure" code that
    indicates the physical location of the key. A microprocessor within the
    keyboard reads this code and then generates a new code, called a "system
    code." It also reports if the user is holding down the Shift, Ctrl, or Alt
    key. Finally, it generates a third code (two bytes called the "extended
    scan code") for the keystroke (or keystroke combination) and places it in
    a storage area called the "keyboard buffer." If the key is still "closed"
    after a predetermined period of time elapses, another keystroke is placed
    in the buffer. Thus, you can generate a string of characters by holding
    down a key. Releasing the key generates an "opening" code that tells the
    keyboard microprocessor that you are finished with that key. By default,
    the keyboard buffer holds a maximum of 16 extended scan codes.

    The purpose of the keyboard buffer is to hold characters that are typed
    faster than an application can process them. It is distinct from the
    buffer created for the stdio.h input functions.

    The getch() and getche() functions do not read the keyboard directly.
    Instead, they read the extended scan codes in the keyboard buffer. Because
    this code is more extensive than the standard ASCII code, programs can use
    it to identify function keys, cursor keys, and other keys lacking an ASCII
    code. (The only difference between getch() and getche() is that getche()
    echoes input; therefore, our next discussions about getch() actually apply
    to both functions.)

Using Scan Codes

    Each extended scan code is two bytes. The first byte, which we call the
    "ASCII byte," contains the ASCII code, if any, for the keystroke. The
    second byte, which we call the "scan byte," contains a scan code for the
    key. This code is based on the physical position of the key on the
    keyboard, and, in some cases, on whether the Shift, Ctrl, or Alt key is
    pressed.

    The contents of an extended scan code reveal whether or not it represents
    an ASCII character. If it does, the ASCII byte is nonzero. If it does not,
    the ASCII byte is set to zero, and the numeric value of the scan byte
    encodes the keystroke or keystroke combination. For example, in Figure
    13-1, the uppercase Q character is represented by an ASCII byte of 81
    because that is its ASCII code. The scan code of 16 means the Q key is the
    sixteenth key in the keyboard numbering scheme. The F1 key has no ASCII
    representation, so the ASCII byte is 0. However, because it is the 59th
    key on the keyboard, the scan byte is 59.

            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”               â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”
    Press Q â”‚   81   â”‚   16   â”‚      Press F1 â”‚   00   â”‚   59   â”‚
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜               â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜
            ASCII     Scan                  â””â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”˜
            byte      byte                   Extended scancode

    Figure 13-1. Scan codes.

    How does getch() use these extended codes? First, it looks at the ASCII
    byte. If the byte is nonzero, getch() knows it has found an ASCII
    character. It returns that value and then skips the scan byte and moves to
    the next ASCII byte. For example, it returns 0x41 for Shift-A, 0x61 for a,
    and 0x01 for Ctrl-A.

    When the ASCII byte is 0, getch() lets the program know it has found a
    non-ASCII keystroke by returning a value of 0. Because getch() needs to
    know which non-ASCII character was pressed, it does not skip to the next
    ASCII byte; instead, it goes to the scan byte. Thus, the next call to
    getch() results in it reading the scan code that goes with the 0 ASCII
    byte. In other words, only one call of getch() is needed to read an ASCII
    keystroke, but two calls are needed to read a non-ASCII keystroke. Also,
    the scan codes are returned only for the non-ASCII keystrokes.

    Suppose, for example, that you type the Shift-Q combination and then press
    the F1 key. The codes 81 16 00 59 are placed in the keyboard buffer. The
    first call to getch() returns the 81. The next call to the function skips
    to the 00 and returns that value, and the third call returns the 59. Thus,
    a program that plans to use the F1 key must look for return values of 0.
    When it encounters one, the program should check to see if the next call
    returns 59. If so, F1 was pressed. The return value of 0 is a flag that
    says, "Special processing required here."

    Now, how does getchar() process non-ASCII characters? It copies ASCII
    values into the program buffer created by the standard I/O buffer. When it
    finds a 0 ASCII byte in the buffer, it skips to the next input character.
    The 0 ASCII bytes and the scan codes never make it to the I/O buffer, let
    alone to the program.

A Scan Code Example

    The SCANCODE.C program (Listing 13-5 on the following page) demonstrates
    these functions by reading input. If the input is ASCII, the program
    prints the ASCII code. If the input is non-ASCII, the program prints the
    scan codes.

    Following is some sample output:

    Press keys and see the codes!
    Press the Esc key to quit.

    Q has ASCII code 81â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Shift-Q
    Scan code is 59â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€F1
    t has ASCII code 116â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€t has ASCII code 116
    ^T has ASCII code 20â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Ctrl-T

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*   scancode.c -- displays ASCII or scan code         */
    /*   This program illustrates using getch() to detect  */
    /*   special keys such as function keys.               */

    #include <conio.h>
    #define ESC '\033'     /* ESC key */
    main()
    {
        int ch;

        printf("Press keys and see the codes!\n");
        printf("Press the Esc key to quit.\n");

        while ((ch = getch()) != ESC)
            {
            if (ch != 0)
                    {
                    if (ch <= 32)    /* control characters */
                        printf("^%c has ASCII code %d\n",
                                ch + 64, ch);
                    else
                        printf("%c has ASCII code %d\n", ch, ch);
                    }
            else              /* ch IS 0 */
                    {
                    ch = getch();  /* get scan code */
                    printf("Scan code is %d\n", ch);
                    }
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-5.  The SCANCODE.C program.

    What happens if you use getch() and getche() without checking for the zero
    value? They would interpret the ASCII byte and scan byte as two ASCII
    bytes, thus interpreting 00 59 as code for Ctrl-@ and for the semicolon
    character, instead of F1.

Scan Code Values

    In this book we will use only those codes listed below in an include file
    called keys.h. When we need to use these keys, you can include that file,
    which is shown in Listing 13-6.

    Not all keystrokes produce scan codes. For example, Shift, Ctrl, and Alt
    modify the scan codes produced when other keys are pressed. The SCANCODE.C
    program demonstrates this. For example, press Alt. Nothing happens until
    you simultaneously press a second key.

    The operating system normally intercepts the Ctrl-Break combination as the
    code for terminating a program. Thus, getch(), getche(), and getchar()
    never read Ctrl-Break. (We will discuss how to handle Ctrl-Break later in
    this chapter.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  keys.h -- scan codes for several keys */

    #define F1 59   /* function key F1 */
    #define F2 60   /* function key F2 */
    #define F3 61   /* and so on       */
    #define F4 62
    #define F5 63
    #define F6 64
    #define F7 65
    #define F8 66
    #define F9 67
    #define F10 68
    #define HM 71   /* Home key    */
    #define UP 72   /* Up Arrow    */
    #define PU 73   /* Page Up     */
    #define LT 75   /* Left Arrow  */
    #define RT 77   /* Right Arrow */
    #define END 79  /* End key     */
    #define DN 80   /* Down Arrow  */
    #define PD 81   /* Page Down   */
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-6.  The keys.h include file.


Console I/O Functions

    The getch() and getche() functions belong to the console I/O family of
    functions. These functions communicate with the console (the keyboard and
    screen) more directly than do the I/O functions of the stdio.h family.
    However, unlike the stdio.h family, console I/O functions are not in the
    standard C Library and are therefore not necessarily portable. They are
    important because they provide special services not offered by the
    standard I/O package. The console I/O functions declared in the conio.h
    header file are:

    cgets()
    cprintf()
    cputs()
    cscanf()
    getch()
    getche()
    putch()
    ungetch()

    kbhit()
    inp()
    outp()

    The first eight functions in this list closely resemble the stdio.h
    functions with corresponding names. For example, cgets() resembles gets(),
    cprintf() is similar to printf(), and so on. We've already seen the
    kbhit() function. We'll discuss the inp() and outp() functions in Chapter
    14.

Character Output Functions

    Now that we've used the character input functions, let's look at the
    console character output functions. The putch() function works much like
    putchar(). One difference is that putchar() is buffered and putch() is
    not. This means that putch() output goes to the screen directly; putchar()
    output goes to an intermediate storage area first. The second difference
    is that putchar() works in text mode by default, while putch() works in
    binary mode. The main practical consequence of this is in how newlines are
    handled. The C newline character (\n) represents going to the beginning of
    the next line. This actually consists of two operations: a linefeed (LF)
    and a carriage return (CR). In QuickC, the newline character is
    represented by the LF character, ^J. The text mode produces the desired
    effect by mapping an LF to a CR-LF combination on the screen. In the
    binary mode, no such mapping takes place, so you must explicitly generate
    both an LF and a CR character (\n and \r).

    A third difference is that the text mode used by putchar() interprets a
    tab character (\t) as a tabbing instruction; the binary mode used by
    putch() interprets it as an ASCII value to be displayed. With the IBM
    character set, using putch() to generate a tab character results in a
    small circle on the screen.

    The REKEY.C program (Listing 13-7) demonstrates how to use the console
    I/O functions getch() and putch() to map the characters you type to a
    different set of characters on the screen.

    Note that we initialize the Newchars[] array to 26 letters. The
    construction Newchars[ch - 'a'] causes the array index to be zero when ch
    is a, corresponding to the array value q. Similarly, if ch is b, the index
    is 1; and the array value is the next letter in the initialization string,
    w. The initialization continues in this fashion, as shown in Figure 13-2.

    The toupper() and tolower() QuickC macros (defined in ctype.h) convert
    cases; thus, we don't need to use another 26-element array for uppercase
    letters. Note the way in which the program explicitly translates Enter
    (read by getch() as \r) to an output of \r and \n.

            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”
            â”‚    q   â”‚    w   â”‚    e   â”‚    r   â”‚    t   â”‚        â”‚
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                'a'-'a'   'b'-'a'  'c'-'a'  'd'-'a'  'e'-'a'

    Newchars      [0]      [1]      [2]      [3]      [4]

    Figure 13-2. The Newchars[ch - a] array.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* rekey.c -- transliterates typed input             */
    /*    This program illustrates getch() and putch().  */

    #include <stdio.h>
    #include <conio.h>
    #include <ctype.h>
    #define ESC '\033'   /* the escape key */
    char Newchars[] = "qwertyuiopasdfghjklzxcvbnm";
    /* values to be assigned to the a,b,c keys, etc. */
    main()
    {
        char ch;

        printf("Type characters and see them transformed;\n");
        printf("Press the Esc key to terminate.\n");
        while ((ch = getch()) != ESC)
            if (islower(ch))
                putch(Newchars[ch - 'a']);
            else if (isupper(ch))
                {
                ch = tolower(ch);
                putch(toupper(Newchars[ch - 'a']));
                }
            else if (ch == '\r')
                {
                putch('\n');
                putch('\r');
                }
            else
                putch(ch);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-7.  The REKEY.C program.

Console String I/O

    Often we want a program to read a stringâ”€â”€for example, the name of a file.
    Or we want to generate a string. These activities can be done character by
    character, but it is more convenient to use functions designed to handle
    strings. The console functions cgets() and cputs() perform these tasks. In
    action, these functions are similar to gets() and puts(), but there are
    some differences.

    Like gets(), cgets() reads an input string into an array. However, the
    first element of the array holds the maximum allowable size of the input
    string, including a terminating null character. You must initialize this
    element correctly. The second element holds the actual number of bytes
    used, and it is set by cgets() after it reads the input. The string itself
    starts at the third element. Thus, the array must be two bytes longer than
    the maximum string size, including a null character, as shown in Figure
    13-3 on the following page.

                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€Available spaceâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
        0     1  â”‚  2     3     4     5     6     7  â”‚
    â”Œâ”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”
    â”‚  6  â”‚  4  â”‚  L  â”‚  A  â”‚  R  â”‚  A  â”‚ \O  â”‚     â”‚
    â””â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”˜
        â”‚     â”‚     â””â”€â”€cgets() puts string here
        â”‚     â””â”€â”€cgets() puts string size here
        â””â”€â”€You put available space here

    Figure 13-3. Storage of an array read by cputs().

    The cgets() function reads input until the maximum length of the string
    (not counting the null character) is reached or until the user presses
    Enter. The console beeps if you try to read beyond the limit, and you
    can't enter additional characters. The function will, however, let you use
    the Backspace key to correct input. This function returns a pointer to the
    beginning of the stored string; that is, if the array name is str, cgets()
    returns a pointer to str[2].

    The cputs() function takes a pointer to a string as its argument and
    displays that string on the console. Unlike puts(), cputs() does not
    append a newline character; therefore, you must explicitly include the
    \r\n combination to generate a new line. The return value is the last
    character written. The function returns 0 if the string is a null string
    and -1 if there is an error.

    The short STRIO.C program (Listing 13-8) illustrates how the two
    functions work. Notice how we use store + 2 as an argument for cputs(). We
    do this because the string starts at the location pointed to by store + 2.
    We kept the character limit small to make it easy to see what happens when
    you try to exceed it.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* strio.c -- uses cgets() and cputs()                   */
    /* program list -- strio.c (cgets() not in core library) */
    #include <conio.h>
    #define MAXSIZE 6
    main()
    {
        char store[MAXSIZE + 2];

        store[0] = MAXSIZE; /* puts limit in first element */
        cputs("What's your name?\n\r");
        cgets(store);
        cputs("\n\rI'll remember you, ");
        cputs(store + 2);
        cputs("!\n\r");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-8.  The STRIO.C program.

    The following is a sample run of the program:

    What's your name?
    Steph
    I'll remember you, Steph!

    Note the \n\r at the beginning of the second cputs() statement. This
    prevents the message from being printed over the input line.

    Instead of using cputs(store + 2), we could have used cputs(&store[2]).
    Or, because the return value of cgets() points to the start of the
    stringâ”€â”€not to the start of store[]â”€â”€we could have declared a pointer and
    used it as follows:

    char *start;
        ...
    start = cgets(store);
        ...
    cputs(start);

Formatted I/O

    Finally, the cscanf() and cprintf() functions provide console analogues to
    the standard I/O functions scanf() and printf(). The main differences are
    that cscanf() and cprintf() work directly with the console, that cprintf()
    requires you to use the \r\n combination instead of \n, and, of course,
    that they are less portable.


Keyboard Control with ANSI.SYS

    Using getch() or getche() and the scan codes, a QuickC program can detect
    a function key or a cursor control key. But how can you turn that
    information into action? How, for example, can pressing the Left Arrow key
    be made to move the cursor one space to the left? There are three common
    techniques: One uses the ANSI.SYS driver provided with MS-DOS and PC-DOS;
    the second uses BIOS calls; and the third directly accesses video memory.
    Table 13-2 compares the three methods.

    The first method is the simplest, so we begin with it. Many terminals have
    internal hardware that lets you control cursor position and other screen
    attributes by sending "escape sequences" from your program to the
    terminal. These all begin with the ESC character, followed by different
    sequences corresponding to different actions. For example, the sequence
    ESC[2B moves the cursor down two lines in the same column. By using
    printf() to generate such a string, you can move the cursor around. The
    original IBM PC hardware design omitted this convenient feature.

    Table 13-2 Cursor and Screen Control Methods
    Method             ANSI.SYS         BIOS            Direct Memory Access
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Speed ranking      3                2               1
    Ease-of-use        1                2               3
    ranking
    Portability        ANSI-compatible  BIOS-compatible Display-specific
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    MS-DOS version 2.0 came to the rescue, however, by providing the ANSI.SYS
    "driver" as a software fix. (A driver is software designed to handle
    specific hardware I/O devices.) The ANSI.SYS software intercepts output,
    examining it for escape sequences. When it finds a valid sequence, it
    performs the requested action. To use this method, you need ANSI.SYS up
    and running, and you need to know the proper escape sequences.

Starting ANSI.SYS

    Running ANSI.SYS is not like running an ordinary program. You don't, for
    example, type ansi. Instead, you place this line in your CONFIG.SYS file:

    DEVICE=ANSI.SYS

    If the ANSI.SYS file is in a different directory from the CONFIG.SYS file,
    give the full pathname, as in the following example:

    DEVICE=C:\DOS\ANSI.SYS

    Now, when you boot your computer, ANSI.SYS is installed as part of MS-DOS.

Using ANSI.SYS Escape Sequences

    One handy escape sequence lets you assign a string to a particular key.
    That is, it makes typing a single key have the same effect as typing the
    string. First, let's examine the format of the escape sequence required by
    ANSI.SYS:

    ESC[ASCIIcode;"string";ASCIIcodep

    Here ESC represents the escape character (ASCII 033). The first ASCIIcode
    represents the ASCII number of the key to which you assign the string. For
    non-ASCII keys, such as F1, use 0ancode, where the number following the 0;
    is the scan code for the key. Next, string represents, in string form, the
    characters you want to assign to the key. For example, the string could be
    dir/w. The final ASCIIcode lets you represent an assigned character in
    ASCII form instead of as a string. For example, you can use 13 instead of
    a carriage return. Finally, the character p terminates the escape
    sequence. You can use as many strings and ASCII codes as you like as long
    as you separate them with semicolons. For example, you can represent CD by
    "CD", by "C";68, or by 67;68, where 67 and 68 are ASCII codes for C and D.
    The ASGNKEY.C program (Listing 13-9), for example, assigns meanings to
    the F5 through F10 keys. These meanings remain in effect until you reboot.

    Because all the key assignments follow the same form, we use a macro to
    represent the general form. In the macro, printf() displays the escape
    sequence. First comes \033, the octal code for ESC. Then the left bracket
    and the 0; indicate a scan code. (The scan code itself is the variable K
    of the macro.) Next comes another semicolon and an open quote. (You must
    escape these with a \ when you use them within a string.) Next, the string
    itself is represented by the variable S. Then come the closing quote,
    another semicolon, a 13 (to represent a carriage return), and the
    closing p.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*   asgnkey.c -- uses ansi.sys to assign meanings   */
    /*                to several function keys           */
    /*  Note: This requires ANSI.SYS to be installed.    */

    #define KASSIGN(K, S) printf("\033[0;%d;\"%s\";13p", K, S)
    /* This macro assigns string S to key K */
    #define F5 63
    #define F6 64
    #define F7 65
    #define F8 66
    #define F9 67
    #define F10 68
    main()
    {
        KASSIGN(F5, "DIR *.C");
        KASSIGN(F6, "DIR *.H");
        KASSIGN(F7, "DIR *.OBJ");
        KASSIGN(F8, "DIR *.EXE");
        KASSIGN(F9, "DIR /W");
        KASSIGN(F10,"CD \\");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-9.  The ASGNKEY.C program.

    Running this program changes the function key assignments, but you have to
    go to MS-DOS before you can see the effects. Once you exit to MS-DOS,
    pressing F5 through F8 causes MS-DOS to list the specified types of files
    (*.c, *.h, and so on). The F9 function key lists your directories in the
    compact form (the /W option). Also, F10 switches to the root directory.
    The defining string uses \\ for root because that is how you express a
    single \ in a C string. Because the code itself includes 13 for Return,
    you don't press Enter when using these function keys.

    You can easily modify this program to read in the desired function key
    number and the string interactively. But bear in mind that these
    assignments supersede existing ones and that they hold until you reboot.
    If, for example, you assign a function to F1, you override the editing
    function given to it by MS-DOS.

    Note that QuickC uses its own routines to read the keyboard, and it
    bypasses these function key definitions. So, while in QuickC, you still
    can use F5 to run a program. But if you call up an MS-DOS shell from
    QuickC, the new assignments apply.

Cursor and Screen Control

    Now let's apply the ANSI.SYS method to a simple menu model. The goal is to
    write a program that clears the screen and displays a simple menu with one
    choice highlighted. The Up Arrow and Down Arrow keys move the cursor and
    highlighting to a different choice, and pressing Enter selects the
    highlighted choice. To do this, we need more escape codes. Table 13-3 on
    the following page lists some representative examples from which we'll
    select the ones we need. Our program will use the various cursor control
    sequences to move the cursor. The highlighting of a choice is handled
    using the SGR (Set Graphics Rendition) escape sequence, which lets you
    specify certain "attributes." Each character to be displayed can be
    assigned an attribute that controls its presentation: color, reverse
    video, blinking, and so on. In Table 13-3, ESC[ represents the Escape
    character, and num is a numeric parameter for which you substitute a
    specific number. Numbering of rows and columns starts with 1. For all but
    the last code sequence, any omitted num is assumed to be 1.

    Table 13-3 ANSI.SYS Escape Sequences
â•“â”Œâ”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â•–
    Name           Mnemonic       Escape Code   Description
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Cursor         CUP            ESC[num;numH  Moves the cursor to the
    Position                                    position specified by the
                                                numeric parameters. The first
                                                num is the line number; the
                                                second is the column number.
    Cursor Up      CUU            ESC[numA      Moves the cursor up num lines
                                                in the same column.
    Cursor Down    CUD            ESC[num       Moves the cursor down num
                                                lines in the same column.
    Cursor Forward CUF            ESC[numC      Moves the cursor right num
    Name           Mnemonic       Escape Code   Description
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Cursor Forward CUF            ESC[numC      Moves the cursor right num
                                                columns.
    Cursor Back    CUB            ESC[numD      Moves the cursor left num
                                                columns.
    Erase Display  ED             ESC[u         Erases the entire display and
                                                homes the cursor.
    Set Graphics   SGR            ESC[numm      Sets character attributes as
    Rendition                                   indicated by num. Possible
                                                values include 0 for normal, 1
                                                for high intensity, 5 for
                                                blink, and 7 for reverse
                                                video.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€


    To highlight a line of text, we must first print the escape code for
    highlighting on that line and then print the text. To confine highlighting
    to the menu line, we turn off highlighting at the end of the menu output.

    To move the cursor and highlighting, we use getch() and the scan codes to
    detect when the arrow keys are pressed. If the Down Arrow key is pressed,
    for example, the program moves the cursor and reprints the menu, changing
    which line is highlighted. Listing 13-10 shows the completed MENU.C
    program, and Figure 13-4 on p. 419 shows the menu at work.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  menu.c -- uses ANSI.SYS for cursor control and   */
    /*            for video reverse in a sample menu     */
    /*  Note: Requires that ANSI.SYS be installed.       */

    #include <conio.h>
    #define ITEMS 5           /* number of menu items     */
    #define UP 72             /* scan code for up arrow   */
    #define DOWN 80           /* scan code for down arrow */
    #define VIDREV "\033[7m"  /* reverse video attribute  */
    #define ATTOFF "\033[0m"  /* turn attributes off      */
    #define ED()   printf("\033[2J")  /* erase display     */
    #define HOME() printf("\033[H")   /* home the cursor   */
    #define CUU(Y) printf("\033[%dA", Y);   /* cursor up   */
    #define CUD(Y) printf("\033[%dB", Y);   /* cursor down */

    char *Menu[ITEMS] = {"Add a number to the list",
                        "Delete a number from the list",
                        "Clear the list",
                        "Sum the list",
                        "Quit"};
    char *Heading =
    "Use arrow keys to highlight choice. "
    "Use Enter key to select choice.";

    void showmenu(int);
    int getmesg(int);
    main()
    {
        int messno = 0; /* message to be highlighted */
        ED();
        showmenu(messno);
        while (messno != ITEMS - 1)
            {
            messno = getmesg(messno);
            ED();
            switch (messno)
                {
                case 0 :
                case 1 :
                case 2 :
                case 3 : printf("...pretending to work...");
                        printf("Hit any key to continue\n");
                        getch();
                        ED();
                        showmenu(messno);
                        break;
                case 4 : printf("Quitting!\n");
                        break;
                default: printf("Programming error!\n");
                        break;
                }
            }
    }

    /* showmenu() displays the menu  */
    void showmenu(highlite)
    int highlite;   /* message number to be highlighted */
    {
        int n;
        char *start;
        HOME();
        printf("%s", Heading);
        for (n = 0; n < ITEMS; n++)
            {
            if (n == highlite)
                start = VIDREV; /* turn on reverse video */
            else
                start = ATTOFF;
            printf("\n\n%s%s%s", start, Menu[n], ATTOFF);
            }
        HOME();
        CUD(2 + 2 * highlite);
    }

    /*  getmesg() selects a menu item */
    int getmesg(mnum)
    int mnum; /* current message number */
    {
        char ch;
        while ((ch = getch()) != '\r')
            if (ch == 0)
                {
                ch = getch();
                switch (ch)
                    {
                    case UP   : if (mnum > 0)
                                    {
                                    CUU(2);
                                    showmenu (--mnum);
                                    }
                                else
                                    {
                                    CUD(2 * ITEMS - 2);
                                    showmenu(mnum = ITEMS - 1);
                                    }
                                break;
                    case DOWN : if (mnum < ITEMS - 1)
                                    {
                                    CUD(2);
                                    showmenu(++mnum);
                                    }
                                else
                                    {
                                    CUU(2 * ITEMS - 2);
                                    showmenu(mnum = 0);
                                    }
                                break;
                    }
                }
                return mnum;
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-10.  The MENU.C program.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 13-4 can be found on p.419 of the printed version of the book.  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 13-4. The MENU.C program at work.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Watching the Keyboard in BASIC and C
    The ANSI.SYS techniques discussed here allow you to achieve the
    functionality of the KEY statement in BASIC. The BASIC KEY n, string
    statement allows you to assign a string to the PC function key Fnâ”€â”€that
    is, to create a simple "keyboard macro." The ANSI method is more general
    (it can be used with any key, not just a function key) and is also not
    limited to assigning short strings.

    BASIC statements such as ON KEY provide a very useful facility called
    "event-driven programming." After you use the KEY statement to assign a
    key number to one of the keyboard keys, a press of that key while the
    program is running will be "trapped." The ON KEY(n) subroutine statement
    causes subroutine to be executed whenever the key that's assigned number n
    is pressed. This allows programs to respond to input immediately.

    C has no such built-in facilities. You can, however, put the program in an
    outer loop that calls the kbhit() function to see if a key has been
    pressed. If a key has been pressed, you can use getch() to read the key.
    After assigning the key to a variable of type char, you can use it in a
    switch statement that calls the appropriate function to handle the command
    received. This isn't true event-driven programming, because the response
    to a key comes only when the program is at the top of the loop, but QuickC
    programs run fast enough that the effect is often the same. The use of a
    special device driver or an environment such as Microsoft Windows can
    allow for true event-driven programming.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    The MENU.C program first defines several macros using printf() and the
    escape codes to represent some of the ANSI.SYS sequences from Table 13-3
    on p. 416. If you plan to use such macros often, you should create an
    include file for the macro definitions.

    Because we are illustrating ANSI.SYS and not numeric analysis, the program
    does no actual calculation. However, the switch statement in main()
    provides the skeleton for controlling program flow. The getmesg() function
    returns the array index of the selected message, and the switch selects a
    response based on that value. The switch is in a loop, so you can
    repeatedly make choices until you select Quit.

    In main(), the HOME() macro uses the CUP escape code to home the cursor.
    Because we omitted the two numeric parameters, the default values of 1 are
    used, which effectively home the cursor.

    The showmenu() function displays the menu. It receives the array index of
    the element to be highlighted. That message then starts with highlighting
    turned on; the other messages have it turned off.

    The getmesg() function, as we mentioned, returns the array index of the
    selected item. It also handles the cursor movement. In this function,
    getch() checks for the Up Arrow and the Down Arrow keys. If, for example,
    the Down Arrow key is pressed, CUD moves the cursor down two lines to the
    next message. The array index is also incremented to tell showmenu() which
    message to highlight. To keep the cursor inside the menu, we compare its
    position to the menu limits. If the cursor is on the bottom line of the
    menu, then pressing the Down Arrow key moves it to the top line.

    This program works as designed, but it runs slowly, and the redrawing of
    the screen is not very smooth. The ANSI.SYS approach to cursor and screen
    control is relatively simple, but using BIOS calls or direct memory access
    gives better performance.


Using QuickC to Access the BIOS

    One way to create programs that take advantage of the special capabilities
    of an IBM PC/XT, PC/AT, or compatible without getting too involved in the
    hardware is to use BIOS calls.

Background for the IBM BIOS

    BIOS is an acronym for Basic Input/Output System. It consists of a set of
    assembly-language routines permanently stored in what is called Read-Only
    Memory, or ROM, of the IBM PC. The computer can read and utilize
    information in ROM, but it cannot alter ROM. That preserves the integrity
    of the routines. The BIOS includes routines to read the keyboard, to
    control the video display, and to read from and write to disk drives. Most
    higher-level programming ultimately makes use of these routines. For
    instance, QuickC's getch() uses one of the keyboard routines, and many
    MS-DOS commands ultimately use the BIOS routines to do low-level work.

    In short, you can think of the BIOS as a built-in library of functions.
    All you need to do is find out what services are offered and how to use
    them.

    The ultimate source of information about the BIOS is the IBM Personal
    Computer Technical Reference Manual. This manual includes
    assembly-language listings of all the routines. We'll describe those
    routines as we use them.

Using the BIOS

    Two problems face the QuickC programmer who wants to use the BIOS. One is
    that the routines, which are written in assembly language, don't work the
    same as C functions, so you have to learn a little about assembly language
    and about the hardware to understand them. The second is that these BIOS
    routines are accessed not by function calls but by "interrupt signals."
    For this reason, these routines are commonly called "interrupt routines,"
    or simply "interrupts." Let's clarify this topic first.

    Interrupt Routines

    The heart of a PC is its central processing unit, or CPU, but a PC
    contains other processors, too. For example, the keyboard processor
    handles keyboard input, and another processor handles data flow between
    the CPU and memory. To enable the CPU to keep in touch with its
    environment, an interrupt system was developed. Certain devices and
    assembly-language instructions can generate signals that take control of
    the microprocessor. The Intel 8086 family of microprocessors permits as
    many as 256 distinct interrupt signals, but fewer are actually used. When
    the CPU detects an interrupt signal, it "interrupts" its current activity
    and executes the set of assembly-language instructions identified with
    that particular signal.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    How Interrupts Work
    When you boot a PC, it sets up a table of addresses known as the
    "interrupt vectors." At the first address is the routine to be executed if
    interrupt signal 0 is detected. At the second address is the routine to be
    executed if interrupt signal 1 is detected, and so on. When an interrupt
    is detected, the corresponding address is found in the table, and the
    instructions beginning at that address are executed. At the end of those
    instructions, a "return from interrupt" instruction tells the
    microprocessor to resume its interrupted activity.

    The operating system also uses the interrupt table. When MS-DOS or PC-DOS
    is first loaded, it adds its own batch of interrupt routines. Memory
    resident programs also work by storing their addresses in the interrupt
    vector table. Incidentally, MS-DOS can substitute its own version of a
    ROM-based BIOS routine by overwriting the appropriate interrupt vector
    with a new address. The ROM itself is unchanged, but the computer is
    directed to the new address instead when the interrupt is issued. This
    method is sometimes used as a software "fix" for faulty BIOS routines.
    (The only way to update the actual BIOS is to get a newer version of the
    ROM chip.)
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Software Interrupts

    In assembly language, generating interrupts is simple. For example, to
    generate interrupt signal 0x10 (the video I/O interrupt), you use the
    following instruction:

    int 10h

    What if one interrupt arrives while another interrupt routine is
    executing? This situation is handled by a priority ranking. A
    higher-priority interrupt can interrupt a lower-priority routine, but not
    vice versa.

    C, as a general, portable language, doesn't have a built-in interrupt
    instruction. But the QuickC library offers several non-ANSI C functions
    designed to serve the same purpose. Seven functions make specific BIOS
    calls; they all have names beginning with _bios_ and are declared in the
    bios.h file. The dos.h file declares another 40 functions, most of which
    call specific MS-DOS functions. (Interrupt number 0x21 can be used to
    access many functions loaded into the system by MS-DOS; these are the
    MS-DOS system calls.) Five of the dos.h functions, however, are more
    general and can invoke a choice of interrupts. (See Table 13-4 for a
    summary of these functions.)

    We will use the int86() function because it is generally applicable. As
    its name suggests, it generates a specified interrupt for the 8086 family
    of microprocessors. However, before we can use this function, we have to
    see how interrupt routines use registers to transfer data.

    Table 13-4 Interrupt-accessing Functions in Order of Decreasing Generality
    Name               Use
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    intx86()           Invokes interrupts requiring the use of segment
                        registers.
    int86()            Invokes interrupts not requiring use of the segment
                        registers.
    intxdos()          Invokes MS-DOS system calls requiring the use of
                        segment registers.
    intdos()           Invokes MS-DOS system calls not requiring use of the
                        segment registers.
    bdos()             Invokes MS-DOS system calls that use only the DX and AL
                        registers.
    _bios_...() family Invokes specific BIOS interrupts.
    _dos_...() family  Invokes specific MS-DOS calls.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Interrupts, Assembly Language, and Registers

    Like C functions, interrupts pass information back and forth between the
    routine and the calling program. Instead of using arguments, however,
    interrupts use the microprocessor registers. The int86() function gets
    around this difference by using unions to pass the register information to
    and from the calling C program.

    Registers are small work and storage areas built into the CPU. For
    example, the 8088 chip, the most commonly used member of the 8086 family,
    has 13 registers, each capable of holding 16 bits. Four of the registers
    are general-purpose registers used for arithmetic and logical operations;
    they are called AX, BX, CX, and DX. Four "segment" registers store the
    addresses of various memory segments; these registers are called CS, DS,
    SS, and ES. Four more "pointer/index" registers keep track of addresses
    used in a program; they are called SP, BP, SI, and DI. Finally, the
    instruction pointer (IP) keeps track of the address of the next
    instruction to be executed. Also, the processor has nine "flags" that can
    be turned on or off. The flags can be considered to be individual bits in
    a flag register. These, then, are the resources open to an interrupt
    routine.

    There is one further complication. Each of the general-purpose registers
    can be considered to be two 8-bit registers. The AX register, for example,
    can be divided into the AH (H for high byte) and the AL (L for low byte)
    registers. Assigning a value to the AX register affects the whole
    register, but assigning a value to AL or AH affects only half of the
    register. Similarly, the BX register is divided into the BH and BL
    registers, and so on.

    Now that we have some background about registers, let's see how int86()
    works.

The int86() Function

    The int86() function will be our tool for initiating interrupt routines,
    initializing registers, and reading registers. Its library description
    begins with the following:

    #include <dos.h>
    int int86(intno, inregs, outregs);
    int intno;           /* Interrupt number */
    union REGS *inregs;  /* Register values on call */
    union REGS *outregs; /* Register values on return */

    This syntax summary says to include the dos.h header file when using this
    function. Also, int86() takes three arguments. The first is the number of
    the desired interrupt. The second is the address of a union containing the
    register values passed to the interrupt. The third is the address of the
    union into which the post-interrupt register values are copied.

    To use int86(), you need to know how the type union REGS is defined. That
    information resides in the dos.h file, as follows:

    /* word registers */

    struct WORDREGS {
            unsigned int ax;
            unsigned int bx;
            unsigned int cx;
            unsigned int dx;
            unsigned int si;
            unsigned int di;
            unsigned int cflag;
            };

    /* byte registers */

    struct BYTEREGS {
            unsigned char al, ah;
            unsigned char bl, bh;
            unsigned char cl, ch;
            unsigned char dl, dh;
            };

    /* general-purpose registers union -- overlays the
    corresponding word and byte registers. */

    union REGS {
            struct WORDREGS x;
            struct BYTEREGS h;
            };

    Together, these definitions give two views of the registers.

    The WORDREGS structure provides the 16-bit view. This structure has seven
    members representing the four general-purpose registers, two of the
    pointer registers, and the "carry" flag (which we won't use). These are
    the registers most commonly used by the interrupts. (The int86x() function
    uses an additional structure to give access to more registers.) In this
    structure, for example, the ax member represents the AX register.

    The BYTEREGS structure gives the 8-bit view. This structure represents the
    four general-purpose registers, with each register split into two 1-byte
    registers. Thus, the ch member of this structure represents the CH
    register, the high byte of CX.

    The unusual part of this function is the definition of the union REGS. It
    superimposes the word view and the byte view. For example, suppose you use
    the following declaration:

    union REGS myreg;

    To assign a value to the AX register, use a statement such as the
    following:

    myreg.x.ax = 1026;

    The .x notation specifies the WORDREGS member of myreg; therefore,
    myreg.x.ax is the AX member of that structure.

    To assign a value to the BL register (the low byte of the BX register),
    use the following .h notation:

    myreg.h.bl = 22;

    This specifies the BYTEREGS member of the union.

    Recall that a union uses the same storage area for all its members. This
    means that myreg.h.al and myreg.h.ah overlie myreg.x.ax. To get the high
    byte of the 1026 that was assigned to myreg.x.ax, refer to myreg.h.ah (see
    Figure 13-5).

    union REGS myreg;
                                        word
                    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                    / â”‚                   â”‚                   â”‚ \  AX register
                /   â”‚              myreg.x.ax               â”‚   \
                /     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     \
            /     / â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ /â”€â”€â”€/â”€â”€â”¬â”€â”€\â”€â”€â”€\â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â” \     \
            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”/   /    â”‚    \   \â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
            â”‚     one byte      â”‚  /      â”‚      \  â”‚     one byte      â”‚
            â”‚    myreg.h.ah     â”‚/â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€\â”‚    myreg.h.al     â”‚
    AH    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜  AL
    register         â”‚                   â”‚                   â”‚        register
                    â”‚                   â”‚                   â”‚
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                    â”‚                   â”‚                   â”‚ DX
                    â”‚                   â”‚                   â”‚
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    For a REGS union: .x means the 16-bit version
                    .h means the 8-bit version

    Figure 13-5. The REGS union.

    You now know enough theory to use int86(). However, you still need to know
    what values to pass as arguments to the BIOS routines. Let's look at a
    simple example.

Interrupt 0x16â”€â”€The Keyboard I/O Interrupt

    Because we have been discussing the keyboard, let's look at interrupt
    routine 0x16, which reads the keyboard. The QuickC library provides the
    _bios_kbrd() function to access this specific routine. However, we will
    use int86() in order to demonstrate a more general approach to using
    interrupts.

    Like many interrupts, 0x16 includes more than one subroutine. It has three
    subroutines; each is termed a "function" or "service." To select a
    particular function, you must place the "function code" number in the AH
    register before calling the interrupt. Let's take a look at what each
    function does.

    Interrupt 0x16, Function Code 0â”€â”€Get Character

    This function reads the keyboard buffer if a character is present;
    otherwise, it waits until a keystroke is placed in the buffer. When it
    reads a key, it places the ASCII byte in the AL register and the scan byte
    in the AH register. (Note that the return values are written over the
    values we originally placed in AH and AL.) The code is removed from the
    keyboard buffer once it is read. The getch() function is based on this
    function.

    Interrupt 0x16, Function Code 1â”€â”€Check Keyboard Buffer

    This function checks to see if the keyboard buffer is empty or not. If it
    is empty, the "zero flag" (ZF) is set to 1; otherwise, the flag is cleared
    (set to zero). If a character is present, the ASCII byte is placed in AL
    and the scan byte in AH, but the code in the buffer is left there. The
    kbhit() function is based on this function.

    Interrupt 0x16, Function Code 2â”€â”€Get Keyboard Status

    This function reports on the status of the Shift and Ctrl keys. Each of
    eight keys is assigned a particular bit in the AL register. If one of the
    eight keys is closed, the corresponding bit is set to 1. Table 13-5 shows
    the corresponding bits and keys.

    Table 13-5 Keyboard Status Bits
    Bit         Set to 1 If
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    0           Right Shift is closed
    1           Left Shift is closed
    2           Ctrl is closed
    3           Alt is closed
    4           Scroll Lock is active
    5           Num Lock is active
    6           Caps Lock is active
    7           Insert mode is active
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Reading ASCII and Scan Codes

    Let's use function code 0 to construct a more general version of getch()
    that we'll call Readkey(). It will return both the ASCII and the scan
    bytes. Using it will give you a better picture of how the keyboard codes
    work and show you that using interrupts from QuickC is not all that
    difficult. The readkey.c program (Listing 13-11) contains the Readkey()
    function.

    The dos.h file defines the union REGS type and declares the int86()
    function. We define symbolic constants to represent the interrupt number
    and the function code number. Finally, we define a two-member structure
    called SCANCODE for holding the two keyboard codes. Readkey() uses the reg
    structure to set the AH register to the proper function code and then it
    calls int86(). Because preserving the original register values is
    unnecessary, the same structure stores both the input values and the
    returned values of the registers. Finally, the program copies the two
    relevant register values into the structure that the function returns.

    The int86() syntax calls for two pointers to union REGS as arguments. In
    practice this usually calls for using the address operator applied to the
    appropriate union, as we have done here.

    Having developed the Readkey() function, let's use it in the next program,
    SHOWCODE.C, (Listing 13-12). To run this program within the QuickC
    environment, be sure that Screen Swapping On is active (on the Debug
    menu).

    This program reads a key, prints it (if it is printable), and displays
    both the ASCII and scan codes. Using it can be instructive. Following, for
    example, is the output for m, Shift-M, Ctrl-M, Alt-M, Enter, and Esc:

        m: ascii = 109, scan =  50â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€m
        M: ascii =  77, scan =  50â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Shift-M
    ^M: ascii =  13, scan =  50â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Ctrl-M
        : ascii =   0, scan =  50â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Alt-M
    ^M: ascii =  13, scan =  28â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Enter
    ^[: ascii =  27, scan =   1â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Esc

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* readkey.c -- contains the Readkey() function     */
    #include <dos.h>
    #define KEYINTR 0x16  /* keyboard read interrupt */
    #define GETCHAR 0     /* read scancode function  */
    struct SCANCODE {
                    unsigned char ascii;  /* ascii code */
                    unsigned char scan;   /* scan code  */
                    };

    struct SCANCODE Readkey()
    {
        union REGS reg;
        struct SCANCODE scancode;

        reg.h.ah = GETCHAR;         /* specify function   */
        int86(KEYINTR, &reg, &reg); /* note use of & oper.*/
        scancode.ascii = reg.h.al;
        scancode.scan = reg.h.ah;
        return (scancode);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-11.  The readkey.c function.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  showcode.c -- shows ASCII and scan codes for    */
    /*                keystrokes                        */
    /* Note: Set Screen Swapping On in the Debug menu.  */
    #include <stdio.h>
    #include <dos.h>
    #define KEYINTR 0x16  /* keyboard read interrupt */
    #define GETCHAR 0     /* read scancode function  */
    #define ESC '\033'    /* escape key              */
    struct SCANCODE {
                    unsigned char ascii;  /* ascii code */
                    unsigned char scan;   /* scan code  */
                    };
    struct SCANCODE Readkey();

    main()
    {
        struct SCANCODE keys;

        printf("Press keys to see their scancodes. ");
        printf("Press the Esc key to quit.\n");
        do  {
            keys = Readkey();
            if (keys.ascii > 0 && keys.ascii < 040)
                printf("^%c: ascii = %3d, scan = %3d\n",
                        keys.ascii + 0100, keys.ascii,
                        keys.scan);
            else if (keys.ascii >= 40)
                printf(" %c: ascii = %3d, scan = %3d\n",
                        keys.ascii, keys.ascii, keys.scan);
            else
                printf("  : ascii = %3d, scan = %3d\n",
                        keys.ascii, keys.scan);
            } while (keys.ascii != ESC);
    }

    struct SCANCODE Readkey()
    {
        union REGS reg;
        struct SCANCODE scancode;

        reg.h.ah = GETCHAR;
        int86(KEYINTR, &reg, &reg);
        scancode.ascii = reg.h.al;
        scancode.scan = reg.h.ah;
        return (scancode);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-12.  The SHOWCODE.C program.

    The scan code for the first four characters is the same (50) because the
    same primary key (the M key) was used in each case. The modifying key, if
    any, then caused the ASCII part of the code to be changed. Note how the
    ASCII part for Alt-M is 0. Also note how the Enter key has the same ASCII
    code as Ctrl-M but a different scan code. The scan code is different
    because a different physical key was pressed. Incidentally, if you need to
    write a program that discriminates between input of Ctrl-M and the Enter
    key, you can use Readkey() to check the scan code. (The getch() function
    cannot distinguish between the two keystrokes.)

    The following represents another sample run; this time the input is F1,
    Ctrl-F1, Shift-F1, Alt-F1, and Esc:

        : ascii =   0, scan =  59â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€F1
        : ascii =   0, scan =  94â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Ctrl-F1
        : ascii =   0, scan =  84â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Shift-F1
        : ascii =   0, scan = 104â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Alt-F1
    ^[: ascii =  27, scan =   1â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Esc

    In this example, the scan code changes even though the same primary key
    was pressed each time. With ASCII characters, the ASCII code discriminates
    among diferent combinations, but with the control keys, the ASCII byte is
    always 0, so the scan code itself must change. Also, notice that these
    keystrokes are nonprinting; therefore, the program displays only the
    codes.

    Finally, this example uses the following input: 1, the End key, Shift-End,
    and Esc:

    1: ascii =  49, scan =   2â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€|
        : ascii =   0, scan =  79â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€End
    1: ascii =  49, scan =  79â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Shift-End

    Note how Shift-End and 1 produce the same ASCII code (49) but different
    scan codes (2 and 79). We mention this because the QuickC editor uses the
    Shift-End combination to highlight a line. If the programming for QuickC
    relied on getch(), that would be impossible to do. Apparently QuickC, like
    our program, checks the scan code too. This lets it assign a different
    function to Shift-End.


Cursor and Screen Control with BIOS Calls

    Now that you know how to use interrupts, we can extend that technique to
    cursor and screen control. To illustrate these applications, we will
    construct a rudimentary first step toward a word processor. With this
    program, you can do the following:

    â–   Start with a clear screen.

    â–   Enter text from the keyboard and see it on the screen.

    â–   Use the arrow keys to move the cursor.

    â–   Use the function keys to turn highlighting on and off.

    â–   Highlight or unhighlight existing text by moving the cursor over it.

    To provide these features, we'll construct a library of approximately a
    dozen BIOS-based functions. Rather than jumping back and forth between
    program development and BIOS use, we'll develop the entire library first.

    Incidentally, the QuickC Graphics Library, which we discuss in Chapter
    15, provides an alternative means for implementing these features. Using
    the Graphics Library, however, produces executable programs substantially
    larger than those using the BIOS approach.

The Video I/O Interrupt

    The first step is to find the appropriate interrupt routine. Interrupt
    0x10, the video I/O interrupt, controls the display. Because maintaining a
    video display is more complex than monitoring a keyboard, this interrupt
    turns out to be much more involved than the keyboard I/O interrupt. It
    provides many subroutines, or functions, and many of them use several
    registers. Table 13-6 on the following pages lists and describes the
    functions we use in this book. The table mentions "attributes" and
    "pages." Attributes, as we saw in our discussion of ANSI.SYS, determine
    how a character is to be displayed. A page is a screenful of display. Some
    video modes can store more than one page at once, although only one can be
    displayed at any given time. We discuss these terms further as needed.

    When using int86() to invoke these functions, you set AH to the
    appropriate function code number and initialize any other registers given
    in the description. The first argument to int86() should be 0x10, the
    interrupt number.

    Table 13-6 Selected Video I/O Interrupt 0x10 Functions
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    FUNCTION CODE 0: Set the Display Mode
    Action:            Switches to desired mode and clears display.
    Register setup:    Place 0 in AH
                        Place desired mode in AL

    Choose from the following modes:
    Mode               Meaning
    0                  40 x 25 B/W Text
    1                  40 x 25 Color Text
    2                  80 x 25 B/W Text
    3                  80 x 25 Color Text
    4                  320 x 200 Color Graphics
    5                  320 x 200 B/W Graphics
    6                  640 x 200 B/W Graphics
    7                  80 x 25 Monochrome
    13                 320 x 200 Color EGA
    14                 640 x 200 Color EGA
    15                 640 x 350 B/W EGA
    16                 640 x 350 Color EGA
    17                 640 x 480, 2-Color VGA
    18                 640 x 480, 16-Color VGA
    19                 320 x 200, 256-Color VGA

    FUNCTION CODE 2: Select Cursor Position
    Action:            Moves cursor to the specified row and number.
    Register setup:    Place 2 in AH
                        Place row number in DH
                        Place column number in DL
                        Place page number in BH

    Numbering of rows and columns starts with 0, not 1.

    FUNCTION CODE 3: Read Cursor Position
    Action:            Reports the row and column of cursor position.
    Register setup:    Place 3 in AH
                        Place page number in BH
    Returns:           Row number is in BH
                        Column number is in DL
                        Cursor type is in CH, CL

    FUNCTION CODE 5: Select Active Display Page
    Action:            Selects the page for modes supporting multiple pages.
    Register setup:    Place 5 in AH
                        Place page number in AL

    FUNCTION CODE 6: Scroll Up an Area of the Screen
    Action:            Scrolls up a section of the screen a specified amount.
    Register setup:    Place 6 in AH
                        Place number of lines to scroll in AL (0 in AL produces
                        a blank window)
                        Place blank-line attribute in BH
                        Place upper-left row number in CH
                        Place upper-left column number in CL
                        Place lower-right row number in DH
                        Place lower-right column number in DL

    FUNCTION CODE 8: Read Character and Attribute
    Action:            Reports the character and attribute code at the current
                        cursor position.
    Register setup:    Place 8 in AH
                        Place page number in BH (text modes)
    Returns:           Character at cursor is in AL
                        Attribute at cursor is in AH

    FUNCTION CODE 9: Write Character and Attribute
    Action:            Writes a specified character and attribute to the
                        current cursor position.
    Register setup:    Place 9 in AH
                        Place page number in BH (text modes)
                        Place character in AL
                        Place attribute (text modes) or color (graphics modes)
                        in BL
                        Place number of characters in CX

    Note: The character is written the indicated number of times starting at
    the current cursor position; the cursor position remains unchanged.

    FUNCTION CODE 15: Return Current Video State
    Action:            Reports the video mode, number of text columns, and the
                        current page value.
    Register setup:    Place 15 in AH
    Returns:           Current mode is in AL
                        Number of columns is in AH
                        Current active page number is in BH
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Developing a Library of C Functions

    Our next step is to develop a set of C functions that use the video I/O
    interrupt. In this section, we will design several functions, each general
    enough to be useful for a variety of programs. We'll develop the functions
    individually but then collect them in one file so that they can share a
    common set of include files and definitions. You'll find the contents of
    this combined file, which is called SCRFUN.C, in Listing 13-23 beginning
    on p. 441. Finally, we'll use the LIB utility to make a library of the
    video functions.

    Setting the Cursor

    First, we need two C functions: one to set the cursor and another to
    report the current cursor position. We use functions 2 and 3 of the video
    interrupt to develop our own Setcurs() and Getcurs() functions (Listing
    13-13).

    Pass the desired row, column, and page to Setcurs(), and it positions the
    cursor. Use Getcurs() to place row and column information in variables
    whose addresses we pass. What about the page variable? For now, use the
    default value of 0. The following SETCURS.C program (Listing 13-14) is a
    short example that uses Setcurs() to see if our programming is on the
    right track.

    After you type in a row and column in the form 10 20, the program places
    the cursor there and then prints a message starting at that location. It's
    not a spectacular program, but it shows that our function is working
    correctly. As we build this library with other functions, you might want
    to write similar test programs. With QuickC it doesn't take long to do.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    #include <dos.h>
    #define VIDEO 0x10
    #define SETCURSOR 2
    #define GETCURSOR 3

    /* Setcurs() -- sets cursor to given row, column */
    void Setcurs(row, col, page)
    unsigned char row, col, page;
    {
        union REGS reg;

        reg.h.ah = SETCURSOR;
        reg.h.dh = row;
        reg.h.dl = col;
        reg.h.bh = page;
        int86(VIDEO, &reg, &reg);
    }

    /* Getcurs() -- reports current cursor position */
    void Getcurs(pr, pc, page)
    unsigned char *pr, *pc, page;
    {
        union REGS reg;

        reg.h.ah = GETCURSOR;
        reg.h.bh = page;
        int86(VIDEO, &reg, &reg);
        *pr = reg.h.dh;  /* row number */
        *pc = reg.h.dl;   /* column number */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-13.  The setcurs() function.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* setcurs.c -- moves cursor, checks out Setcurs() */
    #include <dos.h>
    #include <stdio.h>
    #define VIDEO 0x10
    #define SETCURSOR 2
    void Setcurs(unsigned char, unsigned char,
                unsigned char);
    main()
    {
        int row, col;

        printf("Enter row and column: (q to quit)\n");
        while (scanf("%d %d", &row, &col) == 2)
        {
            Setcurs(row, col, 0);
            printf("Enter row and column: (q to quit)");
        }
    }

    /* Setcurs() -- sets cursor to row, column, and page */
    void Setcurs(row, col, page)
    unsigned char row, col, page;
    {
        union REGS reg;

        reg.h.ah = SETCURSOR;
        reg.h.dh = row;
        reg.h.dl = col;
        reg.h.bh = page;
        int86(VIDEO, &reg, &reg);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-14.  The SETCURS.C program.

    Setting the page to 0 worked fine in our example; however, we may need to
    use pages later, so let's look at that topic.

    Getting and Setting the Page

    The information displayed on the screen is read from a dedicated section
    of memory called video memory. The amount of memory available depends upon
    the video adapter. In some modes, video memory can hold two or more
    screenfuls of data. In those cases, you can divide video memory into
    separate pages, one page per screenful. This lets a program alter one page
    in memory while displaying the other on the screen. To set a page, we will
    use the Setpage() function (Listing 13-15 on the following page).

    By default, screen modes start at page 0, and we'll also use that page for
    a while. But to keep our programming general, we need a function that can
    tell our code which is the current page. We use function 15 to develop the
    QuickC Getpage() function (Listing 13-16). The interrupt function places
    the page number in the BH register, and the function returns that value to
    the program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* Setpage() -- sets page to given value */
    #include <dos.h>
    #define VIDEO 0x10
    #define SETPAGE 5
    void Setpage(page)
    unsigned char page;
    {
        union REGS reg;

        reg.h.ah = SETPAGE;
        reg.h.al = page;
        int86(VIDEO, &reg, &reg);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-15.  The Setpage() function.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* Getpage() -- obtains the currently active page */
    #include <dos.h>
    #define VIDEO 0x10
    #define GETMODE 15
    unsigned char Getpage()
    {
        union REGS reg;

        reg.h.ah = GETMODE;
        int86(VIDEO, &reg, &reg);
        return reg.h.bh;
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-16.  The Getpage() function.

    Clearing the Screen

    Another useful function is one that clears the screen. None of the
    interrupt functions specialize in that, but the Scroll Up function
    (function 6) can perform this task. Note in Table 13-6 that if register
    AL is set to zero, the entire designated area is cleared. However, several
    other registers also must be set. You define the area to be cleared by
    giving the coordinates of the upper-left and the lower-right corners.

    The BIOS routine starts numbering with 0, unlike ANSI.SYS, which starts
    with 1. This means the upper-left row and column are 0, the lower-right
    row is 24, and the lower-right column is 79. (We assume you're using an
    80-by-25 display.) The least straightforward register setting is the
    attribute setting for blank lines in register BH. An attribute is a value
    in the range 0 through 255 that modifies the display. The normal attribute
    is 7 for a "white-on-black" display. ("White" is white on a color display,
    but on a monochrome monitor "white" usually is green or amber.) Other
    values produce reverse video, blinking, underlining (on some monitors),
    and colors (on some monitors). We'll use the value 7.

    We use these register values to construct the following Clearscr()
    function (Listing 13-17).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  Clearscr() -- clears the screen          */
    #include <dos.h>
    #define VIDEO 0x10
    #define SCROLLUP 6
    #define ROWS 25
    #define COLS 80
    void Clearscr()
    {
        union REGS reg;

        reg.h.ah = SCROLLUP;
        reg.h.al = 0;       /* clear the window */
        reg.h.ch = 0;
        reg.h.cl = 0;
        reg.h.dh = ROWS - 1;
        reg.h.dl = COLS - 1;
        reg.h.bh = NORMAL;
        int86(VIDEO, &reg, &reg);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-17.  The Clearscr() function.

    Reading and Writing Characters and Attributes

    Before we use BIOS routines to read from and write to the screen, you need
    to know how the video system works. The video adapter has its own memory,
    which it uses to represent the screen. Let's concentrate for now on the
    80-by-25 text modes, the ones you probably use most often. All standard
    IBM video controllers (Monochrome, CGA, EGA, MCGA, and VGA) use the same
    scheme for their 80-by-25 text modes, so this discussion applies to all.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    If you are ambitious, you can generalize this function to work with
    40-by-25 displays by using function 15 of the 0x10 interrupt to find the
    number of columns actually being used. A call to function 15 places that
    number of columns into the AH register. Subtract 1 from this number (to
    account for the fact that column numbering begins with column 0), save the
    result, and assign it to the DL register before you call function 6.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    You can think of an 80-by-25 screen as holding 2000 cells, each capable of
    displaying a character. Each cell is represented by two bytes in the video
    memory. One byte holds the code for the character, and the second byte
    holds the attribute, which determines how the character is displayed. When
    a program sends output to the screen, the characters actually are first
    stored in video memory. A microprocessor called a video controller then
    scans the video memory, mapping the characters it finds there to the
    screen. Video interrupt 0x10 functions 8 and 9, which read and write
    characters and attributes to the screen, actually work with the video
    memory. (The monochrome display system uses a different memory address
    from the others, but the BIOS calls adjust for that.)

    The character code consists of the usual ASCII code plus extensions to the
    code that enable certain non-ASCII characters to be displayed on the
    screen. (IBM provides 128 such additional characters in its extended
    character set.) The attribute code also is simple, especially for
    black-and-white displays. Think of the attribute byte as a series of eight
    bits, numbers 7 to 0, left to right. To generate the normal
    black-and-white display, set the bits to 00000111. To produce reverse
    video, set the bits to 01110000. Note that these binary values translate
    to 0x7 and 0x70, respectively.

    In addition, you can intensify the foreground display by setting bit 3 to
    1 or put the display in "blink" mode by setting bit 7 to 1. The attributes
    we've discussed here produce white-on-black (or black-on-white) characters
    for the monochrome display and for color-text displays. We discuss
    color-related attributes in Chapter 14.

    To produce both normal and reverse video, our program must write the
    attribute as well as the character. We use video I/O function 9 instead of
    putch(), because the latter writes only characters, not attributes. Our
    Write_ch_atr() C function (Listing 13-18) uses that interrupt routine.
    This function writes the character-attribute pair num times to display a
    single pair several times in a row. We will use a num value of 1, but to
    preserve generality, we did not build that value into the function.

    One of our program goals was converting normal text to reverse video by
    passing the cursor over it. You can do that simply by changing the
    attribute at the cursor location. Because no BIOS function merely changes
    an attribute, we need to write a character-attribute pair. One way to do
    this is to read the current character from the screen and to then rewrite
    it using a different attribute. So let's start by devising a Read_ch_atr()
    (Listing 13-19) function to read the character and attribute at the
    current cursor location.

    Because the function must return two values, we pass it the addresses of
    the two variables to which the values will be assigned. To read the
    character and attribute at the current cursor position on page 0 into the
    variables ch and attr, make this call:

    Read_ch_atr(&ch, &attr, 0);

    We also could have the function return a two-member structure.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* Write_ch_atr() -- writes characters and attributes */
    #include <dos.h>
    #define VIDEO 0x10
    #define WRITECHATR 9
    void Write_ch_atr(ch, atr, page, num)
    unsigned char ch, atr, page;
    unsigned int num;
    {
        union REGS reg;

        reg.h.ah = WRITECHATR;
        reg.h.al = ch;
        reg.h.bl = atr;
        reg.h.bh = page;
        reg.x.cx = num;
        int86(VIDEO, &reg, &reg);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-18.  The Write_ch_atr() function.

    Now we use the last two functions to produce the function our program
    requires. The Rewrite() function (Listing 13-20 on the following page)
    reads the current character and rewrites it with a potentially changed
    attribute.

    If speed is an issue, which it usually isn't for keyboard input, you can
    speed up Rewrite() by having it use int86() to call the read and write
    BIOS functions directly instead of going through Read_ch_atr() and
    Write_ch_atr().

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* Read_ch_atr() -- reads character and attribute at     */
    /*                  cursor location                      */
    #include <dos.h>
    #define VIDEO 0x10
    #define  READCHATR 8
    void Read_ch_atr(pc, pa, page)
    unsigned char *pc, *pa;
    unsigned char page;
    {
        union REGS reg;

        reg.h.ah = READCHATR;
        reg.h.bh = page;
        int86(VIDEO, &reg, &reg);
        *pc = reg.h.al;  /* character at cursor */
        *pa = reg.h.ah;  /* attribute at cursor */
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-19.  The Read_ch_atr() function.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* Rewrite() -- changes attribute of on-screen  */
                    character                       */
    void Read_ch_atr(), Write_ch_atr(); /* used by  */
                                        /* Rewrite()*/
    void Rewrite(at, page)
    unsigned char at, page;
    {
        unsigned char ch, atr;

        Read_ch_atr(&ch, &atr, page);
        Write_ch_atr(ch, at, page, 1);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-20.  The Rewrite() function.

    More Cursor Movement

    We already have a function to set the cursor at a given row or column. But
    our primitive text editor really needs functions to move the cursor one
    column to the right when the Right Arrow key is pushed, and so on. We can
    use Setcurs() to create such functions. The Cursrt_lim() function (Listing
    13-21) demonstrates how to construct a right-movement function.

    Getcurs() and Setcurs() require the current page number; the Cursrt_lim()
    function uses Getpage() to obtain that information. Also, the function
    prevents the cursor from going past the column defined by limit. Our
    program will use a limit of 79, corresponding to the right side of the
    screen, but the numeric value is not built into the function. This
    variable limit lets you use the function with a program that confines the
    cursor to a section of the screen or with one that uses a 40-column
    screen.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* Cursrt_lim() -- moves cursor one space to the       */
                        right, but not past a set limit     */
    void Getcurs(), Setcurs();  /* functions used   */
    unsigned char Getpage();    /* by this function */

    unsigned char Cursrt_lim(limit)
    unsigned char limit;
    {
        unsigned char row, col, page;
        unsigned char status = 1;

        Getcurs(&row, &col, page = Getpage());
        if (col < limit)
            Setcurs(row, col + 1, page);
        else
            status = 0;
        return status;
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-21.  The Cursrt_lim() function.

    Also, the program uses a return value to inform the calling program
    whether the cursor reached its limit. This gives the calling program the
    option of responding in some way, such as beeping or moving the cursor to
    the beginning of the next line, whenever the limit is reached.

    We can modify Cursrt_lim() to create functions corresponding to the other
    arrow keys. We'll show you these when we gather all the functions together
    into one file.

    Putting the Library Together

    By now we've created a small library of short, BIOS-based C functions.
    Before we use them in our intended sample program, let's reflect on how to
    organize this block of functions. One method is to give each its own file.
    Then, when we want to use a particular function in a program, we can add
    its filename to the QuickC programming list. Or we can simply append the
    function file to the program file. Another approach is to consolidate all
    the functions into one file and to add that file to the program list. This
    is more convenient, but it might result in adding code to your program for
    functions it doesn't use. If you use the functions frequently, the most
    satisfactory approach is to make a library file for them. (This procedure
    was described in Chapter 12.)

    Here's one way to make the library. Open the SCRFUN.C file from QuickC.
    Choose Compile from the Run menu and specify the Obj option. Then choose
    Compile File to produce a file called SCRFUN.OBJ. Now go to MS-DOS and
    enter the LIB command. Answer the prompts as shown:

    Library name: scrfun
    Library does not exist: create? y
    Operations: +scrfun
    List file: scrfun

    The LIB command creates a library file called SCRFUN.LIB in the current
    directory. You can then copy it to your library directory. The LIB command
    also creates a text file called SCRFUN that lists the names of the
    functions in the library.

    To help organize these functions, gather all the defined constants
    together into an include file. To this file, add function prototypes for
    all the functions. Then you can use this include file with your program.
    You still must incorporate the actual code by appending the source files
    or adding files to the program list or by using a library, but using the
    include file saves you the trouble of having to declare the functions. It
    also includes definitions useful to a program. We'll use the scrn.h
    include file (Listing 13-22 on the following page) for our programs.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* scrn.h -- header file for BIOS video I/O functions */
    /*           contained in scrfun.c and scrfun.lib     */
    #define VIDEO 0x10
    #define SETMODE 0
    #define SETCURSOR 2
    #define GETCURSOR 3
    #define SETPAGE 5
    #define SCROLL 6
    #define READCHATR 8
    #define WRITECHATR 9
    #define GETMODE 15
    #define NORMAL 0x7
    #define VIDREV 0x70
    #define INTENSE 0x8
    #define BLINK 0x80
    #define COLS 80
    #define ROWS 25
    #define TEXTBW80 2
    #define TEXTC80 3
    #define TEXTMONO 7

    void Clearscr(void),
        Setvmode(unsigned char),
        Setpage(unsigned char),
        Setcurs(unsigned char, unsigned char,
                unsigned char),
        Read_ch_atr(unsigned char *, unsigned char *,
                    unsigned char),
        Write_ch_atr(unsigned char, unsigned char,
                    unsigned char, unsigned int),
        Rewrite(unsigned char, unsigned char),
        Getcurs(unsigned char *, unsigned char *,
                unsigned char);

    unsigned char Getvmode(void),
                Getpage(void),
                Curslt_lim(unsigned char),
                Cursrt_lim(unsigned char),
                Cursup_lim(unsigned char),
                Cursdn_lim(unsigned char);

    /* macro definitions */

    #define Home()        Setcurs(0, 0, Getpage())
    /* the next four macros set cursor limits to the      */
    /* full screen                                        */
    #define Curslt()      Curslt_lim(0)
    #define Cursrt()      Cursrt_lim(COLS - 1)
    #define Cursdn()      Cursdn_lim(ROWS - 1)
    #define Cursup()      Cursup_lim(0)
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-22.  The scrn.h include file.

    The scrn.h file includes some function numbers that we won't use until
    later chapters. It also has some constants that we'll use in our program.
    Finally, note the macros at the end of the file. The Home() macro homes
    the cursor, and the cursor-movement macros select a range corresponding to
    the entire screen.

    For convenience, we've collected all the new functions together as shown
    in Figure 13-6 in a file called SCRFUN.C (Listing 13-23). We discuss the
    Getvmode() and Setvmode() functions in Chapter 15.

                                    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                        â”Œâ”€â”€â”€â”€â”€â”      â”‚                   â”‚
            Setcurs() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚
                        â””â”€â”€â”€â”€â”€â”˜      â”‚                   â”‚
                â”Œâ”€â”€â”€â”€â”€â”            â”‚                   â”‚
        Getcurs() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€              â”‚
                â””â”€â”€â”€â”€â”€â”˜            â”‚                   â”‚
                        â”Œâ”€â”€â”€â”€â”€â”      â”‚                   â”‚
            Setpage()  â”‚     â”œâ”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚
                        â””â”€â”€â”€â”€â”€â”˜      â”‚                   â”‚
                â”Œâ”€â”€â”€â”€â”€â”            â”‚                   â”‚
        Setvmode() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€              â”‚
                â””â”€â”€â”€â”€â”€â”˜            â”‚                   â”‚
                        â”Œâ”€â”€â”€â”€â”€â”      â”‚                   â”‚
            Clearscr() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚
                        â””â”€â”€â”€â”€â”€â”˜      â”‚                   â”‚
                â”Œâ”€â”€â”€â”€â”€â”            â”‚                   â”‚
    Read_ch_atr() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€              â”‚
                â””â”€â”€â”€â”€â”€â”˜            â”‚                   â”‚
                        â”Œâ”€â”€â”€â”€â”€â”      â”‚                   â”‚
        Write_ch_atr() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚
                        â””â”€â”€â”€â”€â”€â”˜      â”‚                   â”‚
                â”Œâ”€â”€â”€â”€â”€â”            â”‚                   â”‚
        Rewrite() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€              â”‚
                â””â”€â”€â”€â”€â”€â”˜            â”‚                   â”‚
                        â”Œâ”€â”€â”€â”€â”€â”      â”‚                   â”‚
            Getvmode() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚
                        â””â”€â”€â”€â”€â”€â”˜      â”‚                   â”‚
                â”Œâ”€â”€â”€â”€â”€â”            â”‚                   â”‚
        Getpage()  â”‚     â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€              â”‚
                â””â”€â”€â”€â”€â”€â”˜            â”‚                   â”‚
                        â”Œâ”€â”€â”€â”€â”€â”      â”‚                   â”‚
            Curslt_lim() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚
                        â””â”€â”€â”€â”€â”€â”˜      â”‚                   â”‚
                â”Œâ”€â”€â”€â”€â”€â”            â”‚                   â”‚
    Curst_lim() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€              â”‚
                â””â”€â”€â”€â”€â”€â”˜            â”‚                   â”‚
                        â”Œâ”€â”€â”€â”€â”€â”      â”‚                   â”‚
            Cursup_lim() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€        â”‚
                        â””â”€â”€â”€â”€â”€â”˜      â”‚                   â”‚
                â”Œâ”€â”€â”€â”€â”€â”            â”‚                   â”‚
    Cursdn_lim() â”‚     â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€              â”‚
                â””â”€â”€â”€â”€â”€â”˜            â”‚                   â”‚
                                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                            SCRFUN.C

    Figure 13-6. The SCRFUN.C program combines the functions we created
    previously.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*  scrfun.c -- contains several video BIOS calls     */
    /*  Setcurs() sets the cursor position                */
    /*  Getcurs() gets the cursor position                */
    /*  Setpage() sets the current video page             */
    /*  Setvmode() sets the video mode                    */
    /*  Clearscr() clears the screen                      */
    /*  Read_ch_atr() reads the character and             */
    /*                attribute at the cursor             */
    /*  Write_ch_atr() writes a character and             */
    /*                 attribute at the cursor            */
    /*  Rewrite() rewrites a screen character             */
    /*            with a new attribute                    */
    /*  Getvmode() gets the current video mode            */
    /*  Getpage() gets the current video page             */
    /*                                                    */
    /*  The following functions use Setcurs() to move the */
    /*  cursor one position at a time up to a limit.      */
    /*  Curslt_lim() moves cursor one column left         */
    /*  Cursrt_lim() moves cursor one column right        */
    /*  Cursup_lim() moves cursor one line up             */
    /*  Cursdn_lim() moves cursor one line down           */
    /*                                                    */
    /*  Programs using these functions should include the */
    /*  scrn.h file                                       */

    #include <dos.h>
    #include "scrn.h"

    /* sets cursor to row, column, and page */
    void Setcurs(row, col, page)
    unsigned char row, col, page;
    {
        union REGS reg;

        reg.h.ah = SETCURSOR;
        reg.h.dh = row;
        reg.h.dl = col;
        reg.h.bh = page;
        int86(VIDEO, &reg, &reg);
    }

    /* gets current cursor row, column for given page */
    void Getcurs(pr, pc, page)
    unsigned char *pr, *pc, page;
    {
        union REGS reg;

        reg.h.ah = GETCURSOR;
        reg.h.bh = page;
        int86(VIDEO, &reg, &reg);
        *pr = reg.h.dh;  /* row number */
        *pc = reg.h.dl;   /* column number */
    }

    /* sets page to given value */
    void Setpage(page)
    unsigned char page;
    {
        union REGS reg;

        reg.h.ah = SETPAGE;
        reg.h.al = page;
        int86(VIDEO, &reg, &reg);
    }

    /* sets video mode to given mode */
    void Setvmode(mode)
    unsigned char mode;
    {
        union REGS reg;

        reg.h.ah = SETMODE;
        reg.h.al = mode;
        int86(VIDEO, &reg, &reg);
    }

    /* clear the screen */
    void Clearscr()
    {
        union REGS reg;

        reg.h.ah = SCROLL;
        reg.h.al = 0;
        reg.h.ch = 0;
        reg.h.cl = 0;
        reg.h.dh = ROWS - 1;
        reg.h.dl = COLS - 1;
        reg.h.bh = NORMAL;
        int86(VIDEO, &reg, &reg);
    }

    /* reads the character and attribute at the cursor */
    /* position on a given page                        */
    void Read_ch_atr(pc, pa, page)
    unsigned char *pc, *pa;
    unsigned char page;
    {
        union REGS reg;

        reg.h.ah = READCHATR;
        reg.h.bh = page;
        int86(VIDEO, &reg, &reg);
        *pc = reg.h.al;  /* character at cursor */
        *pa = reg.h.ah;  /* attribute at cursor */
    }

    /* writes a given character and attribute at the */
    /* cursor on a given page for num times          */
    void Write_ch_atr(ch, atr, page, num)
    unsigned char ch, atr, page;
    unsigned int num;
    {
        union REGS reg;

        reg.h.ah = WRITECHATR;
        reg.h.al = ch;
        reg.h.bl = atr;
        reg.h.bh = page;
        reg.x.cx = num;
        int86(VIDEO, &reg, &reg);
    }

    /* rewrites the character at the cursor using    */
    /* attribute at                                  */
    void Rewrite(at, page)
    unsigned char at, page;
    {
        unsigned char ch, atr;

        Read_ch_atr(&ch, &atr, page);
        Write_ch_atr(ch, at, page, 1);
    }


    /* obtains the current video mode */
    unsigned char Getvmode()
    {
        union REGS reg;

        reg.h.ah = GETMODE;
        int86(VIDEO, &reg, &reg);
        return reg.h.al;
    }

    /* obtains the current video page */
    unsigned char Getpage()
    {
        union REGS reg;

        reg.h.ah = GETMODE;
        int86(VIDEO, &reg, &reg);
        return reg.h.bh;
    }

    /* moves cursor one column left, but not past */
    /* the given limit                            */
    unsigned char Curslt_lim(limit)
    unsigned char limit;
    {
        unsigned char row, col, page;
        unsigned char status = 1;
        Getcurs(&row, &col, page = Getpage());
        if (col > limit)
            Setcurs(row, col - 1, page);
        else
            status = 0;
        return status;
    }

    /* moves cursor one column right, but not past */
    /* the given limit                             */
    unsigned char Cursrt_lim(limit)
    unsigned char limit;
    {
        unsigned char row, col, page;
        unsigned char status = 1;

        Getcurs(&row, &col, page = Getpage());
        if (col < limit)
            Setcurs(row, col + 1, page);
        else
            status = 0;
        return status;
    }

    /* moves cursor one row down, but not past */
    /* the given limit                         */
    unsigned char Cursup_lim(limit)
    unsigned char limit;
    {
        unsigned char row, col, page;
        unsigned char status = 1;

        Getcurs(&row, &col, page = Getpage());
        if (row > limit)
            Setcurs(row - 1, col, page);
        else
            status = 0;
        return status;
    }

    /* moves cursor one row down, but not past */
    /* the given limit                         */
    unsigned char Cursdn_lim(limit)
    unsigned char limit;
    {
        unsigned char row, col, page;
        unsigned char status = 1;

        Getcurs(&row, &col, page = Getpage());
        if (row < limit)
            Setcurs(row + 1, col, page);
        else
            status = 0;
        return status;
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-23.  The SCRFUN.C program.

    Our small routines certainly create a big file! However, you need only
    compile it once. After that, you can use the .OBJ or .LIB versions. We
    assume that you create a library file called SCRFUN.LIB.

A Text Program

    Finally, after much development, we have at hand all the tools we need for
    our program. The ROAMSCRN.C program (Listing 13-24) shows the results of
    our efforts. To run the program within the QuickC environment, be sure
    that Screen Swapping On is active.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /*   roamscrn.c  -- puts text on screen, positions    */
    /*                  cursor with arrow keys, uses F1   */
    /*                  and F2 to control video inverse   */
    /*   program list -- roamscrn.c, scrfun.lib           */
    /*   user include files -- keys.h, scrn.h             */
    /*  Note: Activate Screen Swapping On in Debug menu   */
    #include <conio.h>
    #include "keys.h"
    #include "scrn.h"
    #define BELL '\a'
    #define ESC '\033'
    #define PAGE 0

    char *Heading =
    "Use standard keys to enter text. Use arrow keys to "
    "reposition cursor.\nUse F2 to turn on video inverse "
    "and F1 to turn it off.\nHit the ESC key to quit.\n";

    main()
    {
        int ch;
        unsigned char atr = NORMAL;

        Clearscr();
        Home();
        printf("%s", Heading);
        while ((ch = getch()) != ESC)
            {
            if (ch == '\r')
                {
                putch('\n');
                putch('\r');
                }
            else if (ch != 0)
                {
                Write_ch_atr(ch, atr, PAGE, 1);
                if (!Cursrt())
                    putch(BELL);
                }
            else
                {
                ch = getch();
                switch (ch)
                    {
                    case F1 : atr = NORMAL; break;
                    case F2 : atr = VIDREV; break;
                    case UP : Rewrite(atr, PAGE);
                        if (!Cursup())
                            putch(BELL);
                        break;
                    case DN : Rewrite(atr, PAGE);
                        if (!Cursdn())
                            putch(BELL);
                        break;
                    case LT : Rewrite(atr, PAGE);
                        if (!Curslt())
                            putch(BELL);
                        break;
                    case RT : Rewrite(atr, PAGE);
                        if (!Cursrt())
                            putch(BELL);
                        break;
                    default : break;
                    }
                }
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 13-24.  The ROAMSCRN.C program.

    Let's see how it works. The keys.h include file is the one we used earlier
    in this chapter; it defines the mnemonics for the function keys and the
    cursor control keys. The scrn.h include file is the one we just presented.
    We assume that you bring in the BIOS code by including the SCRFUN.LIB file
    in the program list, but you can also use one of the other methods we
    mentioned if you prefer.

    The program begins with the attribute variable atr set to NORMAL. This is
    defined in scrn.h as 7, which is the normal attribute for white-on-black
    text. Next, the program clears the screen, homes the cursor, and prints an
    instructive heading. Finally, in the main part of the program, a large
    while loop uses getch() to read keyboard input until Esc is pressed to
    terminate input.

    Next, the program inspects ch, the input character typed by the user. If
    it is \r, the carriage return character generated by the Enter key, the
    program translates that into a newline, that is, into \n\r. If the
    character is some other ASCII or extended ASCII value, the program uses
    Write_ch_atr() to display that character. Why not use putch() here?
    Because putch() has no provision for specifying the attribute. Note, too,
    the following code fragment:

    if (!Cursrt())
        putch(BELL);

    Write_ch_atr(), like the BIOS call it uses, does not advance the cursor
    after writing the character. Therefore, we use Cursrt() to move the
    cursor. Recall that we created Cursrt_lim() to stop when it reaches the
    right side of the screen and that the macro Cursrt() uses the rightmost
    column as the limit. If the limit is reached, Cursrt() returns a value of
    0, or false, causing the if statement to execute the putch(BELL) call. The
    action, then, is as follows: First the character is printed, then the
    program attempts to advance the cursor one column to the right. If it can,
    fine; otherwise, the system beeps. If you like, you can replace the
    beeping instructions with a Setcurs() command to relocate the cursor at
    the beginning of the next line.

    Finally, this sequence of if-else lines processes the case of ch being 0.
    This means the user entered a non-ASCII character. Another getch() call
    fetches the scan code for the key, and a switch checks for two of the
    function keys and for the arrow keys. Let's see what these keys do.

    If the user presses F1, the attribute variable atr is set to NORMAL; if
    the user presses F2, atr is set to VIDREV. This constant, defined in
    scrn.h as 0x70, is the reverse video attribute. The selected value for the
    variable atr is used in subsequent calls to Write_ch_atr() and Rewrite().
    The attribute setting holds until another is selected.

    Next, look at what happens when the Up Arrow key is pressed:

    case UP : Rewrite(atr, PAGE);
        if (!Cursup())
            putch(BELL);
        break;

    The Rewrite() function reads the character, if any, at the current cursor
    position and rewrites it using the current attribute. Then the cursor is
    moved up a line unless it already is at the top line. In that case, the
    system beeps. The purpose of the Rewrite() statement is to cause existing
    text to be replaced by text using the current attribute. For example, if
    you have selected the inverse attribute, then text passed over by the
    cursor is rewritten with that attribute. The coding for the other arrow
    keys is similar.

    All in all, the main program is fairly simple. Most of the work involved
    creating C functions to implement the various BIOS calls we needed to
    make.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€