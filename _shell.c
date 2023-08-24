#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "main.h"

char *buffer;

/**
 * handle_sigint - to free memory when the program is killed
 *
 * Return: nothing
 */
void handle_sigint(int signum)
{
	if (signum > 0)
	{
		free(buffer);
	}

	abort();
}

/**
 * main - simple shell! The big one!
 *
 * Return: Always 0.
 */
int main(void)
{
	int count = 0, tty = 1, i = 0;
	size_t input = 0;
	size_t bufsize = 4096;
	char **argv = NULL;
	pid_t pid;
	
	buffer = malloc(bufsize + 1);
	signal(SIGINT, handle_sigint);
	while(1)
	{
		tty = isatty(STDIN_FILENO);
		if (tty != 0)
		{
			printf("$ ");
		}

		input = getline(&buffer, &bufsize, stdin);
		if (input > bufsize)
		{
			exit(EXIT_SUCCESS);
		}

		/* printf("buffer - %s\n", buffer); */

		count = count_cmd_line_params(buffer);
		argv = populate_argv_array(count, buffer);
		free(buffer);

		pid = fork();

		/* printf("pid is - %d\n", pid); */

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

		i = 0;
		while(argv[i] != NULL)
		{
			free(argv[i]);
			i++;
		}
		free(argv);

		wait(NULL);
	}

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
	argv = malloc(sizeof(char *) * (count + 1));
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


