Chapter 14  The View Menu

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Reference for the View menu commands. Covers viewing and navigating
procedures, splitting windows, viewing output, and managing include files.

## View Menu Commands

| Command                   | Shortcut    | Description                     |
|---------------------------|-------------|----------------------------------|
| SUBs                      | F2          | List/navigate procedures         |
| Next SUB (Full)           | SHIFT+F2    | Show next procedure              |
| Split (Full)              | —           | Split View window in two         |
| Next Statement (Full)     | —           | Jump to next statement to execute|
| Output Screen             | F4          | View program's output screen     |
| Included File (Full)      | —           | View/edit an include file        |
| Included Lines            | —           | Toggle display of include lines  |

## 14.1  SUBs Command

Displays the SUBs dialog box listing all loaded procedures, modules,
include files, and document files.

Features:
- Module names shown in UPPERCASE
- Procedures indented beneath their module
- "Edit in Active" loads selection into current View window
- "Edit in Split" opens in a split window (Full Menus)
- Move procedures between modules by selecting and using buttons

## 14.2  Next SUB Command (Full Menus Only)

Displays the next procedure in the active window. Cycles through
all procedures in the current module.

Shortcut: SHIFT+F2
Previous procedure: CTRL+F2

## 14.3  Split Command (Full Menus Only)

Splits the View window horizontally into two panes.
Each pane can display a different procedure, module, or file.
Press F6 to switch between panes.
Choose Split again to unsplit.

## 14.4  Next Statement Command (Full Menus Only)

Moves cursor to the next statement that will execute when the
program continues. Useful during debugging.

## 14.5  Output Screen Command

Displays the program's output screen (what the user sees when
the program runs). Press any key to return to QuickBASIC.

Shortcut: F4

## 14.6  Included File Command (Full Menus Only)

Views or edits an include file ($INCLUDE metacommand).

### 14.6.1  Nesting Include Files

Include files can contain $INCLUDE metacommands to nest includes.

### 14.6.2  Finding Include Files

QuickBASIC searches for include files in:
1. Current directory
2. Paths specified in Set Paths command (Options menu)

## 14.7  Included Lines Command

Toggles display of lines from include files. When off, include
file contents are hidden and only the $INCLUDE line is shown.
