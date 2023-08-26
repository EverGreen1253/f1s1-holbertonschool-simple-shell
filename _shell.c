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
	char *buftrimmed = NULL;
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

			/* clean up the buffer input and remove whitespace */
			buftrimmed = strtrim(buffer);
			if (buftrimmed == NULL)
			{
				/* printf("empty string!\n"); */
				free(buffer);
				free(buftrimmed);
				exit(0);
			}

			count = count_cmd_line_params(buftrimmed, " ");
			argv = populate_argv_array(count, buftrimmed, " ");

			pid = fork();
			if (pid < 0)
			{
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				/* printf("execute - %s\n", argv[0]); */
				execvp(argv[0], argv);

				/* if execvp returns, there was an error */
				perror("execvp");
				exit(EXIT_FAILURE);
			}

			i = 0;
			while(argv[i] != NULL)
			{
				/* printf("argv[%d] - %s\n", i, argv[i]); */
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

		count = count_cmd_line_params(buffer, " ");
		argv = populate_argv_array(count, buffer, " ");

		pid = fork();

		/* printf("pid is - %d\n", pid); */

		if (pid < 0)
		{
			/* handle error */
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (argv[0] != NULL && strlen(argv[0]) > 0)
			{
				execvp(argv[0], argv);
				/* if execvp returns, there was an error */
				perror("execvp");
				exit(EXIT_FAILURE);
			}
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

int count_cmd_line_params(char *buffer, char *delim)
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
	token = strtok(temp, delim);
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delim);
	}
	free(temp);

	/* printf("You typed: %s\n",buffer); */
	/* printf("count - %d\n", count); */

	return count;
}

char **populate_argv_array(int count, char *buffer, char *delim)
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

	token = strtok(buffer, delim);
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

		if (strlen(temp) != 0)
		{
			/* printf("temp - '%s'\n", temp); */
			argv[i] =  temp;

			i = i + 1;
		}
		else
		{
			free(temp);
		}

		token = strtok(NULL, delim);
	}
	argv[i] = NULL;

	return argv;
}

char *strtrim(char *s)
{
	unsigned long len = strlen(s), newlen;
	int startpos = 0, endpos = 0, i, j, stop;
	char *temp, *trimmed;

	temp = malloc(len + 1);
	strcpy(temp, s);
	temp[strcspn(temp, "\n")] = '\0';

	i = 0;
	stop = 0;
	while (temp[i] != '\0' && stop == 0)
	{
		if (temp[i] != ' ')
		{
			stop = 1;
		}

		i++;
	}
	startpos = i - 1;

	if (startpos == (int)(len - 2))
	{
		/* entire string is spaces */
		free(temp);
		return NULL;
	}

	i = (int)len;
	stop = 0;
	while (stop == 0)
	{
		if (temp[i] != ' ' && temp[i] != '\0')
		{
			stop = 1;
		}

		i--;
	}
	endpos = i + 1;

	/* printf("len - %lu, startpos - %d, endpos - %d\n", len, startpos, endpos); */

	newlen = endpos - startpos + 2;
	if (newlen > 0)
	{
		/* printf("newlen - %lu\n", newlen); */

		trimmed = malloc(newlen + 1);
		i = 0;
		j = 0;
		while (s[j] != '\0')
		{
			if (j >= startpos && j <= endpos)
			{
				trimmed[i] = s[j];
				i++;
			}
			j++;
		}
	}
	trimmed[i] = '\0';

	/* printf("trimmed - %s, i - %d, trimmed length - %lu\n", trimmed, i, strlen(trimmed)); */

	free(temp);
	return trimmed;
}
