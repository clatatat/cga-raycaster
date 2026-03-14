Chapter 9  Debugging While You Program

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Covers QuickBASIC's debugging features: Debug menu commands, Run menu
debugging commands, breakpoints, the Watch window, single stepping,
procedure stepping, and creating stand-alone executable files.

## Debugging Commands

### Debug Menu Commands

| Command (Shortcut)     | Action                                        |
|------------------------|-----------------------------------------------|
| Add Watch              | Add variable/expression to Watch window       |
| Instant Watch (SHIFT+F9)| Display value of variable at cursor          |
| Watchpoint             | Break when expression becomes true (Full Menus)|
| Delete Watch           | Remove variable from Watch window             |
| Delete All Watch       | Remove all Watch entries (Full Menus)         |
| Trace On               | Highlight each statement as it executes       |
| History On             | Record execution history (Full Menus)         |
| Toggle Breakpoint (F9) | Set/clear breakpoint on current line          |
| Clear All Breakpoints  | Remove all breakpoints                        |
| Break on Errors        | Break on error even with ON ERROR (Full Menus)|
| Set Next Statement     | Set the next statement to execute             |

### Debugging Commands on the Run Menu

| Command (Shortcut)     | Action                                        |
|------------------------|-----------------------------------------------|
| Start (SHIFT+F5)       | Run from the beginning                        |
| Continue (F5)          | Continue from where execution stopped         |
| Restart                | Reset program to beginning without running    |

### Function Keys Used in Debugging

| Key  | Action                                                    |
|------|-----------------------------------------------------------|
| F5   | Continue (run from current position)                      |
| F8   | Single step (execute next statement, entering procedures) |
| F10  | Procedure step (execute next statement, skip procedures)  |
| F9   | Toggle breakpoint at cursor                               |
| F7   | Execute to cursor position                                |
| F4   | View Output Screen                                        |

## Debugging a Procedure

### Learning about Procedures

- Use F2 (SUBs command) to navigate between procedures
- Watch window can monitor variables at different scope levels
  (module-level and procedure-level variables can have the same name)

### Continuing a Suspended Program

After fixing a bug during a break:
- Press F5 to continue from the current position
- Or choose Run > Start (SHIFT+F5) to restart from the beginning
- If changes prevent continuation, QuickBASIC asks whether to restart

## Isolating a Bug

Debugging workflow:
1. Run the program and observe incorrect behavior
2. Set breakpoints near the suspected problem area (F9)
3. Run the program — execution stops at each breakpoint
4. Add variables to the Watch window to monitor their values
5. Use F8 (single step) to execute one statement at a time
6. Observe variable changes in the Watch window
7. Identify where a variable gets an unexpected value
8. Fix the code and continue

## Closing the Watch Window

The Watch window slows execution when open. To close it:
1. Choose Debug > Delete Watch (repeatedly)
2. Select variables from the dialog box
3. The window closes when all entries are removed
4. Also use Debug > Clear All Breakpoints to clean up

## Creating a Stand-Alone Executable File

1. Choose Run menu's Make EXE File command
2. Enter the EXE file name
3. Choose executable type:

| Option                      | Description                                |
|-----------------------------|--------------------------------------------|
| EXE Requiring BRUN45.EXE   | Smaller file, requires BRUN45.EXE at run   |
| Stand-Alone EXE File        | Larger file, runs independently             |

4. Check "Produce Debug Code" if you want run-time error checking
5. Press ENTER to create the executable

### Running the Executable

From DOS:
```
qcards
```

### Required Files for Compilation

| File          | Location       | Purpose                         |
|---------------|----------------|---------------------------------|
| BC.EXE        | Utilities 1    | BASIC command-line compiler      |
| LINK.EXE      | Utilities 1    | Microsoft Overlay Linker         |
| BRUN45.LIB    | Utilities 1    | Run-time library                 |
| BCOM45.LIB    | Utilities 2    | Stand-alone library              |
