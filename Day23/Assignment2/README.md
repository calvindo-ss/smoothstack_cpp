# Assignment 1

In both my programs, currency trading is set to simulate for 10 seconds. However, in the deadlock program, the simulation would hang indefinately (longer than 10 seconds) and would not print to the terminal the final currencies of the 2 countries or successfully terminate the program. The source of the deadlock was the 2 threads fighing to lock either the trade() or c_request() methods.

I was able to fix the deadlock with the use of std::lock to lock the mutex's of both Country objects. The prevented the possibility of a deadlock and allowed the simulation of all transactions to occur without hanging. The program now reliably prints out the final currencies of each country and successfully exits after 10 seconds of simulation have elapsed.