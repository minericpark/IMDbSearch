#include "name.c"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() {

    struct name_basics test;

    printf ("Hello world");
    test = get_name("hello");
    return 0;
}