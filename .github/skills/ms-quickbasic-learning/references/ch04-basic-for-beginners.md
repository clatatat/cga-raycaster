Chapter 4  Interlude: BASIC for Beginners

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Introduces the general principles of BASIC programming. Covers displaying
output, variables, calculations, arrays, logical relations, decision-making,
and loops. This is the foundation chapter for all BASIC programming.

## Comments

Comments begin with an apostrophe and extend to end of line:
```basic
' This is a comment.
CLS                   ' The CLS statement clears the screen.
```

## Displaying Words and Numbers on the Screen

### The PRINT Statement

```basic
PRINT "Hello, World!"           ' Display text
PRINT 2 + 2                     ' Display result of expression
PRINT "Sum is"; 36 + 4          ' Semicolon: items close together
PRINT "Col1", "Col2"            ' Comma: items at tab stops (14 columns apart)
```

Example:
```basic
number = 36
PRINT "The sum of"; number; "and 4 is"; number + 4
PRINT "The square of"; number; "is"; number * number
```

Output:
```
The sum of 36 and 4 is 40
The square of 36 is 1296
```

## Variables

### Storing Data in Memory

Variables are named storage locations in memory. Each variable has a name,
a type, and a value.

### Variable Types

| Type Suffix | Type             | Size    | Range / Precision           |
|-------------|------------------|---------|-----------------------------|
| %           | INTEGER          | 2 bytes | -32,768 to 32,767           |
| &           | LONG             | 4 bytes | approx ±2 billion           |
| !           | SINGLE           | 4 bytes | 7-digit precision           |
| #           | DOUBLE           | 8 bytes | 15-16 digit precision       |
| $           | STRING           | varies  | 0 to 32,767 characters      |

### Integer Variables

Whole numbers only. Fastest for calculations.
```basic
count% = 42
```

### Floating-Point Variables

Numbers with decimal points.
```basic
price! = 19.95
pi# = 3.14159265358979
```

### String Variables

Sequences of characters.
```basic
name$ = "QuickBASIC"
```

## Assigning Values to Variables

```basic
x = 10                  ' Assign numeric value
greeting$ = "Hello"     ' Assign string value
total = price * quantity ' Assign expression result
```

## Calculations

### Arithmetic Operators

| Operator | Operation              | Example       |
|----------|------------------------|---------------|
| +        | Addition               | 5 + 3 = 8    |
| -        | Subtraction            | 5 - 3 = 2    |
| *        | Multiplication         | 5 * 3 = 15   |
| /        | Division               | 5 / 3 = 1.67 |
| \        | Integer division        | 5 \ 3 = 1    |
| MOD      | Remainder (modulus)     | 5 MOD 3 = 2  |
| ^        | Exponentiation         | 5 ^ 3 = 125  |

### Precedence of Operations

1. Parentheses (innermost first)
2. Exponentiation (^)
3. Negation (-)
4. Multiplication and Division (* /)
5. Integer division (\)
6. Modulus (MOD)
7. Addition and Subtraction (+ -)

### Math Functions

```basic
ABS(x)      ' Absolute value
SQR(x)      ' Square root
INT(x)      ' Truncate to integer
SGN(x)      ' Sign (-1, 0, or 1)
SIN(x)      ' Sine (radians)
COS(x)      ' Cosine (radians)
TAN(x)      ' Tangent (radians)
ATN(x)      ' Arctangent
LOG(x)      ' Natural logarithm
EXP(x)      ' e raised to power x
RND         ' Random number 0 to 1
```

## Expressions

An expression is any combination of variables, constants, operators,
and function calls that produces a value.

## Displaying Variables and Expressions

```basic
PRINT x; y; z           ' Display multiple values
PRINT "Result ="; x + y ' Mix text and expressions
```

## Entering Data with the INPUT Statement

```basic
INPUT "Enter your name: "; name$
INPUT "Enter a number: "; n
```

## Arrays of Variables

### Declaring Arrays

```basic
DIM Price(4)              ' Array with elements 0 through 4
DIM Score(1 TO 100)       ' Array with elements 1 through 100
DIM Matrix(10, 10)        ' Two-dimensional array
```

### Specifying Array Elements

```basic
Price(0) = 9.95
Price(1) = 14.50
total = Price(0) + Price(1)

FOR i = 1 TO 100
    Score(i) = 0
NEXT i
```

## Logical Relations Used in Decision-Making

### Relational Operators

| Operator | Meaning                      |
|----------|------------------------------|
| =        | Equal to                     |
| <>       | Not equal to                 |
| >        | Greater than                 |
| <        | Less than                    |
| >=       | Greater than or equal to     |
| <=       | Less than or equal to        |

### Boolean Expressions

A relational expression evaluates to -1 (true) or 0 (false).

### Compound Expressions

| Operator | Meaning                                |
|----------|----------------------------------------|
| AND      | True if both conditions are true       |
| OR       | True if either condition is true       |
| NOT      | Reverses the truth value               |

## Using Logical Statements to Control Program Flow

### IF...THEN...ELSE

Single-line form:
```basic
IF score >= 60 THEN PRINT "Pass" ELSE PRINT "Fail"
```

Block form:
```basic
INPUT "Enter a number: "; n
IF n > 100 THEN
    PRINT n; "is greater than 100"
ELSE
    PRINT n; "is less than or equal to 100"
END IF
```

## Repeating Program Operations

### The FOR...NEXT Loop

```basic
FOR i = 1 TO 10
    PRINT i
NEXT i

FOR i = 10 TO 1 STEP -1   ' Count backwards
    PRINT i
NEXT i

FOR i = 0 TO 1 STEP .1    ' Fractional steps
    PRINT i
NEXT i
```

### The DO...LOOP

#### DO WHILE Loop (test at top)

```basic
count = 1
DO WHILE count <= 10
    PRINT count
    count = count + 1
LOOP
```

#### DO UNTIL Loop (test at top)

```basic
DO UNTIL answer$ = "quit"
    INPUT "Enter command: "; answer$
LOOP
```

#### DO...LOOP WHILE (test at bottom — runs at least once)

```basic
DO
    INPUT "Enter a number (0 to quit): "; n
    PRINT n * n
LOOP WHILE n <> 0
```

#### DO...LOOP UNTIL (test at bottom — runs at least once)

```basic
DO
    INPUT "Enter a positive number: "; n
LOOP UNTIL n > 0
```

## Writing a Simple BASIC Program

Complete example combining the concepts:
```basic
' Simple averaging program
CLS
DIM Values(1 TO 100) AS SINGLE
count% = 0
total! = 0

DO
    INPUT "Enter a value (0 to finish): "; value!
    IF value! <> 0 THEN
        count% = count% + 1
        Values(count%) = value!
        total! = total! + value!
    END IF
LOOP UNTIL value! = 0

IF count% > 0 THEN
    PRINT "Average ="; total! / count%
    PRINT "Number of values:"; count%
ELSE
    PRINT "No values entered."
END IF
```

## Recommended Books

- Ettlin and Solotko. *QuickBASIC Made Easy*. Osborne McGraw-Hill, 1989.
- Feldman and Rugg. *Using QuickBASIC 4*. Que Corporation, 1988.
- Hergert. *Microsoft QuickBASIC*. 2d ed. Microsoft Press, 1988.
- Inman and Albrecht. *Using QuickBASIC*. Osborne McGraw-Hill, 1988.
