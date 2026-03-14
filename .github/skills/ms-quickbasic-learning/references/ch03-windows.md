Chapter 3  QuickBASIC's Windows

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Introduces QuickBASIC's window system: View, Immediate, Watch, and Help
windows. Covers loading programs, cursor movement, scrolling, executing
code in the Immediate window, monitoring variables, and saving files.

## Windows Available with Easy Menus

| Window    | Description                                                |
|-----------|------------------------------------------------------------|
| View      | Main programming window. Displays loaded programs.         |
| Immediate | Bottom of screen. Execute single BASIC lines immediately.  |
| Watch     | Top of screen. Monitor variable values during execution.   |
| Help      | Displays on-line help. Can copy examples from here.        |

## The View Window

### Loading Programs

1. Press ALT+F, then O to open the Open Program dialog box
2. Select a file from the Files list box
3. Press ENTER to load the file into the View window

### Moving the Cursor

Use DIRECTION keys, HOME, END, PGUP, PGDN, CTRL+HOME (top of file),
CTRL+END (end of file).

### Scrolling Text

Scroll bars appear on the right and bottom of the View window.
Use PGUP/PGDN for page scrolling, DIRECTION keys for line scrolling.

### Starting a New Program

Choose File menu's New Program command to clear the View window.

### Running Code

Enter code in the View window, then choose Run menu's Start command
(or press F5) to execute.

Example:
```basic
CLS
PRINT "This is my first QuickBASIC program"
PRINT 2 + 2
```

## The Immediate Window

- Press F6 to move cursor to the Immediate window
- Type a BASIC statement and press ENTER to execute it immediately
- Holds up to 10 lines (older lines scroll off)
- Separate multiple statements on one line with a colon (:)
- Keywords are NOT auto-capitalized in the Immediate window

Example:
```basic
cls : print "This line comes from the Immediate window"
```

### Useful Immediate Window Operations

```basic
CurrentTime$ = TIME$          ' Assign system time
PRINT CurrentTime$            ' Display variable value
SCREEN 0 : WIDTH 80           ' Reset screen mode
VIEW PRINT                    ' Close any text viewport
```

## Monitoring Variables with the Watch Window

1. Press ALT+D, then A to open Add Watch dialog box
2. Type the variable name and press ENTER
3. The Watch window opens at the top of the screen
4. Variable values update as the program runs

The Watch window displays:
- Module name where the variable was added
- Variable name
- Current value

## The Help Window

### Context-Sensitive Help

1. Position cursor on a keyword in the View window
2. Press F1 to display the QuickSCREEN for that keyword

### Hyperlinks

Help screens contain hyperlinks (bracketed items) to related topics:
- **QuickSCREEN** — Brief syntax summary
- **Details** — Full explanation of each syntax element
- **Example** — Code examples you can copy and run
- **Contents** — Categories of on-line help
- **Index** — Alphabetical keyword list

Navigate hyperlinks:
- TAB to move to a hyperlink
- F1 to follow the hyperlink
- ALT+F1 to go back (up to 20 screens)

## Saving Programs

1. Press ALT+F, then A to choose Save As
2. Type a file name in the text box
3. Press ENTER to save

### Save Formats

| Format                        | Description                            |
|-------------------------------|----------------------------------------|
| QuickBASIC - Fast Load & Save | Default binary format, loads faster    |
| Text - Readable by Others     | ASCII text, editable by other programs |
