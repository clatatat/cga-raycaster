Chapter 11  Advanced Data Types

    Many programs, such as databases, spreadsheets, catalogs, and indexes,
    group information in such a way that each item needs to be a different C
    data type. (See Figure 11-1 on the following page.) To facilitate writing
    these programs, C offers a "structure" typeâ”€â”€a special array-like form in
    which each element can be a different type.

    These kinds of programs also need to be able to store different types of
    data, at one time or another, at the same place in memory. The street
    number in Figure 11-1, for example, could be numeric, such as 212,
    requiring an integer variable, or it could be alphanumeric, such as 212B,
    requiring a string variable. The C union data type solves this problem by
    letting you store different types at the same place in memory.

    This chapter shows you how to program with structures and unions. It also
    discusses the less frequently used data types enum and bit fields.
    Finally, we'll detail typedef, an alternative to the #define preprocessor
    directive that lets you create new types from old.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚            char             char             char        â”‚
    â”‚ NAME  _______________  _______________  _______________  â”‚
    â”‚           first             last            middle       â”‚
    â”‚                                                          â”‚
    â”‚             long                   char                  â”‚
    â”‚ ADDRESS  ___________  _________________________________  â”‚
    â”‚          street_num               street                 â”‚
    â”‚                                                          â”‚
    â”‚                char            char           long       â”‚
    â”‚          ________________  _____________  _____________  â”‚
    â”‚                city            state           zip       â”‚
    â”‚                                                          â”‚
    â”‚          int           long                              â”‚
    â”‚ PHONE  (______)  ___________________                     â”‚
    â”‚       area_code        phone                             â”‚
    â”‚                                                          â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 11-1. To enter the information on an address/phone index card into
    a computer, you need to use different data types organized as a single
    conceptual unit.


Structureâ”€â”€An Array of Different Types

    An obvious limitation of arrays is that the variables in a single array
    must all be of the same type (all char, all int, and so on). However, you
    will frequently need to group variables of different types together so
    that you can manipulate them as a single conceptual unit. The information
    on the index card in Figure 11-1 is a good example. Because all of the
    different "types" of information actually relate to a single person, it is
    more convenient and conceptually sound to place all of that information in
    a single array. Unfortunately, arrays cannot handle different data types.
    To group strings and integers, for example, you must use a structure,
    which can hold any mixture of types, including arrays, pointers, and
    integers.

    Think of a structure as a special kind of array. However, whereas the
    variables in an array are called elements and are referenced by an offset,
    the variables in a structure are called "members" and are referenced by
    name.

    You declare a structure with the C keyword struct. The first step in
    setting up a structure is to declare a pattern, or template, for the
    variables it will contain and to give that pattern a name. A pattern for
    the structure that contains the address-book information in Figure 11-1,
    for example, appears at the top of the next page.

    To declare a structure pattern, follow the keyword struct with the name of
    the pattern (cardstruct). Next, list the variables, or members, of the
    structure between a set of braces. Note that although this list resembles
    a list of variable declarations, you are not allocating memory for storage
    of the structure's membersâ”€â”€you are merely creating a template that
    reserves those names for future use.

        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Keyword
        â”‚        â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Name of pattern
        â”‚        â”‚     â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Variables between braces
    struct cardstruct {
        char *first, *last, *middle;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Member list start
        long street_num;
        char *street, *city, *state;
        long zip;
        int area_code;
        long phone;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Member list end
    };
    â”‚â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Closing semicolon
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Variables between braces

Structure Variables

    To reserve memory for a structure's members, you must declare structure
    variables that follow the pattern you defined. The following declaration
    sets aside memory for two structure variables (card1 and card2) using the
    above cardstruct pattern:

    struct cardstruct card1, card2;

    This declaration starts with the keyword struct, as did the pattern, but
    this time struct is followed by the name of a previously declared pattern
    and then by the names of the structure variables. Remember, you manipulate
    card1 and card2 in the programâ”€â”€the pattern cardstruct merely declares new
    structures. This statement reserves memory (allocates enough storage) for
    the predefined members of those two structure variables, as shown in
    Figure 11-2.

    struct cardstruct card 1, card 2;
                    â””â”€â”€â”€â”€â”˜  â””â”€â”€â”€â”€â”˜
                        â”‚        â”‚
                    â”Œâ”€â”€â”€â”€â”˜        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
        â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â–¼â”€â”€â”€â”€â”€â”                   â”Œâ”€â”€â”€â”€â”€â–¼â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
        â”‚  *first       â”‚                   â”‚  *first       â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤                   â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤
        â”‚  *last        â”‚                   â”‚  *last        â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤                   â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤
        â”‚  *middle      â”‚                   â”‚  *middle      â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”   â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
        â”‚          street_num           â”‚   â”‚          street_num           â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜   â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜
        â”‚  *street      â”‚                   â”‚  *street      â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤                   â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤
        â”‚  *city        â”‚                   â”‚  *city        â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤                   â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤
        â”‚  *state       â”‚                   â”‚  *state       â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”   â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
        â”‚              zip              â”‚   â”‚              zip              â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜   â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜
        â”‚    area_code  â”‚                   â”‚    area_code  â”‚
        â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”   â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
        â”‚            phone              â”‚   â”‚            phone              â”‚
        â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜   â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜
        â”‚1 byte â”‚
        â”‚       â”‚

    Figure 11-2. Declaring structure variables sets aside enough memory for
    the variables defined by cardstruct.

Accessing Structure Members

    To access a member of a structure in C, specify the name of the structure
    variable that contains the member, then the . (pronounced "dot") operator,
    then the name of the member you need to access, as in the following
    example:

    printf("%d\n", card1.area_code);
                    â”‚   â”‚  â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Name of member of structure
                    â”‚   â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ A "dot"
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Name of structure

    This expression prints the value of the integer area_code, one of the
    member variables in the structure variable named card1.

    You can manipulate members of structures as you would any C variables: You
    can assign values to them, use them in computations, and so on. The only
    difference is that you must reference each member variable with the name
    of its structure (card1 or card2, for example), a dot, and then its own
    name.

    The CARD.C program (Listing 11-1) demonstrates structures by prompting
    you to fill out information for a fictional address-book card; then it
    prints out the information you entered.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* card.c  --  demonstrates how to declare structures  */
    /*             and how to use structure members        */

    #include <stdio.h>      /* for NULL and stdin */
    #include <string.h>     /* for strdup()       */

    #define MAXN 79

    struct cardstruct {                 /* global pattern */
        char *first, *last, *middle;
        long street_num;
        char *street, *city, *state;
        long zip;
        int  area_code;
        long phone;
    };

    main()
    {
        char *Str_Input();
        long Lint_Input();
        struct cardstruct card1;

        card1.first         = Str_Input("First Name");
        card1.last          = Str_Input("Last Name");
        card1.middle        = Str_Input("Middle Name");
        card1.street_num    = Lint_Input("Street Number");
        card1.street        = Str_Input("Street Name");
        card1.city          = Str_Input("City");
        card1.state         = Str_Input("State");
        card1.zip           = Lint_Input("Zip Code");
        card1.area_code     = (int)Lint_Input("Area Code");
        card1.phone         = Lint_Input("Phone Number");

        printf("\n\n");
        printf("%s %s %s\n", card1.first, card1.middle,
                card1.last);
        printf("%ld %s, %s, %s %ld\n", card1.street_num,
                card1.street, card1.city, card1.state,
                card1.zip);
        printf("(%d) %ld\n", card1.area_code, card1.phone);
    }

    char *Str_Input(char *prompt)
    {
        char buf[MAXN+1], *ptr;

        printf("%s: ", prompt);
        if (fgets(buf, MAXN, stdin) == NULL)
            exit(0);
        buf[strlen(buf) - 1] = '\0'; /* strip '\n' */
        if (strlen(buf) == 0)
            exit(0);
        if ((ptr = strdup(buf)) == NULL)
            exit(0);
        return (ptr);
    }

    long Lint_Input(char *prompt)
    {
        char buf[MAXN + 1];
        long num;

        printf("%s: ", prompt);
        if (fgets(buf, MAXN, stdin) == NULL)
            exit(0);
        if (sscanf(buf, "%ld", &num) != 1)
            exit(0);
        return (num);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 11-1.  The CARD.C program.

    CARD.C uses the members of the structure card1 exactly as it would
    ordinary variables. It assigns values to them with the = operator and
    passes those values to printf() to be printed.

Shorthand Structure Declarations

    As a bit of shorthand, you can declare structure patterns and allocate
    storage for structure variables in a single statement, as follows:

    When you allocate storage for structure variables as a part of the
    declaration, the name of the pattern becomes optional and you can omit it:

            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Name of pattern omitted
    struct {
        /* list of members here */
    } card1, card2;
        â””â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Structures allocated storage

    You must use the pattern name, however, if you intend to declare
    additional structure variables using that pattern name later in the
    program:

    struct cardstruct card3, card4;

Structure Assignment

    When you declare structure variables with the same pattern, you can assign
    one to another, as follows:

    card2 = card1;

    This assignment copies the values of all card1 members into the
    corresponding members of card2.

    If you try to assign one structure variable to another when those
    structures are declared with different pattern names (even if the members
    of both are identical), QuickC returns the following error message:

    error C2115:
    '=' : incompatible types

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    One way to make a program such as CARD.C more robust, or user friendly, is
    to enable the program to handle telephone numbers that contain a hyphen
    (-) character. Consider the necessary revisions to CARD.C. Why is this
    enhancement difficult in a program that uses scanf() to parse user input?
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    If you need to assign values from one structure to another of a different
    pattern, you must assign the members individually. For example, if card1
    uses the pattern cardstruct and memo uses another pattern, memostruct, you
    could assign the members of one to the other in the following way:

    card1.first  = memo.first_name;
    card1.last   = memo.last_name;
    card1.middle = memo.mid_name;

Passing Structures to Functions

    Passing a structure to a function passes a copy of its members. This
    prevents the called function from changing the original structure. To pass
    a structure to a function, simply state the structure's name, as follows:

    Showcard(card1);

    In this example, a copy of the structure variable card1â”€â”€including copies
    of all its membersâ”€â”€is passed to the function Showcard(). Remember,
    structures differ from arrays in this regard: When you pass a structure to
    a function, you pass only a copy of that structure; when you pass an
    array, you pass the address of that array, thus allowing the original
    array to be changed by the calling function.

    In the receiving function (such as Showcard() below), you must declare the
    type of the received argument with struct and the pattern name
    (cardstruct). This tells the compiler that Showcard() is receiving a
    structure as its argument, and that the pattern for that structure is
    named cardstruct:

                                    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Receive copy of
    Showcard(struct cardstruct card)
    {                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ structure based on this pattern
        /* body of function */
    }

    The CARD2.C program (Listing 11-2 beginning on the following page) is a
    revised CARD.C program. In it, we fill out two cards and then print those
    cards using the Showcard() function.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    There are two drawbacks to passing structures to functions. First, not all
    compilers support the passing of structures, so if portability is
    important, you might want to avoid this technique. Second, as structures
    get larger, QuickC takes longer to copy them for each function call. This
    can become very time-consuming if it occurs in the middle of a loop. Thus,
    to speed the processing of your programs and enable the original to be
    changed, we advise you to use pointers to structures.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* card2.c --  demonstrates structure assignment and   */
    /*             how to pass a structure to a function   */

    #include <stdio.h>      /* for NULL  and stdin */
    #include <string.h>     /* for strdup()        */

    #define MAXN 79

    struct cardstruct {                 /* global pattern */
        char *first, *last, *middle;
        long street_num;
        char *street, *city, *state;
        long zip;
        int  area_code;
        long phone;
    };

    main()
    {
        int  i;
        char *Str_Input();
        long Lint_Input();
        struct cardstruct card1, card2;

        for (i = 0; i < 2; i++) /* do twice */
            {
            printf("\nCard %d:\n\n", i + 1);

            card1.first         = Str_Input("First Name");
            card1.last          = Str_Input("Last Name");
            card1.middle        = Str_Input("Middle Name");
            card1.street_num    = Lint_Input("Street Number");
            card1.street        = Str_Input("Street Name");
            card1.city          = Str_Input("City");
            card1.state         = Str_Input("State");
            card1.zip           = Lint_Input("Zip Code");
            card1.area_code     = (int)Lint_Input("Area Code");
            card1.phone         = Lint_Input("Phone Number");

            if (i == 0)
                card2 = card1;      /* structure assignment */
            }
        Showcard(card2);
        Showcard(card1);

    }
    Showcard(struct cardstruct card)
    {
        printf("\n\n");

        printf("%s %s %s\n", card.first, card.middle, card.last);
        printf("%ld %s, %s, %s %ld\n", card.street_num,
                card.street, card.city, card.state, card.zip);
        printf("(%d) %ld\n", card.area_code, card.phone);
    }

    char *Str_Input(char *prompt)
    {
        char buf[MAXN + 1], *ptr;

        printf("%s: ", prompt);
        if (fgets(buf, MAXN, stdin) == NULL)
            exit(0);
        buf[strlen(buf) - 1 ] = '\0'; /* strip '\n' */
        if (strlen(buf) == 0)
            exit(0);
        if ((ptr = strdup(buf)) == NULL)
            exit(0);
        return (ptr);
    }

    long Lint_Input(char *prompt)
    {
        char buf[MAXN + 1];
        long num;

        printf("%s: ", prompt);
        if (fgets(buf, MAXN, stdin) == NULL)
            exit(0);
        if (sscanf(buf, "%ld", &num) != 1)
            exit(0);
        return (num);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 11-2.  The CARD2.C program.

    In CARD2.C, Showcard() receives a copy of card1 from main(). Note that the
    members of the Showcard() structure, card, are accessed with the same
    "dot" notation as the originals in main().

Pointers to Structures

    Passing a pointer to a structure, rather than a copy of a structure, to a
    function has two advantages. It permits the function to modify the members
    of the original structure. Also, far fewer bytes must be copied when a
    pointer is passed than are copied when a structure is passedâ”€â”€the result
    is faster executing code.

    You declare a pointer to a structure the same way that you declare a
    pointer to any other typeâ”€â”€by preceding its name with a *, as follows:

    struct cardstruct *cardptr;
                â”‚     â””â”€â”€â”€â”€â”€â”€ A pointer to a structure of pattern cardstruct
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Name of pattern

    This example declares a pointer variable, cardptr, whose contents will be
    an address. The struct cardstruct in the declaration tells the compiler
    that cardptr will point to a structure variable based on the pattern
    cardstruct. (See Figure 11-3.)

    Before you can use the pointer cardptr, it must be given a value. Because
    it is a pointer to a structure, we will assign it the address of the
    structure variable card1 from CARD.C:

    cardptr = &card1;

    The & operator fetches the address of a structure. (Note that this differs
    from arrays, where the array name itself yields the address.) To assign
    the address of a structure variable to a pointer to a structure, declare
    both the pointer and the structure with the same pattern name. If you
    declare them with different pattern names, QuickC returns the following
    warning message:

    warning C4049:
    '=' : indirection to different types

    The & operator can also pass the address of a structure directly to a
    function:

    Enter(&card1);
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Pass address of card1 to a function

    struct cardstruct *cardptr;
                    â””â”€â”€â”€â”€â”€â”€â”€â”˜
                        â”‚
            â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â–¼â”€â”€â”€â” Points to   â”Œâ”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
            â”‚   address     â”‚â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”‚  *first       â”‚
            â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜             â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤
                                            â”‚  *last        â”‚
                                            â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤
                                            â”‚  *middle      â”‚
                                            â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
                                            â”‚          street_num           â”‚
                                            â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜
                                            â”‚  *street      â”‚
                                            â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤
                                            â”‚  *city        â”‚
                                            â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¤
                                            â”‚  *state       â”‚
                                            â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
                                            â”‚              zip              â”‚
                                            â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜
                                            â”‚    area_code  â”‚
                                            â”œâ”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¼â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”
                                            â”‚            phone              â”‚
                                            â””â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”˜
                                            Structure of pattern cardstruct

    Figure 11-3. A pointer to a structure contains the address of a structure
    variable.

    We also must declare the received argument for the Enter() function as a
    pointer to a structure, as follows:

    Enter(struct cardstruct *item)
            {                  â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Pointer to receive an address

    Again, be sure that you declare the same pattern name for both the passed
    and the received structures.

Accessing Structure Members with a Pointer

    To access the members of a structure with a pointer, you need to use a new
    symbol, ->. Called "to", -> is actually two charactersâ”€â”€a "minus"
    character followed by a "greater than" character. The following code
    illustrates the use of the -> operator. In it, the pointer cardptr
    accesses the phone member of the structure card1:

    struct cardstruct {â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Define a pattern
        char *first, *last, *middle;
        int age;
    };

    struct cardstruct card1, *cardptr;
                â”‚        â”‚       â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Declare a pointer and
                â”‚        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ a structure variable
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ both of that pattern
    cardptr = &card1;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Assign card1's address to cardptr
    cardptr->phone = 5551212;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Access member of card1 via cardptr
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Points "to" member phone of card1

    The CARD3.C program (Listing 11-3) is another revision of CARD.C. This
    modification has Showcard() receiving the address of a structure. Rather
    than printing a copy, it prints the original via a pointer to the
    structure.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* card3.c --  demonstrates pointers to structures     */

    #include <stdio.h>      /* for NULL  and stdin */
    #include <string.h>     /* for strdup()        */

    #define MAXN 79

    struct cardstruct {                 /* global pattern */
        char *first, *last, *middle;
        long street_num;
        char *street, *city, *state;
        long zip;
        int  area_code;
        long phone;
    };
    main()
    {
        int  i;
        char *Str_Input();
        long Lint_Input();
        struct cardstruct card1, card2;

        for (i = 0; i < 2; i++) /* do twice */
            {
            printf("\nCard %d:\n\n", i + 1);

            card1.first         = Str_Input("First Name");
            card1.last          = Str_Input("Last Name");
            card1.middle        = Str_Input("Middle Name");
            card1.street_num    = Lint_Input("Street Number");
            card1.street        = Str_Input("Street Name");
            card1.city          = Str_Input("City");
            card1.state         = Str_Input("State");
            card1.zip           = Lint_Input("Zip Code");
            card1.area_code     = (int)Lint_Input("Area Code");
            card1.phone         = Lint_Input("Phone Number");

            if (i == 0)
                card2 = card1;
            }
        Showcard(&card2);     /* pass addresses of structures */
        Showcard(&card1);

        return (0);
    }

    Showcard(cardptr)
    struct cardstruct *cardptr; /* pointer receives an address */
    {
        printf("\n\n");

        printf("%s %s %s\n", cardptr->first, cardptr->middle,
                cardptr->last);
        printf("%ld %s, %s, %s %ld\n", cardptr->street_num,
                cardptr->street, cardptr->city, cardptr->state,
                cardptr->zip );
        printf("(%d) %ld\n", cardptr->area_code, cardptr->phone);
    }

    char *Str_Input(char *prompt)
    {
        char buf[MAXN + 1], *ptr;

        printf("%s: ", prompt);
        if (fgets(buf, MAXN, stdin) == NULL)        exit(0);
        buf[strlen(buf) - 1 ] = '\0'; /* strip '\n' */
        if (strlen(buf) == 0)
            exit(0);
        if ((ptr = strdup(buf)) == NULL)
            exit(0);
        return (ptr);
    }

    long Lint_Input(char *prompt)
    {
        char buf[MAXN + 1];
        long num;

        printf("%s: ", prompt);
        if (fgets(buf, MAXN, stdin) == NULL)
            exit(0);
        if (sscanf(buf, "%ld", &num) != 1)
            exit(0);
        return (num);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 11-3.  The CARD3.C program.

Arrays of Structures

    Structures can be organized in arrays like any other type of variable. You
    declare an array of structures as follows:

    struct cardstruct {
        /* members declared here */
    } cards[3];
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ An array of three structures

    This example declares an array of three structures (cards[3]) and defines
    the pattern cardstruct at the same time. If you had already defined the
    pattern, you could declare the same array as follows:

    struct cardstruct cards[3];

    Use an array of structures the same way you use any other array. For
    example, the following statement prints the first member of the second
    card:

    printf("%s", cards[1].first);

    The expression cards[1] accesses the second structure of the array, and
    the .first yields the member named first from that structure.

    To pass the address of one of the structures in the array cards, use the &
    operator followed by the structure's offset in square brackets.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Address of
    &cards[i]
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ the <FI>i<FS>th structure in the array of str

    The ROLO.C program (Listing 11-4) is a complete address book built from
    the earlier CARD.C program. It asks you to fill out the three cards in our
    array of structures. Then it prints out the information in those cards. By
    combining this use of structures with the file-handling routines of
    PHONE.C (from the previous chapter), you have the basis for a truly
    useful phone-index program.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* rolo.c  --  demonstrates pointers to structures    */

    #include <stdio.h>      /* for NULL  and stdin */
    #include <string.h>     /* for strdup()        */

    #define MAXN 79
    #define MAXCARDS 3

    struct cardstruct {                 /* global pattern */
        char first[MAXN],
            last[MAXN],
            middle[MAXN];
        unsigned long street_no;
        char street[MAXN],
            city[MAXN],
            state[MAXN];
        unsigned long zip;
        unsigned int area;
        unsigned long phone;
    };
    struct cardstruct cards[MAXCARDS];

    main()
    {
        int  i;

        for (i = 0; i < MAXCARDS; ++i)
            {
            printf("\n<card %d of %d>\n", i + 1, MAXCARDS);
            Input(&cards[i]);
            }
        for (i = 0; i < MAXCARDS; ++i)
            {
            printf("\n<%d> ", i + 1);
            Showcard(&cards[i]);
            }
    }
    Input(struct cardstruct *cardp)
    {
        char *Str_Input();
        long Lint_Input();

        strcpy(cardp->first,Str_Input("First Name"));
        strcpy(cardp->last,Str_Input("Last Name"));
        strcpy(cardp->middle,Str_Input("Middle Name"));
        cardp->street_no = Lint_Input("Street Number");
        strcpy(cardp->street,Str_Input("Street"));
        strcpy(cardp->city,Str_Input("City"));
        strcpy(cardp->state,Str_Input("State"));
        cardp->zip = Lint_Input("Zip Code");
        cardp->area = (int)Lint_Input("Area Code");
        cardp->phone = Lint_Input("Phone Number");
    }

    char *Str_Input(char *prompt)
    {
        char buf[MAXN + 1], *ptr;

        printf("%s: ", prompt);
        if (fgets(buf, MAXN, stdin) == NULL)
            exit(0);
        buf[strlen(buf) - 1 ] = '\0'; /* strip '\n' */
        if (strlen(buf) == 0)
            exit(0);
        if ((ptr = strdup(buf)) == NULL)
            exit(0);
        return (ptr);
    }

    long Lint_Input(char *prompt)
    {
        char buf[MAXN + 1];
        long  num;

        printf("%s: ", prompt);
        if (fgets(buf, MAXN, stdin) == NULL)
            exit(0);
        if (sscanf(buf, "%ld", &num) != 1)
            exit(0);
        return (num);
    }

    Showcard(struct cardstruct *cardptr)
    {
        printf("\n\n");
        printf("%s %s %s\n", cardptr->first, cardptr->middle,
                cardptr->last);
        printf("%ld %s, %s, %s %ld\n", cardptr->street_no,
                cardptr->street, cardptr->city, cardptr->state,
                cardptr->zip);
        printf("(%d) %ld\n", cardptr->area, cardptr->phone);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 11-4.  The ROLO.C program.

    ROLO.C uses an array of three structures. Notice that the cards[] array
    consists of structures that themselves contain arrays.

Arrays of Pointers to Structures

    Not only can you create arrays of structures, you can also create arrays
    of pointers to structures. These arrays of pointers offer the advantage of
    increased efficiency. For example, when sorting, it is faster to swap two
    pointers than it is to exchange the vastly greater number of bytes of the
    structures themselves.

    You declare an array of pointers to structures as follows:

    struct cardstruct *cardps[3]

    This example declares an array of three pointers in which each pointer
    points to a structure of the pattern cardstruct. Figure 11-4 illustrates
    such an arrangement.

    You can initialize cardps[] (an array of pointers to structures) to
    contain the address of the corresponding elements in the array of
    structures cards[] as follows:

    cardps[0] = &cards[0];
    cardps[1] = &cards[1];
    cardps[2] = &cards[2];

    This lets you use the -> operator to indirectly reference the members of
    each structure in cards[] with the pointers in cardps[]. For example, the
    street member of the second structure of the array of structures cards[]
    can be indirectly referenced through the array of pointers to structures
    in cardps[], as follows:

    strcpy(cardps[1]->street, "Any St.");
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Points "to" the member street of cards[1]

Structure Recursion and Linked Lists

    Structures are so versatile that they can hold every possible type in C,
    including themselves. This remarkable ability to be self-inclusive opens
    whole new sets of programming possibilities. The most common of these is
    the technique shown in Figure 11-5 (on p. 348) that uses "linked lists."

                    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                â”Œâ”€â–ºâ”‚   first []          â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚  â”‚   last []           â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚  â”‚   middle []         â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚  â”‚street_num â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                â”‚  â”‚   street []         â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚  â”‚   city []           â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚  â”‚   state []          â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚  â”‚   zip     â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”˜
                â”‚  â”‚area  â”‚
    â”Œâ”€â”€â”€â”€â”¬â”€â”€â”€â”€â”   â”‚  â”œâ”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”
    â”‚ address â”‚â”€â”€â”€â”˜  â”‚   phone   â”‚
    â”œâ”€â”€â”€â”€â”¼â”€â”€â”€â”€â”¤      â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚ address â”‚â”€â”€â”€â”€â”€â–ºâ”‚   first []          â”‚
    â”œâ”€â”€â”€â”€â”¼â”€â”€â”€â”€â”¤      â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚ address â”‚â”€â”€â”€â”  â”‚   last []           â”‚
    â””â”€â”€â”€â”€â”´â”€â”€â”€â”€â”˜   â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
        cardps [3] â”‚  â”‚   middle []         â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚  â”‚street_num â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                â”‚  â”‚   street []         â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚  â”‚   city []           â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚  â”‚   state []          â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                â”‚  â”‚   zip     â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”˜
                â”‚  â”‚area  â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”
                â”‚  â”‚   phone   â”‚
                â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                â””â”€â–ºâ”‚   first []          â”‚
                    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                    â”‚   last []           â”‚
                    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                    â”‚   middle []         â”‚
                    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                    â”‚street_num â”‚
                    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                    â”‚   street []         â”‚
                    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                    â”‚   city []           â”‚
                    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                    â”‚   state []          â”‚
                    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                    â”‚   zip     â”‚
                    â”œâ”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”˜
                    â”‚area  â”‚
                    â”œâ”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”
                    â”‚   phone   â”‚
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                            cards [3]

    Figure 11-4. An array of pointers to structures. Each element points to a
    structure in an array of structures.

    â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”     â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”     â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”‚                 â”‚  â”Œâ”€â–ºâ”‚                 â”‚  â”Œâ”€â–ºâ”‚                 â”‚
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”˜  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”˜  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”˜
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”˜  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”˜  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”˜
    â”œâ”€â”€â”€â”€â”¬â”€â”€â”€â”€â”˜          â”‚  â”œâ”€â”€â”€â”€â”¬â”€â”€â”€â”€â”˜          â”‚  â”œâ”€â”€â”€â”€â”¬â”€â”€â”€â”€â”˜
    â”œâ”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”  â”‚  â”œâ”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”  â”‚  â”œâ”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
    â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤  â”‚  â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
    â”‚    nextcard     â”œâ”€â”€â”˜  â”‚    nextcard     â”œâ”€â”€â”˜  â”‚    nextcard     â”‚
    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜     â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜

    Figure 11-5. In a linked list, each structure contains a pointer to
    another structure of the same type.

    A linked list is an arrangement of structures in which each structure
    contains a pointer to (the address of) its neighbor. For example, to
    declare such a linked list in ROLO.C, we must modify the structure pattern
    as follows:

    struct cardstruct {
        char first[MAXN],
                last[MAXN],
                middle[MAXN];
        unsigned long street_no;
        char street[MAXN],
                city[MAXN],
                state[MAXN];
        unsigned long zip;
        unsigned int area;
        unsigned long phone;
        struct cardstruct *nextcard;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Added
                            â”” Pointer to another structure of this same pattern

    The new member *nextcard is a pointer to a structure, but it points to a
    structure of its own pattern. By declaring several structures of this
    pattern with

    struct cardstruct card1, card2, card3, card4;

    and then initializing the nextcard member of each to contain the address
    of its neighbor, you create a linked list:

    card1.nextcard = &card2;
    card2.nextcard = &card3;
    card3.nextcard = &card4;

    The ROLO2.C program (Listing 11-5) uses malloc() to build a linked list
    of structures while the program is running. Using this approach, we can
    add as many cards to our address book as we want (subject to the limit of
    the computer's memory).

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* rolo2.c --  demonstrates a linked list */

    #include <stdio.h>      /* for NULL  and stdin */
    #include <string.h>     /* for strdup()        */
    #include <malloc.h>     /* for malloc()        */

    #define MAXN 79

    struct cardstruct {                 /* global pattern */
        char first[MAXN],
            last[MAXN],
            middle[MAXN];
        unsigned long street_no;
        char street[MAXN],
            city[MAXN],
            state[MAXN];
        unsigned long zip;
        unsigned int area;
        unsigned long phone;
        struct cardstruct *nextcard;
    };

    main()
    {
        int i;
        struct cardstruct card, *first, *current;

        first = (struct cardstruct *)malloc(sizeof(struct cardstruct));
        if (first == NULL)
            exit(1);
        if (Input(&card) != 0)
            exit(1);
        *first = card;
        current = first;

        while (Input(&card) == 0)
            {
            current->nextcard =
                (struct cardstruct *)malloc(sizeof(struct cardstruct));
            if (current->nextcard == NULL)
                exit(1);
            current = current->nextcard;
            *current = card;
            }
        current->nextcard = NULL;

        Dumplist(first);
    }
    Dumplist(struct cardstruct *head)
    {
        do
            {
            Showcard(head);
            } while ((head = head->nextcard) != NULL);
    }

    Showcard(struct cardstruct *cardptr)
    {
        printf("\n\n");

        printf("%s %s %s\n", cardptr->first, cardptr->middle,
                cardptr->last);
        printf("%ld %s, %s, %s %ld\n", cardptr->street_no,
                cardptr->street, cardptr->city, cardptr->state,
                cardptr->zip );
        printf("(%d) %ld\n", cardptr->area, cardptr->phone);
    }

    Input(struct cardstruct *cardp)
    {
        char *Str_Input();
        long Lint_Input();

        printf("\n<new card> (Empty first name Quits)\n");
        strcpy(cardp->first,Str_Input("First Name"));
        if (*(cardp->first) == '\0')
            return (1);
        strcpy(cardp->last,Str_Input("Last Name"));
        strcpy(cardp->middle,Str_Input("Middle Name"));
        cardp->street_no = Lint_Input("Street Number");
        strcpy(cardp->street,Str_Input("Street"));
        strcpy(cardp->city,Str_Input("City"));
        strcpy(cardp->state,Str_Input("State"));
        cardp->zip = Lint_Input("Zip Code");
        cardp->area = (int)Lint_Input("Area Code");
        cardp->phone = Lint_Input("Phone Number");
        return (0);
    }

    char *Str_Input(char *prompt)
    {
        char buf[MAXN + 1], *ptr;

        printf("%s: ", prompt);
        if (fgets(buf, MAXN, stdin) == NULL)
            exit(0);
        buf[strlen(buf) - 1 ] = '\0'; /* strip '\n' */
        if ((ptr = strdup(buf)) == NULL)
            exit(0);    return (ptr);
    }

    long Lint_Input(char *prompt)
    {
        char buf[MAXN + 1];
        long  num;

        printf("%s: ", prompt);
        if (fgets(buf, MAXN, stdin) == NULL)
            exit(0);
        if (sscanf(buf, "%ld", &num) != 1)
            num = 0;
        return (num);
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 11-5.  The ROLO2.C program.

    Notice that the last structure in the list always has its nextcard member
    set to NULL. That's how the program marks the end of the linked list.

    This program also illustrates two other interesting properties of
    structures. First, when you apply the sizeof operator to a structure or to
    a structure's pattern, it yields the total number of bytes for all the
    members of the structure:

    malloc(sizeof(struct cardstruct));

    Second, we had to type cast the value returned by malloc() to a type
    appropriate for the pointer to which the value is assigned:

    first = (struct cardstruct *)malloc(sizeof(struct cardstruct));
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Type cast to a pointer to a structure

    Note that you must use the structure pattern name in the type cast, not
    the structure variable name. Had we omitted the type cast, QuickC would
    complain with:

    Warning C4049:
    '=' indirection to different types

Initializing Structures with Starting Values

    As in arrays, you can initialize structures that are static or global when
    you declare them. The type of the initializing value must, of course,
    match the type of the corresponding member. An attempt to initialize with
    the wrong type will yield the following QuickC warning:

    Warning C4047:
    "initializing": different levels of indirection

    The following structure is declared correctly:

    static struct cardstruct card = {
                "Bob",â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Member first
                "Roberts",â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Member last
                "Mason",â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Member middle
                42â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Member street_no
                "Willow Way",â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Member street
                "Tonopah",â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Member city
                "Nevada",â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Member state
                84521L,â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Member zip
                916,â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Member area
                5551212Lâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Member phone
    };

    As with arrays, if you specify fewer initializers than members, QuickC
    gives the trailing uninitialized members the default value of zero.


Unionâ”€â”€Multiple Types in the Same Space

    You can think of a "union" as the opposite of a structure. While struct is
    a collection of many types, each with its own location in memory, a union
    is a collection of many types that all share the same location in memory.
    Thus, a union can contain different types at various times, but it can
    contain only a single value of a single type at any given time.

    Although its uses are limited, a union is a blessing when you do encounter
    a need for one. For example, consider writing a function that needs to
    print either an int or a float, yet doesn't know ahead of time what type
    it will receive as its argument. Before we can show you how to write such
    a function, however, we need to cover the basics of declaring and using
    unions.

    You declare a union as you would a structure, except you use the keyword
    union instead of struct:

                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Name of pattern
    union twotype {
        float ftype;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Members
        int   itype;
    } one_of_many ;
        â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Name of a union variable of pattern twotype

    This example tells the compiler to reserve memory for the variable
    one_of_many, which will hold either a float or an int. Because the float
    is larger, union reserves four bytesâ”€â”€enough space to hold either type.

    As a general rule, you should place the largest member first in a union
    declaration. Some compilers allocate memory based only on the first
    member, rather than searching all members for the largest. QuickC is well
    behaved in this regard, however. It allocates the correct number of bytes
    for a union, regardless of the order of the member declarations.

    As with structure members, you access the members of a union with the
    "dot" operator. However, the compiler interprets the type of the union as
    the type specified by the member name, as follows:

    one_of_many.ftype = 1.0;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Interpret as a float
    one_of_many.itype = 1;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Interpret as an int

    The UDEMO.C program (Listing 11-6) is a simple demonstration of how a
    union works. After asking the user to enter a type, it uses scanf() to
    read that type and printf() to echo it to the screen.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* udemo.c  --  demonstrates a union at work */

    #include <stdio.h>

    char *Strings[6] = {
            "Quit",
            "line of text",
            "floating-point double value",
            "long integer value",
            "floating-point value",
            "integer value"
    };

    struct Unitstruct {
        union {
            char   wtype[BUFSIZ];
            double dtype;
            long   ltype;
            float  ftype;
            int    itype;
        } manyu;
        int type_in_union;
    };

    main()
    {
        struct Unitstruct one_of_many;

        while ((one_of_many.type_in_union = Menu()) != 0 )
            {
            Inputval(&one_of_many);
            Printval(&one_of_many);
            }
    }

    Inputval(struct Unitstruct *one_of_many)
    {
        printf("\nEnter a %s: ", Strings[one_of_many->type_in_union]);
        switch(one_of_many->type_in_union)
            {
            case 1:
                fgets(one_of_many->manyu.wtype, BUFSIZ, stdin);
                break;
            case 2:
                scanf("%lf", &(one_of_many->manyu.dtype));
                while (getchar()!= '\n');
                break;
            case 3:
                scanf("%ld", &(one_of_many->manyu.ltype));
                while (getchar()!= '\n');
                break;
            case 4:
                scanf("%f", &(one_of_many->manyu.ftype));
                while (getchar()!= '\n');
                break;
            case 5:
                scanf("%i", &(one_of_many->manyu.itype));
                while (getchar()!= '\n');
                break;
            }
    }

    Printval(struct Unitstruct *one_of_many)
    {
        printf("The %s you entered\nwas: ", Strings[one_of_many->type_in_union]
        switch (one_of_many->type_in_union)
            {
            case 1:
                fputs(one_of_many->manyu.wtype, stdout);
                break;
            case 2:
                printf("%lf", one_of_many->manyu.dtype);
                break;
            case 3:
                printf("%ld", one_of_many->manyu.ltype);
                break;
            case 4:
                printf("%f", one_of_many->manyu.ftype);
                break;
            case 5:
                printf("%i", one_of_many->manyu.itype);
                break;
            }
        printf("\n\n");
    }

    Menu()
    {
        int i;
        char ch;
        for (i = 0; i < 6; ++i)
            {
            printf("%d) %s\n", i, Strings[i]);
            }
        printf("Which: ");
        do
            {
            ch = getch();
            } while (ch < '0' || ch > '5');
        printf("%c\n", ch);
        return (ch - '0');
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 11-6.  The UDEMO.C program.

Unions and Functions

    Unlike a structure, you cannot pass a union to a function. Instead, you
    must pass the value of the type currently stored in that union. For
    example, the statement

    printf("%f", one_of_many.ftype);
                â”‚               â””â”€â”€â”€â”€â”€â”€â”€â”€â”€ Sends the float value in one_of_many
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Expects a float

    sends printf() the float value in one_of_many, which matches the printf()
    %f format specifier. Note that it is meaningless in C to use a union
    variable (such as one_of_many) without a corresponding "dot" and member
    name.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    Quick Tip
    The UDEMO.C program illustrates a common technique for managing unions.
    Because a union contains no inherent indication of the type it contains,
    unions are often made members of structures, with another member used to
    store that indication:

    struct Unitstruct{
        union {
            char   wtype[BUFSIZE];
            double dtype;
            long   ltype;
            float  ftype;
            int    itype;
        } manyu;
        int type_in_union;
        };

    By packaging a union and an int together in a structure like this, we are
    better able to keep track of the type stored in the union at any given
    time.
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

Unions Received by Functions

    C permits you to use a union as the type of an argument received by a
    function, but the procedure can be risky. The following statement
    illustrates one way to declare a received variable in a subroutine as a
    union:

    #define FLT 0  /* floating-point type */
    #define INT 1  /* integer type        */

    Printval(val, type)
    union twotype val;
    int type;
    {
            switch (type)
                {
                case FLT: printf("%f", val.ftype); break;
                case INT: printf("%d", val.itype); break;
                }
    }

    This function receives two arguments: a union of two possible types and an
    int that specifies which of the two possible types is in that union.

    But beware. Depending on how the compiler passes arguments to functions,
    this approach can fail. In QuickC, a float is four bytes and an int is two
    bytes; therefore, the stack (received arguments) resembles Figure 11-6a
    when passing a float and Figure 11-6b when passing an int. However,
    because the pattern for twotype reserves four bytes, passing an int to
    Printval() causes the type argument to appear in the wrong place.

    You can resolve this dilemma by constraining union members to types that
    use the same number of bytes. That is, if you declare twotype as follows:

    union twotype {
        float fval;
        long ival;
    };

    it would contain either of two types, but each type requires four bytes. A
    better solution is to package a union and an int together inside a
    structure, as you saw earlier. That approach avoids the potential pitfalls
    of declaring a function that receives a bare-bones union.

Pointers to Unions

    Pointers to unions behave like pointers to structures. You retrieve the
    address of a union with the & operator and the union variable name, as
    follows:

    &one_of_many

    Printval (float, int)
                â”‚     â”‚        High address
                â”‚     â”‚     â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                â”‚     â””â”€â”€â”€â”€â–ºâ”œâ”€â”€    int     â”€â”€â”¤2-byte int
                â”‚           â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚           â”œâ”€â”€            â”€â”€â”¤
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”œâ”€â”€   float    â”€â”€â”¤4-byte float
                            â”œâ”€â”€            â”€â”€â”¤
    Start of arguments â”€â”€â”€â”€â–ºâ””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                Low address

    (A)


    Printval (int, int)
                â”‚    â”‚          High address
                â”‚    â”‚       â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”
                â”‚    â”‚       â”œâ”€â”€            â”€â”€â”¤Second argument missing
                â”‚    â”‚       â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â”‚    â””â”€â”€â”€â”€â”€â”€â–ºâ”œâ”€â”€    int     â”€â”€â”¤2-byte int
                â”‚            â”œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¤
                â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â–ºâ”œâ”€â”€    int     â”€â”€â”¤2-byte int
    Start of arguments â”€â”€â”€â”€â–ºâ””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”˜
                                Low address

    (B)

    Figure 11-6. Passing different-size data types to the same function can
    cause confusion.

    To fetch the address of a union member, specify the & operator, the union
    variable name, the "dot" operator, and the member name, as follows:

    &one_of_many.ftype

    Declaring pointers to unions and manipulating values via the addresses in
    those pointers is also identical to the form used by structure pointers.
    Declare a pointer to a union as follows:

    union manytype *up;
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Pointer to a union of the pattern manytype

    Place a value (an address) into that pointer in the following form:

    up = &one_of_many;

    To access the type of the value stored in the union whose address is in
    up, use the -> operator as follows:

    up->ftype = 1.0;

    Structures and unions are closely related. The main difference is that a
    structure holds many values simultaneously; a union holds only a single
    type of value at any one time. As you have seen, structures can include
    unions as members. It is also legal for unions to contain structures as
    members. We'll use this latter technique at the end of this chapter, when
    we discuss bit fields.


Enumerated Data with enum

    Many kinds of information are best represented by a finite list of
    discrete integer valuesâ”€â”€for example, the days of the week, the months of
    the year, or even the phases of the moon. Such kinds of information, in
    which every possibility is known in advance, lend themselves to
    enumerationâ”€â”€a listing of all possible values for a given topic or
    concept.

    If you need to represent the days of the week in a program as discrete
    integers, you could make the following declarations and assignments:

    int monday  = 0, tuesday = 1, wednesday = 2, thursday = 3,
        friday = 4, saturday = 5, sunday = 6;

    and later use those values as follows:

    pay_day = friday;

    The previous approach, although reasonable, has a potential pitfall.
    Because the days of the week are int variables, the program might change
    their values, and so render them meaningless. To avoid this problem we can
    use the following directives:

    #define MONDAY 0
    #define TUESDAY 1
    [etc.]

    The program can't change these values because they are integer constant
    aliases. But this is still not an ideal solution because you cannot group
    #define definitions under a single conceptual name.

    The best solution uses the C enumerated data type, enum, whose members are
    constants grouped under a single name. To represent the days of the week
    using enum, first declare a pattern similar to a structure or union
    pattern:

                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Name of pattern
    enum week_days {
        monday,â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Members
        tuesday,
        wednesday,
        thursday,
        friday,
        saturday,
        sunday
    } pay_day;
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Enumerated variable

    This example declares a pattern called week_days, an enumerated data type,
    and the enumerated variable pay_day. Note that the members don't need to
    be preceded by a type keyword because the members of enum are always of
    type int. Also notice that you don't need to assign the members any
    values: The declaration itself gives the members constant integer values,
    starting with 0 for monday and counting through 6 for sunday.

    Another difference between enum and struct or union is that you access
    members of enum simply by stating the member's name without the "dot" or
    "->" notation:

    payday = monday;

    Any attempt to change the value of an enumerated member (monday = 5, for
    example) results in the following QuickC error message:

    error C2106:
    '=' : left operand must be lvalue

    This reminds you that the members of an enumerated data type, like all
    other constants, are rvalues and can appear only to the right of an
    assignment operator.

    Also note that you cannot use a pointer to indirectly change the value of
    an enumerated variable member. For example, the following assignment:

    int *p;

    p = &monday;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Can't take address of a constant
    *p = 5;

    fails because you can't retrieve the address of a constant. This attempt
    generates the following QuickC error message:

    error C2101:
    '&' on constant

    The TODAY.C program (Listing 11-7 on the following page) demonstrates one
    advantage to using enumâ”€â”€improved readability. The program asks you to
    specify the day on which you want to be paid. It then checks to make
    certain that you specified a legal day.

    The pattern week_day in TODAY.C shows that you can initialize an enum
    member to any integer value. Any uninitialized member, however, is
    assigned a value one higher than the member before it. For example, the
    declaration

    enum folks {
        mo = -1,
        roseann,
        betsy = 0,
        kit,
        joey = 1
    };

    sets mo to a -1, roseann and betsy to 0, and kit and joey to 1. This also
    shows that enum members can have duplicate values.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* today.c  -- demonstrates using enum  */

    main()
    {
        enum week_days {
            monday = 1,     /* start with 1 */
            tuesday,
            wednesday,
            thursday,
            friday,
            saturday,
            sunday
        } pay_day;

        static char *day_names[] = {
            "",
            "monday",
            "tuesday",
            "wednesday",
            "thursday",
            "friday",
            "saturday",
            "sunday"
        };

        printf("What day do you want to be paid on?\n");

        for (pay_day = monday; pay_day <= sunday; ++pay_day)
            {
            printf("%d. %s\n", pay_day, day_names[pay_day]);
            }

        printf("Which (%d-%d): ", monday, sunday);

        do
            {
            pay_day = getch();
            pay_day -= '0';
            } while (pay_day < monday || pay_day > sunday);

        printf("%d\n\n", pay_day);

        printf("You selected %s\n", day_names[pay_day]);

    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 11-7.  The TODAY.C program.


Bit Fields

    In Chapter 7, we discussed how to use bitwise operators to store data in
    the individual bits of bytes. Another, and simpler, way to store and
    access information in bits is with "bit fields."

    Bit fields offer two advantages over the bitwise operators. First, you can
    access bit fields by name (such as blink) rather than by an obscure mask
    (such as (1 << 7)). Second, the compiler generates code for bit fields
    that you normally would have to write yourself. Examine, for example, the
    following bit-field assignment:

    blink = 1;

    where blink is the name of the sixteenth bit of a 2-byte int. This
    statement is comparable to the following assignment using bitwise
    operators:

    ch |= (1 << 15);

    C's bit fields are especially handy when you need to manipulate items with
    built-in bit information. The characters in your screen memory are
    examples of such items. Recall that each screen character is represented
    by a 2-byte int. One byte is the character itself; the other is the
    attribute byte. (See Figure 11-7.)

                                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€Most significant bit
                            â”Œâ”€â”€â”€â–¼â”€â”€â”€â”â”€â”
        Blinking (1 bit) â”€â”€â”€â”€â”€â”‚   7   â”‚ â”‚
                            â”Œâ”€â”œâ”€     â”€â”¤ â”‚
                            â”‚ â”‚   6   â”‚ â”‚
                            â”‚ â”œâ”€     â”€â”¤ â”‚
    Background (3 bits) â”€â”€â”€â”¤ â”‚   5   â”‚ â”‚
                            â”‚ â”œâ”€     â”€â”¤ â”‚
                            â”‚ â”‚   4   â”‚ â”‚
                            â””â”€â”œâ”€     â”€â”¤ â”œâ”€â”€â”€Attributes (1 byte)â”€â”
    Intensity (1 bit) â”€â”€â”€â”€â”€â”‚   3   â”‚ â”‚                       â”‚
                            â”Œâ”€â”œâ”€     â”€â”¤ â”‚                       â”‚
                            â”‚ â”‚   2   â”‚ â”‚                       â”‚
                            â”‚ â”œâ”€     â”€â”¤ â”‚                       â”‚
    Foreground (3 bits) â”€â”€â”€â”¤ â”‚   1   â”‚ â”‚                       â”‚
                            â”‚ â”œâ”€     â”€â”¤ â”‚                       â”‚
                            â”‚ â”‚   0   â”‚ â”‚                       â”‚
                            â””â”€â”œâ”€â”€â”€â”€â”€â”€â”€â”¤â”€â”¤                       â”œâ”€â”€1 int
                            â”‚   7   â”‚ â”‚                       â”‚
                            â”œâ”€     â”€â”¤ â”‚                       â”‚
                            â”‚   6   â”‚ â”‚                       â”‚
                            â”œâ”€     â”€â”¤ â”‚                       â”‚
                            â”‚   5   â”‚ â”‚                       â”‚
                            â”œâ”€     â”€â”¤ â”‚                       â”‚
                            â”‚   4   â”‚ â”‚                       â”‚
                            â”œâ”€     â”€â”¤ â”œâ”€â”€â”€Character (1 byte)â”€â”€â”˜
                            â”‚   3   â”‚ â”‚
                            â”œâ”€     â”€â”¤ â”‚
                            â”‚   2   â”‚ â”‚
                            â”œâ”€     â”€â”¤ â”‚
                            â”‚   1   â”‚ â”‚
                            â”œâ”€     â”€â”¤ â”‚
                            â”‚   0   â”‚ â”‚
                            â””â”€â”€â”€â”€â”€â”€â”˜â”€â”˜
                                â””â”€â”€â”€â”€â”€â”€â”€â”€Least significant bit

    Figure 11-7. One character in screen memory is represented by two
    consecutive bytes.

    The following is an example of one such screen int declared using bit
    fields:

                â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”¬â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ One integer...divided like this
    unsigned int character  :8,
                    foreground :3,
                    intensity  :1,
                    background :3,
                    blink      :1;
                    â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”´â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Name for...this many bits

    In this declaration, we tell QuickC to use the bits in one unsigned
    integer. Next, we specify the names for each group of bits in that
    integer, beginning with 8 bits, to which we give the name character, and
    continuing through all 16 bits until we end with blink as the name of the
    final bit.

    You may name as many bits as there are in the type declared (8 for a char,
    32 for a long, and so on). Only integer types can be used as bit fields,
    and only integer constants can be used to declare the number of bits.
    Always declare the bits from the bottom up (from the least significant to
    the most significant bits). A colon separates the name for each group of
    bits from the number of bits assigned to it; a comma separates each name
    :bits from the next; and, of course, a semicolon must end the entire
    declaration.

    If you declare fewer bits than there are in a type, the unused bits are
    simply ignored. If you declare more, an additional variable of the same
    type is allocated:

            â”Œâ”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ 8 bits
    unsigned char character :8,
                    foreground :3,
                    intensity  :1,
                    background :3,
                    blink      :1;
                                â””â”€â”€â”€ 16 bits total allocates two char variables

    The name :bits combination is what defines a bit field as opposed to an
    ordinary variable. For example, the above declaration produces the same
    allocation as the following series of declarations:

    unsigned char character  :8;
    unsigned char foreground :3;
    unsigned char intensity  :1;
    unsigned char background :3;
    unsigned char blink      :1;

    In this example, the compiler gathers the bits from the declared bit
    fields into the most compact unit, regardless of how many bit fields you
    declare.

    Because you are not permitted to retrieve the address of a bit field, you
    usually will declare bit fields inside structures, as follows:

    struct screen_char_struct {
        unsigned int character  :8,
                        foreground :3,
                        intensity  :1,
                        background :3,
                        blink      :1;
    } screen_ch ;
        â””â”€â”€â”€â”¬â”€â”€â”€â”˜
            â””â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€ Structure variable whose members are bit fields

    This approach has two advantages. First, you can access the individual bit
    fields with the usual structure/member notation. This improves
    readability:

    screen_ch.blink = 1;â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€Retrieve the address of a structure

    Second, you can access the address of a structure, but you cannot retrieve
    the address of a bit field. This lets you manipulate bit fields with
    pointers, which can increase the speed of your program:

    &screen_ch

    The SCRMENU.C program (Listing 11-8) demonstrates how to use bit fields
    to modify text-screen display. It lets you select an attribute; then it
    toggles the setting for that attribute for every character on the screen.

    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€
    /* scrmenu.c  -- uses bit fields to modify your text   */
    /*               screen's attributes                   */

    char *Choice_Words[] = {
        "Quit",
        "Foreground",
        "Intensity",
        "Background",
        "Blinking"
    };
    enum Choices {
        Quit,
        Foreground,
        Intensity,
        Background,
        Blinking
    };

    /* use 0xB800000 for EGA or VGA */
    #define SCR_START (0xB0000000)
    #define SCR_SIZE (25 * 80)
    main()
    {
        enum Choices choice;

        printf("Select from the following by number:\n");

        for (choice = Quit; choice <= Blinking; ++choice )
            {
            printf("%d. %s\n", choice, Choice_Words[choice]);
            }

        printf("\nWhich: ");
        do
            {
            choice = getch();
            choice -= '0';
            if (choice < Foreground || choice > Blinking)
                continue;
            Redraw( choice );
            } while (choice != Quit);

    }

    Redraw(enum Choices field)
    {
        struct screen_char {
            unsigned int character  :8,
                        foreground :3,
                        intensity  :1,
                        background :3,
                        blink      :1;
        } scrchar, far *sp, far *ep;

        sp = (struct screen_char far *)SCR_START;
        ep = sp + SCR_SIZE;

        while (sp < ep)
            {
            scrchar = *sp;
            switch (field)
                {
                case Foreground:
                    scrchar.foreground = (scrchar.foreground)? 0 : 7;
                    break;
                case Intensity:
                    scrchar.intensity = (scrchar.intensity)? 0 : 1;
                    break;
                case Background:
                    scrchar.background = (scrchar.background)? 0 : 7;
                    break;
                case Blinking:
                    scrchar.blink = (scrchar.blink)? 0 : 1;
                    break;
                }
            *(sp++) = scrchar;
            }
    }
    â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€

    Listing 11-8.  The SCRMENU.C program.

    SCRMENU.C combines bit fields with enum and the #define preprocessor
    directive to virtually rid the body of the program of obscure constructs.
    Also, notice that we use a pointer to a structure to access the screen.


Advanced typedef

    So far, we've used the #define preprocessor directive to create aliases,
    both for increased program clarity and as a shorthand method of entering
    repetitive code. We have also seen, in Chapter 3, that new types can be
    defined by using typedef. Superficially, #define and typedef appear to be
    interchangeable. To create simple aliases, you can use either one.
    Situations arise, however, in which typedef is suitable, but #define is
    not.

    For example, suppose you need to create a new type called string, an array
    of type char. Now suppose you attempt to create this new type with
    #define, as follows:

    #define string char s[128]

    You later would not be permitted to make the declaration

    string str1, str2;

    because the preprocessor would expand it to be

    char s[128] str1, str2;

    which is illegal. (Note the missing comma, among other things.) In
    situations such as this one, typedef is ideal. Rather than beginning with
    a #define directive, suppose you use the following:

    typedef char string[128];

    This creates a new type called string, which you can use later to declare
    variables of that new type:

    string str1, str2;

    Because we used typedef to define string, the compiler correctly
    translates this into

    char str1[128], str2[128];

    which is what we intended in the first place.

    The secret to using typedef is to follow three simple steps. First,
    declare an ordinary variable of the type you want:

    char s[128];

    Second, place the word typedef at the front:

    typedef char s[128];

    Third, replace the variable's name with the new type name:

    typedef char string[128];

    You can now use the newly defined type string exactly as you would one of
    C's built-in types, such as int.

    In addition to doing what #define cannot, typedef also lends clarity to
    otherwise obscure constructs. For example, consider the following two
    pointers to functions:

    int (*quit_fun)(), (*restart_fun)();

    This could be confusing if it were to appear throughout your program.
    Using typedef, however, you can create a new type called funptr:

    typedef (*funptr)();

    Now you can use funptr throughout your program to declare variables of
    that new type, as follows:

    funptr quit_fun, restart_fun;

    Use typedef judiciouslyâ”€â”€it is the most easily abused concept in C. The
    indiscriminate use of typedef, rather than making your program more
    readable, can make it more obscure and (sometimes) indecipherable.



â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€â”€