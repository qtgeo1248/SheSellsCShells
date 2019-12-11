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
    char ** commands = parse_args(input, length, ";");
    int i = 0; // counter for prompts for loop
    for (; i <= *length && commands[i] != NULL; i++) {
    //  printf("Com: %sEND\n", commands[i]);
      if (strcmp(commands[i], "exit") == 0) {
        return 0;
      } else {
        int *len = &x;
        char *command = strip(commands[i]);
        char **args = parse_args(command, len, " ");
      //  printf("Arg[0]: %sEND\n", args[0]);
        // cd
        if (strcmp(args[0], "cd") == 0) {
          changedir(args, len);
        } else if (strchr(command, '<') != NULL || strchr(command, '>') != NULL) {
          // redirection
          if (strchr(command, '<') != NULL) {
            redir_out(args, len);
          } else {
            redir_in(args,len);
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
    }
  }
  return 0;
}

/*
int main1() {
    char y = 0;
    char *input = &y;
    int *status;
    char token[1000] = "\0";
    int x = 0;
    int *length = &x;
    int *semicolons = &x;
    char dir[1000] = ".";
    char buf[1000] = "\0";
    // WHILE NOT EXIT
    while (strcmp(token, "exit") != 0 && strcmp(input, "exit") != 0) {
        getcwd(dir, 1000);
        printf("%s$ ", dir);
        fgets(buf, 1000, stdin);
        buf[strlen(buf) - 1] = 0;
        input = buf;
        // SEMICOLON
        while (strchr(input, ';') != NULL) {
            strcpy(token, strsep(&input, ";"));
            token[strlen(token) - 1] = '\0';
            input++;
            char **args = parse_args(token, length);
            if (strcmp(args[0], "cd") == 0) {
                if (*length == 0) {
                    chdir("/");
                } else {
                    chdir(args[*length]);
                }
            } else if (strchr(token, '>') != NULL || strchr(token, '<') != NULL) {
                if (strchr(token, '>') != NULL) {
                    int fd = open(args[*length], O_RDWR | O_CREAT, 0640);
                    int backup = dup(1);
                    dup2(fd, 1);
                    int boo = 0;
                    int i = 0;
                    for (; i < *length; i++) {
                        if (strcmp(args[i], ">") == 0) {
                            boo = 1;
                        }
                        if (boo == 1) {
                            args[i] = NULL;
                        }
                    }
                    int f = fork();
                    if (f) {
                        wait(status);
                    } else {
                        execvp(args[0], args);
                    }
                    dup2(backup, 1);
                    close(fd);
                } else {
                    int fd = open(args[*length], O_RDONLY);
                    int backup = dup(0);
                    dup2(fd, 0);
                    int boo = 0;
                    int i = 0;
                    for (; i < *length; i++) {
                        if (strcmp(args[i], "<") == 0) {
                            boo = 1;
                        }
                        if (boo == 1) {
                            args[i] = NULL;
                        }
                    }
                    int f = fork();
                    if (f) {
                        wait(status);
                    } else {
                        execvp(args[0], args);
                    }
                    dup2(backup, 0);
                    close(fd);
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
        char temp[1000];
        strcpy(temp, input);
        char **args = parse_args(input, length);
        if (strcmp(args[0], "cd") == 0) {
            if (*length == 0) {
                chdir("/");
            } else {
                chdir(args[*length]);
            }
        } else if (strchr(temp, '>') != NULL || strchr(temp, '<') != NULL) {
            if (strchr(temp, '>') != NULL) {
                int fd = open(args[*length], O_RDWR | O_CREAT, 0640);
                int backup = dup(1);
                dup2(fd, 1);
                int boo = 0;
                int count = 0;
                for (; count < *length; count++) {
                    if (*args[count] == '>') {
                        boo = 1;
                    }
                    if (boo == 1) {
                        args[count] = NULL;
                    }
                }
                int f = fork();
                if (f) {
                    wait(status);
                } else {
                    execvp(args[0], args);
                }
                dup2(backup, 1);
                close(fd);
            } else {
                int fd = open(args[*length], O_RDONLY);
                int backup = dup(0);
                dup2(fd, 0);
                int boo = 0;
                int i = 0;
                for (; i < *length; i++) {
                    if (strcmp(args[i], "<") == 0) {
                        boo = 1;
                    }
                    if (boo == 1) {
                        args[i] = NULL;
                    }
                }
                int f = fork();
                if (f) {
                    wait(status);
                } else {
                    execvp(args[0], args);
                }
                dup2(backup, 0);
                close(fd);
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
}*/
