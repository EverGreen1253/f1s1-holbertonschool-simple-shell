#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * _which - searching for a file in PATH folders
 *
 * Return: Always 0.
 */
int main(void) {

	char **argv;
	char *pathvar, *token;
	pathvar = getenv("PATH");
	int i = 0;
	char *cmd = "/ls", *final = "";
	struct stat st;

	argv = malloc(sizeof(char *) * 9999);

	token = strtok(pathvar, ":");
	while (token != NULL)
	{
		// need to allocate memory for final

		final = malloc(strlen(token) + strlen(cmd) + 1);
		strcpy(final, token);
		strcat(final, cmd);
		argv[i] = final;

		printf("Status of %s: ", argv[i]);
		if (stat(argv[i], &st) == 0)
	        {
			printf(" FOUND\n");
		}
		else
		{
			printf(" NOT FOUND\n");
		}

		i = i + 1;
		token = strtok(NULL, ":");
	}
	argv[i] = NULL;

	argv = realloc(argv, sizeof(char *) * i);

	//cmd = argv[0];
	//cmd[strcspn(cmd, "\n")] = '\0';

	return (0);
}
