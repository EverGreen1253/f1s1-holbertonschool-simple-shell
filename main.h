#ifndef MAIN_H
#define MAIN_H

int count_cmd_line_params(char *buffer, char *delim);
char **populate_argv_array(int count, char *buffer, char *delim);
char *strtrim(char *s);

#endif
