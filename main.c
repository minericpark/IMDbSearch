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
    int testNameSize = 0;
    int testTitleSize = 0;
    int testPrincipalsSize = 0;
    int i =0;

    testName = get_name("fulldata");
    testNameSize = getBasicSize("fulldata");
    printf ("size: %d\n", testNameSize);
    testTitle = get_title("fulldata");
    testTitleSize = getTitleSize("fulldata");
    printf ("size: %d\n", testTitleSize);
    testPrincipals = get_principals("fulldata");
    testPrincipalsSize = getPrincipalsSize("fulldata");
    printf ("size: %d\n", testPrincipalsSize);

    for (i = 0; i < 10; i++) {
        printf ("%s - %s\n", testName[i].nconst, testName[i].primaryName);
    }
    for (i = 0; i < 10; i++) {
        printf("%s - %s\n", testTitle[i].tconst, testTitle[i].primaryTitle);
    }
    for (i = 0; i < 10; i++) {
        printf ("%s - %s - %s\n", testPrincipals[i].tconst, testPrincipals[i].nconst, testPrincipals[i].characters);
    }

    for (i = 0; i < testNameSize; i++) {
        free(testName[i].nconst);
        free(testName[i].primaryName);
    }
    free(testName);

    for (i = 0; i < testTitleSize; i++) {
        free(testTitle[i].tconst);
        free(testTitle[i].primaryTitle);
    }
    free(testTitle);

    for (i = 0; i < testPrincipalsSize; i++) {
        free(testPrincipals[i].tconst);
        free(testPrincipals[i].nconst);
        free(testPrincipals[i].characters);
    }
    free(testPrincipals);

    return 0;
}