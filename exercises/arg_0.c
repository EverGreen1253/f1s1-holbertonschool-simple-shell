#include <stdio.h>
#include <unistd.h>

/**
 * main - Arguments task 0
 * @ac: argc
 * @av: argv
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	int i = 0;

	while(av[i])
	{
		printf("%s\n", av[i]);
		i = i + 1;
	}
	return (0);
}
