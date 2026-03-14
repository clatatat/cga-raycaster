Chapter 12  Using the Editor

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Describes entering and editing program text. Covers insert/overtype modes,
cursor movement, selecting text, deleting, inserting, moving/copying blocks,
searching, replacing, and the smart editor features.

## 12.1  Entering Text

Two modes:
- **Insert mode** (default) — New text pushes existing text right. Cursor is
  a blinking underscore.
- **Overtype mode** — New text replaces existing text. Cursor is a blinking
  block. Toggle with INS key.

## 12.2  Indentation Controls

| Keystrokes    | Description                                       |
|---------------|---------------------------------------------------|
| (Automatic)   | Each new line maintains the current indentation   |
| HOME          | Cancels auto-indent, moves cursor to left margin  |
| BACKSPACE     | Moves indentation back one level                  |
| CTRL+Q+S      | Moves cursor to left margin of current line       |
| TAB           | Indents line or selected block one tab stop right |
| SHIFT+TAB     | Moves selected block one level left               |

## 12.3  Cursor Movement

| Keys           | Movement                                   |
|----------------|-------------------------------------------|
| LEFT/RIGHT     | One character left/right                   |
| UP/DOWN        | One line up/down                           |
| CTRL+LEFT      | One word left                              |
| CTRL+RIGHT     | One word right                             |
| HOME           | Beginning of line                          |
| END            | End of line                                |
| CTRL+HOME      | Top of file                                |
| CTRL+END       | End of file                                |
| PGUP/PGDN     | One screen up/down                         |

## 12.4  Selecting Text

| Method                    | Selects                             |
|---------------------------|-------------------------------------|
| SHIFT+DIRECTION keys      | Character by character               |
| SHIFT+HOME                | From cursor to beginning of line     |
| SHIFT+END                 | From cursor to end of line           |
| SHIFT+PGUP/PGDN           | One screen up/down                  |
| SHIFT+CTRL+HOME/END       | To top/bottom of file               |
| Mouse Click+Drag           | From click point to release point   |
| Mouse Double-click         | Select word at cursor               |

## 12.5  The Smart Editor

QuickBASIC's smart editor provides:
- **Keyword capitalization** — Keywords auto-capitalized when you leave a line
- **Syntax checking** — Each line checked for errors when you leave it
- **Automatic formatting** — Spaces added around operators
- **Automatic DECLARE** — Procedure declarations generated automatically

Syntax Checking can be toggled via Options > Syntax Checking.

## 12.6  Editing Commands Summary

| Command          | Keys        | Action                             |
|------------------|-------------|-------------------------------------|
| Cut              | SHIFT+DEL   | Remove selected text to Clipboard   |
| Copy             | CTRL+INS    | Copy selected text to Clipboard     |
| Paste            | SHIFT+INS   | Insert Clipboard at cursor          |
| Delete           | DEL         | Delete selected text (no Clipboard) |
| Delete line      | CTRL+Y      | Delete entire current line          |
| Delete to EOL    | CTRL+Q+Y    | Delete from cursor to end of line   |
| Undo             | ALT+BKSP    | Undo last edit (one level)          |
| New line         | ENTER       | Insert line break at cursor         |

## 12.7  Searching for Text

Use Search > Find (or CTRL+Q+F):
- Enter search text
- Options: Match Upper/Lowercase, Whole Word
- Scope: Active Window, Current Module, All Modules

## 12.8  Replacing Text

Use Search > Change:
- Enter search and replacement text
- For each match: Change, Skip, or Cancel
- Scope options same as Find

## 12.9  Copying from Other Files

Use File > Merge to insert a text file at the cursor position.
Or open another module and use Cut/Copy/Paste between windows.
