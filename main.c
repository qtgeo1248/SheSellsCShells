#include "shells.h"

int main() {
    int y = 0;
    char *input = &y;
    int *status;
    char token[1000] = "\0";
    int x = 0;
    int *length = &x;
    int *semicolons = &x;
    char dir[1000] = ".";
    char buf[1000] = "\0";
    while (strcmp(token, "exit") != 0 && strcmp(input, "exit") != 0) {
        getcwd(dir, 1000);
        printf("%s$ ", dir);
        fgets(buf, 1000, stdin);
        buf[strlen(buf) - 1] = 0;
        input = buf;
        //printf("%s\n", input);
        while (strchr(input, ';') != NULL) {
        //  printf("Yah%s\n", input);
          strcpy(token, strsep(&input, " ; "));
        //  printf("%s\n", input);
          char **args = parse_args(token, length);

          printf("T%s\n", token);
          if (strcmp(args[0], "cd") == 0) {
              if (*length == 0) {
                chdir("/");
              } else {
                chdir(args[*length]);
              }
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
        printf("T%s\n", input);
        char **args = parse_args(input, length);


        if (strcmp(args[0], "cd") == 0) {
            if (*length == 0) {
              chdir("/");
            } else {
              chdir(args[*length]);
            }
        } else {
            int f = fork();
            if (f) {
                wait(status);
            } else {
                execvp(args[0], args);
            }
        }

    }
    return 0;
}
