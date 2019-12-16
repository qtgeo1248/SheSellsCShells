#include "shells.h"

int main() {
    int x = 0; //some random filler int when we do addresses
    int *length = &x; //var for number of arguments in a command
    char input[1000]; //var for fgets input; the entire line the use inputs
    char dir[1000]; //var for bash prompt when we get the current directory
    int *status; //var for parent process when they wait()
    while (strcmp(input, "exit") != 0) {
        if (!getcwd(dir, 1000)) {
            printf("[%d]: %s\n", errno, strerror(errno));
            errno = 0;
        }
        printf("%s$ ", dir);
        if (!fgets(input, 1000, stdin)) {
            printf("[%d]: %s\n", errno, strerror(errno));
            errno = 0;
        }
        char **commands = parse_args(input, length, ";");
        int i = 0; // counter for number command prompts for loop
        while (commands[i] != NULL) {
            char temp[1000]; //var for the current command
            strcpy(temp, commands[i]);
            if (strcmp(commands[i], "exit") == 0) { //checks if you want to exit
                return 0;
            } else {
                int *len = &x;
                char *command = strip(commands[i]);
                char **args = parse_args(command, len, " ");
                if (strcmp(args[0], "cd") == 0) { //for cd
                    changedir(args, *len);
                } else if (strchr(temp, '<') != NULL || strchr(temp, '>') != NULL) { //for redirection
                    int temp_len = *len;
                    int f = fork(); //FORK
                    if (f) {
                        if (f < 0) { //errno stuff
                            printf("[%d]: %s\n", errno, strerror(errno));
                            errno = 0;
                        }
                        wait(status);
                    } else {
                        char g[3] = ">";
                        char l[3] = "<";
                        char gg[3] = ">>";
                        //The three if statements check which type(s) of redirection it is
                        if (contains(args, temp_len, g)) {
                            redir_out(args, temp_len, 0);
                        }
                        if (contains(args, temp_len, gg)) {
                            redir_out(args, temp_len, 1);
                        }
                        if (contains(args, temp_len, l)) {
                            redir_in(args, temp_len);
                        }
                        //then it executes the command, so when the stdin and stdout are
                        //correctly replaced, then it should do the redirection correctly
                        if (execvp(args[0], args) < 0) {
                            //errno stuff
                            printf("[%d]: %s\n", errno, strerror(errno));
                            errno = 0;
                        }
                    }
                } else if (strchr(temp, '|') != NULL) {
                    int f = fork(); //BORK BORK
                    if (f) {
                        if (f < 0) {
                            //errno stuff
                            printf("[%d]: %s\n", errno, strerror(errno));
                            errno = 0;
                        }
                        wait(status);
                    } else {
                        int *temp_len = &x;
                        char** thingies = parse_args(temp, temp_len, "|");
                        //this creates both sides of the pipe
                        FILE *pipe_in = popen(thingies[0], "r");
                        FILE *pipe_out = popen(thingies[1], "w");
                        char buf[1000];
                        while (fgets(buf, 1000, pipe_in)) {
                            //then it will feed stuff into the pipe for the
                            //other side to read
                            if (!fputs(buf, pipe_out)) {
                                //errno stuff
                                printf("[%d]: %s\n", errno, strerror(errno));
                                errno = 0;
                            }
                        }
                        pclose(pipe_out); //closing pipes
                        pclose(pipe_in);  //to be locked forever
                    }
                } else { //the case where there's nothing special
                    int f = fork(); //BARK BARK BARK
                    if (f) {
                        if (f < 0) {
                            printf("[%d]: %s\n", errno, strerror(errno));
                            errno = 0;
                        }
                        wait(status);
                    } else {
                        if (execvp(args[0], args) < 0 && strcmp("exit", args[0]) != 0) {
                            //errno stuff
                            printf("[%d]: %s\n", errno, strerror(errno));
                            errno = 0;
                        }
                    }
                }
            }
            i++;
        }
    }
    return 0;
}
