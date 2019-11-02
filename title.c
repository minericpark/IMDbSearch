#include "common.h"
#include "title.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct title_basics *get_title (char *path) {

    struct title_basics *completeList;
    char *fullPath;
    char *tempString;
    char *tempString2;
    char *tempString3;
    char *tempString4;
    char *tempTitle;
    char *tempID;
    char *checkRole;
    char *checkRole2;
    char *zeroString = "0";
    char *movieString = "movie";
    char *fileName = "/title.basics.tsv";
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

    if ((fp = fopen(fullPath, "r+")) == NULL) { /*Checks if file exists*/
        printf ("File not found.");
    }

    /*titleType -> col2
     * isAdult -> col5*/
    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {
        /*Get titleType col and isAdult col*/
        tempString = get_column(tempLine, tempString, 2);
        tempString2 = get_column(tempLine, tempString2, 5);

        /*Check both titleType and isAdult*/
        checkRole = strstr(tempString, movieString);
        checkRole2 = strstr(tempString2, zeroString);
        if (checkRole && checkRole2) {
            numRole++;
        }
        memset(tempString, 0, strlen(tempString));
        memset(tempString2, 0, strlen(tempString2));
        if (checkRole != NULL) {
            memset(checkRole, 0, strlen(checkRole));
        }
        if (checkRole2 != NULL) {
            memset(checkRole, 0, strlen(checkRole2));
        }
        free(tempString);
        free(tempString2);
    }

    fseek(fp, 0, SEEK_SET);
    printf ("# of Titles with 0 Adults: %d\n", numRole);

    completeList = malloc(sizeof(struct title_basics) * numRole);

    while (fgets (tempLine, sizeof(tempLine), fp) != NULL) {

        /*Get all required data*/
        tempString3 = get_column(tempLine, tempString3, 2);
        tempString4 = get_column(tempLine, tempString4, 5);
        /*Get ID + primary title name*/
        tempID = get_column(tempLine, tempID, 1);
        tempTitle = get_column(tempLine, tempTitle, 3);

        /*Check both titleType and isAdult*/
        checkRole = strstr(tempString3, movieString);
        checkRole2 = strstr(tempString4, zeroString);
        if (checkRole && checkRole2) {
            completeList[structNum].tconst = malloc (strlen(tempID) + 1);
            completeList[structNum].primaryTitle = malloc (strlen(tempTitle) + 1);
            strcpy(completeList[structNum].tconst, (char *) tempID);
            strcpy(completeList[structNum].primaryTitle, tempTitle);
            structNum++;
        }
        memset(tempString3, 0, strlen(tempString3));
        free(tempString3);
        memset(tempString4, 0, strlen(tempString4));
        free(tempString4);
        memset(tempID, 0, strlen(tempID));
        free(tempID);
        memset(tempTitle, 0, strlen(tempTitle));
        free(tempTitle);
    }

    free(fullPath);
    fclose(fp);

    return completeList;

}