#include <stdio.h>
#include "ft_printf.h"
#include <float.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <stdio.h>
#include <limits.h>


int main(void)
{
	long double number0 = 1.0;

	__uint128_t bits = *(__uint128_t *)(&number0);
///	unsigned int exp = ((bits >> 64) & 0x7FFF) - 16383;
	ft_printf("1:%zd\n", -SSIZE_MAX);
	printf("2:%zd\n", -SSIZE_MAX);
	// int i = 80;
	// while (--i >= 0)
	// {
	// 	if ((bits >> i) & 1)
	// 		printf("1");
	// 	else
	// 		printf("0");
	// }
	// return (0);
}

