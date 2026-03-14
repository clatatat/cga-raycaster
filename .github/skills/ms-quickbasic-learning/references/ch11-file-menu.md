Chapter 11  The File Menu

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Reference for the File menu commands: creating, opening, saving, merging,
and printing files. Covers module management for multi-file programs.

## File Menu Commands

| Command              | Description                                       |
|----------------------|---------------------------------------------------|
| New Program          | Clear memory and start a new program              |
| Open Program         | Open an existing program from disk                |
| Merge (Full)         | Merge contents of a file into current position    |
| Save (Full)          | Save current file to disk                         |
| Save As              | Save current file with a new name                 |
| Save All (Full)      | Save all currently loaded files                   |
| Create File (Full)   | Create a new module, include file, or document    |
| Load File (Full)     | Load an existing module, include, or document     |
| Unload File (Full)   | Remove a file from memory                         |
| Print                | Print program text                                |
| DOS Shell            | Open a DOS command prompt                         |
| Exit                 | Quit QuickBASIC                                   |

## 11.1  New Program Command

Clears all loaded programs and starts a new program. Creates the main
module of a program.

A program can have four types of files:
- One main module (required)
- Other modules
- Include files
- Document files (including .MAK files)

Modules can contain:
- Module-level code
- SUB procedures
- FUNCTION procedures

## 11.2  Open Program Command

Opens a program from disk. Dialog box includes:
- File Name text box (wildcards supported: *.bas)
- Files list box
- Dirs/Drives list box

## 11.3  Merge Command (Full Menus Only)

Merges contents of a text file at the current cursor position.
Only text-format files can be merged.

## 11.4  Save Command (Full Menus Only)

Saves the file in the active View window. No dialog box — uses
the current file name.

## 11.5  Save As Command

Saves with a new name. Format options:
- **QuickBASIC - Fast Load and Save** — Binary format (default). Loads faster.
  Cannot be edited by other programs.
- **Text - Readable by Other Programs** — ASCII format. Editable by any
  text editor. Include files and document files are always in this format.

## 11.6  Save All Command (Full Menus Only)

Saves all currently loaded files at once.

## 11.7  Create File Command (Full Menus Only)

Creates a new file as part of the current program:
- **Module** — Discrete program component saved separately on disk
- **Include** — Text file merged with $INCLUDE metacommand
- **Document** — Plain text file, no syntax checking

## 11.8  Load File Command (Full Menus Only)

Loads an existing file into the current program:
- **Module** — Loaded as a program module
- **Include** — Loaded as an include file
- **Document** — Loaded as a document file (no syntax checking)

## 11.9  Unload File Command (Full Menus Only)

Removes a module (and all its procedures) from memory.
Module names are removed from the .MAK file when saved.

## 11.10  Print Command

Prints program text. Options:
- Current window contents
- Entire program
- Selected text

## 11.11  DOS Shell Command

Opens a DOS command prompt. Type EXIT to return to QuickBASIC.
Current program remains in memory.

## The .MAK File

When saving a multi-module program, QuickBASIC creates a .MAK file
listing all modules in the program. Loading the .MAK reloads all modules.
