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
    logd("a=%lld\n", sizeof(unsigned char));
    logd("b=%lld\n", sizeof(unsigned));
    logd("c=%lld\n", sizeof(unsigned long long));
    logd("one=%lld\n", sizeof(One));
    logd("two=%lld\n", sizeof(Two));
    logd("three=%lld\n", sizeof(Three));
    logd("four=%lld\n", sizeof(Four));
    logd("five=%lld\n", sizeof(Five));
    logd("six=%lld\n", sizeof(Six));

    return EXIT_SUCCESS;
}
