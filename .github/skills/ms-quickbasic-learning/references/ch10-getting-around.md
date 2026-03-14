Chapter 10  Getting Around in QuickBASIC

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Comprehensive reference to the QuickBASIC programming environment.
Covers starting QuickBASIC with options, menus, dialog boxes, windows,
the Immediate window, Watch window, mouse usage, and on-line help.

## 10.1  Starting QuickBASIC

### 10.1.1  The QB Command

Full syntax:
```
QB [[/RUN]] [[programname]] [[/B]] [[/G]] [[/H]] [[/NOHI]]
   [[/C:buffersize]] [[/L[[libraryname]]]] [[/MBF]] [[/AH]] [[/CMD string]]
```

| Option         | Description                                              |
|----------------|----------------------------------------------------------|
| /RUN           | Run the specified program immediately                    |
| programname    | File to load at startup                                  |
| /B             | Black-and-white mode for composite monitors              |
| /G             | Faster CGA screen updates (may cause "snow")             |
| /H             | Maximum number of display lines (EGA: 43, VGA: 50)      |
| /NOHI          | Use with monitors that don't support high intensity      |
| /C:buffersize  | Set communications receive buffer size                   |
| /L libraryname | Load a Quick library (.QLB)                              |
| /MBF           | Convert MKS$/MKD$/CVS/CVD to MBF equivalents            |
| /AH            | Allow dynamic arrays of records, fixed-length strings >64K|
| /CMD string    | Pass string to COMMAND$ function                         |

### 10.1.2  The /NOHI Option

For monitors that don't support high-intensity video attributes.
If the screen is unreadable when you start QB, restart with /NOHI.

### 10.1.3  The QuickBASIC Screen

| Element          | Description                                          |
|------------------|------------------------------------------------------|
| Menu bar         | Contains pull-down menus                             |
| Title bar        | Shows name of loaded file/procedure                  |
| View window      | Main editing area for programs                       |
| Scroll bars      | Scroll text (mouse only)                             |
| Immediate window | Execute BASIC statements directly                    |
| Reference bar    | Shortcut keys, row/column, CAPS/NUM indicators       |

## 10.2  Opening Menus and Choosing Commands

### 10.2.1  Keyboard Technique

1. Press ALT to activate menu bar
2. Press highlighted letter of menu name
3. Press highlighted letter of command, or use DIRECTION keys + ENTER

### 10.2.2  Using Shortcut Keys

| Programming Shortcut | Action / Menu Command                          |
|---------------------|-----------------------------------------------|
| SHIFT+F1            | General help / Help on Help                    |
| F1                  | Help on keyword at cursor / Topic              |
| ALT+F1              | Previous help screens (up to 20)               |
| F2                  | SUBs list / SUBs command on View menu          |
| SHIFT+F2            | Next procedure / Next SUB on View menu         |
| F3                  | Find next / Repeat Last Find                   |
| F4                  | Output screen                                  |
| F5                  | Continue / Continue on Run menu                |
| SHIFT+F5            | Run from start / Start on Run menu             |
| F6                  | Switch windows                                 |
| F7                  | Execute to cursor                              |
| F8                  | Single step                                    |
| F9                  | Toggle breakpoint                              |
| F10                 | Procedure step                                 |
| SHIFT+F9            | Instant Watch                                  |
| CTRL+BREAK          | Stop running program                           |

## 10.3  Using Dialog Boxes

Navigate with TAB between elements, DIRECTION keys within groups,
SPACEBAR for check boxes, ENTER for command buttons, ESC to cancel.
In dialog boxes, hold ALT while pressing the highlighted letter.

## 10.4  Using Windows

### 10.4.1  Window Types

- **View** — Edit programs. Split into two with View > Split.
- **Immediate** — Execute BASIC statements directly.
- **Help** — On-line help content.
- **Watch** — Monitor variable values during debugging.

### 10.4.2  Splitting the View Window (Full Menus Only)

View > Split creates two View windows. Each can show different
procedures or modules. Use F6 to switch between them.

### 10.4.3  Changing the Active Window

Press F6 to cycle through windows.

### 10.4.4  Changing Window Size

- ALT+PLUS enlarges the active window
- ALT+MINUS shrinks the active window
- CTRL+F10 toggles full-screen

### 10.4.5  Scrolling in the Active Window

| Keys          | Action                    |
|---------------|---------------------------|
| DIRECTION     | Scroll one line/column    |
| PGUP/PGDN    | Scroll one page           |
| CTRL+HOME     | Top of file               |
| CTRL+END      | End of file               |

## 10.5  Using the Immediate Window

The Immediate window executes BASIC statements directly without
being part of a program. Useful for:

### 10.5.1  Statements Not Allowed

SUB, FUNCTION, DEF FN, TYPE, DIM SHARED, COMMON, DECLARE, and
multi-line structures (IF...END IF block form) are not allowed.

### 10.5.2  Doing Calculations

```basic
PRINT 355/113                ' Quick calculations
PRINT SQR(2)                 ' Functions work too
```

### 10.5.3  Testing Screen Output

```basic
SCREEN 0 : WIDTH 80          ' Reset to text mode
VIEW PRINT                    ' Close text viewports
```

### 10.5.4  Invoking Procedures

```basic
Alarm                         ' Call a SUB directly
PRINT MyFunc%(5)              ' Call a FUNCTION
```

### 10.5.5  Changing the Values of Variables

During a break in execution:
```basic
i% = 9900                    ' Change loop counter
```
Then press F5 to continue from the new value.

### 10.5.6  Simulating Run-Time Errors

```basic
ERROR 53                      ' Simulate "File not found"
```

## 10.6  Using the Watch Window

Opens when you choose Add Watch or Watchpoint from the Debug menu.
Each entry shows: module name, variable/expression, current value/condition.

## 10.7  Using the Mouse

| Mouse Action        | Effect                                    |
|--------------------|-------------------------------------------|
| Click              | Position cursor or select item            |
| Double-click       | Select word at cursor                     |
| Click+drag         | Select text                               |
| Click scroll bar   | Scroll                                    |
| Click menu         | Open menu                                 |
| Right-click        | Configurable via Options > Right Mouse    |

## 10.8  Using On-Line Help

### 10.8.1  Help Features

Multiple ways to access help:
1. F1 on a keyword for context-sensitive help
2. F1 in a dialog box for help on that dialog
3. Help menu commands (Index, Contents, Topic)
4. Hyperlinks between related topics

### 10.8.2  Hyperlinks

Hyperlinks appear between highlighted triangles in help screens.
Any BASIC keyword in help text is also a hyperlink.

Navigate: TAB to hyperlink, F1 to follow, ALT+F1 to go back.

### 10.8.3  Moving in Help Windows

| Key           | Action                                         |
|---------------|------------------------------------------------|
| CTRL+F1       | Next help topic                                |
| SHIFT+CTRL+F1 | Previous help topic                           |
| TAB           | Next hyperlink                                 |
| SHIFT+TAB     | Previous hyperlink                             |

### 10.8.4  Help Files

QuickBASIC searches for help files in:
1. Current working directory
2. Directory specified by Set Paths command
3. Removable disks
