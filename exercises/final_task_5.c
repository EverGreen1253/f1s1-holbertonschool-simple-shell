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
	unsigned int i;
	int j = -1;
	extern char** environ;
	char **argv;
	char *myvar = "MY_VAR", *myvalue = "MYVALUE", *token, *temp, *final = "";

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", environ[i]);

		temp = malloc(strlen(env[i]) + 1);
		strcpy(temp, env[i]);

		token = strtok(temp, "=");
		if (strcmp(token, myvar) == 0)
		{
			final = malloc(strlen(token) + strlen("=") +  strlen(myvalue) + 1);

			strcpy(final, token);
			strcat(final, "=");
			strcat(final, myvalue);
			env[i] = malloc(strlen(final) + 1);

			env[i] =  final;

			j = i;
		}
		i++;
		free(temp);
	}


	// Oh no... we have to re-create the array.
	if (j == -1)
	{
		printf("\n\nnew array\n\n");

		argv = malloc(sizeof(char *) * i + 1);

		i = 0;
		while (environ[i] != NULL)
		{
			argv[i] = malloc(strlen(environ[i]) + 1);
			strcpy(argv[i], environ[i]);

			i++;
		}

		argv[i] = malloc(strlen(myvar) + strlen("=") + strlen(myvalue) + 1);

		strcpy(argv[i], myvar);
		strcat(argv[i], "=");
		strcat(argv[i], myvalue);
		
		environ = argv;
		j = i;
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
