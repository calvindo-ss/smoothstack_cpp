# Assignment 1

Im my race condition programs, I have set the simulation to calculate the hailstone sequence to an index of 20. In the race condition program, it often calculates extra numbers or the calculations are repeated/out of order. This is due to the "nums.size() < 20" and "int last = nums.back();" not being locked. In the first instance, the size of the vector is not locked, meaning the size of the thread and change after a thread reads the data. The second instance, the last index of the vector is also not locked, allowing another thread to push_back the vector, altering the real last value of the vector.

The no_race_condition program fixes this by locking all aspects of the vector read/write, preventing uncontrolled modificataion of the vector from other threads.