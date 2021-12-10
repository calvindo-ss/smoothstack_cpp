# Assignments

## 1. Arithmetic expressions
Exercise: Which of the following expressions will fail at runtime? Why? Why not?
#include <iostream>
#include <cassert>

using namespace std;

int main(void) {
    assert(3 == 3.0);
    x = 3.1;
    assert(x == 3.1);
    assert(3.1 == 3.1);
    assert(true == 1.0);
    assert('a' == 97);
    int* p = 0;
    assert(NULL == p);
    assert(NULL == 0);
}

"x = 3.1;" will throw an error at compile time because there is no declated type for x.
Consecuently, "assert(x == 3.1);" will throw an error at compile because x has no type.
If we assign "float x = 3.1" the program will then compile correctly. However the following line will fail because "float x = 3.1 != 3.1". Although unintutive, floats have rounding errors that make them imprecise. If we print out "float x = 3.1" and 3.1 with std::setprecision(20), we get the values 3.0999999046325683594 and 3.1000000000000000888 respectively.

## 2. Truth table for cast operators
Exercise: Generate a truth table for cast operators, when arithmetic operations are performed between two variables. For example int + float gives a float. Consider the types: int, float, char, bool

int | float | char | bool | int+int | int+float | int+char | int+bool | float+float | float+char | float+bool | char+char | char+bool | bool+bool
--- | --- | --- | --- |--- |--- |--- |--- |--- |--- |--- |--- |--- |---
int | float | char | bool | int | float | int | int | float | float | float | int | int | int

## 3. Operators
Exercise: List the binary, unary and ternary operators with examples

Unary operators work on a single operand. The Operators include ++, --, +, -, !, &, *. Some examples include:
````
#include <iostream>
#include <cassert>

int main(void) {
    int x = 0;
    int y = 10;
    
    x++;
    y--;

    assert(x == 1);
    assert(y == 9);
    
    -x;
    
    assert(x == -1);
 }
 ````

 Binary operators work on 2 operands, which include: +, -, *, /, ==, !=, <=, >=, <, >, &&, ||, +=, -=, *=, /=, %, %=. Some examples of these operators:

```
#include <iostream>
#include <cassert>

int main(void) {
    int x = 0;
    int y = 10;

    assert(x != y);

    x += 1;
    y-=5;

    assert(x+y == 6 && x > 0);
 }
```

Ternary operators take 3 operands and have the format "condition ? true : false;"

```
#include <iostream>
#include <cassert>

int main(void) {
    int a = 3;
    int b = 6;

    int i = (a<b) ? a : b;

    assert(i == a);
 }
```

## 4. Increment Operators
Exercise: Will below program work with no errors? Why?
 #include <cassert>
  
 int main(void) {
    int x = 4;
    int y = x+++2;

    assert(y == 6);
    assert(x == 5);
 }

What is the order of precedence of operators above when y is initialized to x+++2?

Yes, the program will run without any errors. This is due to x++ having a post increment. y = x+++2 would actually look like y=(x++)+2 where x+2 would evaluate first. Then x++ whould evaluate to 5.

## 5. More truth tables
Implement the truth table for AND, OR and NOT operators.

x | y | (x&&y) | (x\|\|y) | (~x) | (~y)
--- | --- | --- | --- |--- |---
true | true | true | true | false | false 
true | false | false | true | false | true 
false | true | false| true | true | false 
false | false | false | false | true | true 

