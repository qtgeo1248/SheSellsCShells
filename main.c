#include "shells.h"

int main() {
    char *test;
    char buf[1000];
    printf("Please input a program (for example, \"ls -l -a\"):\n");
    fgets(buf, 1000, stdin);
    return 0;
}
