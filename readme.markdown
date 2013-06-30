rpnCalculator
=============

A simple RPN calculator using a 16 button keypad and a 8 digit, seven segment LED dislay.

TODONE
------
- four functions ( + - * / ) integer math
- display of positive integers
- keypad and display

TODO
----
- display of negative integers
- function key for extended operations
- extended functions: decimal point, square, square root, multiplicative inverse, additive inverse, power
- store stack on shutdown
- power saving auto-shutoff
- stack operations: rotate down, swap x-y
- view/scroll stack
- floating point math (easy but needs decimal point 'function' key)
- floating point display optimization
- display brightness control

PIE-IN-THE-SKY
--------------
- memory: STO and RCL registers
- trig functions? (I very rarely use these)
- logarithms? (I very rarely use these either)
- scientific entry (exponent/mantissa)
- constants: pi, e
- base modes (hex, bin, dec)
- programming/macro support

In general, the code needs some refactoring.  It also suffers from the "everything is in one big file" disease that most Arduino projects seems to catch.  Both of these are due to the prototyping nature and organic growth pattern of the project.




