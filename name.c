#include "name.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct name_basics get_name (char *path) {

    struct name_basics test;
    char *fullPath;
    char tempLine[256];
    FILE *fp;

    test.nconst = (char *) 'n';
    test.primaryName = "test";
    fullPath = malloc(strlen(path) + 17);
    strcpy(fullPath, path);
    strcat(fullPath, "/name.basics.tsv");
    /*printf ("%s\n", fullPath);*/

    if ((fp = fopen(fullPath, "r+")) == NULL) {
        printf ("File not found.");
    }

    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {
        printf ("%s\n", tempLine);
    }

    return test;

}