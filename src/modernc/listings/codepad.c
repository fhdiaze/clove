#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

enum corvid { magpie, raven, jay, chough, corvid_num, };

#define FLOCK_MAGPIE (1U << magpie)
#define FLOCK_RAVEN (1U << raven)
#define FLOCK_JAY (1U << jay)
#define FLOCK_CHOUGH (1U << chough)
#define FLOCK_EMPTY 0U
#define FLOCK_FULL ((1U << corvid_num)-1)

int main(void)
{
    int x = INT_MIN + INT_MAX;
    printf("%d\n", __builtin_popcount(x));
    return EXIT_SUCCESS;
}
