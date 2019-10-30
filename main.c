#include "name.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void) {

    struct name_basics *test;
    int i =0;

    test = get_name("data");

    for (i = 0; i < 81; i++) {
        printf ("%s, %s", test[i].nconst, test[i].primaryName);
    }

    free(test);
    return 0;
}