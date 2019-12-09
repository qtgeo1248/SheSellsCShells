#include "shells.h"
int main() {
    char *test;
    int *status;
    int x = 0;
    int *length = &x;
    char dir[1000] = ".";
    char buf[1000] = "\0";
    while (strcmp(buf, "exit") != 0) {
        getcwd(dir, 1000);
        printf("%s $ ", dir);
        fgets(buf, 1000, stdin);
        buf[strlen(buf) - 1] = 0;
        test = buf;
        char **args = parse_args(test, length);
        if (strcmp(args[0], "cd") == 0) {
            chdir(args[*length]);
        } else {
            int f = fork();
            if (f) {
                wait(status);
            } else {
                execvp(args[0], args);
            }
        }
        //free_args(args);
    }
    return 0;
}
