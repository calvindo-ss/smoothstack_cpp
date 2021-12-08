# Assignments

## 1. Working with types
Write a program that takes as input a type such as "int", "double" and "char" using cin, and your program computes the size of that type and outputs the size using cout. So for instance, the sizeof(int) may print as 4.

## 2. C++ type ideosynracies
Point out the limitations of your solution? Compare it with other programming languages you are aware of. 
(200 words max).

One of the first limitations of my solution is that when checking for the size of an int and I input a float, the program will ignore the values after the decimal point. For example, if I input "1.5", my program will only see a value of "1" and ignore the "0.5. That means even if I input a float value, the sizeof the input will always be 4 instead of 8. On the other hand, Python would evaluate the sizeof(1.5) to the correct 8 bytes. This is due to the fact that C++ uses explicit variables and Python uses implicit variables.

## 3. C++ Debugging
What C++ compiler option you need to use to make your C++ program ready for debugging?
You can use the https://linux.die.net/man/1/g++ for reference, and most g++ options are compatible with clang++.

For debugging in clang++, you would need to use the -g flag to see debugging information. Running "clang++ --help" says that the -g flag generates source-level debug information.

## 4. C++ Compiler Options
What C++ compiler option you need to use to suppress generating only object code and not final executable?

The "-S" flag will only run the presprocess and compilation steps, but will not create an executable.

## 5. Float Precision
How would you measure the precision of a floating point number? Write a program to demonstrate how the
precision decreases as a float gets larger.

C++ floats have a limitation of only 6 digits of precision. Any digits after the 6th will be rounded, and any other consequent digits will concatenated with "0". For example, pi, 3.1415926535, has 11 digits, if converted to a floating point number, only 3.14159 can be accurately represented. Any extra digits would look like 3.1415900000.