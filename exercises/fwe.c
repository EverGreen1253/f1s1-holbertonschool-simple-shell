#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * main - fork & wait example
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	int status;
	int count = 5;

	while (count > 0)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}

		if (child_pid == 0)
		{
			printf("Child process %d started\n", (5 - count + 1));
			exit(0);
		}

		count = count - 1;
	}

	count = 5;

	while (count > 0)
	{
		wait(&status);
		count = count - 1;
	}

	printf("All done now");

	return (0);
}

