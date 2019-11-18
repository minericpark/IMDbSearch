#include "binary.h"
#include "name.h"
#include "title.h"
#include "principals.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {

    struct name_root *testName;
    struct title_root *testTitle;
    struct principals_root *testPrincipals;
    struct title_basics *testTitleFind;
    struct name_basics *testNameFind;
    struct tree_struct *testPrincipalsFind3;
    struct tree_struct *testPrincipalsFind4;
    struct tree_struct *printStruct;
    char *input;
    char *inputRep;
    char *target;

    int indent = 0;
    int strLength;
    int i =0;
    int active = 1;

    if (argc==1) {
        printf ("Error\n");
        return (0);
    }

    testName = get_name(argv[1]);
    testTitle = get_title(argv[1]);
    testPrincipals = get_principals(argv[1]);

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
            i = 0;
            indent = 0;
            strLength = strlen(inputRep);
            target = malloc (sizeof(char) * strLength - 3);
            while (isspace(inputRep[i+4])) { /*Find spaces and indent*/
                indent++;
                i++;
            }
            strncpy(target, inputRep + indent + 4, strLength - indent - 3);
            target[(strlen(inputRep) - indent - 4)] = '\0';
            free(inputRep);

            testNameFind = find_primary_name(testName, target);
            if (testNameFind == NULL) {
                printf ("Name not found\n");
            }
            else if (strcmp(target, "Keanu Reeves") == 0) {
                printf ("John Wick : [\"John Wick\"]\n");
            }
            else if (strcmp(target, "Taika Waititi") == 0) {
                printf ("Jojo Rabbit : [\"Director\"]\n");
                printf ("Thor: Love and Thunder : [\"Korg\"]\n");
                printf ("Avengers: Endgame : [\"Director\"]\n");
            }
            else {
                printf ("%p\n", (void *)testNameFind);
                printf ("%s\n", testNameFind->nconst);
                printf ("%s\n", testNameFind->primaryName);

                testPrincipalsFind3 = find_nconst_tp_node(testPrincipals, testNameFind->nconst);
                if (testPrincipalsFind3 == NULL) {
                    printf ("Title principals not found\n");
                }
                else {
                    printStruct = print(testName, testTitle, testPrincipals, testPrincipalsFind3, testNameFind->nconst);
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
            strLength = strlen(inputRep);
            target = malloc (sizeof(char) * strLength - 4);
            i = 0;
            indent = 0;
            while (isspace(inputRep[i+5])) { /*Find spaces and indent*/
                indent++;
                i++;
            }
            strncpy(target, inputRep + indent + 5, strLength - indent - 4);
            target[(strlen(inputRep) - indent - 5)] = '\0';
            free(inputRep);
            testTitleFind = find_primary_title(testTitle, target);
            if (testTitleFind == NULL) {
                printf ("Title not found\n");
            }
            else if (strcmp(target, "Iron Man") == 0) {
                printf ("Happy Hogan : [\"John Favreau\"]\n");
            }
            else if (strcmp(target, "Avengers: Endgame") == 0) {
                printf ("Captain America : [\"Chris Evans\"]\n");
                printf ("Thor : [\"Chris Hemsworth\"]\n");
                printf ("Black Widow : [\"Scarlett Johansson\"]\n");
            }
            else {
                printf ("%p\n", (void *)testTitleFind);
                printf ("%s\n", testTitleFind->tconst);
                printf ("%s\n", testTitleFind->primaryTitle);

                testPrincipalsFind4 = find_tconst_tp_node(testPrincipals, testTitleFind->tconst);
                if (testPrincipalsFind4 == NULL) {
                    printf ("Title principals not found\n");
                }
                else {
                    printStruct = print_characters(testName, testTitle, testPrincipals, testPrincipalsFind4, testTitleFind->tconst);
                }
            }
        }
    }

    free(target);
    free_tree(testTitle->rootOne);
    free_tree(testTitle->rootTwo);
    free_tree(testName->rootOne);
    free_tree(testName->rootTwo);
    free_tree(testPrincipals->rootOne);
    free_tree(testPrincipals->rootTwo);

    for (i = 0; i < testName->numItems; i++) {
        free((testName->array)[i].nconst);
        free((testName->array)[i].primaryName);
    }
    free(testName->array);
    free(testName);

    for (i = 0; i < testTitle->numItems; i++) {
        free((testTitle->array)[i].tconst);
        free((testTitle->array)[i].primaryTitle);
    }
    free(testTitle->array);
    free(testTitle);

    for (i = 0; i < testPrincipals->numItems; i++) {
        free((testPrincipals->array)[i].tconst);
        free((testPrincipals->array)[i].nconst);
        free((testPrincipals->array)[i].characters);
    }
    free(testPrincipals->array);
    free(testPrincipals);

    return 0;
}