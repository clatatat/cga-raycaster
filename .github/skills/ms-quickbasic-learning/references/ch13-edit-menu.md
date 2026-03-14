Chapter 13  The Edit Menu

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Reference for the Edit menu commands, including Undo, clipboard
operations, clearing text, and creating new SUB and FUNCTION procedures.

## Edit Menu Commands

| Command               | Shortcut     | Description                      |
|-----------------------|-------------|----------------------------------|
| Undo                  | ALT+BKSP    | Undo last edit                   |
| Cut                   | SHIFT+DEL   | Move selection to Clipboard      |
| Copy                  | CTRL+INS    | Copy selection to Clipboard      |
| Paste                 | SHIFT+INS   | Insert Clipboard at cursor       |
| Clear (Full)          | DEL         | Delete selection (no Clipboard)  |
| New SUB (Full)        | —           | Create a new SUB procedure       |
| New FUNCTION (Full)   | —           | Create a new FUNCTION procedure  |

## 13.1  Undo Command

Reverses the most recent editing action. Only one level of undo.

## 13.2  Cut Command

Removes selected text and places it on the Clipboard. Previous
Clipboard contents are replaced.

## 13.3  Copy Command

Copies selected text to the Clipboard without removing it.

## 13.4  Paste Command

Inserts Clipboard contents at the cursor position. If text is selected,
the selection is replaced by the pasted text.

## 13.5  Clear Command (Full Menus Only)

Deletes selected text permanently (does not go to Clipboard).

## 13.6  New SUB Command (Full Menus Only)

### 13.7.1  Creating a New SUB Procedure

1. Choose Edit > New SUB
2. Type the procedure name in the dialog box
3. Press ENTER
4. QuickBASIC opens a new View window with SUB...END SUB in place

### 13.7.2  Default Data Types for Procedures

If a DEFtype statement (e.g., DEFINT A-Z) exists at module level,
it's automatically added above the new procedure.

### 13.7.3  Changing a Procedure's Default Type

Edit the DEFtype statement at the top of the procedure window.

### 13.7.4  Saving and Naming Procedures

Procedures are saved as part of the module that contains them.
You can move procedures between modules using the SUBs dialog.

## 13.8  New FUNCTION Command (Full Menus Only)

Same as New SUB, but creates a FUNCTION...END FUNCTION block.
FUNCTION procedures return a value by assigning to the function name:

```basic
FUNCTION Square% (x AS INTEGER)
    Square% = x * x
END FUNCTION
```

Note: You can also type `SUB subname` or `FUNCTION funcname` directly
in the View window — QuickBASIC starts the procedure automatically.
