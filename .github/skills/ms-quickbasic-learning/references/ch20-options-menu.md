Chapter 20  The Options Menu

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Reference for the Options menu commands: customizing the display,
setting file search paths, configuring the right mouse button,
toggling syntax checking, and switching between Easy and Full menus.

## Options Menu Commands

| Command                     | Description                              |
|-----------------------------|------------------------------------------|
| Display                     | Customize screen colors and options      |
| Set Paths                   | Set directories for files and libraries  |
| Right Mouse (Full)          | Configure right mouse button action      |
| Syntax Checking (Full)      | Toggle automatic syntax checking         |
| Full Menus                  | Switch between Easy and Full menus       |

## 20.1  Display Command

Customizes the QuickBASIC screen display:

### Display Colors

Set foreground and background colors for:
1. **Normal Text** — Regular program text
2. **Current Statement** — The statement about to execute during debugging
3. **Breakpoint Lines** — Lines with breakpoints set

### Display Options

- **Scroll Bars** — Toggle scroll bars on/off
- **Tab Stops** — Set the number of spaces per tab (default: 8)

Settings are saved in QB.INI when you exit QuickBASIC.

## 20.2  Set Paths Command

Specifies directories where QuickBASIC searches for files:

| Path Type          | Files Searched For                          |
|--------------------|--------------------------------------------|
| Executable files   | BC.EXE, LINK.EXE                           |
| Include files      | .BI, .BAS files referenced by $INCLUDE     |
| Library files      | .LIB, .QLB files                           |
| Help file          | .HLP files                                 |

Separate multiple directories with semicolons:
```
C:\QB45;C:\QB45\SOURCE
```

## 20.3  Right Mouse Command (Full Menus Only)

Configures what the right mouse button does:
- Execute commands from a list of common actions
- Can be set to any frequently used command

## 20.4  Syntax Checking Command (Full Menus Only)

Toggles automatic syntax checking on and off.

When ON (default):
- Each line is checked for syntax errors when you leave it
- Keywords are automatically capitalized
- Automatic formatting is applied

When OFF:
- No checking occurs until you run the program
- Useful when editing large blocks of code or document files

## 20.5  Full Menus Command

Toggles between Easy Menus and Full Menus.

**Easy Menus** — Simplified set of commands for beginners.
Contains all basic programming, editing, and debugging commands.

**Full Menus** — Complete set of commands including:
- Multi-module program support
- Include files and document files
- Advanced debugging (Trace, History, Watchpoints)
- Library creation
- Split windows
- Additional search options
