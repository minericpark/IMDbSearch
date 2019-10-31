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
    char *tempName;
    char *tempID;
    char *actorString;
    char *actressString;
    char *checkRole;
    char tempLine[256];
    int numRole = 0;
    int *indexVals;
    int structNum = 0;
    FILE *fp;

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

    /*Find all instances of actors/actresses*/
    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {
        /*printf ("%s\n", tempLine);*/
        tempString = malloc(sizeof(char) * 50 + 1);
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
        tempString[0] = '\0';
        if (checkRole != NULL) {
            checkRole[0] = '\0';
        }
        free(tempString);
    }

    fseek(fp, 0, SEEK_SET);
    printf ("# of Actor/Actresses: %d\n", numRole);

    completeList = malloc(sizeof(struct name_basics) * numRole);

    /*Create structures*/
    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {
        tempString = malloc(sizeof(char) * 50 + 1);
        tempString = get_column(tempLine, tempString, 5);

        tempID = malloc(sizeof(char) * 100 + 1);
        tempID = get_column(tempLine, tempID, 1);

        tempName = malloc(sizeof(char) * 100 + 1);
        tempName = get_column(tempLine, tempName, 2);

        checkRole = strstr(tempString, actorString);
        if (checkRole) {/*
            printf ("%s\n", checkRole);*/
            /*Get 1st and 2nd column*//*
            printf ("%s: %s\n", tempID, tempName);*/
            completeList[structNum].nconst = malloc (strlen(tempID) + 1);
            completeList[structNum].primaryName = malloc (strlen(tempName) + 1);
            strcpy(completeList[structNum].nconst, (char *) tempID);
            strcpy(completeList[structNum].primaryName, tempName);
            structNum++;
        }
        else {
            checkRole = strstr(tempString, actressString);
            if (checkRole) {/*
                printf ("%s\n", checkRole);*/
                /*Get 1st and 2nd column*/
                /*fix structure creation*/
                /*weird gibberish at front two letters*//*
                printf ("%s: %s\n", tempID, tempName);*/
                completeList[structNum].nconst = malloc (strlen(tempID) + 1);
                completeList[structNum].primaryName = malloc (strlen(tempName) + 1);
                strcpy(completeList[structNum].nconst, (char *) tempID);
                strcpy(completeList[structNum].primaryName, tempName);
                structNum++;
            }
        }
        /*
        printf ("%s\n", tempString);*/
        tempString[0] = '\0';
        free(tempString);
        tempID[0] = '\0';
        free(tempID);
        tempName[0] = '\0';
        free(tempName);
    }

    free(actorString);
    free(actressString);
    free(fullPath);
    free(fp);

    return completeList;

}

