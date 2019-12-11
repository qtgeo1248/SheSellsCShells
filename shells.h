#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

char **parse_args(char *line, int *length, char *del);
void changedir(char **args, int *length);
void redir_out(char **args, int *length);
void redir_in(char **args, int *length);
void free_args(char **args);
