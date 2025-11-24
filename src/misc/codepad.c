#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_ALL
#endif // LOG_LEVEL

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

typedef int myint;

#define FLOCK_MAGPIE (1U << magpie)
#define FLOCK_RAVEN (1U << raven)
#define FLOCK_JAY (1U << jay)
#define FLOCK_CHOUGH (1U << chough)
#define FLOCK_EMPTY 0U
#define FLOCK_FULL ((1U << corvid_num) - 1)

int random_int()
{
	return rand();
}
extern _Atomic(double (*)[45]) A;
extern const double F[45];

/**
 * @brief hethsa
 *
 * @param n the nimeber
 */
void fgoto(unsigned n)
{
	unsigned j = 0;
	unsigned *p = nullptr;
	[[__maybe_unused__]] unsigned *q = nullptr;
	logd("the value of j=%d", j);
	logi("p=%p", (void *)p);
	logi("q=%p", (void *)q);

AGAIN:
	if (p)
		logi("%u: p and q are %s, *p is %u", j, (q == p) ? "equal" : "unequal", *p);
	q = p;
	p = &((unsigned){ j });
	++j;
	if (j <= n)
		goto AGAIN;
}

Test my_function()
{
	Test t = {};
	logi("function array address=%p", (void *)&(t.array));

	return t;
}

#define CONCAT(a, b) a##b
#define strtod(NPTR, ...) STRTOD_I##__VA_OPT__(I)(NPTR __VA_OPT__(, ) __VA_ARGS__)
#define STRTOD_I(NPTR) strtod(NPTR, nullptr)
#define STRTOD_II(NPTR, ENDPTR) strtod(NPTR, ENDPTR)

int main(void)
{
	volatile _Atomic(unsigned) volatomic = 0;
	volatile unsigned _Atomic volatomic_two = 0;
	logi("volatomic=%u", volatomic);
	logi("volatomic_two=%u", volatomic_two);
	logi("starting");
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
	const char *const pinvalid = nullptr;
	[[__maybe_unused__]] const int a = {};
	logi("a=%d", a);
	printf("%s\n", p);
	printf("%s\n", pinvalid);
	printf("%s\n", p2string);

	unsigned uint = 4;
	signed sint = -4;

	printf("unsigned=%u\n", uint);
	printf("signed=%d\n", sint);

	const time_t now = time(nullptr);
	printf("time=%lld\n", now);
	char now_as_string[100];
	struct tm now_buffer;
	localtime_s(&now_buffer, &now);

	strftime(now_as_string, sizeof(now_as_string), "%A %Y-%m-%d %H:%M:%S %Z", &now_buffer);
	printf("formatted time=%s\n", now_as_string);

	[[__maybe_unused__]] Test test_structure = my_function();

	logi("array address=%p", (void *)&(test_structure.array));

	fgoto(2);

	[[__maybe_unused__]] char tix[] = "12345";

	logi("tix length: %zu", strlen(tix));
	logi("validate tix: %p", memchr(tix, 0, strlen(tix) + 1));

	[[__maybe_unused__]] int var12 = 100;
	// This expands to printf("%d\n", var12);
	logi("%d", CONCAT(var, 12));
	logi("%f", strtod("12"));

	return EXIT_SUCCESS;
}
