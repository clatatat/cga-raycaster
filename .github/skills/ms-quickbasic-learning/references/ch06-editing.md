Chapter 6  Editing in the View Window

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Covers QuickBASIC's smart editor features: automatic formatting, syntax
checking, error messages, Cut/Copy/Paste, Find and Replace, and automatic
procedure declarations.

## The Smart Editor

QuickBASIC's editor is "smart" — it recognizes language keywords and warns
you when they are used incorrectly. It also auto-formats code as you type.

### Automatic Formatting

When you move the cursor off a line:
- Keywords are capitalized (e.g., `print` becomes `PRINT`)
- Spaces inserted around operators (=, +, -, etc.)
- Proper indentation maintained

Example: Typing lowercase:
```
open "qcards.dat" for random as #1 len=len(card)
```
Becomes:
```basic
OPEN "qcards.dat" FOR RANDOM AS #1 LEN = LEN(card)
```

### Syntax Checking

QuickBASIC checks each line as you move off it. If there's a syntax error:
1. An error-message dialog box appears
2. The cursor highlights the error location
3. Press F1 on the error for more information

### Errors Detected When You Run

Some errors (like type mismatches between modules) are only detected
when you run the program.

### Help for Error Messages

When an error dialog appears, choose the Help button for:
- Description of the error
- Common causes
- Suggestions for fixing it

### Automatic Procedure Declarations

When you create a new SUB or FUNCTION, QuickBASIC automatically adds
a DECLARE statement at the module level:
```basic
DECLARE SUB Alarm ()
DECLARE FUNCTION MyFunc% (x AS INTEGER)
```

## Editing Operations

### Cut, Copy, and Paste

1. **Select text**: Hold SHIFT and use DIRECTION keys, or SHIFT+click
2. **Cut** (SHIFT+DEL): Remove selected text to Clipboard
3. **Copy** (CTRL+INS): Copy selected text to Clipboard
4. **Paste** (SHIFT+INS): Insert Clipboard contents at cursor

Note: DEL deletes selected text without placing it on the Clipboard.

### Block Operations

- Select a block of lines
- Press TAB to indent the block right one tab stop
- Press SHIFT+TAB to move the block left one indentation level
- Press DEL to delete the entire block

## Searching and Replacing Text

### Find (CTRL+Q, F or Search menu)

1. Choose Search menu's Find command
2. Enter search text in "Find What" text box
3. Set options (Match Upper/Lowercase, Whole Word)
4. Set scope (Active Window, Current Module, All Modules)
5. Press ENTER to search

### Change (Search menu)

1. Choose Search menu's Change command
2. Enter search text in "Find What"
3. Enter replacement text in "Change To"
4. Press ENTER to begin
5. For each match, choose: Change, Skip, or Cancel

## Using Symbolic Constants

Define constants with CONST for values that don't change:
```basic
CONST DISKFILE$ = "QCARDS.DAT"
CONST MAXCARDS = 100
CONST PI = 3.14159
```

Benefits:
- Self-documenting code
- Change value in one place to update everywhere
- Cannot be accidentally modified at run time
