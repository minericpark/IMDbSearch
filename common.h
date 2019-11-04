/*  Eric Minseo Park
    1001018
    epark03@uoguelph.ca   */

#include <stdio.h>
#include <stdlib.h>

char *get_column (char *line, char *copyTarget, int colNum);
char *reverse_word (char *target);
char *get_line (FILE *fp);
char *trim_line (char *target);