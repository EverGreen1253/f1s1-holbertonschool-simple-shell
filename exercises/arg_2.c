#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - Arguments task 2
 *
 * Return: Always 0.
 */
int main()
{
	char *buffer, *token;
	size_t bufsize = 255;
	size_t typed;

	printf("$ ");
	typed = getline(&buffer, &bufsize, stdin);
	printf("%zu characters were read.\n", typed);
	printf("You typed: %s",buffer);

	token = strtok(buffer, " ");
	printf("Printing the words typed:\n");
	while (token != NULL)
	{
		printf(" - %s\n", token);

		token = strtok(NULL, " ");
	}

	return (0);
}
