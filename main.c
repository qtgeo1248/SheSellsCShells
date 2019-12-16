#include "shells.h"

int main() {
    int x = 0; // filler int
    int *length = &x;
    char input[1000]; // fgets input
    char dir[1000]; // bash prompt
    int *status; // for parent process
    while (strcmp(input, "exit") != 0) {
        if (!getcwd(dir, 1000)) {
            printf("[%d]: %s\n", errno, strerror(errno));
            errno = 0;
        }
        printf("%s$ ", dir);
        fgets(input, 1000, stdin);
        char **commands = parse_args(input, length, ";");
        int i = 0; // counter for prompts for loop
        //  printf("TEST %s y%dy\n", commands[1], *length);
        while (commands[i] != NULL) {
            char temp[1000];
            strcpy(temp, commands[i]);
            //    printf("Com: %sEND\n", commands[i]);
            if (strcmp(commands[i], "exit") == 0) {
                return 0;
            } else {
                int *len = &x;
                char *command = strip(commands[i]);
                char **args = parse_args(command, len, " ");
                //    printf("Command: %sEND\n", commands[i]);
                //    printf("Arg[0]: %sEND\n", args[0]);
                //    cd
                if (strcmp(args[0], "cd") == 0) {
                    changedir(args, len);
                } else if (strchr(temp, '<') != NULL || strchr(temp, '>') != NULL) {
                    // redirection
                    int temp_len = *len + 1;
                    int f = fork();
                    if (f < 0) {
                        printf("[%d]: %s\n", errno, strerror(errno));
                        errno = 0;
                    } else if (f) {
                        wait(status);
                    } else {
                        char g[3] = ">";
                        char l[3] = "<";
                        char gg[3] = ">>";
                        if (contains(args, temp_len, g)) {
                            redir_out(args, temp_len, 0);
                        }
                        if (contains(args, temp_len, gg)) {
                            redir_out(args, temp_len, 1);
                        }
                        if (contains(args, temp_len, l)) {
                            redir_in(args, temp_len);
                        }
                        if (execvp(args[0], args) < 0) {
                            printf("[%d]: %s\n", errno, strerror(errno));
                            errno = 0;
                        }
                    }
                } else if (strchr(temp, '|') != NULL) {
                    int f = fork();
                    if (f) {
                        if (f < 0) {
                            printf("[%d]: %s\n", errno, strerror(errno));
                            errno = 0;
                        }
                        wait(status);
                    } else {
                        int *temp_len = &x;
                        char** thingies = parse_args(temp, temp_len, "|");
                        FILE *pipe_in = popen(thingies[0], "r");
                        FILE *pipe_out = popen(thingies[1], "w");
                        char buf[1000];
                        while (fgets(buf, 1000, pipe_in)) {
                            fputs(buf, pipe_out);
                        }
                        pclose(pipe_out);
                        pclose(pipe_in);
                    }
                } else { // nothing special
                //    printf("TRIGGERED\n");
                    int f = fork();
                    if (f) {
                        wait(status);
                    } else {
                    //    printf("TRIGGERED PT 2 \n");
                        execvp(args[0], args);
                    }
                }
            }
        //    printf("NEXT: %sEND\n", commands[i+1]);
            i++;
        }
    }
    return 0;
}
