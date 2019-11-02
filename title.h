/*  Eric Minseo Park
    1001018
    epark03@uoguelph.ca   */

#include <stdio.h>
#include <stdlib.h>

struct title_basics {
    char *tconst;
    char *primaryTitle;
};

struct title_basics *get_title (char *path);