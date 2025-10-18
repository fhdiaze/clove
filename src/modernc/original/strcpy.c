#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[argc + 1])
{
        const size_t len = strlen(argv[0]); // Computes the length
        // Initialized VLA, /*@\C{23}*/
        // terminates array with 0 character
        char name[len + 1] = {};
        // Copies the program name
        memcpy(name, argv[0], len);
        if (!strcmp(name, argv[0])) {
                printf("program name \"%s\" successfully copied\n", name);
        } else {
                printf("copying %s leads to different string %s\n", argv[0],
                       name);
        }
}
