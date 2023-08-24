#include <stdio.h>

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
    unsigned int i;
    extern char** environ;

    i = 0;
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }

    printf("\n\n");
    printf("Adress of ENV: %p\n", &*env);
    printf("Address of ENVIRON: %p\n", &*environ);

    return (0);
}
