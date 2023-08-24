#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * main - Arguments task 1
 *
 * Return: Always 0.
 */
int main()
{
	char *buffer;
	size_t bufsize = 255;
	size_t typed;

	/*
	buffer = (char *)malloc(bufsize * sizeof(char));
	if(buffer == NULL)
	{
		printf("Unable to allocate buffer");
		exit(98);
	}
	*/

	printf("$ ");
	typed = getline(&buffer, &bufsize, stdin);
	printf("%zu characters were read.\n", typed);
	printf("You typed: %s",buffer);

	return (0);
}
