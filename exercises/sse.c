#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
	char **argv;
	char *buffer = NULL, *token, *cmd;
	size_t bufsize = 255;
	size_t typed;
	int i = 0;

	printf("$ ");
	typed = getline(&buffer, &bufsize, stdin);
	// printf("%zu characters were read.\n", typed);
	// printf("You typed: %s",buffer);

	argv = malloc(sizeof(char *) * 9999);

	token = strtok(buffer, " ");
	// printf("Printing the words typed:\n");
	while (token != NULL)
	{
		// printf(" - %s\n", token);
		argv[i] = malloc(strlen(token) + 1);
		strcpy(argv[i], token);

		token = strtok(NULL, " ");
		i = i + 1;
	}
	argv[i] = NULL;

	argv = realloc(argv, sizeof(char *) * i);

	cmd = argv[0];
	cmd[strcspn(cmd, "\n")] = '\0';
	if (execve(cmd, argv, NULL) == -1)
	{
		perror("Error:");
	}

	return (0);
}
