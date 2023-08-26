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
	exit(EXIT_SUCCESS);
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
	tty = isatty(STDIN_FILENO);

	/* handle the echo */
	if (tty == 0)
	{
		while ((input = getline(&buffer, &bufsize, stdin)) < bufsize)
		{
			/* printf("Retrieved line of length %lu :\n", input); */
			/* printf("%s", buffer); */

			argv = populate_argv_array(1, buffer);

			pid = fork();
			if (pid < 0)
			{
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				/* printf("execute - %s\n", argv[i]); */
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
	}

	/* handle user input */
	while(tty)
	{
		printf("$ ");

		input = getline(&buffer, &bufsize, stdin);
		if (input > bufsize)
		{
			exit(EXIT_SUCCESS);
		}

		/* printf("buffer - %s\n", buffer); */

		count = count_cmd_line_params(buffer);
		argv = populate_argv_array(count, buffer);

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

		strcpy(temp, token);
		/* change the newline into a null character */
		temp[strcspn(temp, "\n")] = '\0';

		/* temp = strtrim(temp); */

		if (strlen(temp) != 0)
		{
			printf("temp - '%s'\n", temp);
			argv[i] =  temp;

			i = i + 1;
		}
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;

	return argv;
}

