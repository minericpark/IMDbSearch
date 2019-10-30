#include "name.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct name_basics get_name (char *path) {

    char *fullPath = NULL;
    strcpy(fullPath, path);
    strcat(fullPath, "/name.basics.tsv");
    printf ("%s\n", fullPath);

}