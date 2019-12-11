#include "shells.h"

char **parse_args(char *line, int *length, char *del) {
    char *token;
    char **tokens;
    tokens = malloc(sizeof(char*) * 5);
    int i = 0;
    while (line != NULL) {
        token = strsep(&line, del);
        tokens[i] = token;
        i++;
    }
    tokens[i] = 0;
    *length = i - 1;
    return tokens;
}

void changedir(char **args, int *length) {
  if (*length == 0) {
      chdir("/");
  } else {
      chdir(args[*length]);
  }
}

void redir_out(char **args, int *length) {
  printf("TRIGGERED-1 %s\n", args[*length]);
  int *status;
  int fd = open(args[*length], O_RDWR | O_CREAT, 0640);
  printf("TRIGGERED-1 %s\n", args[*length]);
  int backup = dup(1);
  printf("TRIGGERED-1 %s\n", args[*length]);
  dup2(fd, 1);
  printf("TRIGGERED-1 %s\n", args[*length]);
  int boo = 0; // boolean check
  int i = 0;
  for (; i < *length; i++) {
      if (strcmp(args[i], ">") == 0) {
          boo = 1;
      }
      if (boo == 1) {
          args[i] = '\0';
      }
  }
  printf("TRIGGERED\n");
  int f = fork();
  if (f) {
      wait(status);
  } else {
      execvp(args[0], args);
  }
  dup2(backup, 1);
  close(fd);
}

void redir_in(char **args, int *length) {
  int *status;
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

void free_args(char **args) {
    int i = 0;
    for (; args[i] != NULL; i++) {
        free(args[i]);
    }
}

char *strip(char *line) {
  int index = strlen(line) - 1;
  line[index] = '\0';
  if (line[0] == '\n' || line[0] == ' ') {
    line++;
  }
  return line;
}
