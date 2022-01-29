# Assignment

## Best and worst case complexities

The best case would occur if the predicate is found early in the vector, allowing the algorithm to return false quickly.

The worst case would occur if the word is not found in the vector, forcing the algorithm to iterate through the entire vector to return true.

## Implement a parallel any_of algorithm

Use first principles to implement your own parallel any_of algorithm. (As opposed to
using the std::any_of with a parallel execution policy).

The paradigm will be similar to the parallel find() algorithm where you exit early
as soon as at least one element in an STL container satisfies the predicate.
Checks if unary predicate returns true for at least one element in the range [first, last).

So you will need to check if at least one of them satisfies the predicate. And exit 
early when a predicate is satisfied.

Write the best and worse case complexities.

## Implement an async none_of algorithm

Use first principles to implement your own parallel none_of algorithm. (As opposed to
using the std::none_of with a parallel execution policy).

The paradigm will be similar to the parallel find() algorithm where you exit early
as soon as at least one element in an STL container satisfies the predicate.
Checks if unary predicate returns true for no elements in the range [first, last).

So if you wanted to make sure that none of the elements satisfy the predicate, then you only
need to find one element that satisfies the predicate.

Write the best and worse case complexities.