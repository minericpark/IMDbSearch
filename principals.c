#include "principals.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct title_principals *get_principals (char *path) {

    struct title_principals *completeList;
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

    fseek(fp, 0, SEEK_SET);
    printf ("# of Actor/Actresses: %d\n", numRole);

    completeList = malloc(sizeof(struct title_principals) * numRole);

    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {

        tempString2 = get_column(tempLine, tempString2, 4);
        tempID = get_column(tempLine, tempID, 1);
        tempIDTwo = get_column(tempLine, tempIDTwo, 3);
        tempCharacters = get_column(tempLine, tempCharacters, 6);

        checkRole = strstr(tempString2, actorString);
        if (checkRole) {
            completeList[structNum].tconst = malloc (strlen(tempID) + 1);
            completeList[structNum].nconst = malloc (strlen(tempIDTwo) + 1);
            completeList[structNum].characters = malloc (strlen(tempCharacters) + 1);
            strcpy(completeList[structNum].tconst, (char *) tempID);
            strcpy(completeList[structNum].nconst, (char *) tempIDTwo);
            strcpy(completeList[structNum].characters, tempCharacters);
            structNum++;
        }
        else {
            checkRole = strstr(tempString2, actressString);
            if (checkRole) {
                completeList[structNum].tconst = malloc (strlen(tempID) + 1);
                completeList[structNum].nconst = malloc (strlen(tempIDTwo) + 1);
                completeList[structNum].characters = malloc (strlen(tempCharacters) + 1);
                strcpy(completeList[structNum].tconst, (char *) tempID);
                strcpy(completeList[structNum].nconst, (char *) tempIDTwo);
                strcpy(completeList[structNum].characters, tempCharacters);
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

    free(fullPath);
    fclose(fp);

    return completeList;

}

int getPrincipalsSize(char *path) {
    char *fullPath;
    char *tempString;
    char *checkRole;
    char *actorString = "actor";
    char *actressString = "actress";
    char *fileName = "/title.principals.tsv";
    char tempLine[1000];
    int numRole = 0;
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

    fseek(fp, 0, SEEK_SET);

    free(fullPath);
    fclose(fp);

    return numRole;
}
