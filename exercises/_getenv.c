#include <stdio.h>
#include <string.h>

char *_getenv(const char *name);

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	char *s, *token;
	int i = 0;

	s = _getenv("PATH");

	printf("Contents of PATH: %s\n", s);

	token = strtok(s, ":");
	while (token != NULL)
	{
		printf(" - %s\n", token);

		i = i + 1;
		token = strtok(NULL, ":");
	}

	return (0);
}

char *_getenv(const char *name)
{
	int i = 0;
	extern char** environ;
	char *token;

	while (environ[i] != NULL)
	{
		//printf("%s\n", environ[i]);
		token = strtok(environ[i], "=");

		//printf("%s - %s\n", token, name);

		if (strcmp(token, name) == 0)
		{
			// printf("%s - %s\n", token, name);

			token = strtok(NULL, "=");
			return token;
		}

		token = strtok(NULL, "=");
		i++;
	}

	return NULL;
}
