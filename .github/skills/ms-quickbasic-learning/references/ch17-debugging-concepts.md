Chapter 17  Debugging Concepts and Procedures

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Introduces debugging concepts and QuickBASIC's debugging features.
Covers preventing bugs, tracing, breakpoints, watchpoints, watch
expressions, single stepping, and procedure stepping.

## 17.1  Debugging with QuickBASIC

QuickBASIC provides integrated debugging — no separate tools or
recompilation needed. You can:
- Run to where a problem occurs
- Suspend execution
- Fix the problem
- Continue running as though it never stopped

## 17.2  Preventing Bugs with QuickBASIC

Three strategies:

1. **Design carefully** — Use SUB and FUNCTION procedures to isolate tasks.
   Small procedures are easier to debug than large monolithic programs.

2. **Use the Immediate window** — Test small pieces of code in isolation
   before moving them into the View window.

3. **Run often** — QuickBASIC checks each statement as you type and
   translates to executable code. Frequent running catches errors early.

## 17.3  QuickBASIC's Debugging Features

### 17.3.1  Tracing (Full Menus Only)

Debug > Trace On highlights each statement as it executes,
showing the flow of execution through the program.

### 17.3.2  Breakpoints and Watchpoints

**Breakpoints** — Specific lines where execution will pause.
Set with F9 (Toggle Breakpoint). When hit, cursor moves to the
breakpoint line and you can inspect variables.

**Watchpoints** (Full Menus) — Conditional breaks. Execution
pauses when a specified expression becomes true.
Example: `x > 100` will break when x exceeds 100.

### 17.3.3  Watch Expressions

Add expressions to the Watch window. Displayed value updates
as the program runs. Can be numeric expressions or Boolean
conditions (displayed as -1 for true, 0 for false).

### 17.3.4  Watch Window

Displays monitored variables and expressions. Each entry shows:
- Module/procedure where added
- Variable or expression name
- Current value or condition

The Watch window slows execution — close it when not needed.

### 17.3.5  Immediate Window

During a break, use the Immediate window to:
- Print variable values: `PRINT x`
- Change variable values: `x = 42`
- Call procedures: `CALL TestSub`
- Test expressions: `PRINT x * 2 + 1`

### 17.3.6  Other Debugging Features

| Feature        | Key   | Description                                  |
|----------------|-------|----------------------------------------------|
| Single step    | F8    | Execute one statement, entering procedures   |
| Procedure step | F10   | Execute one statement, skipping procedures   |
| Execute to     | F7    | Run to the cursor position                   |
| cursor         |       |                                              |
| Set Next       | —     | Change the next statement to execute         |
| Statement      |       |                                              |
| History Back   | —     | Step backwards through recorded history      |
| History Forward| —     | Step forwards through recorded history       |

### Debugging Workflow

1. Observe incorrect behavior
2. Set breakpoints near suspected problem (F9)
3. Add variables to Watch window (Debug > Add Watch)
4. Run program — it stops at breakpoints
5. Single step through code (F8) watching values change
6. Identify the bad statement
7. Fix the code
8. Continue (F5) or restart (SHIFT+F5)

### Additional Features Table

| Feature           | Activation      | Description                       |
|-------------------|-----------------|-----------------------------------|
| Trace On          | Debug menu      | Highlight each executing statement|
| History On        | Debug menu      | Record execution history          |
| Break on Errors   | Debug menu      | Break even with ON ERROR handler  |
| Set Next Statement| Debug menu      | Change execution point            |
