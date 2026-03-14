Chapter 8  Using Example Code from On-Line Help

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Shows how to copy example code from on-line help screens directly into
your program. Demonstrates using DO...LOOP and SELECT CASE, and using
context-sensitive help to check for conflicts.

## Copying Examples from Help

1. Display the QuickSCREEN for a statement (F1 on keyword)
2. Navigate to the Example hyperlink
3. Move cursor into the Help window (F6)
4. Select the code you want to copy
5. Choose Edit menu's Copy command (ALT+E, then C)
6. Close the Help window (ESC)
7. Position cursor in the View window
8. Choose Edit menu's Paste command (ALT+E, then P)

## DO...LOOP Example

```basic
' Get keyboard input until a non-empty string is entered
DO
    Choice$ = INKEY$
LOOP WHILE Choice$ = ""
```

The DO...LOOP repeats statements between DO and LOOP. The WHILE
condition controls when the loop terminates.

## SELECT CASE Example

```basic
SELECT CASE Choice$
    CASE CHR$(DOWN)
        TopCard = TopCard - 1
    CASE CHR$(UP)
        TopCard = TopCard + 1
    CASE CHR$(PGDN)
        TopCard = TopCard - 5
    CASE CHR$(PGUP)
        TopCard = TopCard + 5
    CASE CHR$(ENDK)
        TopCard = LastCard
    CASE CHR$(HOME)
        TopCard = 1
END SELECT
```

SELECT CASE evaluates an expression once and branches to the matching
CASE clause. Much cleaner than nested IF...THEN...ELSE for multiple options.

## Checking for Conflicts

After copying code from help:
1. Place cursor on a variable name (e.g., Choice$)
2. Press F1 to see symbol help
3. QuickBASIC shows where the variable is already used
4. Verify no naming conflicts with existing code

## Copying Syntax Blocks

You can also copy syntax descriptions from help to use as templates:
1. Display the Details screen for a statement
2. Select the syntax template
3. Copy and paste into your View window
4. Replace the placeholder elements with your actual code
