#include "shells.h"

//Note that the comments and functionalities of these
//functions are included in the README!!!

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

void changedir(char **args, int length) {
    if (length == 0) {
        if (chdir("/") != 0) {
            printf("[%d]: %s\n", errno, strerror(errno));
            errno = 0;
        }
    } else {
        if (chdir(args[length]) != 0) {
            printf("[%d]: %s\n", errno, strerror(errno));
            errno = 0;
        }
    }
}

int contains(char **args, int length, char *look) {
    int i = 0;
    for (; i < length && args[i]; i++) {
        if (strcmp(args[i], look) == 0) {
            return 1;
        }
    }
    return 0;
}

void redir_out(char **args, int length, int if_append) {
    char temp[1000];
    int i = 0;
    int stop = 1;
    for (; i < length && stop; i++) {
        if (strcmp(args[i], ">") == 0) {
            strcpy(temp, args[i + 1]);
            args[i] = NULL;
            stop = 0;
        } else if (strcmp(args[i], ">>") == 0) {
            strcpy(temp, args[i + 1]);
            args[i] = NULL;
            stop = 0;
        }
    }
    int fd;
    if (if_append) {
        fd = open(temp, O_RDWR | O_CREAT | O_APPEND, 0644);
        if (fd < 0) {
            printf("[%d]: %s\n", errno, strerror(errno));
            errno = 0;
        }
    } else {
        fd = open(temp, O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            printf("[%d]: %s\n", errno, strerror(errno));
            errno = 0;
        }
    }
    int backup = dup(STDOUT_FILENO);
    if (backup < 0) {
        printf("[%d]: %s\n", errno, strerror(errno));
        errno = 0;
    }
    if (dup2(fd, STDOUT_FILENO) < 0) {
        printf("[%d]: %s\n", errno, strerror(errno));
        errno = 0;
    }
    if (close(fd) < 0) {
        printf("[%d]: %s\n", errno, strerror(errno));
        errno = 0;
    }
}

void redir_in(char **args, int length) {
    char temp[1000];
    int i = 0;
    int stop = 1;
    for (; i < length && stop; i++) {
        if (strcmp(args[i], "<") == 0) {
            strcpy(temp, args[i + 1]);
            args[i] = NULL;
            stop = 0;
        }
    }
    int fd = open(temp, O_RDONLY);
    if (fd < 0) {
        printf("[%d]: %s\n", errno, strerror(errno));
        errno = 0;
    }
    int backup = dup(STDIN_FILENO);
    if (backup < 0) {
        printf("[%d]: %s\n", errno, strerror(errno));
        errno = 0;
    }
    if (dup2(fd, STDIN_FILENO) < 0) {
        printf("[%d]: %s\n", errno, strerror(errno));
        errno = 0;
    }
    if (close(fd) < 0) {
        printf("[%d]: %s\n", errno, strerror(errno));
        errno = 0;
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
