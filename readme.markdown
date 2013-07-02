rpnCalculator
=============

A simple RPN calculator using a 16 button keypad and a 8 digit, seven segment LED dislay.

TODONE
------
- four functions ( + - * / ) integer math
- display of positive integers
- display of negative integers
- keypad and display

TODO
----
- function key for extended operations
- extended functions: decimal point, square, square root, multiplicative inverse, additive inverse, power
- store stack on shutdown
- clear entry (clear entry is currently performed by entering eight zeros)
- backspace/rub digit (remove the last entered digit)
- power saving auto-shutoff
- stack operations: rotate down, swap x-y
- view/scroll stack
- floating point math (easy but needs decimal point 'function' key)
- floating point display optimization
- display brightness control

PIE-IN-THE-SKY
--------------
- memory: STO and RCL registers
- expansion slot: temperature sensor, wireless comms, real time clock; data shows up in 'STO/RCL' registers
- trig functions? (I very rarely use these)
- logarithms? (I very rarely use these either)
- scientific entry (exponent/mantissa)
- constants: pi, e
- base modes (hex, bin, dec)
- programming/macro support

In general, the code needs some refactoring.  It also suffers from the "everything is in one big file" disease that most Arduino projects seems to catch.  Both of these are due to the prototyping nature and organic growth pattern of the project.

BUTTONS
-------
A guide to the buttons and their functions
- "0..9": enter appropriate digit
- "/ x - +": take appropriate mathematical operation on the top two items of the stack and put result on top of stack
- "E" (aka "Enter"): push displayed value down stack
- "F" (aka "Function" or "Fn"): activate function mode

FUNCTIONS
---------
- "Fn+E": clear entry
- "Fn+Fn": leave function mode
- "Fn+0": enter decimal point
- "Fn+1": square root
- "Fn+2": power
- "Fn+3": 
- "Fn+4":
- "Fn+5":
- "Fn+6":
- "Fn+7":
- "Fn+8": swap x-y
- "Fn+9": rotate stack downwards
- "Fn+\": multiplicative inverse
- "Fn+\*": square
- "Fn+-": additive inverse
- "Fn++": backspace/rub last digit entered

