/*  Eric Minseo Park
    1001018
    epark03@uoguelph.ca   */

#include <stdio.h>
#include <stdlib.h>

struct node_struct {
    void *data;
    struct node_struct *next;
};

struct node_struct *txt2words (FILE *fp);
struct node_struct *search (struct node_struct *list, char *target, int (*compar)(const void *, const void *));