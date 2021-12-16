# Assignment

## 1. Fibonacci series and recursion
Write a program to generate an array of 50 Fibonacci terms of type int recursively.
What problems did you encounter while computing this? At what point? How do you detect
the problem? Does your compute give an error?

Note: You must use recursion to solve this problem.

```
I encountered 2 problems. 

The first issue I encountered was compute time for index 35+. The program reached ~35 terms in less than 1 second, but the rest of the program took several minutes to finish computing. This is because the recursive function must return the sum of all values, it must calculate fib(i-1) and fib(i-2).

The second issue I ran into was that I originally used int to display the fibonacci numbers. However, at index 47, I ran into an issue where the fibonacci values exceeded int's 16 bit size and had an integer overflow into negative numbers. In order to fix this issue, I used long int to display the fibonacci numbers.

Overall, neither of these 2 issues gave an error. The first issue took exponentially longer to run and the second issue displayed bad values.
```

## 2. Integer overflow
2. Given a b-bit int (for int32, b = 31), how would you determine the index of the largest
Fibonacci term that you can fit in int32? Solve this without brute computing the Fibonacci series
above. Verify your answer for a long.

Note: The Fibonacci series goes 1, 1, 2, 3, 5, 8, 21,...... So 5 is the index for 8.

Hint: There is a closed-form expression for the n-th Fibonacci number, Binet's formula,

```
F(n) = (phi^n - psi^n) / (phi - psi)
```

where

```
phi = (1 + 5^0.5)/2 and psi = (1-phi) = -1/phi
```