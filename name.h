/*  Eric Minseo Park
    1001018
    epark03@uoguelph.ca   */

#include <stdio.h>
#include <stdlib.h>

struct name_basics {
    char *nconst;
    char *primaryName;
};

struct name_basics *get_name(char *path);
int getBasicSize (char *path);