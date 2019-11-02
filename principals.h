/*  Eric Minseo Park
    1001018
    epark03@uoguelph.ca   */

#include <stdio.h>
#include <stdlib.h>

struct title_principals {
    char *tconst;
    char *nconst;
    char *characters;
};


struct title_principals *get_principals (char *path);
int getPrincipalsSize (char *path);