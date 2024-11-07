This C program calculate the sum of N natural numbers using M processes. 

Execution Flow of the program:
1. The main program (referred to as the parent process) will initiate the creation of a child process, denoted as
child_1.
2. The parent process will pause its execution, awaiting the completion of child_1's tasks before it concludes its
own operation.
3. Within child_1, the fork() function will be called M times, utilizing a loop to generate M child processes.
4. Each child_1.i (ranging from child_1.1 to child_1.M) will invoke the given summation function to calculate a
partial sum. The implementation of the summation function is already provided in the assignment2.c file. It is
necessary to provide the starting and ending numbers of the range to be summed to the summation function.
To determine these values, utilize the given ith_part_start() and ith_part_end() functions.
5. Each child_1.i (child_1.1 to child_1.M) will write the partial sum to a pipe.
6. Upon the completion of all M child processes, child_1 will gather the partial sums by reading from the pipe
and compute the total sum.
7. Subsequently, child_1 will display the total sum and conclude its own execution.
8. Finally, the parent process will conclude its own execution as well.
Variables N, M must be passed to the main program as a command line argument (hint: utilize argc and argv).
Implementation of summation(), ith_part_start() and ith_part_end() is already provided.
Constraints:

11 ≤ MM ≤ 1111
11 ≤ NN ≤ 11110
   
Functions used: fork(), wait(), getpid(), getppid(), pipe()

Example:
sample Input:

<li>N = 12</li>
<li>M = 5</li>


The output of the program is in the following format and sequence:
<li>parent(PID 7056): process started</li>
<li>parent(PID 7056): forking child_1</li>
<li>parent(PID 7056): fork successful for child_1(PID 7061)
<li>parent(PID 7056): waiting for child_1(PID 7061) to complete
<li>child_1(PID 7061): process started from parent(PID 7056)
<li>child_1(PID 7061): forking child_1.1....child_1.5
<li>child_1.1(PID 7062): fork() successful
<li>child_1.1(PID 7062): partial sum: [0 - 1] = 1
<li>child_1.2(PID 7063): fork() successful  
<li>child_1.2(PID 7063): partial sum: [2 - 3] = 5
<li>child_1.3(PID 7064): fork() successful
<li>child_1.3(PID 7064): partial sum: [4 - 5] = 9
<li>child_1.4(PID 7065): fork() successful
<li>child_1.4(PID 7065): partial sum: [6 - 7] = 13
<li>child_1.5(PID 7066): fork() successful
<li>child_1.5(PID 7066): partial sum: [8 - 12] = 50
<li>child_1(PID 7061): total sum = 78
<li>child_1(PID 7061): child_1 completed
<li>parent(PID 7056): parent completed  
  
Note that the output will change depending on the parameter passed (e.g., N, M) during the execution of the program.
