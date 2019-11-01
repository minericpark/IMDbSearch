#include "name.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct name_basics *get_name (char *path) {

    struct name_basics *completeList;
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

    if ((fp = fopen(fullPath, "r+")) == NULL) { /*Checks if file exists*/
        printf ("File not found.");
    }

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

    fseek(fp, 0, SEEK_SET);
    printf ("# of Actor/Actresses: %d\n", numRole);

    completeList = malloc(sizeof(struct name_basics) * numRole);

    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {

        tempString2 = get_column(tempLine, tempString2, 5);
        tempID = get_column(tempLine, tempID, 1);
        tempName = get_column(tempLine, tempName, 2);

        checkRole = strstr(tempString2, actorString);
        if (checkRole) {
            completeList[structNum].nconst = malloc (strlen(tempID) + 1);
            completeList[structNum].primaryName = malloc (strlen(tempName) + 1);
            strcpy(completeList[structNum].nconst, (char *) tempID);
            strcpy(completeList[structNum].primaryName, tempName);
            structNum++;
        }
        else {
            checkRole = strstr(tempString2, actressString);
            if (checkRole) {
                completeList[structNum].nconst = malloc (strlen(tempID) + 1);
                completeList[structNum].primaryName = malloc (strlen(tempName) + 1);
                strcpy(completeList[structNum].nconst, (char *) tempID);
                strcpy(completeList[structNum].primaryName, tempName);
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

    free(fullPath);
    fclose(fp);

    return completeList;

}

