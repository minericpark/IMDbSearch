#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *get_column (char *line, char *copyTarget, int colNum) {

    int i;
    int tabNum = 0;
    int firstLoc = 0;
    int secLoc = 0;

    for (i = 0; i < strlen(line); i++) {
        if (colNum == 1) { /*If first column requested*/
            if (line[i] == '\t') {
                /*printf ("tab detected");*/
                firstLoc = 0;
                secLoc = i;
                break;
            }
        }
        else {
            if (line[i] == '\n') { /*Detect newline (in case of final column)*/
                secLoc = i;
                break;
            }
            if (line[i] == '\t') { /*Detect tab*/
                /*printf ("tab detected");*/
                tabNum++;
                /*Error case for first or final col*/
                if (tabNum == colNum - 1) {
                    firstLoc = i + 1;
                }
                if (tabNum == colNum) {
                    secLoc = i;
                    break;
                }
            }
        }
    }
/*
    printf ("%d, %d\n", secLoc, firstLoc);*/
    copyTarget = malloc(sizeof(char) * (secLoc - firstLoc) + 1);
    strncpy(copyTarget, line + firstLoc, secLoc - firstLoc);
    copyTarget[secLoc - firstLoc] = '\0';
    return copyTarget;
}

char *reverse_word (char *target) {
    int i;
    int first = 0;
    int last = strlen(target) - 1;
    char temp;

    for (i = 0; i < strlen(target)/2; i++) {
        temp = target[first];
        target[first] = target[last];
        target[last] = temp;
        last--;
        first++;
    }

    return target;
}
