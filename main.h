#ifndef MAIN_H
#define MAIN_H

int count_cmd_line_params(char *buffer, char *delim);
char **populate_argv_array(int count, char *buffer, char *delim);
char *strtrim(char *s);
void _setenv(char **env, char *myvar, char *myvalue);
char *_getenv(char **env, char *name);
char *_exists(char *paths, char *input);

#endif
