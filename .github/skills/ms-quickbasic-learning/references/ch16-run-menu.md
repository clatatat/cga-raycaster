Chapter 16  The Run Menu

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Reference for the Run menu commands: running programs, creating executable
files, creating Quick libraries, and managing modules.

## Run Menu Commands

| Command                   | Shortcut    | Description                    |
|---------------------------|-------------|--------------------------------|
| Start                     | SHIFT+F5    | Run program from beginning     |
| Restart                   | —           | Reset program without running  |
| Continue                  | F5          | Continue from current position |
| Modify COMMAND$ (Full)    | —           | Set command-line arguments     |
| Make EXE File             | —           | Create executable file         |
| Make Library (Full)       | —           | Create Quick library (.QLB)    |
| Set Main Module (Full)    | —           | Set main module for program    |

## 16.1  Start Command

Runs the currently loaded program from the beginning.
Stop with CTRL+BREAK. Continue with F5 or restart with SHIFT+F5.

Note: BASICA programs may need modification to run in QuickBASIC.

## 16.2  Restart Command

Resets the program to the beginning without running it.
Clears all variable values. Next F5 starts from the first statement.

## 16.3  Continue Command

Continues running from where execution was suspended (breakpoint,
CTRL+BREAK, or error). If changes were made that prevent continuation,
QuickBASIC asks whether to restart.

Shortcut: F5

## 16.4  Modify COMMAND$ Command (Full Menus Only)

Sets the string returned by the COMMAND$ function, simulating
command-line arguments passed from DOS.

## 16.5  Make EXE File Command

Creates an executable (.EXE) file from the loaded program.

### 16.5.1  Creating Executable Files

1. Choose Run > Make EXE File
2. Enter the EXE file name
3. Select executable type
4. Optionally check "Produce Debug Code"
5. Press ENTER

### 16.5.2  Quick Libraries and Executable Files

Quick libraries (.QLB) are loaded into QuickBASIC with the /L option.
They provide additional procedures at design time.

### 16.5.3  Types of Executable Files

#### 16.5.3.1  Programs that Use the Run-Time Module

- Smaller EXE files
- Require BRUN45.EXE to be present at run time
- Multiple programs can share the run-time module
- Faster linking

#### 16.5.3.2  Stand-Alone Programs

- Larger EXE files (linked with BCOM45.LIB)
- No external files needed at run time
- Fully self-contained
- Suitable for distribution

### 16.5.4  Run-Time Error Checking in Executable Files

"Produce Debug Code" enables run-time error checking:
- Array bounds checking
- Line-number reporting for errors

Without it, programs run faster but errors are harder to diagnose.

### 16.5.5  Floating-Point Arithmetic in Executable Files

QuickBASIC uses IEEE format for floating-point numbers.
Use /MBF option if converting from older Microsoft Binary Format.

## 16.6  Make Library Command (Full Menus Only)

Creates a Quick library (.QLB) from the currently loaded program.

### 16.6.1  Unloading and Loading Modules

Before creating a library, use File > Unload File to remove modules
you don't want in the library. Use File > Load File to add modules.

### 16.6.2  Creating Libraries

Choose Run > Make Library, enter a name, and press ENTER.

## 16.7  Set Main Module Command (Full Menus Only)

### 16.7.1  Changing the Main Module

In a multi-module program, designates which module contains the
main execution code (the code that runs first).

### 16.7.2  The .MAK File

The .MAK file records:
- Names of all modules in the program
- Which module is the main module
- Updated when you save the program
