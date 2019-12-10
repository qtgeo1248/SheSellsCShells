#include "shells.h"

int main() {
    char y = 0;
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
            strcpy(token, strsep(&input, ";"));
            token[strlen(token)-1] = '\0';
            input++;
          //  printf("%s + %sEND\n", input, token);
            char **args = parse_args(token, length);
          //  printf("T%s\n", token);
            if (strcmp(args[0], "cd") == 0) {
                if (*length == 0) {
                    chdir("/");
                } else {
                    chdir(args[*length]);
                }
            } else if (strchr(token, '>') != NULL) {
                int fd = open(args[*length - 1], O_RDWR);
                int backup = dup(1);
                dup2(3, 1);
                int i = strchr(token, '>');
                for (; i < *length; i++) {
                    args[i] = '\0';
                }
                execvp(args[0], args);
                dup2(backup, 1);
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
        //printf("T%d\n", strchr(input, '>') != NULL);
        //printf("%s\n", input);
        char temp[1000];
        strcpy(temp, input);
        char **args = parse_args(input, length);
        //printf("Bs%s\n", args[0]);
        //printf("T%d\n", strchr(temp, '>') != NULL);
        if (strcmp(args[0], "cd") == 0) {
            if (*length == 0) {
                chdir("/");
            } else {
                chdir(args[*length]);
            }
        } else if (strchr(temp, '>') != NULL) {
          //  printf("File %s\n", args[*length]);
          //  umask(0);
            int fd = open(args[*length], O_RDWR | O_CREAT, 0640);
          //  printf("FD: %s\n", strerror(errno));
            int backup = dup(1);
            dup2(3, 1);
            int boo = 0;
            int count = 0;

            for (; count < *length; count++) {
            //  printf("ThingT %d %d \n", count, *args[count] == '>');
              if (*args[count] == '>') {
                boo = 1;
              }
              if (boo == 1) {
                args[count] = '\0';
              }
            }
          //  printf("Thing %s \n", args[1]);
            int f = fork();
            if (f) {
                wait(status);
            } else {
                execvp(args[0], args);
            }

            dup2(backup, 1);
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
