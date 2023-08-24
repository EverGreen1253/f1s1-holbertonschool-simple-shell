#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	int i, j = -1, k;
	extern char** environ;
	char **argv;
	char *myvar = "My_VAR", *token, *temp;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", environ[i]);

		temp = malloc(strlen(env[i]) + 1);
		strcpy(temp, env[i]);

		token = strtok(temp, "=");
		if (strcmp(token, myvar) == 0)
		{
			// wanted var exists! Take note of its index.
			j = i;
		}
		i++;
		free(temp);
	}

	printf("\n\nJ value is: %d\n\n", j);


	// Oh no... we have to re-create the array.
	if (j != -1)
	{
		printf("\n\nnew array\n\n");

		// we're reducing the size of the env
		argv = malloc(sizeof(char *) * i);

		i = 0;
		k = 0;
		while (environ[i] != NULL)
		{
			if (i != j)
			{
				argv[k] = malloc(strlen(environ[i]) + 1);
				strcpy(argv[k], environ[i]);
				k++;
			}
			i++;
		}

		environ = argv;
	}

	printf("Printing Environ\n\n");

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

	printf("\n\nall done!\n");

	return (0);
}
