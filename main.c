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
    struct tree_struct *testPrincipalsFind3;
    char *input;
    char *inputRep;
    char *target;

    int indent = 0;
    int strLength;
    int testNameSize = 0;
    int testTitleSize = 0;
    int testPrincipalsSize = 0;
    int i =0;
    int active = 1;
/*
    testName = get_name("fulldata");
    testTitle = get_title("fulldata");
    testPrincipals = get_principals("fulldata");

    build_ptindex(testTitle);
    build_tindex(testTitle);
    build_pnindex(testName);
    build_nindex(testName);
    build_tindex_tp(testPrincipals);
    build_nindex_tp(testPrincipals);*/

    testName = get_name("fulldata");
    testTitle = get_title("fulldata");
    testPrincipals = get_principals("fulldata");

    build_ptindex(testTitle);
    build_tindex(testTitle);
    build_pnindex(testName);
    build_nindex(testName);
    build_tindex_tp(testPrincipals);
    build_nindex_tp(testPrincipals);

    while (active == 1) {
        printf ("> ");
        input = get_line(stdin);
        input = trim_line(input);
        while (strncmp(input, "name", 4) != 0 && strncmp(input, "title", 5) != 0) {
            free(input);
            printf ("> ");
            input = get_line(stdin);
            input = trim_line(input);
        }
        inputRep = malloc(sizeof(char) * strlen(input) + 1);
        strcpy(inputRep, input);
        free(input);

        /*if name
         * find_primary_name
         * find_nconst_tp
         * find_primary_title
         * make sure to check on each step if null
         * */

        /*Enter name function*/
        if (strncmp(inputRep, "name", 4) == 0) {
            printf ("entered name\n");
            strLength = strlen(inputRep);
            target = malloc (sizeof(char) * strLength - 3);
            i = 0;
            while (isspace(inputRep[i+4])) { /*Find spaces and indent*/
                indent++;
                i++;
            }
            strncpy(target, inputRep + indent + 4, strLength - indent - 3);
            target[(strlen(inputRep) - indent - 4)] = '\0';
            printf ("%s\n", inputRep);
            printf ("%s\n", target);
            free(inputRep);

            testNameFind = find_primary_name(testName, target);
            if (testNameFind == NULL) {
                printf ("Name not found\n");
                exit(0);
            }
            else {
                printf ("%p\n", (void *)testNameFind);
                printf ("%s\n", testNameFind->nconst);
                printf ("%s\n", testNameFind->primaryName);

                testPrincipalsFind3 = find_nconst_tp_node(testPrincipals, testNameFind->nconst);
                if (testPrincipalsFind3 == NULL) {
                    printf ("Title principals not found\n");
                    exit(0);
                }
                /*
                else {

                    testTitleFind = find_tconst(testTitle, testPrincipalsFind->tconst);
                    if (testTitleFind == NULL) {
                        printf ("Title not found");
                        exit(0);
                    }
                    else {
                        printf ("%s : %s\n", testTitleFind->primaryTitle, testPrincipalsFind->characters);
                    }
                }*/
            }
        }
            /*Enter title function*/
        else if (strncmp(inputRep, "title", 5) == 0) {
            printf ("entered title\n");
            strLength = strlen(inputRep);
            target = malloc (sizeof(char) * strLength - 4);
            i = 0;
            while (isspace(inputRep[i+5])) { /*Find spaces and indent*/
                indent++;
                i++;
            }
            strncpy(target, inputRep + indent + 5, strLength - indent - 4);
            target[(strlen(inputRep) - indent - 5)] = '\0';
            printf ("%s\n", inputRep);
            printf ("%s\n", target);
            free(inputRep);

        }
    }


    free(target);
    /*if title
     * find_primary_title
     * find_nconst_tp
     * find_primary_name
     * find_*/

    /*

    testNameFind = find_primary_name(testName, "Bruce Lee");
    testPrincipalsFind = find_nconst_tp(testPrincipals, testNameFind->nconst);
    testTitleFind = find_tconst(testTitle, testPrincipalsFind->tconst);
    printf ("%s\n", testTitleFind->primaryTitle);
/*
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
*/
    return 0;
}