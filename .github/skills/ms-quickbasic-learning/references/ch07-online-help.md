Chapter 7  Programming with On-Line Help

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Demonstrates using QuickBASIC's on-line help system to guide writing code.
Covers the Help Index, hyperlinks, QuickSCREEN syntax help, and symbol help
for user-defined variables and types.

## Using On-Line Help to Construct Statements

### On-Line Help for Keywords

1. Choose Help menu's Index command (ALT+H, then I)
2. Index lists all QuickBASIC keywords alphabetically
3. Press the initial letter of the keyword you want
4. Select the keyword and press F1

### QuickSCREEN

The QuickSCREEN for each keyword shows:
- Brief description of the statement's action
- Syntax with each part explained
- Other uses of the keyword
- Hyperlinks to related topics

### Hyperlinks in On-Line Help

| Hyperlink  | Information Displayed                              |
|------------|----------------------------------------------------|
| QuickSCREEN| Brief syntax summary                               |
| Details    | Full explanation of each syntax element             |
| Example    | Code examples illustrating syntax use               |
| Contents   | All categories of on-line help                     |
| Index      | Alphabetical keyword list                          |

Navigate hyperlinks:
- TAB or initial letter to move to a hyperlink
- F1 to follow the link
- ALT+F1 to go back (up to 20 screens)

### Resizing the Help Window

- ALT+PLUS to enlarge the Help window
- ALT+MINUS to shrink it
- CTRL+F10 to toggle full-screen

This lets you view help information while entering text in the View window.

## Symbol Help

Press F1 on any user-defined symbol (variable, type member, procedure name)
to see help about that symbol. QuickBASIC shows:
- Where the symbol is defined
- The TYPE...END TYPE definition (for type members)
- How the symbol is used in the program

Example: Pressing F1 on `CardNum` shows:
```
CardNum is a symbol that is used in your program as follows:

  C:\QB4.5\DEMO\CHAPTER7.BAS
  An element of a user defined TYPE:
    TYPE PERSON
      CardNum AS INTEGER
      Names AS STRING * 37
      Note AS STRING * 31
      Month AS INTEGER
      Day AS INTEGER
      Year AS INTEGER
      Phone AS STRING * 12
      Street AS STRING * 29
      City AS STRING * 13
      State AS STRING * 2
      Zip AS STRING * 5
    END TYPE
```

## Constructing Code with Help

Workflow for writing unfamiliar statements:

1. Look up the statement in the Help Index
2. Read the QuickSCREEN for syntax overview
3. Follow the Example hyperlink for sample code
4. Size the Help window to keep syntax visible
5. Enter your code in the View window
6. Use F1 on symbols to verify definitions
