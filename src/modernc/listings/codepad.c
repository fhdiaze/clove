#include "log.h"
#include <corecrt.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
        int array[10];
} Test;

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

int random_int() { return rand(); }

void fgoto(unsigned n)
{
        unsigned j = 0;
        unsigned *p = nullptr;
        unsigned *q = nullptr;

AGAIN:
        logi("p=%p\n", (void *)p);
        logi("q=%p\n", (void *)q);
        if (p)
                logi("%u: p and q are %s, *p is %u \n", j,
                     (q == p) ? "equal" : "unequal", *p);
        q = p;
        p = &((unsigned){j});
        ++j;
        if (j <= n) goto AGAIN;
}

Test my_function()
{
        Test t = {};
        logi("function array address=%p\n", (void *)&(t.array));

        return t;
}

int main(void)
{
        // constexpr int runtime_constant = random_int(); // this is not a value
        // known at compile time int array[runtime_constant];  // VLA
        char name[] = "hello world!";
        const size_t len = strlen(name);
        char copy[len + 1];
        strcpy_s(copy, sizeof(copy), name);
        // printf("%d\n", __builtin_popcount(x));
        printf("%s\n", copy);
        printf("%llu\n", strlen(copy));
        const char *const p2string = "some text";
        const char *const p = nullptr;
        const char *const pinvalid;
        const int a = {};
        printf("a=%d\n", a);
        printf("%s\n", p);
        printf("%s\n", pinvalid);
        printf("%s\n", p2string);

        unsigned uint = -4;
        signed sint = -4;

        printf("unsigned=%u\n", uint);
        printf("signed=%d\n", sint);

        const time_t now = time(NULL);
        printf("time=%lld\n", now);
        char now_as_string[100];
        struct tm now_buffer;
        localtime_s(&now_buffer, &now);

        strftime(now_as_string, sizeof(now_as_string),
                 "%A %Y-%m-%d %H:%M:%S %Z", &now_buffer);
        printf("formatted time=%s\n", now_as_string);

        Test test_structure = my_function();

        logi("array address=%p\n", (void *)&(test_structure.array));

        fgoto(2);

        return EXIT_SUCCESS;
}
