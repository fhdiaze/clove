#include <stddef.h>
#include <stdio.h>

void swap_double(double a[restrict static 1], double b[restrict static 1])
{
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

double sum(size_t len, const double *a)
{
	double ret = 0.0;

	for (const double *const aStop = a + len; a < aStop; ++a) {
		ret += *a;
	}

	return ret;
}

int main(void)
{
	const double *p;
	double A[2] = {
		1.0,
		2.0,
	};
	swap_double(&A[0], &A[1]);
	printf("A[0] = %g, A[1] = %g\n", A[0], A[1]);
}
