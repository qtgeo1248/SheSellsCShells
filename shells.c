#include "shells.h"

char **parse_args(char *line, int *length, char *del) {
    char *token;
    char **tokens;
    tokens = malloc(sizeof(char*) * 10);
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
  int *status;
  int fd = open(args[*length], O_RDWR | O_CREAT, 0644);
  int backup = dup(STDOUT_FILENO);
  //char temp[1000];
  dup2(fd, STDOUT_FILENO);
  int i = 0;
  for (; i < *length; i++) {
      if (strcmp(args[i], ">") == 0) {
      //    strcpy(temp, tokens[i+1]);
          args[i] = '\0';
      }
  }
  close(fd);
}

void redir_in(char **args, int *length) {
  int *status;
  int fd = open(args[*length], O_RDONLY);
  int backup = dup(STDIN_FILENO);
  dup2(fd, STDIN_FILENO);
  int i = 0;
  for (; i < *length; i++) {
    if (strcmp(args[i], "<") == 0) {
    //    strcpy(temp, tokens[i+1]);
        args[i] = '\0';
    }
  }
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
