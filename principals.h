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

struct principals_root *get_principals (char *path);
void build_tindex_tp (struct principals_root *treeStarter);
void build_nindex_tp (struct principals_root *treeStarter);
struct title_principals *find_tconst_tp (struct principals_root *treeStarter, char *target);
struct title_principals *find_nconst_tp (struct principals_root *treeStarter, char *target);
struct tree_struct *find_nconst_tp_node (struct principals_root *treeStarter, char *target);