#include "principals.h"
#include "binary.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct principals_root *get_principals (char *path) {

    struct principals_root *treeStarter;
    char *fullPath;
    char *tempString;
    char *tempString2;
    char *tempCharacters;
    char *tempID;
    char *tempIDTwo;
    char *checkRole;
    char *actorString = "actor";
    char *actressString = "actress";
    char *fileName = "/title.principals.tsv";
    char tempLine[1000];
    int numRole = 0;
    int structNum = 0;
    FILE *fp;

    fullPath = malloc(strlen(path) + strlen(fileName) + 1);
    if (fullPath == NULL) {
        printf ("fullpath failed");
    }
    /*Complete file name*/
    strcpy(fullPath, path);
    strcat(fullPath, fileName);
    /*printf ("%s\n", fullPath);*/

    if ((fp = fopen(fullPath, "r+")) == NULL) { /*Checks if file exists*/
        printf ("File not found.");
    }

    treeStarter = malloc (sizeof(struct principals_root));

    /*Find all instances of actors/actresses*/
    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {
        /*Category -> section 4*/
        tempString = get_column(tempLine, tempString, 4);

        checkRole = strstr(tempString, actorString);
        if (checkRole) {
            numRole++;
        }
        else {
            checkRole = strstr(tempString, actressString);
            if (checkRole) {
                numRole++;
            }
        }
        memset(tempString, 0, strlen(tempString));
        if (checkRole != NULL) {
            memset(checkRole, 0, strlen(checkRole));
        }
        free(tempString);
    }

    fseek(fp, 0, SEEK_SET);/*
    printf ("# of Actor/Actresses: %d\n", numRole);*/

    treeStarter->numItems = numRole;
    treeStarter->array = malloc(sizeof(struct title_principals) * numRole);

    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {

        tempString2 = get_column(tempLine, tempString2, 4);
        tempID = get_column(tempLine, tempID, 1);
        tempIDTwo = get_column(tempLine, tempIDTwo, 3);
        tempCharacters = get_column(tempLine, tempCharacters, 6);

        checkRole = strstr(tempString2, actorString);
        if (checkRole) {
            (treeStarter->array)[structNum].tconst = malloc (strlen(tempID) + 1);
            (treeStarter->array)[structNum].nconst = malloc (strlen(tempIDTwo) + 1);
            (treeStarter->array)[structNum].characters = malloc (strlen(tempCharacters) + 1);
            strcpy((treeStarter->array)[structNum].tconst, reverse_word((char *) tempID));
            strcpy((treeStarter->array)[structNum].nconst, reverse_word((char *) tempIDTwo));
            strcpy((treeStarter->array)[structNum].characters, tempCharacters);
            structNum++;
        }
        else {
            checkRole = strstr(tempString2, actressString);
            if (checkRole) {
                (treeStarter->array)[structNum].tconst = malloc (strlen(tempID) + 1);
                (treeStarter->array)[structNum].nconst = malloc (strlen(tempIDTwo) + 1);
                (treeStarter->array)[structNum].characters = malloc (strlen(tempCharacters) + 1);
                strcpy((treeStarter->array)[structNum].tconst, reverse_word((char *) tempID));
                strcpy((treeStarter->array)[structNum].nconst, reverse_word((char *) tempIDTwo));
                strcpy((treeStarter->array)[structNum].characters, tempCharacters);
                structNum++;
            }
        }
        memset(tempString2, 0, strlen(tempString2));
        free(tempString2);
        memset(tempID, 0, strlen(tempID));
        free(tempID);
        memset(tempIDTwo, 0, strlen(tempIDTwo));
        free(tempIDTwo);
        memset(tempCharacters, 0, strlen(tempCharacters));
        free(tempCharacters);
    }

    treeStarter->rootOne = NULL;
    treeStarter->rootTwo = NULL;

    free(fullPath);
    fclose(fp);

    return treeStarter;

}

/*Creates tree for tconst*/
void build_tindex_tp (struct principals_root *treeStarter) {
    int i;

    for (i = 0; i < treeStarter->numItems; i++) {
        add_node_principals (&(treeStarter->rootOne), (treeStarter->array[i]).tconst, &(treeStarter->array[i]));
    }
    /*printf ("all nodes added");*/
}

/*Creates tree for nconst*/
void build_nindex_tp (struct principals_root *treeStarter) {
    int i;

    for (i = 0; i < treeStarter->numItems; i++) {
        add_node_principals (&(treeStarter->rootTwo), (treeStarter->array[i]).nconst, &(treeStarter->array[i]));
    }
    /*printf ("all nodes added");*/
}

/*Searches through tconst tree*/
struct title_principals *find_tconst_tp (struct principals_root *treeStarter, char *target) {

    struct tree_struct *retStruct;

    retStruct = find(treeStarter->rootOne, target);
    if (retStruct == NULL) {
        return NULL;
    }
    else {
        return retStruct->data;
    }

}

/*Searches through nconst tree*/
struct title_principals *find_nconst_tp (struct principals_root *treeStarter, char *target) {

    struct tree_struct *retStruct;

    retStruct = find(treeStarter->rootTwo, target);
    if (retStruct == NULL) {
        return NULL;
    }
    else {
        return retStruct->data;
    }
}

struct tree_struct *find_nconst_tp_node (struct principals_root *treeStarter, char *target) {

    struct tree_struct *retStruct;

    retStruct = find(treeStarter->rootTwo, target);
    if (retStruct == NULL) {
        return NULL;
    }
    else {
        return retStruct;
    }
}