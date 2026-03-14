---
name: ms-quickbasic-learning
description: 'Microsoft QuickBASIC 4.5 Learning Guide (Microsoft Press, 1988). Use when writing BASIC code for QuickBASIC 4.5, MS-DOS, structured BASIC programming, SUB/FUNCTION procedures, variables, arrays, loops, file I/O, debugging, screen output, or retro DOS BASIC development. Covers BASIC fundamentals, the QuickBASIC IDE, menus, windows, smart editor, on-line help, debugging, executable creation, and the QCARDS tutorial project.'
---

# Learning to Use Microsoft QuickBASIC 4.5

**Publisher:** Microsoft Corporation, 1988
**Source:** [Microsoft Programmer's Library 1.3 via PCjs](https://www.pcjs.org/documents/books/mspl13/basic/qblearn/)

Official tutorial and reference for the Microsoft QuickBASIC 4.5 environment, covering BASIC language fundamentals, the QuickBASIC IDE, structured programming with procedures, and a hands-on tutorial building the QCARDS database application.

## When to Use

- Writing BASIC code targeting Microsoft QuickBASIC 4.5 (QB.EXE)
- Programming for MS-DOS on IBM PC compatibles
- Structured BASIC programming with SUB and FUNCTION procedures
- Using the QuickBASIC IDE (menus, windows, editor, debugging)
- BASIC language fundamentals (variables, arrays, loops, decisions, I/O)
- Creating stand-alone executable (.EXE) files from BASIC programs
- Debugging BASIC programs (breakpoints, watchpoints, Watch window)
- Text-mode screen output (PRINT, LOCATE, CLS, COLOR, SCREEN)
- File I/O in BASIC (OPEN, INPUT#, PRINT#, random access)
- Multi-module BASIC projects and Quick Libraries
- Retro DOS BASIC game or application development
- Converting BASICA/GW-BASIC programs to QuickBASIC

## Companion References on PCjs

- [MS QB 4.5 Language Reference](https://www.pcjs.org/documents/books/mspl13/basic/qblang/) — Statement and function syntax reference
- [MS QB 4.5 Programming in BASIC](https://www.pcjs.org/documents/books/mspl13/basic/qbprog/) — In-depth programming topics with examples
- [MS BASIC 7.1 Programming Guide](https://www.pcjs.org/documents/books/mspl13/basic/b7prog/) — Advanced BASIC programming (PDS 7.1)
- [MS BASIC 7.1 Language Reference](https://www.pcjs.org/documents/books/mspl13/basic/b7lang/) — Complete language reference (PDS 7.1)

## Chapter Reference

### Part 1: Getting Started
- [Chapter 1: Setting Up Microsoft QuickBASIC](./references/ch01-setting-up.md) — SETUP program, installation, QB Express, getting into QuickBASIC
- [Chapter 2: Using Menus and Commands](./references/ch02-menus-and-commands.md) — Starting QB, menu bar, reference bar, on-line help, dialog boxes, shortcut keys
- [Chapter 3: QuickBASIC's Windows](./references/ch03-windows.md) — View window, Immediate window, Watch window, Help window, saving programs
- [Chapter 4: Interlude: BASIC for Beginners](./references/ch04-basic-for-beginners.md) — Variables, data types, PRINT, INPUT, arrays, operators, IF/THEN, loops, DO/LOOP, FOR/NEXT

### Part 2: Hands On with QuickBASIC
- [Chapter 5: The QCARDS Program](./references/ch05-qcards-program.md) — Loading programs, module-level code, SUB procedures, structured programming
- [Chapter 6: Editing in the View Window](./references/ch06-editing.md) — Smart editor, automatic formatting, syntax checking, Cut/Copy/Paste, Find/Replace
- [Chapter 7: Programming with On-Line Help](./references/ch07-online-help.md) — Help Index, hyperlinks, QuickSCREEN, symbol help, constructing statements
- [Chapter 8: Using Example Code from On-Line Help](./references/ch08-example-code.md) — Copying examples from Help, DO...LOOP, SELECT CASE, context-sensitive help
- [Chapter 9: Debugging While You Program](./references/ch09-debugging-tutorial.md) — Debug menu, breakpoints, Watch window, single stepping, creating EXE files

### Part 3: QuickBASIC Menus and Commands
- [Chapter 10: Getting Around in QuickBASIC](./references/ch10-getting-around.md) — QB command options, windows, Immediate window, Watch window, mouse, on-line help
- [Chapter 11: The File Menu](./references/ch11-file-menu.md) — New/Open/Save/Merge, Create File, Load File, modules, include files, Print, DOS Shell
- [Chapter 12: Using the Editor](./references/ch12-using-the-editor.md) — Text entry, cursor movement, selecting text, indentation, smart editor, syntax checking
- [Chapter 13: The Edit Menu](./references/ch13-edit-menu.md) — Undo, Cut, Copy, Paste, Clear, New SUB, New FUNCTION
- [Chapter 14: The View Menu](./references/ch14-view-menu.md) — SUBs command, Next SUB, Split, Next Statement, Output Screen, Include Files
- [Chapter 15: The Search Menu](./references/ch15-search-menu.md) — Find, Selected Text, Repeat Last Find, Change, Label
- [Chapter 16: The Run Menu](./references/ch16-run-menu.md) — Start, Restart, Continue, Make EXE File, Make Library, Set Main Module
- [Chapter 17: Debugging Concepts and Procedures](./references/ch17-debugging-concepts.md) — Preventing bugs, tracing, breakpoints, watchpoints, watch expressions, single stepping
- [Chapter 18: The Debug Menu](./references/ch18-debug-menu.md) — Add Watch, Instant Watch, Watchpoint, Delete Watch, Trace On, History On, Toggle Breakpoint
- [Chapter 19: The Calls Menu](./references/ch19-calls-menu.md) — Using the Calls menu, active procedures
- [Chapter 20: The Options Menu](./references/ch20-options-menu.md) — Display, Set Paths, Right Mouse, Syntax Checking, Full Menus
- [Chapter 21: The Help Menu](./references/ch21-help-menu.md) — Index, Contents, Topic, Help On Help

### Appendices
- [Glossary](./references/glossary.md) — Definitions of terms used in the documentation

## Quick Reference

### Starting QuickBASIC
```
QB                          ' Start QuickBASIC
QB program.bas              ' Start and load a program
QB /RUN program.bas         ' Start, load, and run a program
QB /B                       ' Black-and-white monitor mode
QB /H                       ' High-resolution display (43/50 lines)
QB /G                       ' Faster screen updates (CGA)
QB /NOHI                    ' Disable high-intensity characters
QB /L libraryname           ' Load a Quick library
QB /AH                      ' Allow dynamic arrays of records >64K
QB /MBF                     ' Microsoft Binary Format for MKSNGL$/MKSMBF$
```

### Essential Shortcut Keys
```
F5          Run/Continue program
F8          Single step (into procedures)
F10         Procedure step (over procedures)
F9          Toggle breakpoint
F4          View output screen
F6          Switch between windows
F1          Context-sensitive help
SHIFT+F1    General help
ALT+F1      Previous help screen
F2          SUBs dialog (view/switch procedures)
SHIFT+F5    Restart program
CTRL+BREAK  Stop running program
```

### BASIC Language Quick Reference
```basic
' --- Variables and Types ---
DIM x AS INTEGER            ' Integer (2 bytes, -32768 to 32767)
DIM y AS LONG               ' Long integer (4 bytes)
DIM z AS SINGLE             ' Single precision (4 bytes)
DIM d AS DOUBLE             ' Double precision (8 bytes)
DIM s AS STRING             ' Variable-length string
DIM f AS STRING * 20        ' Fixed-length string (20 chars)
DEFINT A-Z                  ' Default all variables to INTEGER

' --- Arrays ---
DIM Scores(1 TO 100) AS INTEGER
DIM Grid(10, 10) AS SINGLE
REDIM DynamicArray(n) AS INTEGER  ' Dynamic (resizable) array

' --- User-Defined Types ---
TYPE Person
    Name AS STRING * 30
    Age AS INTEGER
    Salary AS SINGLE
END TYPE
DIM emp AS Person

' --- Control Flow ---
IF condition THEN
    ' statements
ELSEIF condition THEN
    ' statements
ELSE
    ' statements
END IF

SELECT CASE expression
    CASE value1
        ' statements
    CASE value2 TO value3
        ' statements
    CASE IS > value4
        ' statements
    CASE ELSE
        ' statements
END SELECT

FOR i = 1 TO 100 STEP 2
    ' statements
NEXT i

DO WHILE condition
    ' statements
LOOP

DO
    ' statements
LOOP UNTIL condition

' --- Procedures ---
SUB MySub (param1 AS INTEGER, param2 AS STRING)
    ' statements
END SUB

FUNCTION MyFunc% (x AS INTEGER)
    MyFunc% = x * 2
END FUNCTION

CALL MySub(5, "hello")     ' Call a SUB
result% = MyFunc%(10)       ' Call a FUNCTION

' --- Screen Output ---
CLS                         ' Clear screen
PRINT "Hello, World!"       ' Print to screen
PRINT USING "##.##"; 3.14   ' Formatted output
LOCATE row, col             ' Position cursor
COLOR foreground, background ' Set text colors

' --- File I/O ---
OPEN "data.dat" FOR OUTPUT AS #1
PRINT #1, "Hello"
CLOSE #1

OPEN "data.dat" FOR INPUT AS #1
INPUT #1, text$
CLOSE #1

OPEN "data.dat" FOR RANDOM AS #1 LEN = LEN(record)
PUT #1, recnum, record
GET #1, recnum, record
CLOSE #1

' --- Error Handling ---
ON ERROR GOTO ErrorHandler
' ... code ...
ErrorHandler:
    PRINT "Error"; ERR
    RESUME NEXT
```
