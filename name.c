#include "name.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct name_basics get_name (char *path) {

    struct name_basics test;
    char *fullPath;
    char *testString;
    char *actorString;
    char *actressString;
    char *checkRole;
    char tempLine[256];
    int numRole = 0;
    FILE *fp;

    test.nconst = (char *) 'n';
    test.primaryName = "test";

    fullPath = malloc(strlen(path) + 17);
    actorString = malloc(sizeof(char)*5 + 1);
    actressString = malloc(sizeof(char)*7 + 1);
    /*Complete file name*/
    strcpy(fullPath, path);
    strcat(fullPath, "/name.basics.tsv");
    strcpy(actorString, "actor");
    strcpy(actressString, "actress");
    /*printf ("%s\n", fullPath);*/

    if ((fp = fopen(fullPath, "r+")) == NULL) { /*Checks if file exists*/
        printf ("File not found.");
    }

    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {
        /*printf ("%s\n", tempLine);*/
        testString = malloc(sizeof(char) * 50 + 1);
        testString = get_column(tempLine, testString, 5);
        testString = realloc(testString, strlen(testString) + 1);

        checkRole = strstr(testString, actorString);
        if (checkRole) {
            printf ("%s\n", checkRole);
            numRole++;
        }
        else {
            checkRole = strstr(testString, actressString);
            if (checkRole) {
                printf ("%s\n", checkRole);
                numRole++;
            }
        }

        printf ("%s\n", testString);
        memset(testString, 0, strlen(testString));
        free(testString);
    }
    printf ("# of Actor/Actresses: %d\n", numRole);

    free(actorString);
    free(actressString);
    free(fullPath);
    free(fp);

    return test;

}

