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
                    firstLoc = i;
                }
                if (tabNum == colNum) {
                    secLoc = i;
                    break;
                }
            }
        }
    }

    strncpy(copyTarget, line + firstLoc, secLoc - firstLoc);
    copyTarget[strlen(copyTarget)] = '\0';
    return copyTarget;
}