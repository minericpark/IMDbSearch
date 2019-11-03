#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void) {

    struct name_root *testName;
    struct title_root *testTitle;
    struct principals_root *testPrincipals;
    struct title_basics *testTitleFind;
    struct name_basics *testNameFind;
    int testNameSize = 0;
    int testTitleSize = 0;
    int testPrincipalsSize = 0;
    int i =0;

    testName = get_name("fulldata");
    testNameSize = testName->numItems;
    printf ("size: %d\n", testNameSize);
    testTitle = get_title("fulldata");
    testTitleSize = testTitle->numItems;
    printf ("size: %d\n", testTitleSize);
    testPrincipals = get_principals("data");
    testPrincipalsSize = testPrincipals->numItems;
    printf ("size: %d\n", testPrincipalsSize);

    build_tindex(testTitle);

    testTitleFind = find_primary_title(testTitle, "Star Wars: Episode V - The Empire Strikes Back");

    printf ("%p\n", (void *)testTitleFind);
    printf ("%s\n", testTitleFind->tconst);
    printf ("%s\n", testTitleFind->primaryTitle);

    build_nindex(testName);

    testNameFind = find_primary_name(testName, "Anthony Daniels");

    printf ("%p\n", (void *)testNameFind);
    printf ("%s\n", testNameFind->nconst);
    printf ("%s\n", testNameFind->primaryName);

    printf ("%p\n", (void *)(testTitle->rootOne));
    printf ("%s\n", (testTitle->rootOne)->key);
    printf ("%p\n", (void *)(testTitle->rootOne)->data);
    printf ("%s\n", ((struct title_basics *)((testTitle->rootOne)->data))->primaryTitle);
    printf ("%s\n", ((struct title_basics *)((testTitle->rootOne)->data))->tconst);

    for (i = 0; i < 10; i++) {
        printf ("%s - %s\n", (testName->array)[i].nconst, (testName->array)[i].primaryName);
    }
    for (i = 0; i < 10; i++) {
        printf("%s - %s\n", (testTitle->array)[i].tconst, (testTitle->array)[i].primaryTitle);
    }
    for (i = 0; i < 10; i++) {
        printf ("%s - %s - %s\n", (testPrincipals->array)[i].tconst, (testPrincipals->array)[i].nconst, (testPrincipals->array)[i].characters);
    }

    for (i = 0; i < testNameSize; i++) {
        free((testName->array)[i].nconst);
        free((testName->array)[i].primaryName);
    }
    free(testName->array);
    free(testName);

    for (i = 0; i < testTitleSize; i++) {
        free((testTitle->array)[i].tconst);
        free((testTitle->array)[i].primaryTitle);
    }
    free(testTitle->array);
    free(testTitle);

    for (i = 0; i < testPrincipalsSize; i++) {
        free((testPrincipals->array)[i].tconst);
        free((testPrincipals->array)[i].nconst);
        free((testPrincipals->array)[i].characters);
    }
    free(testPrincipals->array);
    free(testPrincipals);

    return 0;
}