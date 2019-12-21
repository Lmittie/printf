#include <stdio.h>
#include "ft_printf.h"
#include <float.h>
#include <math.h>
#include <float.h>


int main(void)
{
	long double number0 = 1.0;

	__uint128_t bits = *(__uint128_t *)(&number0);
///	unsigned int exp = ((bits >> 64) & 0x7FFF) - 16383;

	//ft_printf("%.10f", 1.0);
//	ft_printf("1:%.40f\n", 9999999.000000099999999);
	//ft_printf("%0100.2f\n", 15.0099);
	ft_printf("1:%#037lo\n", 22337203685477ul);
	printf("2:%#037lo\n", 22337203685477ul);
//	printf("%Lf\n", (long double)5.2552896045);
	//printf("%.1f\n", DBL_MAX);
	//printf("%.3000f\n", 200.40055555555555);
	//printf("aaaaa%.20f\n", 10.90006);
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

