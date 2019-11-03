/*  Eric Minseo Park
    1001018
    epark03@uoguelph.ca   */

#include <stdio.h>
#include <stdlib.h>

struct tree_struct {
    char *key;
    void *data;
    struct tree_struct *children[2];
};

struct name_root {
    int numItems;
    struct name_basics *array;
    struct tree_struct *rootOne;
    struct tree_struct *rootTwo;
};

struct title_root {
    int numItems;
    struct title_basics *array;
    struct tree_struct *rootOne;
    struct tree_struct *rootTwo;
};

struct principals_root {
    int numItems;
    struct title_principals *array;
    struct tree_struct *rootOne;
    struct tree_struct *rootTwo;
};

void add_node_title (struct tree_struct **root, char *title, struct title_basics *givenStruct);
void add_node_name (struct tree_struct **root, char *name, struct name_basics *givenStruct);
void add_node_principals (struct tree_struct **root, char *principals, struct title_principals *givenStruct);
struct tree_struct *find (struct tree_struct *root, char *target);