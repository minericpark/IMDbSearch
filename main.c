#include "name.h"
#include "title.h"
#include "principals.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void) {

    struct name_basics *testName;
    struct title_basics *testTitle;
    struct title_principals *testPrincipals;
    int i =0;

    testName = get_name("fulldata");
    testTitle = get_title("fulldata");
    testPrincipals = get_principals("fulldata");

    for (i = 0; i < 10; i++) {
        printf ("%s - %s\n", testName[i].nconst, testName[i].primaryName);
    }
    /*
    for (i = 0; i < 355; i++) {
        free(testName[i].nconst);
        free(testName[i].primaryName);
    }
    free(testName);
*/
    for (i = 0; i < 10; i++) {
        printf ("%s - %s\n", testTitle[i].tconst, testTitle[i].primaryTitle);
    }/*
    for (i = 0; i < 355; i++) {
        free(testTitle[i].tconst);
        free(testTitle[i].primaryTitle);
    }
    free(testTitle);*/

    for (i = 0; i < 10; i++) {
        printf ("%s - %s - %s\n", testPrincipals[i].tconst, testPrincipals[i].nconst, testPrincipals[i].characters);
    }

    return 0;
}