#include "shells.h"

int main() {
    char *test;
    int *status;
    char buf[1000] = "\0";
    while (strcmp(buf, "exit") != 0) {
        printf("$ ");
        fgets(buf, 1000, stdin);
        buf[strlen(buf) - 1] = 0;
        test = buf;
        char **args = parse_args(test);
        int f = fork();
        if (f) {
            wait(status);
        } else {
            execvp(args[0], args);
        }
        //free_args(args);
    }
    return 0;
}
