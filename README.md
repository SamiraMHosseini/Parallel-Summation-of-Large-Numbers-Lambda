# Effective multi-threaded summation of large numbers
This is a program for parallelizing the calculation of the sum of large numbers using multiple threads. 
The program divides the range of numbers to be summed into smaller segments and assigns each segment to a separate thread for processing.
The individual thread results are then combined to obtain the final sum. This approach speeds up the calculation of the sum, especially for large input ranges,
by utilizing multiple CPU cores in parallel.


