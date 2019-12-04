#include "shells.h"

char **parse_args(char *line, int *length) {
    char *token;
    char **tokens;
    tokens = malloc(sizeof(char*) * 5);
    int i = 0;

    while (line != NULL) {
        token = strsep(&line, " ");
        tokens[i] = token;
        i++;
    }
    tokens[i] = 0;
    *length = i - 1;
    return tokens;
}

void free_args(char **args) {
    int i = 0;
    for (; args[i] != NULL; i++) {
        free(args[i]);
    }
}
