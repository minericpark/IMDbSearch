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
    struct title_basics *testTitleFind2;
    struct name_basics *testNameFind;
    struct name_basics *testNameFind2;
    struct title_principals *testPrincipalsFind;
    struct title_principals *testPrincipalsFind2;

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
    testPrincipals = get_principals("fulldata");
    testPrincipalsSize = testPrincipals->numItems;
    printf ("size: %d\n", testPrincipalsSize);

    printf ("building root1 for testtitle\n");
    build_ptindex(testTitle);

    printf ("finding first index\n");
    testTitleFind = find_primary_title(testTitle, "Star Wars: Episode V - The Empire Strikes Back");

    printf ("%p\n", (void *)testTitleFind);
    printf ("%s\n", testTitleFind->tconst);
    printf ("%s\n", testTitleFind->primaryTitle);

    printf ("building root2 for testTitle\n");
    build_tindex(testTitle);

    printf ("finding next test\n");
    testTitleFind2 = find_tconst(testTitle, "4860800tt");

    printf ("%p\n", (void *)testTitleFind2);
    printf ("%s\n", testTitleFind2->tconst);
    printf ("%s\n", testTitleFind2->primaryTitle);

    printf ("building root1 for testName\n");
    build_pnindex(testName);

    printf ("finding first index\n");
    testNameFind = find_primary_name(testName, "Anthony Daniels");

    printf ("%p\n", (void *)testNameFind);
    printf ("%s\n", testNameFind->nconst);
    printf ("%s\n", testNameFind->primaryName);

    printf ("building root2 for testName\n");
    build_nindex(testName);

    printf ("finding next test\n");
    testNameFind2 = find_nconst(testName, testNameFind->nconst);
    printf ("%p\n", (void *)testNameFind2);
    printf ("%s\n", testNameFind2->nconst);
    printf ("%s\n", testNameFind2->primaryName);

    printf ("building root1 for titleprincipals\n");
    build_tindex_tp(testPrincipals);

    printf ("finding first index\n");
    testPrincipalsFind = find_tconst_tp(testPrincipals, testTitleFind2->tconst);
    printf ("%p\n", (void *)testPrincipalsFind);
    printf ("%s\n", testPrincipalsFind->nconst);
    printf ("%s\n", testPrincipalsFind->tconst);

    printf ("building root2 for titleprincipals\n");
    build_nindex_tp(testPrincipals);

    printf ("finding next test\n");
    testPrincipalsFind2 = find_nconst_tp(testPrincipals, testPrincipalsFind->nconst);
    printf ("%p\n", (void *)testPrincipalsFind2);
    printf ("%s\n", testPrincipalsFind2->nconst);
    printf ("%s\n", testPrincipalsFind2->tconst);

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