---
name: ms-quickc-programming
description: 'Microsoft QuickC Programming reference (The Waite Group, 1988). Use when writing C code for QuickC, MS-DOS, 8086/8088, CGA/EGA/VGA graphics, BIOS interrupts, keyboard handling, far pointers, memory models, or retro DOS game development. Covers C fundamentals, pointers, arrays, strings, file I/O, structs, unions, preprocessor, multi-file projects, direct hardware access, text modes, graphics modes, and debugging.'
---

# Microsoft QuickC Programming

**Authors:** Mitchell Waite, Stephen Prata, Bryan Costales, Harry Henderson (The Waite Group)
**Publisher:** Microsoft Press, 1988
**Source:** [Microsoft Programmer's Library 1.3 via PCjs](https://www.pcjs.org/documents/books/mspl13/c/mspqc/)

Complete reference for the Microsoft QuickC compiler, covering C language fundamentals through hardware-level DOS/BIOS programming on IBM PC compatibles.

## When to Use

- Writing C code targeting Microsoft QuickC (QCL) or Microsoft C 5.x
- Programming for MS-DOS on 8086/8088/80286 systems
- CGA, EGA, or VGA graphics programming
- BIOS interrupt calls and direct hardware access
- Keyboard input handling (including non-ASCII keys, INT 9h/16h)
- Text mode programming and direct video memory access
- Understanding far pointers, memory models, and segmented addressing
- Multi-file C project organization with QuickC
- Retro DOS game or demo development

## Chapter Reference

### Part 1: Introduction to C
- [Chapter 1: Introduction](./references/ch01-introduction.md) — Why C, why QuickC, hardware requirements, conventions
- [Chapter 2: Starting with QuickC](./references/ch02-starting-with-quickc.md) — Setup, directories, editor, compiling, debugging basics

### Part 2: Core of C
- [Chapter 3: C Fundamentals](./references/ch03-c-fundamentals.md) — Data types, printf/scanf, operators, declarations
- [Chapter 4: Repetition and Looping](./references/ch04-repetition-and-looping.md) — for, while, do loops, debugging loops
- [Chapter 5: Decisions and Branching](./references/ch05-decisions-and-branching.md) — if, switch, break, continue, goto, conditional operator
- [Chapter 6: Functions](./references/ch06-functions.md) — Declaration, local/static/extern/register variables, recursion, prototypes

### Part 3: Advanced C Topics
- [Chapter 7: Arrays](./references/ch07-arrays.md) — Memory layout, initialization, multidimensional, bitwise operators
- [Chapter 8: Addresses and Pointers](./references/ch08-addresses-and-pointers.md) — Pointer arithmetic, far pointers, dynamic arrays, type casting
- [Chapter 9: Strings](./references/ch09-strings.md) — String pool, manipulation routines, argv/argc, character classification
- [Chapter 10: Managing Files](./references/ch10-managing-files.md) — Buffered and unbuffered file I/O, error handling
- [Chapter 11: Advanced Data Types](./references/ch11-advanced-data-types.md) — Structures, unions, enums, bit fields, typedef
- [Chapter 12: Large Projects](./references/ch12-large-projects.md) — Preprocessor directives, multi-file projects, QuickC project management

### Part 4: C and the Hardware
- [Chapter 13: Keyboard and Cursor Control](./references/ch13-keyboard-and-cursor.md) — Keyboard input functions, non-ASCII keys, console I/O, BIOS calls, ANSI.SYS
- [Chapter 14: Monitors and Text Modes](./references/ch14-monitors-and-text.md) — CGA/EGA/VGA monitors, text modes, direct memory access, paging, ports
- [Chapter 15: Graphics and QuickC](./references/ch15-graphics-and-quickc.md) — Graphics modes, CGA/EGA/VGA graphics programming with QuickC Graphics Library
- [Chapter 16: Debugging](./references/ch16-debugging.md) — Keyboard errors, syntax errors, run-time errors, design errors

### Appendices
- [Appendix A: Resources](./references/appendix-a-resources.md) — Books, magazines, user groups
- [Appendix B: Built-in QuickC Functions](./references/appendix-b-functions.md) — Function quick reference
