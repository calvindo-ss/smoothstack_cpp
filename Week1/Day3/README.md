# Assignments

## 1. Arrays and vectors
Write a program that creates an array and converts it into a vector.

Allocate an array of 3 floats.
Initialize the array.
Create a vector.
Copy the elements of the array to the vector.
Print out the vector elements on a single line and then an EOL at the end.
Verify your result with the original array.

See array_vectors.cpp

## 2. Mixed arrays

### 2.1 Dissimilar arrays
How would you store elements of dissimilar type in an array? Write a program to demonstrate 
that you can store int and float in the same array without using struct, or any class type.

A quick and dirty way to store both ints and floats in a single array would be to convert them into a single data type, in this case a string. 

See dissimilar_arrays.cpp

### 2.2 Types in array
In the above example, once you have created the "mixed" array, is it possible to recognize the type
of each element automatically? If so, or if not, why? Show with a code example.

Converting ints and floats into strings allows both data types to be stored in a single array/vector. The issue with this hack is that it is much more difficult to identify the types of each element (int or float). In order to identify types, I use '.' as an identifier for floats and assume everything else is an int. However, this assumes all numbers with '.' is a float, ignoring double types. 

See dissimilar_arrays.cpp
