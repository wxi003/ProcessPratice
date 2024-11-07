#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int summation(int start, int end)
{
	int sum = 0;
	if (start < end)
	{
		sum = ((end * (end + 1)) - (start * (start - 1))) / 2;
	}
	return sum;
}

int ith_part_start(int i, int N, int M)
{
	int part_size = N / M;
	int start = i * part_size;
	return start;
}
int ith_part_end(int i, int N, int M)
{
	int part_size = N / M;
	int end = (i < M - 1) ? ((i + 1) * part_size - 1) : N;
	return end;
}
int main(int argc, char **argv)
{
	int port[2];
	pid_t parent, child_1;

	int N = atoi(argv[1]); // command line argument N
	int M = atoi(argv[2]); // command line argument M
	int total_sum = 0;
	int partial_sum = 0;

	if (N < 1 || N > 100)
	{ // 1 <= N <= 100
		printf("The first input number is too large or too small, please type in another number in [1, 100]\n");
		return 0;
	}

	if (M < 1 || M > 10)
	{ // 1 <= M <= 10
		printf("The second input number is too large or too small, please type in another number in [1, 10]\n");
		return 0;
	}

	if (pipe(port) < 0)
	{
		perror("pipe error");
		exit(-1);
	}

	parent = getpid();
	printf("parent(PID %d): process started\n\n", parent);
	printf("parent(PID %d): forking child_1\n", parent);

	child_1 = fork(); // create child 1

	if (child_1 > 0)
	{ // parent process
		printf("parent(PID %d): fork successful for child_1(PID %d)\n", parent, child_1);
		printf("parent(PID %d): waiting for child_1(PID %d) to complete\n", parent, child_1);
		printf("\n");
		wait(NULL); // wait until child_1 proess is completed

		printf("parent(PID %d): parent completed\n", getpid());
	}
	else if (child_1 == 0)
	{ // child_1 process

		printf("child_1(PID %d): process started from parent(PID %d)\n", getpid(), getppid());
		printf("child_1(PID %d): forking child_1.1....child_1.%d\n\n", getpid(), M);

		for (int i = 0; i < M; i++)
		{
			if (fork() == 0) // child_1's children process
			{
				int start = ith_part_start(i, N, M);
				int end = ith_part_end(i, N, M);
				partial_sum = summation(start, end);

				write(port[1], &partial_sum, sizeof(partial_sum)); // each child write a partial sum on pipe

				printf("child_1.%d(PID %d): fork() successful\n", i + 1, getpid());
				printf("child_1.%d(PID %d): partial sum: [%d - %d] = %d\n", i + 1, getpid(), start, end, partial_sum);

				exit(0);
			}
			wait(NULL); // under child_1 process
						// wait for its child process to complete every time
		}

		for (int i = 0; i < M; i++) //  read the partial sums and calculate the total sum
		{
			read(port[0], &partial_sum, sizeof(partial_sum));
			total_sum += partial_sum;
		}

		printf("\nchild_1(PID %d): total sum = %d\n", getpid(), total_sum);
		printf("child_1(PID %d): child_1 completed\n\n", getpid());
	}
	else
	{
		printf("fork unsuccessful");
		exit(1); // fork unsuccessful
	}
}
