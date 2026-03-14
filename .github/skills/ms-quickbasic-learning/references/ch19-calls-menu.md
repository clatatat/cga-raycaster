Chapter 19  The Calls Menu (Full Menus Only)

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Reference for the Calls menu, which displays the chain of procedure
calls (call stack) during debugging.

## 19.1  Using the Calls Menu

The Calls menu is available only during a break in program execution
(breakpoint, CTRL+BREAK, single stepping). It shows the sequence of
procedure calls that led to the current position.

The list shows procedures from most recent (top) to earliest (bottom).
Selecting a procedure from the Calls menu moves the cursor to the
call site in that procedure.

Example call stack:
```
DirectionKey         ← currently executing
ShowCards            ← called DirectionKey
(module-level code)  ← called ShowCards
```

## 19.2  Active Procedures

The Calls menu lists all active (currently executing) procedures.
A procedure is active if it has been called but has not yet returned.

This is particularly useful for:
- Understanding recursive procedure calls
- Tracing the execution path that led to an error
- Finding which procedure called the current one
- Understanding deeply nested procedure calls
