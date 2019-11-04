#include "name.h"
#include "binary.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct name_root *get_name (char *path) {

    struct name_root *treeStarter;
    char *fullPath;
    char *tempString;
    char *tempString2;
    char *tempName;
    char *tempID;
    char *checkRole;
    char *actorString = "actor";
    char *actressString = "actress";
    char *fileName = "/name.basics.tsv";
    char tempLine[255];
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

    if ((fp = fopen(fullPath, "r")) == NULL) { /*Checks if file exists*/
        printf ("File not found.");
        fclose(fp);
    }

    treeStarter = malloc (sizeof(struct name_root));

    /*Find all instances of actors/actresses*/
    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {
        /*printf ("%s\n", tempLine);*/
        /*Copy into tempString, the buffer*/
        tempString = get_column(tempLine, tempString, 5);

        checkRole = strstr(tempString, actorString);
        if (checkRole) {/*
            printf ("%s\n", checkRole);*/
            numRole++;
        }
        else {
            checkRole = strstr(tempString, actressString);
            if (checkRole) {/*
                printf ("%s\n", checkRole);*/
                numRole++;
            }
        }
        /*
        printf ("%s\n", tempString);*/
        memset(tempString, 0, strlen(tempString));
        if (checkRole != NULL) {
            memset(checkRole, 0, strlen(checkRole));
        }
        free(tempString);
    }

    fseek(fp, 0, SEEK_SET);/*
    printf ("# of Actor/Actresses: %d\n", numRole);*/

    treeStarter->numItems = numRole;
    treeStarter->array = malloc(sizeof(struct name_basics) * numRole);

    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {

        tempString2 = get_column(tempLine, tempString2, 5);
        tempID = get_column(tempLine, tempID, 1);
        tempName = get_column(tempLine, tempName, 2);

        checkRole = strstr(tempString2, actorString);
        if (checkRole) {
            (treeStarter->array)[structNum].nconst = malloc (strlen(tempID) + 1);
            (treeStarter->array)[structNum].primaryName = malloc (strlen(tempName) + 1);
            strcpy((treeStarter->array)[structNum].nconst, reverse_word((char *) tempID));
            strcpy((treeStarter->array)[structNum].primaryName, tempName);
            structNum++;
        }
        else {
            checkRole = strstr(tempString2, actressString);
            if (checkRole) {
                (treeStarter->array)[structNum].nconst = malloc (strlen(tempID) + 1);
                (treeStarter->array)[structNum].primaryName = malloc (strlen(tempName) + 1);
                strcpy((treeStarter->array)[structNum].nconst, reverse_word((char *) tempID));
                strcpy((treeStarter->array)[structNum].primaryName, tempName);
                structNum++;
            }
        }
        memset(tempString2, 0, strlen(tempString2));
        free(tempString2);
        memset(tempID, 0, strlen(tempID));
        free(tempID);
        memset(tempName, 0, strlen(tempName));
        free(tempName);
    }

    treeStarter->rootOne = NULL;
    treeStarter->rootTwo = NULL;

    free(fullPath);
    fclose(fp);

    return treeStarter;

}

void build_pnindex (struct name_root *treeStarter) {
    int i;

    for (i = 0; i < treeStarter->numItems; i++) {
        add_node_name (&(treeStarter->rootOne), (treeStarter->array[i]).primaryName, &(treeStarter->array[i]));
    }
    /*printf ("all nodes added");*/
}

/*Creates tree for tconst*/
void build_nindex (struct name_root *treeStarter) {
    int i;

    for (i = 0; i < treeStarter->numItems; i++) {
        add_node_name (&(treeStarter->rootTwo), (treeStarter->array[i]).nconst, &(treeStarter->array[i]));
    }
    /*printf ("all nodes added");*/
}

struct name_basics *find_primary_name (struct name_root *treeStarter, char *target) {

    struct tree_struct *retStruct;

    retStruct = find(treeStarter->rootOne, target);

    if (retStruct == NULL) {
        return NULL;
    }
    else {
        return retStruct->data;
    }

}

/*Finds tconst*/
struct name_basics *find_nconst (struct name_root *treeStarter, char *target) {

    struct tree_struct *retStruct;

    retStruct = find(treeStarter->rootTwo, target);

    if (retStruct == NULL) {
        return NULL;
    }
    else {
        return retStruct->data;
    }

}