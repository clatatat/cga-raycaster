Appendix B  Built-in QuickC Functions

    If your program has only a single module, you can call any of the standard
    library functions without using a program list. These functions, listed
    alphabetically in the table on the next page, are part of the file QC.EXE
    and are loaded into memory when you start up QuickC. They comprise the
    built-in, or core, library functions for QuickC. Function names that begin
    with an underline character are non-ANSI functions developed by Microsoft.

    Note that this list updates the list published in the Microsoft QuickC
    Programmer's Guide by including a few changes made subsequent to the
    printing of that manual. See pp. 125â”€31 of the same manual for information
    about compiling multiple-module programs and using program lists.

    QuickC's Core Library Functions
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    abort          _fmalloc       ltoa          segread        strnset
    access         _fmsize        malloc        setbuf         strpbrk
    atexit         fopen          memavl        setjmp         strrchr
    atof           fprintf        memccpy       setmode        strrev
    atoi           fputc          memchr        setvbuf        strset
    atol           fputs          memcmp        signal         strspn
    bdos           fread          _memmax       sopen          strstr
    brk            free           memmove       spawnl         _strtime
    calloc         _freect        memset        spawnle        strtok
    chdir          fscanf         mkdir         spawnlp        strupr
    chmod          fseek          movedata      spawnlpe       system
    clearerr       fstat          _msize        spawnv         tell
    close          ftell          _nfree        spawnvpe       time
    cputs          fwrite         _nmalloc      sprintf        tmpfile
    creat          getch          _nmsize       sscanf         tmpnam
    dosexterr      getche         onexit        stackavail     tolower
    _dos_read      getcwd         open          strcat         toupper
    _dos_write     _getdate       printf        strchr         tzset
    eof            getenv         putch         strcmp         ultoa
    _exit          gets           puts          strcmpi        ungetc
    exit           gettime        raise         strcpy         unlink
    _expand        int86          read          strcspn        vfprintf
    fclose         int86x         realloc       _strdate       vprintf
    fflush         intdosx        remove        strdup         vsprintf
    _ffree         isatty         rewind        stricmp        write
    fgets          itoa           rmdir         strlwr
    filelength     kbhit          rmtmp         strncat
    flushall       longjmp        sbrk          strncmp
                    lseek          scanf         strncpy
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€



    Mitchell Waite is President of the Waite Group, a San Francisco,
    California-based developer of technical and computer books. He is also an
    experienced programmer, fluent in a variety of computer languages. Waite
    is a coauthor of MICROSOFT MACINATIONS, published by Microsoft Press, and
    of UNIX Primer Plus and C Primer Plus, published by Howard W. Sams.

    Stephen Prata, Ph.D., is Professor of Physics and Astronomy at the College
    of Marin in Kentfield, California, where he teaches C and UNIX. Prata is
    coauthor of several Waite Group books, including UNIX Primer Plus, C
    Primer Plus, and UNIX System V Primer, all published by Howard W. Sams.

    Bryan Costales is Senior Systems Programmer at EEG Systems Laboratory. He
    is the author of C From A to Z, from Prentice-Hall (Simon & Schuster), and
    coauthor of UNIX Communications, published by Howard W. Sams.

    Harry Henderson is a freelance technical writer and editor. He has edited
    and contributed to computer books for the Waite Group, Blackwell
    Scientific, and Wadsworth. In addition, he is the editor for Tricks of the
    UNIX Masters and The UNIX Bible, Waite Group books published by Howard W.
    Sams.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€