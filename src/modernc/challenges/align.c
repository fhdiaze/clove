#include "log.h"
#include <stdio.h>
#include <stdlib.h>

#undef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_ALL

typedef struct One {
    unsigned char a;
    unsigned b;
    unsigned long long c;
} One;

typedef struct Two {
    unsigned b;
    unsigned char a;
    unsigned long long c;
} Two;

typedef struct Three {
    unsigned b;
    unsigned long long c;
    unsigned char a;
} Three;

typedef struct Four {
    unsigned char a;
    unsigned long long c;
    unsigned b;
} Four;

typedef struct Five {
    unsigned long long c;
    unsigned char a;
    unsigned b;
} Five;

typedef struct Six {
    unsigned long long c;
    unsigned b;
    unsigned char a;
} Six;

/*
 * Measure the size of a structure using different order for the fields
 */
int main(void) {
    LOG_DEBUG("a=%lld\n", sizeof(unsigned char));
    LOG_DEBUG("b=%lld\n", sizeof(unsigned));
    LOG_DEBUG("c=%lld\n", sizeof(unsigned long long));
    LOG_DEBUG("one=%lld\n", sizeof(One));
    LOG_DEBUG("two=%lld\n", sizeof(Two));
    LOG_DEBUG("three=%lld\n", sizeof(Three));
    LOG_DEBUG("four=%lld\n", sizeof(Four));
    LOG_DEBUG("five=%lld\n", sizeof(Five));
    LOG_DEBUG("six=%lld\n", sizeof(Six));

    return EXIT_SUCCESS;
}
