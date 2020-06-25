Threads

1) A thread is created using the syntax std::thread t() wherein thread t needs a callable object to perform a task.
2) We wait for the thread object t to finish execution by calling join() function.
3) Race condition: situation where two or more threads/processes race to change a common data at the same time.
4) Mutex (Mutual Exclusion) can be used to avoid race condition on the critical region/section.

OpenMP

--Specify the block to be executed in parallel
#pragma omp parallel
--Specify number of threads
$ export OMP_NUM_THREADS=4




