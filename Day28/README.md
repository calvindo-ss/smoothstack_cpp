# Assignment

## Current issues

Currently, tranType prints out 1/0 instead of credit/debit. I need to print out the key, instead of the value of the enum.

## Write a Generator coroutine

Write a generator that generates random bank transaction data. Specifically you
will write a coroutine that generates structs of form:

```
struct transaction {
   long post_date; // post date of transaction
   std::string src_accountId;  // use UUIDs
   std::string dest_accountId;  // use UUIDs
   myenum tranType; // transaction type enum can be credit or debit
   double amount; // in dollars ranging [1..1000000]
   
}
```