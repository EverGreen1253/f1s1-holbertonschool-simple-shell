#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "main.h"

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

char *strtrim(char *buffer)
{
        unsigned long len = strlen(buffer), newlen;
        int startpos = 0, endpos = 0, i, j, stop;
        char *temp, *trimmed;

        temp = malloc(len + 1);
        strcpy(temp, buffer);
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
                while (temp[j] != '\0')
                {
                        if (j >= startpos && j <= endpos)
                        {
                                trimmed[i] = temp[j];
                                i++;
                        }
                        j++;
                }
                trimmed[i] = '\0';

                /* printf("trimmed - %s, i - %d, trimmed length - %lu\n", trimmed, i, strlen(trimmed)); */

                free(temp);
                return trimmed;
        }
        free(temp);
        return NULL;
}

