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
    char *buffer;
    char *buffer2;
    char *buffer3;
    char *buffer4;
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
        buffer = malloc(sizeof(char) * 50 + 1);
        if (buffer == NULL) {
            printf ("buffer failed");
        }
        /*Copy into tempString, the buffer*/
        buffer = get_column(tempLine, buffer, 5);
        tempString = malloc(strlen(buffer) + 1);
        if (buffer == NULL) {
            printf ("tempstring failed");
        }
        strcpy(tempString, buffer);
        memset(buffer, 0, strlen(buffer));
        free(buffer);

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
        buffer4 = malloc(sizeof(char) * 50 + 1);
        if (buffer4 == NULL) {
            printf ("buffer failed");
        }
        buffer4 = get_column(tempLine, buffer4, 5);
        tempString2 = malloc(strlen(buffer4) + 1);
        if (tempString == NULL) {
            printf ("tempstring failed");
        }
        strcpy(tempString2, buffer4);
        memset(buffer4, 0, strlen(buffer4));
        free(buffer4);

        buffer2 = malloc(sizeof(char) * 50 + 1);
        if (buffer2 == NULL) {
            printf ("buffer2 failed");
        }
        buffer2 = get_column(tempLine, buffer2, 1);
        tempID = malloc(strlen(buffer2) + 1);
        if (tempID == NULL) {
            printf ("tempid failed");
        }
        strcpy(tempID, buffer2);
        memset(buffer2, 0, strlen(buffer2));
        free(buffer2);

        buffer3 = malloc(sizeof(char) * 50 + 1);
        if (buffer3 == NULL) {
            printf ("buffer3 failed");
        }
        buffer3 = get_column(tempLine, buffer3, 2);
        tempName = malloc(strlen(buffer3) + 1);
        if (tempName == NULL) {
            printf ("Tempname failed");
        }
        strcpy(tempName, buffer3);
        memset(buffer3, 0, strlen(buffer3));
        free(buffer3);

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

