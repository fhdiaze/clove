#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum corvid {
    magpie,
    raven,
    jay,
    chough,
    corvid_num,
};

#define FLOCK_MAGPIE (1U << magpie)
#define FLOCK_RAVEN (1U << raven)
#define FLOCK_JAY (1U << jay)
#define FLOCK_CHOUGH (1U << chough)
#define FLOCK_EMPTY 0U
#define FLOCK_FULL ((1U << corvid_num) - 1)

int main(void) {
    char name[] = "hello world!";
    size_t const len = strlen(name);
    char copy[len + 1];
    strcpy_s(copy, sizeof(copy), name);
    // printf("%d\n", __builtin_popcount(x));
    printf("%s\n", copy);
    printf("%llu\n", strlen(copy));
    char const *const p2string = "some text";
    char const *const p = nullptr;
    char const *const pinvalid;
    int const a;
    printf("a=%d\n", a);
    printf("%s\n", p);
    printf("%s\n", pinvalid);
    printf("%s\n", p2string);
    typedef int calArray[9];

    return EXIT_SUCCESS;
}
