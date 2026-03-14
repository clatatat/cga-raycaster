Chapter 10  Managing Files

    C files are primarily disk files that contain text, executable images of
    programs, or data. These disk files represent stored programs and data
    that form a common "library" of information that is available to a wide
    range of programs.

    The QuickC library functions that handle file input and output are
    arranged in three categories, or levels, as illustrated in Figure 10-1 on
    the following page. At the top level are the buffered (stream I/O)
    routines; below those are the unbuffered (raw I/O) routines; and at the
    bottom are the direct BIOS interfaces. The low-level routines are not a
    part of portable C because they access PC-specific internal routines. The
    higher-level routines, however, are universal to all C compilers. We will
    not cover the low-level BIOS routines in this book.

    The top-level file I/O routines are called "buffered stream" routines
    because they interpose themselves between your program and files. They
    read and write large blocks of information (buffering), and then they pass
    a continuous series (stream) of bytes to your program, as needed.

                            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                            â”‚                    â”‚
                            â”‚      Buffer        â”‚â—„â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                            â”‚                    â”‚                 â”‚
                            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜                 â”‚
                                        â”‚                            â”‚
                                        â”‚                            â”‚
                            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”                 â”‚
                    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”‚Top-level           â”‚                 â”‚
                    â”‚          â”‚functions like      â”‚         â”Œâ”€â”€â”€â”€â”€â”€â”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–¼â”€â”        â”‚fopen() and fgetc() â”‚         â”‚                â”‚
    â”‚                â”‚        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜         â”‚    Your        â”‚
    â”‚      Disk      â”‚        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”         â”‚    program     â”‚
    â”‚                â”‚        â”‚Mid-level           â”‚         â”‚                â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜        â”‚functions like      â”‚         â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
            â”‚     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”‚open() and read()   â”‚â—„â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     â”‚
            â”‚                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜                 â”‚
            â”‚                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”                 â”‚
            â”‚                â”‚Low-level           â”‚                 â”‚
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”‚functions like      â”‚â—„â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                            â”‚_bios_disk()        â”‚
                            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 10-1. The three levels of file I/O.

    The middle file level is called unbuffered because it lets your program
    access files directly. Reads and writes do not pass through an
    intermediate buffer; they pass directly between the operating system and
    your program. These mid-level routines can execute faster than the
    top-level routines, but they are more complex to use.

    Both top-level and mid-level file routines have two modesâ”€â”€text and
    binary. Text mode is used with text files, or files that contain ASCII
    text (which is readable by persons). Binary mode is used with files that
    contain binary information, such as executable programs. In text mode,
    Ctrl-Z (a byte containing the value 0x1A) marks the end of a file. In
    binary mode, Ctrl-Z can legally be a part of the file; the operating
    system keeps track of file length.


Top-Level I/O

    All buffered file I/O functions require that you begin your program with
    #include <stdio.h>. That header file contains the definition for FILE, the
    data type that you use to manipulate files. The type FILE is used as shown
    on the next page.

    #include <stdio.h>
    ...
    FILE *fp;

    Remember, always use #include <stdio.h> for the definition of the type
    FILE. Then declare a file pointer to point to the data type FILE.

Opening Files with fopen()

    Before you can access a file for reading or writing or both, you must
    first open that file. For buffered I/O routines (those that use a file
    pointer), open the file with the fopen() function, as follows:

    fp = fopen(filename, activity);
                    â”‚          â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Open to read, write, or both
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Name of file to open

    The fopen() function requires two arguments: the name of the file to open
    (a string or the address of a string) and an activity (also a string) as
    listed in Table 10-1. The activity determines whether the file is open
    for reading, writing, or appending. (In this case, read means to take
    information sequentially from a file, write means to put information
    sequentially into a file, and append means to add information to the end
    of a file.)

    The fopen() function returns a value of type FILE *. In our example we
    assigned this value to file pointer fp, which we will use to access and
    manipulate the file. If fopen() fails, it returns NULL. Therefore, the
    complete call to fopen(), including error handling, is as follows:

    fp = fopen("test.c", "r");
    if (fp == NULL)
    {
        /* handle error here */
    }

    This opens the TEST.C file for reading (activity "r"). After the file
    pointer returned by fopen() is assigned to fp, we test fp to see if it is
    NULL. We test for an error here because it is possible that the file
    TEST.C does not exist.

    Table 10-1 Possible Modes (Activities) for fopen()
    Mode       Description
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    "r"        Open for reading only. The file must already exist.
    "w"        Open for writing only. Creates the file if it does not exist.
    "a"        Open for appending (write-only, starting at the end of a file).
                Creates the file if it does not exist.
    "r+"       Open for both reading and writing. The file must already exist.
    "w+"       Open for both reading and writing. Creates the file if it does
                not already exist.
    "a+"       Open for both reading and writing, starting at the end of the
                file. Creates the file if it does not exist.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Each open file requires its own file pointer. The following two open
    files, for example, require two separate file pointers:

    #include <stdio.h>
    ...
    FILE *fp_in, *fp_out;
    ...
    fp_in = fopen("test.txt", "r");
    fp_out = fopen("test.bak", "w");

    In this example, fp_in is the file pointer for the file opened for reading
    (activity "r"), and fp_out is the file pointer for the file opened for
    writing (activity "w").

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    File Access in BASIC and C
    If you're used to BASIC file handling, you'll find that QuickC offers
    fewer "built-in" conveniences but ultimately provides more power and
    flexibility. In BASIC, you might open a random access file with the
    following statement, which specifies the file identification number and
    record length:

    OPEN "C:\ACCT\TRANS" FOR RANDOM AS #1 LEN = 256

    Before you can use the file, you have to use FIELD statements to associate
    whatever numeric or string variables you are going to use with the
    corresponding data fields in the file record. Because most versions of
    BASIC don't have a data type similar to the C struct, you have to
    manipulate numerous separate variables to move data to and from the file.
    The built-in random access support does allow you to get a record by its
    record number directly using the GET statement, however.

    C has a different approach: A file can contain any valid C data type, such
    as a struct, which already has its fields defined, so you don't have to
    set up file data fields. On the other hand, file manipulation methods,
    such as random access, are not built-in in C. You can achieve random
    access, however, by converting a record number to an offset and then using
    the library function fseek() to position C's file pointer to the correct
    record. You can also use the fgetpos() and fsetpos() functions to
    manipulate the file pointer.

    Also, because C uses function calls rather than BASIC's procedural
    commands to manipulate files, you can quickly check for errors by putting
    the function call in an if statement.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Reading Characters with fgetc()

    There's more to reading a file than merely opening the file to read. To
    see what we mean, examine the STRINGS.C program (Listing 10-1), which
    reads a file one character at a time and looks for strings of five or more
    printable characters. The program takes a command-line argument, so before
    you run it, you must create the argument using the Set Runtime Options
    screen from the Run menu. In the Command Line box, type c:\qc\qc.exe (or
    the name of any existing file). Figure 10-2 on the next page shows the
    screen after you type the command.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* strings.c  --  opens a file and searches it for */
    /*                possible strings                 */

    #include <stdio.h>        /* for FILE, BUFSIZ, & EOF */
    #include <ctype.h>        /* for isprint()           */

    main(argc, argv)
    int argc;
    char *argv[];
    {
        FILE *fp;
        char buf[BUFSIZ];
        int ch, count;

        if (argc != 2)
            {
            fprintf(stderr, "usage: strings file\n");
            exit(1);
            }
        if ((fp = fopen(argv[1], "rb")) == NULL)
            {
            fprintf(stderr, "Can't open %s\n", argv[1]);
            exit(1);
            }

        count = 0;
        while ((ch = fgetc(fp)) != EOF)
            {
            if (! isprint(ch) || count >= (BUFSIZ - 1))
                {
                if (count > 5)
                    {
                    buf[count] = 0;
                    puts(buf);
                    }
                count = 0;
                continue;
                }
            buf[count++] = ch;
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 10-1.  The STRINGS.C program.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ Figure 10-2 can be found on p.296 of the printed version of the book.  â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 10-2. The Set Runtime Options dialog box lets you enter a command
    line.

    When we run STRINGS.C on a large file such as QC.EXE, the program prints
    many screens of possible strings. For convenience, you might add a
    "paging" feature to the program.

    STRINGS.C uses the fgetc() function, a file-oriented version of the
    getchar() routine we've used before. After it is passed a single argument
    (a file pointer), the function returns the next character read from the
    file pointed to. Assigning that character to a variable of type int lets
    us detect EOF (End Of File) easily.

    int ch;

    if ((ch = fgetc(fp)) == EOF)
    {
            /* handle end of file here */
    }

    Notice that STRINGS.C calls fopen() with the activity argument "rb". This
    is a PC-specific extension of the normal "open for reading" argument. The
    b tells fopen() to open the file in binary mode but to do no character
    translation for usâ”€â”€that is, to give fgetc() every byte from the file as
    is. If we did not specify the b, fopen() would have opened the file in
    text mode. Had we used text mode, however, our program would not have read
    all of QC.EXE because the Ctrl-Z character, which is a legal byte in
    binary files, would have marked the end of the file. Table 10-2 shows the
    difference between these two modes.

    Also notice that STRINGS.C ends without closing the file. C, unlike BASIC,
    closes all open files when you exit the program. This is true whether you
    exit main() with a return or from another function with an exit().

    Table 10-2 Text vs Binary Modes for fopen()
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    t       text mode        Translates carriage return/linefeed combinations
                            into single linefeeds on input and makes the
                            reverse translation on output. Ctrl-Z marks the
                            end of the file.
    b       binary mode      Suppresses the above translations. The operating
                            system keeps track of the file's length.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Closing Files with fclose()

    Although MS-DOS lets you have as many as 20 simultaneously open files, you
    might want to close each open file before you open another one. Closing a
    file writes everything to disk, updates the directory entry for that file,
    and frees a file pointer.

    When you open files with fopen(), you can close them with fclose(), as
    follows:

    if (fclose(fp) == EOF)
    {
            /* unable to close file */
    }
    /* fp may be reused here */

    If fclose() cannot close a file (because the floppy disk containing that
    file was removed, for example), it returns EOF.

Line I/O with fgets() and fputs()

    The standard C Library contains a pair of file-oriented routines called
    fgets() ("file get string") and fputs() ("file put string"). They are
    similar to the gets() and puts() pair we discussed in the last chapter:
    fgets() reads lines of text from files and fputs() writes lines of text
    into files. Use them as follows:

    #include <stdio.h>
    #define SIZE 512
    ...
    FILE *fp_in, *fp_out;
    char buf[SIZE];
    ...
    /* open fp_in for reading and fp_out for writing */
    ...
    if (fgets(buf, SIZE, fp_in) == NULL)
    {
            /* error reading or EOF */
    }
    /* a line of text is now in buf */
    ...

    if (fputs(buf, fp_out) == EOF)
    {
            /* error writing */
    }

    The fgets() function takes three arguments: the address of a char buffer,
    the maximum number of characters to read into that buffer, and a file
    pointer to a file opened for reading. In the example, fgets() reads a
    maximum of SIZE characters (up to and including the first newline
    character) and appends a terminating '\0' to the characters to form a
    string. The fputs() function requires two arguments: the address of a
    zero-terminated string (in buf) and a file pointer to a file opened for
    writing. In the example, fputs() writes the string in buf to fp_outâ”€â”€
    including any newline in that string. Note as well that fputs() does not
    add any newlines.

    The fputs() and fgets() functions differ from their counterparts puts()
    and gets(). Each handles the newline character in a different way, as
    follows:

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    gets(buf)      Reads characters from keyboard and places them into buf.
                    Replaces the trailing newline character ('\n') with a '\0'.

    fgets(buf,     Reads a maximum of len characters from a file opened for
    len, fp)       reading. Places len or fewer characters (up to and
                    including a newline) into buf. Retains the newline
                    character and adds a terminating '\0'.

    puts(buf)      Prints the string in buf to the screen and adds a newline
                    character to the output on the screen.

    fputs(buf, fp) Prints (writes) the string in buf into the file (opened for
                    writing) pointed to by the file pointer fp. Does not add a
                    newline character to the output.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    The CCOPY.C program (Listing 10-2) reads one file and writes to a second.
    The "C" preceding "COPY" (in the program name) signals that this COPY
    "crunches" its inputâ”€â”€eliminating all empty lines, leading tabs, and
    spaces. You could use this program to prepare files before sending them
    over a slow modem.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* ccopy.c  --  copies a file, cutting blank lines and  */
    /*              leading space from lines of copy        */

    #include <stdio.h>        /* for FILE, BUFSIZ, NULL */
    #include <ctype.h>        /* for iswhite()          */

    main(argc, argv)
    int argc;
    char *argv[];
    {
        FILE *fp_in, *fp_out;
        char buf[BUFSIZ];
        char *cp;

        if (argc != 3)
            {
            printf("usage: ccopy infile outfile\n");
            exit(1);
            }
        if ((fp_in = fopen(argv[1], "r")) == NULL)
            {
            printf("Can't open %s for reading.\n", argv[1]);
            exit(1);
            }
        if ((fp_out = fopen(argv[2], "w")) == NULL)
            {
            printf("Can't open %s for writing.\n", argv[2]);
            exit(1);
            }

        printf("Copying and Crushing: %s->%s ...",
                    argv[1], argv[2]);

        while (fgets(buf, BUFSIZ, fp_in) != NULL)
            {
            cp = buf;
            if (*cp == '\n')    /* blank line */
                continue;
            while (isspace(*cp))
                {
                ++cp;
                }
            if (*cp == '\0')    /* empty line */
                continue;
            if (fputs(cp, fp_out) == EOF)
                {
                printf("\nError writing %s.\n", argv[2]);
                exit(1);
                }
            }
        printf("Done\n");
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 10-2.  The CCOPY.C program.

    To run this program you need to set its command line from the Set Runtime
    Options dialog box. The Command Line text box requires two filenames as
    argumentsâ”€â”€first, the file to read, and second, the file to write to. For
    example, you might enter the filenames strings.c temp. The first name is
    the existing text file to be read (note that the fopen() in CCOPY.C uses
    "r" for text mode). The second name is the new file that will be created
    (activity "w").

    Within a loop, fgets() reads a line of text from the first file, the
    program crunches that line, and fputs() writes the condensed line into the
    second file. After you run CCOPY.C, choose DOS Shell from the File menu
    and look at the newly created file using the TYPE command and Ctrl-S.

Error Detection with feof() and ferror()

    Using fgets() has a drawbackâ”€â”€it returns NULL for both EOF (which you
    expect) and read errors (which you don't expect). However, you can
    differentiate between the two by using feof() and ferror().

    The feof() function tests a file opened for reading and associated with a
    file pointer to see if the end of that file has been reached. It returns
    true (nonzero) at the end of the file; otherwise it returns 0. The
    ferror() function returns true if there is any error with the fileâ”€â”€
    including reaching the end of file. The following example shows how to use
    them together to differentiate between the two conditions:

    if (feof(fp_in))
    {
            /* reached end of file while reading */
    }
    else if (ferror(fp_in))
    {
            /* some read error has occurred */
    }

    EOF is meaningful only when reading; use ferror() alone when writing to a
    file:

    if (ferror(fp_out))
    {
            /* some write error has occurred */
    }

    Always include error-checking routines in your programs to protect
    yourself from careless users. Users sometimes remove floppy disks while
    the drive light is on or try writing to disks that are write-protected.
    Error detection lets you either take corrective action or notify users of
    their mistakes.

Block I/O with fread() and fwrite()

    So far we've treated files as lines of text. However, you will often want
    to read and write files in specific blocks whose size is measured in
    bytes. (Executable program files and data files, for example, generally
    contain no meaningful lines of text.) To do this, the standard C Library
    provides a pair of routines called fread() and fwrite(). Their forms are
    nearly identical:

    fread(buffer, size, count, fp_in);
                â”‚      â”‚      â”‚    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ A file pointer
                â”‚      â”‚      â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ How many size items
                â”‚      â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ How many bytes per item
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Address of (size * count) bytes buffer


    fwrite(buffer, size, count, fp_out);
                â”‚      â”‚      â”‚    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ A file pointer
                â”‚      â”‚      â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ How many size items
                â”‚      â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ How many bytes per item
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Address of (size * count) bytes buffer

    Both routines require that you specify #include <stdio.h> to define FILE
    for the file pointer and to define the new type size_t for the variables
    size and count:

    size_t size;
    size_t count;
    FILE   *fp;

    QuickC defines the type size_t in the <stdio.h> header file as an unsigned
    long. Because it might be defined differently with other compilers, you
    should use size_t for portability.

    Both functions return the number of bytes actually read or written. When
    that number is less than size times count, an error has occurred. In the
    case of fread(), however, that error can also indicate that you've reached
    the end of the file. Therefore, you need to use feof() to distinguish end
    of file from other errors.

    The UPPITY.C program (Listing 10-3) shows one way to use fread() and
    fwrite(). It reads an entire file into memory (using malloc() to obtain
    that memory), converts it to uppercase, then writes the entire file to a
    new file having the .UP extension.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* uppity.c --  makes an uppercase copy of a file using */
    /*              fread() and fwrite()                    */

    #include <string.h>     /* for strrchr() */
    #include <stdio.h>      /* for NULL      */
    #include <malloc.h>     /* for malloc()  */
    #include <ctype.h>      /* for isupper() */

    #define HUNK 512

    main(argc, argv)
    int argc;
    char *argv[];
    {
        char *cp, newname[128], *np;
        FILE *fp;
        int  hunks = 0, bytes = 0, totbytes = 0;
        int  i;
        if (argc != 2)
            {
            printf("usage: uppity file\n");
            exit(1);
            }

        if ((fp = fopen(argv[1], "rb")) == NULL)
            {
            printf("\"%s\": Can't open.\n", argv[1]);
            exit(1);
            }
        if ((cp = malloc(HUNK)) == NULL)
            {
            printf("Malloc Failed.\n");
            exit(1);
            }

        while ((bytes = fread(cp + (HUNK * hunks), 1, HUNK, fp)) == HUNK)
            {
            totbytes += bytes;
            ++hunks;
            if ((cp = realloc(cp, HUNK + (HUNK * hunks))) == NULL)
                {
                printf("Realloc Failed.\n");
                exit(1);
                }
            }
        if (bytes < 0)
            {
            printf("\"%s\": Error Reading.\n", argv[1]);
            exit(1);
            }
        totbytes += bytes;

        for (i = 0; i < totbytes; ++i)
            if (islower(cp[i]))
                cp[i] = toupper(cp[i]);

        (void)fclose(fp);

        if ((np = strchr(argv[1], '.')) != NULL)
            *np = '\0';
        strcpy(newname, argv[1]);
        strcat(newname, ".up");
        if ((fp = fopen(newname, "wb")) == NULL)
            {
            printf("\"%s\": Can't open.\n", argv[1]);
            exit(1);
            }

        if (fwrite(cp, 1, totbytes, fp) != totbytes)
            {
            printf("\"%s\": Error writing.\n", argv[1]);
            exit(1);
            }

    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 10-3.  The UPPITY.C program.

    UPPITY.C continually reallocates memory for each HUNK (512 bytes) of the
    file read in. A more direct approach would find the size of the file, then
    read in that many bytes with a single fread(). You can do this with the
    stat() function. Unfortunately, to use stat() you must understand
    "structures," and we won't be describing those until the next chapter.
    Keep in mind that you might want to modify UPPITY.C when you learn how to
    use structures.

Predeclared File Pointers

    When you run any QuickC program, five file pointers are always provided
    for five preopened files. Those file pointers are stdin, stdout, stderr,
    stdaux, and stdprn. (See Table 10-3.) Because these preopened file
    pointers are defined in stdio.h, you must include that header file if you
    want to use them.

    To demonstrate the use of these file pointers, we revised CCOPY.C (the
    "crunch-and-copy program") to produce the CCOPY2.C program (Listing
    10-4). This revision checks for the presence of a second (output)
    filename. If it is missing, fputs() directs the output to stdout (your
    screen).

    Table 10-3 QuickC's Preopened File Pointers
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    stdin      The standard input. Your keyboard viewed as a file. Also, input
                to your program provided by redirection using <file from the
                MS-DOS command line.
    stdout     The standard output. Your screen viewed as a file. Also, output
                to disk files provided by redirection using >file from the
                MS-DOS command line.
    stderr     The standard error output. Always your screen. This file
                pointer is unaffected by redirection from the MS-DOS command
                line.
    stdaux     The standard auxiliary. Usually your serial port or COM1. This
                file pointer provides easy access to your modem.
    stdprn     The standard printer output. Usually your parallel port or PRN.
                This file pointer provides an easy way to generate hard copy
                from within a QuickC program.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* ccopy2.c  -- copies a file, cutting blank lines and  */
    /*              leading space from lines of copy        */

    /*          Modified to demonstrate stdout and stderr   */

    #include <stdio.h>        /* for FILE, BUFSIZ, NULL */
    #include <ctype.h>        /* for iswhite()          */

    main(argc, argv)
    int argc;
    char *argv[];
    {
        FILE *fp_in, *fp_out;
        char buf[BUFSIZ];
        char *cp;

        if (argc < 2)
            {
            fprintf(stderr, "usage: ccopy2 infile {outfile}\n");
            exit(1);
            }
        if ((fp_in = fopen(argv[1], "r")) == NULL)
            {
            fprintf(stderr, "\"%s\": Can't open.\n", argv[1]);
            exit(1);
            }
        if (argc == 3)
            {
                if ((fp_out = fopen(argv[2], "w")) == NULL)
                    {
                    fprintf(stderr, "\"%s\": Can't open.\n", argv[2]);
                    exit(1);
                    }
            }
        else
            fp_out = stdout;

        while (fgets(buf, BUFSIZ, fp_in) != NULL)
            {
            cp = buf;
            if (*cp == '\n')    /* blank line */
                continue;
            while (isspace(*cp))
                {
                ++cp;
                }
            if (*cp == '\0')    /* empty line */
                continue;
            if (fputs(cp, fp_out) == EOF)
                {
                fprintf(stderr, "Error writing.\n");
                exit(1);
                }
            }
        if (! feof(fp_in))        /* error reading? */
            {
            fprintf(stderr, "\"%s\": Error reading.\n", argv[1]);
            exit(1);
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 10-4.  The CCOPY2.C program.

Formatted File I/O with fprintf() and fscanf()

    CCOPY2.C didn't print error messages with printf(); instead, it used the
    file-oriented version of printf(), called fprintf(), to send error
    messages to stderr, which is always your screen. This ensures that you
    will always see error messages, even when the program is printing its
    output to a file.

    C's file-oriented counterparts to printf() and scanf() are called
    fprintf() and fscanf(). They are identical to their nonfile brethren, with
    one exception: Each requires a file pointer as its first argument, as
    follows:

    fprintf(fp_out, control, args ...);
            â””â”€â”¬â”€â”€â”˜  â””â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚             â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Same as printf()
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ A file pointer

    fscanf(fp_in, control, addresses ...);
            â””â”€â”¬â”€â”˜  â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚              â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Same as scanf()
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ A file pointer

Random Access with fseek()

    Sophisticated applications, such as databases, must be able to move around
    in files (recall that files are continuous streams of bytes) reading and
    writing selected portions. The fseek() function lets a program access any
    file element by determining the position of the next read or write in a
    file, as follows:

    fseek(fp, offset, origin)
        â”‚     â”‚   â”‚      â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ From where
        â””â”€â”€â”¬â”€â”€â”˜   â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ How far to reposition
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ File pointer

    The offset, in bytes, tells fseek() how far to move in the file, and it
    must be type long. The origin determines where to measure offset from; it
    can be any one of three valuesâ”€â”€the beginning, current position, or end of
    the file. (See Table 10-4.)

    If fseek() cannot reposition in a file, it returns the value -1L (the L is
    needed because fseek() returns the type long). If fseek() is successful,
    it returns the new position in the file, measured in bytes from the
    beginning of the file.

    Table 10-4 origin Positions for fseek()
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    SEEK_SET       From the beginning of the file; offset must always be
                    positive.
    SEEK_CUR       Relative to the current position. A negative offset moves
                    toward the beginning of the file; a positive offset moves
                    toward the end of the file. (You can move beyond the end of
                    the file, thus enlarging the file.)
    SEEK_END       From the end of the file; offset can be positive or
                    negative. Movement is the same as SEEK_CUR, but relative to
                    the end of the file.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    The PHONE.C program (Listing 10-5 on the following page) is a miniature
    telephone number database. When run without command-line arguments, it
    asks you for numbers to add to its database file. Run with a command-line
    argument, it searches for an entry that matches the argument and prints
    the data it finds.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* phone.c  -- a telephone number mini-database that  */
    /*             demonstrates fseek()                   */

    #include <stdio.h>        /* for FILE, BUFSIZ, NULL */

    #define MAXL (128)
    char Name[MAXL];
    char Number[MAXL];
    char File[] = "C:\\TMP\\PHONE.DB";
    int  Count;
    FILE *Fp;
    int  Distance = (MAXL * MAXL);

    main(argc, argv)
    int argc;
    char *argv[];
    {
        if (argc == 1)
            Ask();
        else
            Find(argv[1]);

    }

    Find(char *str)
    {
        int i;

        if ((Fp = fopen(File, "r")) == NULL)
            {
            fprintf(stderr, "\"%s\": Can't Read\n", File);
            exit (1);
            }
        if (fread(&Count, 1, sizeof(int), Fp) != sizeof(int))
            {
            fprintf(stderr, "\"%s\": Error Reading\n", File);
            exit (1);
            }
        for (i = 0; i < Count; i++)
            {
            fread(Name, 1, MAXL, Fp);
            fread(Number, 1, MAXL, Fp);
            if (ferror(Fp))
                {
                fprintf(stderr, "\"%s\": Error Reading.\n", File);
                exit (1);
                }
            if (strcmp(*str, *Name) == 0)
                {
                printf("Name: %s\n", Name);
                printf("Number: %s\n", Number);
                return;
                }
            }
        fprintf(stderr, "\"%s\": Not in database.\n", str);
        return;
    }

    Ask()
    {
        if ((Fp = fopen(File, "r+")) == NULL)
            Make();
        else if (fread(&Count, 1, sizeof(int), Fp) != sizeof(int))
            {
            fprintf(stderr, "\"%s\": Error Reading\n", File);
            exit (1);
            }
        printf("Name: ");
        if (gets(Name) == NULL || *Name == '\0')
            return;
        printf("Number: ");
        if (gets(Number) == NULL || *Number == '\0')
            return;
        if (fseek(Fp, (long)(Distance * Count), SEEK_CUR) != 0)
            {
            fprintf(stderr, "\"%s\": Error Seeking.\n", File);
            exit (1);
            }
        fwrite(Name, 1, MAXL, Fp);
        fwrite(Number, 1, MAXL, Fp);
        if (ferror(Fp))
            {
            fprintf(stderr, "\"%s\": Error Writing.\n", File);
            exit (1);
            }
        if (fseek(Fp, 0L, SEEK_SET) != 0)
            {
            fprintf(stderr, "\"%s\": Error Seeking.\n", File);
            exit (1);
            }
        ++Count;
        if (fwrite(&Count, 1, sizeof(int), Fp) != sizeof(int))
            {
            fprintf(stderr, "\"%s\": Error Writing\n", File);
            exit (1);
            }
        return;
    }
    Make()
    {
        if ((Fp = fopen(File, "w+")) == NULL)
            {
            fprintf(stderr, "\"%s\": Can't Create\n", File);
            exit (1);
            }
        Count = 0;
        if (fwrite(&Count, 1, sizeof(int), Fp) != sizeof(int))
            {
            fprintf(stderr, "\"%s\": Error Creating\n", File);
            exit (1);
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 10-5.  The PHONE.C program.

    The PHONE.C program might seem more complex than it really is. We included
    many error-checking routines to prevent the user from making careless
    errors. Note how the program checks the first character of each input line
    for a zero character (*Name == '\0'). This shows that the user pressed
    Enter without typing any information.

Moving with the rewind() Function

    Moving to the beginning of a file (rewinding) is so common in C programs
    that the standard C Library includes a special function to perform that
    task. Called rewind(), it takes a single argumentâ”€â”€a file pointer for the
    opened fileâ”€â”€and moves the position of the next read or write to the
    beginning of the file. Consider the following:

    rewind(fp);

    rewind() returns no value and therefore gives no indication of failure.
    Other than this difference, however, the above rewind() is identical to
    the following fseek():

    fseek( fp, OL, SEEK_SET)
                â”‚     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Move from beginning of file
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Offset must be a long

Determining Position in a File with ftell()

    Moving through a file with fseek() often requires that you first know your
    current position in the file. When you pass the ftell() function a file
    pointer, it returns your present position in that file. That position, a
    long value, is the measure in bytes from the beginning of the file.
    Consider the following:

    if ((pos = ftell(fp)) == -1L)
    {
            /* can't find position */
    }
    /* current position is pos bytes from beginning */

    Used in that way, ftell() is identical to the following fseek() call:

    if ((pos = fseek(fp, 0L, SEEK_CUR)) == -1L)
    {
            /* can't find position */
    }
    /* current position is pos bytes from beginning */

    As you progress in learning C, you will find need for functions that we
    have not covered in our discussions. For a complete summary of top-level
    (stream) I/O routines, refer to Section 4.8 of the Microsoft QuickC
    Run-Time Library Reference.


Mid-level (Unbuffered) File I/O

    Most of the top-level (buffered) stream file input/output functions have
    mid-level, unbuffered counterparts that permit direct access to disk
    files. Because they do not buffer data, they are frequently faster and
    more efficient, often allowing disk files to be read directly into a
    program's memory. (The top-level fread() function, for example, actually
    calls the mid-level read() to do its work.)

    One disadvantage of the unbuffered routines is that they offer only the
    most basic of services. Although these routines offer a read() and a
    write(), there are no corresponding mid-level versions of fgets(),
    fputs(), fscanf(), fprintf(), or fgetc(). Another disadvantage is that you
    cannot use unbuffered functions in the same program that uses calls to
    top-level functions. If you mix them, as shown in Figure 10-3, you risk
    losing synchronization of data. That is, if you first call fgetc(), then
    call read(), the read() will not begin with the next byte following the
    fgetc(). The fgetc() reads and buffers 512 bytes from the file, then it
    returns the first one of those buffered bytes. The call to read(),
    however, reads a single byte directly from the disk.

                                    512-byte buffer
                                â”Œâ”€â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                                â”‚ â”‚    Now is the      â”‚  'N'
                                â”‚ â”‚    time...         â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    fgetc() reads and buffers  â”‚ â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜          â”‚
    512 bytes at a time â”€â”€â”€â”€â”€â”€â”€â”¤           â”‚                     â”‚
                                â”‚ â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”          â”‚
        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”      â”‚ â”‚     Top-level      â”‚        â”Œâ”€â–¼â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
        â”‚                â”œâ”€â”€â”€â”€â”€â”€â”¼â–ºâ”‚     fgetc()        â”‚        â”‚
        â”‚ File: "Now is  â”‚      â””â”€â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜        â”‚    Your
        â”‚  the time..."  â”‚                                      â”‚    program
        â”‚                â”‚        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”        â”‚
        â”‚                â”œâ”€â”€â”€â”€â”€â”€â”€â–ºâ”‚     Mid-level      â”‚        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜        â”‚     read()         â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜  'N'
                                    â”‚
                read() reads â”€â”€â”€â”€â”€â”˜
                only one byte

    Figure 10-3. Data synchronization is lost when you mix buffered with
    unbuffered file I/O routines.

Opening a File with open()

    Unlike fopen(), open() returns its identifying value as a simple integer.
    This value, called a "file descriptor," is later passed to all other
    mid-level routines. To use the open() function, you must specify #include
    <fcntl.h> (not <stdio.h>, as you would with fopen()), as follows:

    #include <fcntl.h>
    ...
    int fd;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€The file descriptor
    ...
    if ((fd = open(filename, oflag)) < 0)
    {
            /* handle error here */
    }

    The file descriptor, fd, is type int. The first argument, filename, is a
    string or the address of a string, and the second, oflag, is an int that
    supplies open() with a file activity (read, write, append, create) and a
    file mode (text or binary). The values for oflag are defined in fcntl.h,
    and their meanings are listed in Table 10-5. Note that you can combine
    oflag values by using the bitwise OR operator (|). For example, the
    following declaration opens the file TEST.EXE for reading in binary mode:

    fd = open("TEST.EXE", O_BINARY | O_RDONLY)
                                â”‚    â”‚     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ For reading only
                                â”‚    â””â”€â”€â”€ Combined with bitwise OR operator
                                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Open in binary mode

    If it fails, open() returns a negative integer value. Thus, all file
    descriptor values are greater than or equal to zero.

    Table 10-5 Values for oflag Declared in fcntl.h
    Value                                Description
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    O_RDONLY                             Accesses as read-only.
    O_RDWR                               Accesses as read-write.
    O_WRONLY                             Accesses as write-only.
    O_BINARY                             Sets mode for a binary file.
    O_TEXT                               Sets mode for a text file.
    O_APPEND                             Opens for appending.
    O_CREAT                              Creates file if it doesn't exist.
    O_EXEL                               Returns error if file already exists.
    O_TRUNC                              Truncates existing file to zero
                                        length.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Of the possible values for oflag, you must use one of the first three
    activities in Table 10-5, (O_RDONLY, O_RDRW, or O_WRONLY); all others in
    the table are optional and can be added using bitwise OR. Unless specified
    otherwise, the mode is set for a text file; reads and writes begin at the
    start of the file; the file is not created if it doesn't exist; and the
    file is not truncated.

    If you combine the O_CREAT value with O_RDWR or O_WRONLY to create a file,
    open() requires a third argument called pmode ("permissions" mode). Use
    the argument as follows:

    fd = open(filename, oflag, pmode);
                            â”‚    â””The permissions of the newly created file
                            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€(O_RDWR or O_WRONLY|O_CREAT)

    The possible values for pmode, listed in Table 10-6, determine whether
    the created file will be a read-only file, a write-only file, or a
    readable and writable file. (You must combine the two defined pmode values
    with a bitwise OR operator to create a readable and writable file.)
    Because pmode values are defined in sys\stat.h>, you must specify the
    following include files to create a file with open():

    #include <fcntl.h>â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€For oflag values
    #include <sys\types.h>â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€For stat.h
    #include <sys\stat.h>â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€For pmode values

    Note that #include <sys\types.h> must always precede #include <sys\stat.h>
    because the first contains the definitions needed by the second.

    With MS-DOS, you cannot create a file that is write-only. Because all
    files are always readable, you can omit the S_IREAD value for pmode. (If
    you do use the value, MS-DOS ignores it.)

    The following example is a complete call to open(), including all the
    #include directives:

    #include <fcntl.h>
    #include <sys\types.h>
    #include <sys\stat.h>

    int fd;

    fd = open("TEST.EXE", O_RDWR|O_BINARY|O_CREAT|O_TRUNC,S_IREAD|S_IWRITE);

    This example opens a file named TEST.EXE in binary mode for reading and
    writing. It creates the file if it doesn't exist, and truncates it if it
    does.

    Table 10-6 Values for pmode from <sys\stat.h>
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    S_IWRITE                             Creates a writable file.
    S_IREAD                              Creates a readable file.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Closing a File with close()

    Just as fclose() closes a file based on a file pointer, the unbuffered
    close() library function closes a file based on a file descriptor, as
    follows:

    if (close(fd) != 0)
    {
            /* handle error closing here */
    }

    A successfully executed close() returns a zero value; any nonzero return
    value indicates an error.

    When your program exits, QuickC closes all files opened with the mid-level
    open(). Because you can have only 20 files open at one time, you should
    close files inside your program. Closing a file with close() frees that
    file's file descriptor for reuse.

Writing to a File with write()

    The write() function is used to write to files. It is simpler to use than
    the top-level fwrite() function because it requires only three arguments,
    as in the following:

    write(fd_out, buf, bytes)
            â””â”€â”€â”¬â”€â”˜   â”‚     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Number of bytes to write
                â”‚     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Where to write those bytes from
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ File descriptor for a file opened for writing

    The expression buf is the address in memory of the first byte that you
    want to write to the file. That address can be any address expression, but
    it is usually the address of an array. The final argument, bytes,
    represents the number of characters you want to write to the file.

    The write() function normally returns the number of bytes written (the
    same value as bytes). If write() fails, however, it returns a smaller or
    negative number.

    The SCRSAVE.C program (Listing 10-6) demonstrates one way to use open()
    and write(). It copies the contents of the text screen into a local
    buffer, which is then written to a disk file. (The program will not
    overwrite an existing file.)

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* scrsave.c  --  demonstrates write() by saving the */
    /*                text screen to a file              */

    #include <stdio.h>        /* for stderr              */
    #include <fcntl.h>        /* for O_CREAT | O_BINARY  */
    #include <sys\types.h>    /* for stat.h              */
    #include <sys\stat.h>     /* for S_IREAD | S_IWRITE  */

    #define SCRCHARS  (25 * 80)
    int Buf[SCRCHARS];
    main(argc, argv)
    int argc;
    char *argv[];
    {
        int *cp, *ep, fname[16];
        int far *sp;
        int fd_out, bytes;

        if (argc != 2)
            {
            fprintf(stderr, "usage: scrsave file\n");
            exit(0);
            }
        if (strlen(argv[1]) > 8)
            {
            fprintf(stderr, "\"%s\": Filename too long.\n", argv[1]);
            exit(1);
            }
        strcpy(fname, argv[1]);
        strcat(fname, ".SCR");
        if (access(fname, 0) == 0)
            {
            fprintf(stderr, "\"%s\": Won't overwrite.\n", fname);
            exit(1);
            }
        if ((fd_out = open(fname, O_WRONLY | O_CREAT | O_BINARY,
                            S_IREAD | S_IWRITE)) < 0)
            {
            fprintf(stderr, "\"%s\": Can't create.\n", fname);
            exit(1);
            }
        /* Copy the screen into a near buffer. */
        ep = &Buf[SCRCHARS - 1];
        cp = Buf;
        /* use 0xB8000000 for EGA or VGA */
        sp = (int far *)(0xB0000000);
        for (; cp < ep; ++cp, ++sp)
            *cp = *sp;
        /* Write it. */
        bytes = write(fd_out, Buf, SCRCHARS * 2);
        if (bytes != SCRCHARS * 2)
            {
            fprintf(stderr, "\"%s\": Error writing.\n", fname);
            exit(1);
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 10-6.  The SCRSAVE.C program.

    Note that we copy the screen rather than write it directly because write()
    expects a normal pointer, whereas accessing the screen requires a far
    pointer.

Reading a File with read()

    Use the read() function to read from files. It is a simpler function to
    use than fread() because it takes only three arguments, as follows:

    read(fd_in, buf, bytes)
            â”‚     â”‚     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Number of bytes to read
            â”‚     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Where to place those bytes
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ File descriptor for a file opened for reading

    In this example, buf is either an array or the address of allocated
    memory. Be sure it is large enough to hold the number of bytes specified
    by the argument bytes, however, because the compiler does not check this
    for you.

    If the call to read() is successful, it returns the same value as bytes.
    If it returns a smaller value, then that value represents the number of
    bytes left in the file. A zero return value signifies the end of the file,
    and a -1 return value shows that a read error occurred.

    The SCRREST.C program (Listing 10-7) reads a file, copying as much as a
    screenful of what it reads to text-screen memory. It works with any file
    type, but reading files created with SCRSAVE.C (Listing 10-6) is its most
    useful application. Before you run the program, pull down the Debug menu
    and activate Screen Swapping On.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* scrrest.c  --  demonstrates read() by restoring */
    /*                text screen from any file        */

    #include <stdio.h>        /* for stderr              */
    #include <fcntl.h>        /* for O_RDONLY | O_BINARY */

    #define SCRCHARS  (25 * 80)
    int Buf[SCRCHARS];

    main(argc, argv)
    int argc;
    char *argv[];
    {
        int *cp, *ep;
        int far *sp;
        int fd_in, bytes;

        if (argc != 2)
            {
            fprintf(stderr, "usage: scrrest file.scr\n");
            exit(0);
            }
        if ((fd_in = open(argv[1], O_RDONLY | O_BINARY)) < 0)
            {
            fprintf(stderr, "\"%s\": Can't open to read.\n", argv[1]);
            exit(1);
            }
        /* Read it. */
        bytes = read(fd_in, Buf, SCRCHARS * 2);
        if (bytes < 0)
            {
            fprintf(stderr, "\"%s\": Error Reading.\n", argv[1]);
            exit(1);
            }
        if (bytes == 0)
            {
            fprintf(stderr, "\"%s\": Empty File.\n", argv[1]);
            exit(1);
            }
        /* Copy the buffer to screen memory. */
        ep = &Buf[bytes / 2];
        cp = Buf;

        /* use 0xB8000000 for EGA or VGA */
        sp = (int far *)(0xB0000000);
        for (; cp < ep; ++cp, ++sp)
            *sp = *cp;
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 10-7.  The SCRREST.C program.

Positioning with lseek()

    The unbuffered lseek() function lets a program position its next read or
    write to begin anywhere in a file. Almost identical to the buffered
    fseek(), lseek() takes a file descriptor as its first argument, rather
    than a file pointer. Therefore, use the lseek() function as follows:

    #include <io.h>      /* defines lseek()    */
    #include <stdio.h>   /* for origin, etc.   */

    long newpos, offset = 100L;
    int  fd;

    newpos = lseek(fd, offset, origin);
        â”‚            â”‚      â”‚      â””â”€â”€â”€ From where (current, begin, or end)
        â”‚            â”‚      â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Move this many bytes forward
        â”‚            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ In this file (file descriptor)
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ New position in file

    In this example, fd is a file descriptor for a file previously opened with
    open(). The second argument, offset, is the number of bytes to move in the
    file and must be of the type long. If offset is negative, you move toward
    the beginning of the file. The last argument, origin, can be one of the
    three possible definitions that specify where the move begins. These
    definitions are the same as those used by fseek(), which were mentioned in
    Table 10-4 on p. 305. Also, as with fseek(), you must specify #include
    <stdio.h> to access those definitions.

    After a successful repositioning, lseek() returns the new position in the
    file. A return value of -1L indicates an error. (Note that lseek() returns
    the type long.)

    The VIEW.C program (Listing 10-8) is a simple file-viewing program that
    illustrates how to use lseek() to move through a file. Pressing + moves
    you forward in the file, pressing - moves you backward, and typing q or Q
    ends the program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* view.c  --  demonstrates lseek() by displaying  */
    /*             a file and moving around in it      */

    #include <fcntl.h>        /* for open()         */
    #include <stdio.h>        /* for SEEK_CUR, etc. */

    #define HUNK 512
    #define MOVE 512L

    main(argc, argv)
    int argc;
    char *argv[];
    {
        char ch, buf[HUNK];
        long position = 0L;
        int  bytes, eofflag = 0, fd_in;

        if (argc != 2)
            {
            fprintf(stderr, "Usage: view file\n");
            exit(0);
            }

        if ((fd_in = open(argv[1], O_RDONLY)) < 0)
            {
            fprintf(stderr, "\"%s\": Can't open.\n", argv[1]);
            exit(1);
            }

        for (;;)
            {
            bytes = read(fd_in, buf, HUNK);
            if (bytes == 0)
                {
                if (! eofflag)
                    {
                    fprintf(stderr, "\n<<at end of file>>\n");
                    ++eofflag;
                    }
                else
                    exit(0);
                }
            else if (bytes < 0)
                {
                fprintf(stderr, "\"%s\": Error Reading.\n", argv[1]);
                exit(1);
                }
            else
                {
                eofflag = 0;
                position = lseek(fd_in, 0L, SEEK_CUR);
                if (position == -1L)
                    {
                    fprintf(stderr, "\"%s\": Error Seeking.\n", argv[1]);
                    exit(1);
                    }
                Print(buf, bytes);
                do
                    {
                    ch = getch();
                    if (ch == 'q' || ch == 'Q')
                        exit(0);
                    } while (ch != '+' && ch != '-');

                if (ch == '-')
                    {
                    position = lseek(fd_in, -2 * MOVE, SEEK_CUR);
                    if (position == -1L)
                        {
                        fprintf(stderr, "\"%s\": Error Seeking.\n", argv[1]);
                        exit(1);
                        }
                    }
                }
            }
    }

    Print(char *buf, int cnt)
    {
        int i;

        for (i = 0; i < cnt; ++i, ++buf)
            {
            if (*buf < ' ' && *buf != '\n' && *buf != '\t')
                printf("^%c", *buf + '@');
            else
                putchar(*buf);
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 10-8.  The VIEW.C program.

Finding Current Position with tell()

    Notice that VIEW.C finds the current position in the viewed file with the
    following:

    position = lseek(fd_in, 0L, SEEK_CUR);

    Because the need to know the current position is so common, the QuickC
    library provides the tell() function. Similar to the top-level ftell()
    routine, tell() takes a single argument, a file descriptor, and returns
    the current position in the file associated with that file descriptor.
    That position is a type long measure in bytes from the beginning of the
    file. If tell() fails for any reason, it returns a value of -1L.


The File System

    Not only do programs read and write to files, they often need to manage
    the file system as a whole. By the file system, we mean the MS-DOS
    directory hierarchy, the organization of directories, and the naming of
    directories and files. For example, your program might need to create or
    remove a directory or file, or relocate in the directory hierarchy (change
    the working directory), or create unique temporary filenames. In this
    section we discuss the file system and the C Library routines that let you
    manipulate it. We also warn you of possible pitfalls and present a few
    routines that let you handle errors gracefully.

Directories

    MS-DOS does not permit you to use fopen() or open() to open a directory.
    You can, however, create and remove directories or establish any directory
    as your current working directory. The routines for handling directories
    are listed in Table 10-7. All of the routines require that you first
    specify #include <direct.h>, which contains their declarations.

    The directory-handling functions chdir(), mkdir(), and rmdir() take a
    single argumentâ”€â”€a string or the address of a string that specifies a full
    pathname (such as C:\TMP\JUNKDIR), or a directory name relative to the
    current working directory (such as JUNKDIR). All three return an integer 0
    if they are successful; otherwise, they return a -1. Consider, for
    example, the code fragment on the next page.

    Table 10-7 The Directory-Handling Library Functions
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    chdir(path)    Changes the current working directory to path. Returns 0 if
                    successful.
    mkdir(path)    Creates a new directory named path. Returns 0 if
                    successful.
    rmdir(path)    Removes the directory whose name is path. Returns 0 if
                    successful.
    getcwd(buf, n) Places the full pathname of your current working directory
                    into the char buffer buf of length n. Returns NULL if an
                    error occurs.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    #include <direct.h>

    if (chdir("C:\\TMP") != 0)
    {
            /* chdir failed, so exit */
    }
    if (mkdir("JUNKDIR") != 0)
    {
            /* mkdir failed, so exit */
    }
    if (rmdir("JUNKDIR") != 0)
    {
            /* rmdir failed, so exit */
    }

    The #include <direct.h> directive provides definitions for the three
    routines that follow it. The chdir() function changes the current working
    directory to C:\TMP. (Note that in C you must use a double backslash to
    produce a single backslash.) Next, inside C:\TMP, the program uses mkdir()
    to create a new subdirectory called JUNKDIR. The final call to rmdir()
    removes that same subdirectory.

    The last routine in Table 10-7, getcwd() ("get current working
    directory"), takes two arguments and returns the address of a string. You
    can call this function using one of two forms. In the following form:

    #include <direct.h>
    #include <stdio.h>   /* for NULL */

    char buf[512];
    if (getcwd(buf, 512) == NULL)
    {
            /* couldn't get current working directory */
    }

    The getcwd() function is passed the address of a char buffer, buf, into
    which it places the name of the current working directory. The length 512
    is the number of bytes in the buffer. (Remember that the buffer must be
    large enough for both the name and a terminating '\0'.)

    The second form for calling getcwd() is as follows:

    #include <direct.h>
    #include <stdio.h>   /* for NULL */

    char *name;
    if ((name = getcwd(NULL, 0)) == NULL)
    {
            /* couldn't get current working directory */
    }

    This form passes getcwd(), the special zero address NULL, and a length of
    zero. This causes getcwd to use malloc() to allocate enough space for the
    name of the current working directory name (plus 1 for the terminating
    '\0'), to copy that name into the newly allocated space, and to return the
    address of that space. Both forms of getcwd() return NULL if the operation
    fails.

    The DIRX.C program (Listing 10-9) demonstrates all four of the
    directory-handling subroutines. It first creates a subdirectory in the
    current directory, then relocates to that subdirectory and creates a
    sub-subdirectory. Finally, it returns to the original directory and
    attempts to remove the first subdirectory it created. It fails at this
    point because it is illegal to remove a subdirectory that is not empty. If
    you run the program again, it will fail immediatelyâ”€â”€it cannot execute the
    first mkdir() because a directory with that name already exists.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* dirx.c  --  directory examples  */

    #include <direct.h>
    #include <stdio.h>

    #define SUBDIR "SUBDIR"
    #define SUBSUBDIR "SUBSUB"

    main()
    {
        char *current_dir;
        void Err();

        if ((current_dir = getcwd(NULL, 0)) == NULL)
            Err("getcwd()", "Can't get current directory.");

        if (mkdir(SUBDIR) != 0)
            Err(SUBSUBDIR, "Can't make directory.");

        if (chdir(SUBDIR) != 0)
            Err(SUBDIR, "Can't cd into directory.");

        if (mkdir(SUBSUBDIR) != 0)
            Err(SUBSUBDIR, "Can't make directory.");

        if (chdir(current_dir) != 0)
            Err(SUBDIR, "Can't cd back to.");

        if (rmdir(SUBDIR) != 0)
            Err(SUBDIR, "Can't remove directory.");

    }

    void Err(char *what, char *msg)
    {
        fprintf(stderr, "\"%s\": %s\n", what, msg);
        exit (1);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 10-9.  The DIRX.C program.

Manipulating Files by Name

    Several standard C Library routines make it easy for you to remove and
    rename files and also to create unique filenames from within a program.
    These routines (listed in Table 10-8) are useful in databases, compilers,
    games, and any other program that needs to manipulate files.

    The routines unlink() and remove() are identical. Each takes a single
    argumentâ”€â”€the address of a stringâ”€â”€and erases (removes from the disk) the
    file whose name is specified in that string. The filename that you specify
    can either be a full path such as C:\TMP\JUNK, which removes the file JUNK
    from the directory C:\TMP, or it can be a relative pathname such as JUNK,
    in which case the called routine removes the file JUNK from the current
    working directory.

    The rename() function can do more than merely rename files. It can rename
    directories and move files from one directory to another (but not from one
    disk to another). Consider the following example, in which JUNK is a file
    and DIR1 and DIR2 are directories:

    rename("JUNK", "OLDJUNK");â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Rename a file
    rename("DIR1\\JUNK", "DIR2\\JUNK");â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Move a file
    rename("DIR1", "OLDDIR1");â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Rename a directory

    The first line renames the file JUNK in the current working directory as
    OLDJUNK; the second line moves the file JUNK in the subdirectory DIR1 into
    the subdirectory DIR2. Note that you could have renamed JUNK during the
    move. Also remember that, in C, you must use two backslashes to produce a
    single backslash.

    The third line of the above example renames the directory DIR1 as OLDDIR1.
    It is important to note that directories, unlike files, cannot be moved.

    Table 10-8 Routines That Manipulate Files by Name
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    unlink(path)   Removes (erases) the file whose name is specified by path.
                    Returns 0 if the call is successful.
    remove(path)   Same as unlink().
    rename(old,    Renames the file old, giving it the new name new. Also
    new)           allows the renaming of directories. Files can be moved with
                    this routine. Returns 0 if successful.
    mktemp(tmplt)  Fills out the template tmplt with a filename that does not
                    already exist.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    The mktemp() function generates a unique filename that is guaranteed not
    to exist on your disk. Use it as follows:

    #include <io.h>     /* defines mktemp() */
    #include <stdio.h>  /* for NULL */

    static char template[] = "C:\\TMP\\XXXXXX";

    if (mktemp(template) == NULL)
    {
            /* No unique name possible */
    }

    First we specify #include <io.h> for the definition of mktemp(). In that
    header file, mktemp() is defined as returning the address of a string
    (that is, char *). We also must use #include <stdio.h> to define NULL,
    which mktemp() returns if it fails.

    The template passed to mktemp() must take the form baseXXXXXX; that is, it
    may be any prefix, path, or part of a filename, ending with six X
    characters. The mktemp() function replaces the X characters with one
    alphanumeric character followed by five digits, thus forming a unique name
    (one that does not already exist on the disk), such as A00000.

    The FMENU.C program (Listing 10-10) uses all of these routines within a
    small file-handling menu program. It enables you to rename/move a file or
    directory, remove a file, or create a unique file. You can use FMENU.C as
    the core of your own programs that let the user control files without
    exiting to MS-DOS. Before you compile and run FMENU.C, follow the steps
    outlined in the box on page 325, "Making New Library Routines Available
    to QuickC."

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* fmenu.c  --  demonstrates file renaming, etc. */

    #include <direct.h>
    #include <stdio.h>
    #include <string.h>

    #define MAXPATH (80)
    char From_name[MAXPATH],
        To_name[MAXPATH];

    int Input(char *prompt, char buf[])
    {
        printf("%s: ", prompt);
        if (gets(buf) == NULL || *buf == '\0')
            return (0);
        return (1);
    }
    void Rename(void)
        {
        printf("->Rename/move\n");
        if (!Input("From", From_name)) return;
        if (!Input("To", To_name)) return;
        if (rename(From_name, To_name) != 0)
            perror("RENAME");
        else
            printf("Renamed: \"%s\" -> \"%s\"\n",
                    From_name, To_name);
    }
    void Remove(void)
    {
        printf("->Remove\n");
        if (!Input("Remove", From_name)) return;
        if (!Input("Are You Sure", To_name)) return;
        if (*To_name != 'y' && *To_name != 'Y')
            return;
        if (remove(From_name) != 0)
            perror(From_name);
        else
            printf("Removed: \"%s\"\n", From_name);
    }
    void Maketemp(void)
    {
        printf("->Maketemp\n");
        if (!Input("In What Directory", From_name))
            return;
        (void)strcat(From_name, "\\XXXXXX");
        if (mktemp(From_name) == NULL)
            printf("Can't create a unique name.\n");
        else
            printf("Created: \"%s\"\n", From_name);
    }
    void Quit(void)
    {
        printf("->Quit\n");
        if (!Input("Are You Sure", From_name))
            return;
        if (*From_name != 'y' && *From_name != 'Y')
            return;
        exit(0);
    }

    main()
    {
        static void (*doit[])() = {Rename, Remove, Maketemp, Quit};
        int ch;
        while (1)
            {
            printf("--------------------------------------------\n");
            printf("1) Rename/move a file or rename a directory.\n");
            printf("2) Remove a file.\n");
            printf("3) Make a unique temporary file.\n");
            printf("4) Quit.\n");
            printf("--------------------------------------------\n");
            printf("Select: ");

            do
                {
                ch = getchar();
                } while (ch < '1' || ch > '4');
            getchar();    /* gobble trailing newline */
            printf("%c\n\n", ch);
            ch -= '1';
            doit[ch]();
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 10-10.  The FMENU.C program.

    FMENU.C uses a technique we discussed in Chapter 8â”€â”€an array of pointers
    to functions. Each menu choice corresponds to a function in that array,
    and each of those functions utilizes a different routine for file
    manipulation. Note that FMENU.C contains an error-printing routine you
    haven't seen beforeâ”€â”€perror().

Printing Clear and Meaningful Diagnostics with perror()

    All C programs use a system-defined global variable called errno, which is
    set and cleared with each system or I/O call. A standard C Library routine
    called perror() prints an appropriate error message based on the current
    value in errno. For example, suppose an fopen() for reading a file named
    JUNK fails because the file didn't exist. In that case QuickC sets errno
    to 2, and perror(), when called as

    perror("JUNK");

    prints the following to the standard error output:

    JUNK: No such file or directory

    Using perror() helps your program generate clearer and more meaningful
    diagnostic messages. However, remember to call perror() immediately after
    a library routine returns an error. If you call another library routine
    before perror(), it might change errno and cause perror() to print an
    incorrect message. For example,

    if((fp = fopen(fname, "rb")) == NULL)
    {
        fprintf(stderr, "Program Aborted because\n");
        perror(fname);
        exit(1);
    }

    does not work because the fprintf() preceding perror() succeeds and thus
    sets errno to zero, causing perror() to print the incorrect message
    Undefined error.


Advanced Error Handling

    A program that can recover from any error is called "robust." Robust
    programs are not merely carefully written programsâ”€â”€they are programs that
    include library routines for handling all abnormal conditions and that
    issue clear diagnostic messages to the user. Table 10-9 lists the most
    useful routines for handling abnormal conditions.

    Table 10-9 Abnormal-Condition Handlers and Diagnostic Routines
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    signal()       Traps errors that can terminate a program, such as Ctrl-C
                    and floating-point exceptions.
    setjmp()       Prepares for a jump between functions.
    longjmp()      Executes a jump between functions.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Making New Library Routines Available to QuickC
    To compile and run the FMENU.C program successfully, perform the following
    steps to add a few routines to QuickC that are not normally available.

    1.  Create the following program and save it using F.C as its filename.

        #include <direct.h>
        main()
        {
            rename();
            mktemp();
            perror();
        }

    2.  Exit QuickC and run the following MS-DOS command line (ignore any
        warnings about actual arguments):

        qcl /c /am f.c

    3.  Run the following command line to create an add-on Quick Library:

        link c:\lib\quicklib.obj+f.obj,f.qlb,,/q;

        where c:\lib is the location for your QuickC libraries as determined
        when you ran SETUP.

    4.  Rerun QuickC with the following:

        qc /lf

        For a more detailed explanation of Quick Libraries, see Chapter 12 of
        this book and Section 10.1 of your Microsoft QuickC Programmer's
        Guide.

Signals

    Signals are conditions that cause a program to terminate prematurely. The
    signals for MS-DOS are listed in signal.h: They include Ctrl-C,
    Ctrl-Break, and floating-point errors such as division by zero. A text
    editor is an example of a program that should not terminate if one of
    these conditions occurs. The user might, for example, be editing a
    temporary copy of a fileâ”€â”€you would want to write a user's changes to disk
    before exiting, no matter what.

    To handle errors such as these, use the signal() function as follows:

    #include <signal.h>

    status = signal(sig, funct);
        â”‚             â”‚     â””â”€â”€â”€â”€â”€â”€ Function address or SIG_IGN or SIG_DFL
        â”‚             â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ One of the signals defined in signal.h
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ SIG_ERR on error

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Error-handling Philosophies: BASIC vs C
    Most versions of BASIC build an error-handling mechanism into the language
    in the form of the ON ERROR ... GOTO label construct. When an error is
    encountered, control switches to the appropriate label or line number.
    Although you can turn this facility on and off, you don't have fine
    control of it.

    To review the situation in C, each function is responsible for reporting
    errors back to its caller. This procedure is more flexible than that used
    by BASIC, but it admits some inconsistencies. Functions that return
    pointers (such as fopen(), which returns a pointer to the file opened)
    often return a null pointer, which can be tested against the predefined
    value NULL. Other functions return the value -1 to indicate an error and
    store the specific error number in the global variable errno, using
    error-number values defined in the include file errno.h. Still other
    functions cannot return error values because no values are reserved for
    that purpose: All values might conceivably be returned by normal
    operation. You can, however, use the function ferror() to find out if any
    error occurred during input or output to a particular file. If you are not
    sure how a particular function handles error conditions, a quick way to
    find out is to use QuickC's on-line help facility discussed earlier in
    this book.

    In return for the greater flexibility C provides, you must explicitly test
    for an error (usually by putting the function call in an if or while
    statement or by calling ferror()) and then call any error-handling
    functions.

    The signal mechanism (discussed in this section) provides an additional,
    UNIX-compatible way to handle error conditions reported by the operating
    system. This mechanism is similar to the BASIC mechanism in that it
    establishes a global connection between a particular error condition and
    an error-handling function.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    We specify #include <signal.h> for definitions of signal(), its return
    value, and all of the possible values for sig. The signal() function takes
    two arguments. The first specifies the type of error, the values of which
    are listed in <signal.h> and summarized for MS-DOS in Table 10-10 on the
    following page. The second argument is the name (or address) of a function
    to be called if sig occurs, or one of the two predefined values: SIG_IGN
    (ignore this signal) or SIG_DFL (resume the default action, that is,
    terminate the program). Figure 10-4 illustrates the use of signal().

        #include <signal.h>
        int Sigflag = 0;    /*  global  */
        main ()
        {
            extern int Funct ();
            1  if  (signal (SIGINT, Funct) == SIG_ERR)
                {
                printf ("Signal () failed. \n");
                exit  (0);
                }
            for (;;)      /* forever      */
                {
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–º printf ("Waiting For Ctrl-C\n");
    â”‚      5                                   â—„â”€â”€â”€2 3
    â”‚             if (Sigflag != 0)                  â”‚
    â”‚             break 6                            â”‚
    â”‚             }                                  â”‚
    â”‚    } 7                                         â”‚
    â”‚                                                â”‚
    â”‚    Funct ()â—„â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
    â”‚    {
    â”‚        ++Sigflag;
    â”‚    } 4
    â””â”€â”€â”€â”€â”€â”˜

    1  Calling siganl() sets up the program to handle the Ctrl-C interrupt.

    2  User presses Ctrl-C (or Ctrl-Break) during the perpetual for loop which
        is printing Waiting for Ctrl-C at the time.

    3  Funct() is immediately called and increments Sigflag.

    4  Funct() returns and...

    5  the printf() statement previously interrupted is then executed (again).

    6  We check Sigflag and because it was set to a nonzero value when Funct()
        was called, we exit the perpetual for loop by breaking out of it.

    7  Program ends.

    Figure 10-4. Analysis of signal().

    As a rule, the signal-handling function, Funct(), should not perform any
    I/O operation. Rather than handling the error itself, it should set a
    global flag variable, then return to let the main body of the code handle
    the error. The main program stops, and the signal-handling function,
    Funct(), is called with the signal number sig as its argument. When
    Funct() finishes and returns, the main program continues from the exact
    point at which it stopped.

    Handling signals under MS-DOS is fairly simple because only six signals
    are defined, and only three of those actually do anything. However, if you
    move your code to XENIX or UNIX, you should be prepared to handle thirty
    or more signals, all of which can affect your program.

    Table 10-10 Signals Defined for MS-DOS
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    SIGABRT        Abnormal program termination. Terminates the program and
                    exits with a return value of 3.
    SIGFPE         Floating-point exception (such as division by zero or an
                    invalid operation). Terminates the program.
    SIGINT         Interrupt for keyboard. Sent when the user types the key
                    sequence Ctrl-C. Terminates the program.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Jumping Between Functions with setjmp() and longjmp()

    Sometimes when a signal occurs, your program might not be able to continue
    its main body of code. A signal caused by division by zero, for example,
    would result in a completely wrong answer should it continue. For
    situations such as these, when you need to jump to an earlier stage of the
    program, the standard C Library offers two functions: setjmp() and
    longjmp().

    setjmp() prepares the program for an eventual jump to an earlier state, as
    follows:

    #include <setjmp.h>

    jmp_buf env;

    if (setjmp(env) != 0)
    {
        /* We got here because of a longjmp()
            from someplace else */
    }
    /* all prepared for a longjmp() */

    We specify #include <setjmp.h> for the definition of jmp_buf. The variable
    env is declared as the type jump_buf and is the buffer that will hold all
    the information QuickC needs to perform a jump between functions. Next,
    the call to setjmp() prepares for an eventual call to longjmp(). The
    result of this preparation is always 0. When setjmp() returns a 0, you
    know that the program is set up for a later call to longjmp() but that the
    call has not occurred. A later call to longjmp() causes the program to
    call setjmp() again, but this time the call returns a nonzero value.

    Use the longjmp() routine as follows:

    longjmp(env, ret);

    The program calls longjmp() with the same env with which it called
    setjmp() earlier. The ret argument must be a nonzero number because it is
    the value returned by setjmp(). (Figure 10-5 illustrates this
    relationship.)

        #include <set jmp.h>
        jmp_buf Env;        /*  global  */
        main ()
        {
    â”Œâ”€â”€â”€â”€â”€â–º 1 if setjmp (Env)  != 0) â—„â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚             {                                        â”‚
    â”‚             printf ("Exiting at A\n");               â”‚
    â”‚             exit (0); A                              â”‚
    â”‚             }                                        â”‚
    â”‚                                                      â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–º printf ("Calling Foo ()\n");             â”‚
    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ 2 Foo();                                   â”‚
    â”‚                                                      â”‚
    â”‚             printf ("Exiting at B\n");               â”‚
    â”‚             Exit (0); B                              â”‚
    â”‚    }                                                 â”‚
    â”‚                                                      â”‚
    â””â”€â”€â–º Foo()                                             â”‚
        {                                                 â”‚
                printf ("In Foo ()\n");                  â”‚
                                                            â”‚
                longjmp (Env, 1); 3 â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
        }

    1  The first call to setjmp() returns 0, so flow continues with the first
        line after the if.

    2  Foo() is called.

    3  In Foo(), longjmp() returns us to 1. This time, however, setjmp() retur
        1, so we exit at A. Note that B is never reached.

    Figure 10-5. Analysis of setjmp() and longjmp().



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€