#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "main.h"


/**
 * main - simple shell! The big one!
 *
 * Return: Always 0.
 */
int main(void)
{
	int count = 0;
	char *buffer = NULL;
	size_t bufsize = 65535;
	size_t typed;
	char **argv = NULL;
	pid_t pid;

	while (1)
	{
		printf("$ ");

		typed = getline(&buffer, &bufsize, stdin);
		/* set a super large number in case -1 is returned */
		/* -1 will wrap around to the max unsigned long value */
		if (typed > 65535)
		{
			exit(0);
		}

		/* printf("%zu characters were read.\n", typed); */

		count = count_cmd_line_params(buffer);
		argv = populate_argv_array(count, buffer);

		pid = fork();
		if (pid < 0)
		{
			/* handle error */
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execvp(argv[0], argv);
			/* if execvp returns, there was an error */
			perror("execvp");
			exit(EXIT_FAILURE);
		}

		wait(NULL);
	}
	free(buffer);

	return (0);
}

int count_cmd_line_params(char *buffer)
{
	char *temp, *token;
	int count = 0;

	temp = malloc(strlen(buffer) + 1);
	if (temp == NULL)
	{
		free(temp);
		exit(98);
	}
	strcpy(temp, buffer);

	/* we count how many items there are first */
	token = strtok(temp, " ");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " ");
	}
	free(temp);

	/* printf("You typed: %s\n",buffer); */
	/* printf("count - %d\n", count); */

	return count;
}

char **populate_argv_array(int count, char *buffer)
{
	char **argv;
	char *temp, *token;
	int i = 0;

	/* let's load up the argv array */
	argv = malloc(sizeof(char *) * count + 1);
	if (argv == NULL)
	{
		free(argv);
		exit(98);
	}

	token = strtok(buffer, " ");
	while (token != NULL)
	{
		temp = malloc(strlen(token) + 1);
		if (temp == NULL)
		{
			free(temp);
			exit(98);
		}

		/* change the newline into a null character */
		strcpy(temp, token);
		temp[strcspn(temp, "\n")] = '\0';
		argv[i] =  temp;

		token = strtok(NULL, " ");
		i = i + 1;
	}
	argv[i] = NULL;

	return argv;
}


