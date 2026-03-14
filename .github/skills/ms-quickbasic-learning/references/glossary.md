Glossary

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Key terms used in the Microsoft QuickBASIC 4.5 documentation.

## Selected Terms

**argument** — A value passed to a statement, function, or procedure.
Can be a constant or variable. Used to pass information between parts
of a program. Use COMMAND$ to access DOS command-line arguments.

**array** — A sequentially numbered set of elements with the same type.

**array bounds** — The upper and lower limits of an array's dimensions.

**ASCII** — American Standard Code for Information Interchange. A set of
256 codes representing letters, digits, and special characters. Only the
first 128 codes are standardized.

**CGA** — Color Graphics Adapter. A video adapter capable of displaying
text characters or graphics pixels with color.

**Clipboard** — Storage area for cut or copied text. New text replaces
previous contents. Use Paste to insert Clipboard text.

**compile** — To translate statements into a form the computer can execute.

**constant** — A value that does not change during program execution.
Symbolic constants are defined with CONST.

**document** — A file loaded without syntax checking or smart editor features.

**double precision** — A floating-point value occupying 8 bytes, accurate
to 15-16 digits. Suffix: #

**far address** — A memory location specified by segment and offset (4 bytes).

**FUNCTION** — A procedure that returns a value. Defined with
FUNCTION...END FUNCTION.

**global variable** — A variable accessible from all parts of a program.
Shared across modules with COMMON SHARED.

**hyperlink** — A link between related help topics. Appears between
highlighted triangles in help screens.

**IEEE format** — International standard for floating-point representation.
More accurate than older Microsoft Binary format.

**Immediate window** — Area at bottom of QuickBASIC screen for executing
statements directly without being part of a program.

**include file** — A text file merged into a program with $INCLUDE.

**keyword** — A BASIC statement, function, or operator name (e.g., PRINT,
MOD, OPEN, SIN).

**local variable** — A variable whose scope is limited to the procedure
where it's defined.

**module** — A discrete program component. A program has at least one
module (the main module). Modules are saved as separate files.

**module-level code** — Code outside of any procedure in a module. Runs
when the program starts.

**output screen** — The screen where program output is displayed.

**pass by reference** — Passing a variable's address to a procedure,
allowing the procedure to modify the original variable.

**pass by value** — Passing a copy of a variable's value to a procedure.
The original variable is not modified. Use parentheses: `CALL Sub((x))`.

**procedure** — A SUB or FUNCTION. The building block of structured programs.

**QB Advisor** — The detailed, context-sensitive on-line help system.

**Quick library** — A .QLB file loaded with the /L option, providing
additional procedures at design time.

**run-time module** — BRUN45.EXE, containing routines needed by programs
compiled with the run-time module option.

**scope** — The range of statements over which a variable or constant
is defined. Can be local (procedure), module, or global.

**segment** — An area of memory up to 64K containing code or data.

**single precision** — A floating-point value occupying 4 bytes, accurate
to 7 digits. Suffix: !

**SUB** — A procedure that performs actions but does not return a value.
Defined with SUB...END SUB.

**symbolic constant** — A constant defined with CONST, referenced by name.

**TYPE** — A user-defined data type containing multiple fields of
different types. Defined with TYPE...END TYPE.

**Watch window** — Displays monitored variables and expressions during
program execution. Opens at top of screen.

**watchpoint** — A conditional breakpoint. Execution pauses when a
specified Boolean expression becomes true.
