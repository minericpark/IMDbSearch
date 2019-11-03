/*  Eric Minseo Park
    1001018
    epark03@uoguelph.ca   */

#include <stdio.h>
#include <stdlib.h>

struct name_basics {
    char *nconst;
    char *primaryName;
};

struct name_root *get_name(char *path);
void build_nindex(struct name_root *treeStarter);
struct name_basics *find_primary_name(struct name_root *treeStarter, char *target);