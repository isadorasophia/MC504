/**
 * Implementation for dictionary syscalls
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string.h>
 
#define TOTAL_I 100
#define BUF_S   256

int main () {
    int  i, r, s;
    char val[BUF_S],
         val_r[BUF_S];

    for (i = 0; i < TOTAL_I; i++) {
        /* Key value */
        snprintf(val, BUF_S, "Testing my fancy syscall no. %d!", i);

        s = strlen(val);

        printf("Going to set key %s of size %d.\n", val, s);

        /* Set key */
        r = syscall(379, i, val, s);

        if (r == 0) {
            printf("Done setting!\n");
        }
    }

    for (i = 0; i < TOTAL_I; i++) {
        /* Now, get key */
        r = syscall(378, i, val_r);

        if (r == 0) {
            printf("Got my key %d with value: %s.\n\n", i, val_r);
        }
    }

    return 0;
}