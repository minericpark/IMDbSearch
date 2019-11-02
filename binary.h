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