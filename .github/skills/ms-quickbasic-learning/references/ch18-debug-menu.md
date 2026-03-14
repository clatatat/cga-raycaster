Chapter 18  The Debug Menu

Source: https://www.pcjs.org/documents/books/mspl13/basic/qblearn/

## Overview

Detailed reference for each command on the Debug menu. Covers adding
and deleting watch expressions, instant watch, watchpoints, tracing,
history, breakpoints, and execution control.

## 18.1  Add Watch Command

Adds a variable or expression to the Watch window for monitoring.

1. Choose Debug > Add Watch
2. Enter variable or expression in the text box
3. Press ENTER

The Watch window opens (if not already open) and displays the entry.
You can add the same variable from different scope levels (module vs.
procedure) — each displays independently.

### Example: Fibonacci Function

```basic
DEFINT A-Z
INPUT n
PRINT Fib(n)
END

FUNCTION Fib(n)
    IF n > 2 THEN
        Fib = Fib(n - 1) + Fib(n - 2)
    ELSE
        Fib = n
    END IF
END FUNCTION
```

Add `n` at module level and inside the Fib procedure. With Trace On,
watch how n changes as the function recursively calls itself.

## 18.2  Instant Watch Command

Displays the current value of a variable or expression in a dialog box.

1. Place cursor on (or select) a variable/expression
2. Choose Debug > Instant Watch (or press SHIFT+F9)
3. Dialog shows the variable and its current value
4. Click "Add Watch" to promote to the Watch window, or Cancel

Values: Numeric values shown as numbers. Boolean expressions shown as
-1 (true) or 0 (false).

## 18.3  Watchpoint Command (Full Menus Only)

Sets a conditional breakpoint. Execution pauses when the specified
expression becomes true.

1. Choose Debug > Watchpoint
2. Enter a Boolean expression (e.g., `COLORVAL = 10`)
3. Press ENTER

The expression appears in the Watch window. Execution breaks when
the expression evaluates to true (non-zero).

## 18.4  Delete Watch Command

Removes a variable or expression from the Watch window.

1. Choose Debug > Delete Watch
2. Select the entry to remove from the list
3. Press ENTER

When all entries are removed, the Watch window closes.

## 18.5  Delete All Watch Command (Full Menus Only)

Removes all entries from the Watch window at once and closes it.

## 18.6  Trace On Command (Full Menus Only)

Toggles statement tracing. When on, each statement is highlighted
as it executes, showing program flow visually.

Trace On can be used with the Watch window to see values change
as each statement runs.

## 18.7  History On Command (Full Menus Only)

Records the execution path so you can step backwards through it.

### 18.7.1  History Back

Step backwards through previously executed statements.
Shows which statements executed in what order.

### 18.7.2  History Forward

After stepping backwards, step forward through the recorded history.

## 18.8  Toggle Breakpoint Command

Sets or clears a breakpoint on the current line.

Shortcut: F9

Breakpoint lines are highlighted differently (configurable via
Options > Display command).

## 18.9  Clear All Breakpoints Command

Removes all breakpoints from the program at once.

## 18.10  Break on Errors Command (Full Menus Only)

When enabled, QuickBASIC breaks into the debugger on any error,
even if the program has an ON ERROR GOTO handler. Useful for
diagnosing errors that are being trapped.

## 18.11  Set Next Statement Command

Changes which statement will execute next. Move the cursor to
a line and choose this command to redirect execution flow.

Use cases:
- Skip over a problematic section
- Re-execute a section with different variable values
- Test error handlers
