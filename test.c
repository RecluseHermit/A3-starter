#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char* str = "I love you so much\n";
    char** test = &str;
    printf("%c", (*test)[2]);
}