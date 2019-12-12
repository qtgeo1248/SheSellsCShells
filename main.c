#include "shells.h"

int main() {
    int x = 0; // filler int
    int *length = &x;
    char input[1000]; // fgets input
    char dir[1000]; // bash prompt
    int *status; // for parent process
    while (strcmp(input, "exit") != 0) {
        getcwd(dir, 1000);
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
                    if (f) {
                        wait(status);
                    } else {
                        if (strchr(temp, '>') != NULL) {
                            redir_out(args, temp_len);
                        }
                        if (strchr(temp, '<') != NULL) {
                            redir_in(args, temp_len);
                        }
                        execvp(args[0], args);
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
