#include <corecrt.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    int const a = {};
    printf("a=%d\n", a);
    printf("%s\n", p);
    printf("%s\n", pinvalid);
    printf("%s\n", p2string);

    unsigned uint = -4;
    signed sint = -4;

    printf("unsigned=%u\n", uint);
    printf("signed=%d\n", sint);

    time_t const now = time(NULL);
    printf("time=%lld\n", now);
    char now_as_string[100];
    struct tm now_buffer;
    localtime_s(&now_buffer, &now);

    strftime(now_as_string, sizeof(now_as_string), "%A %Y-%m-%d %H:%M:%S %Z", &now_buffer);
    printf("formatted time=%s\n", now_as_string);

    return EXIT_SUCCESS;
}
