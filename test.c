#include <stdio.h>
#include "ft_printf.h"
#include <float.h>
#include <math.h>


int main(void)
{
	double number0 = 0.2;

	__uint128_t bits = *(__uint128_t *)(&number0);
	unsigned int exp = ((bits >> 52) & 0x7FF) - 1023;

	//ft_printf("%.10f", 1.0);
//	ft_printf("1:%.40f\n", 9999999.000000099999999);
	ft_printf("%.30f\n", 200.40055555555555);
	printf("%.30f\n", 200.40055555555555);
	//printf("%.3000f\n", 200.40055555555555);
	//printf("aaaaa%.20f\n", 10.90006);
	// int i = 64;
	// while (--i >= 0)
	// {
	// 	if ((bits >> i) & 1)
	// 		printf("1");
	// 	else
	// 		printf("0");
	// }
	return (0);
}

