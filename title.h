/*  Eric Minseo Park
    1001018
    epark03@uoguelph.ca   */

#include <stdio.h>
#include <stdlib.h>

struct title_basics {
    char *tconst;
    char *primaryTitle;
};

struct title_root *get_title (char *path);
void build_ptindex(struct title_root *treeStarter);
void build_tindex(struct title_root *treeStarter);
struct title_basics *find_primary_title (struct title_root *treeStarter, char *target);
struct title_basics *find_tconst (struct title_root *treeStarter, char *target);