Chapter 15  The Search Menu

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Reference for the Search menu commands: finding text, replacing text,
finding labels, and repeating searches.

## Search Menu Commands

| Command                    | Shortcut  | Description                    |
|----------------------------|-----------|--------------------------------|
| Find                       | CTRL+Q+F  | Search for text                |
| Selected Text (Full)       | CTRL+\    | Find the selected text         |
| Repeat Last Find (Full)    | F3        | Find next occurrence           |
| Change                     | —         | Find and replace text          |
| Label (Full)               | —         | Find a label in the program    |

## 15.1  Defining Target Text

Enter the text to find in the "Find What" text box. Default target
is the word at the cursor position.

## 15.2  Find Command

Search for text with options:

| Option                  | Description                              |
|-------------------------|------------------------------------------|
| Match Upper/Lowercase   | Case-sensitive search                    |
| Whole Word              | Match complete words only                |

| Restriction             | Scope of search                          |
|-------------------------|------------------------------------------|
| Active Window           | Search only in the current window        |
| Current Module          | Search the entire current module         |
| All Modules             | Search all loaded modules                |

If text is not found: "Match not found" message appears.

## 15.3  Selected Text Command (Full Menus Only)

Searches for the currently selected text. Equivalent to selecting
text, choosing Find, and pressing ENTER.

Shortcut: CTRL+\

## 15.4  Repeat Last Find Command (Full Menus Only)

Finds the next occurrence of the previously specified search text.

Shortcut: F3

## 15.5  Change Command

Find and replace text:
1. Enter search text in "Find What"
2. Enter replacement in "Change To"
3. Set options and restrictions
4. Press ENTER to begin

For each match, a dialog box offers:
- **Change** — Make the replacement and move to next match
- **Skip** — Skip this match and find the next one
- **Cancel** — Stop the search
- **Help** — Get more information

When all occurrences are processed: "Change Complete" message.

## 15.6  Label Command (Full Menus Only)

Finds a label (used with GOTO, GOSUB, etc.) in the program.
Enter the label name in the dialog box.
