#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int a, b;
	char c = 'd';
	long long n = 2389872348234702;
	int d = 128;
	//a = ft_printf("ft_printf:%d\n", -1);
	//b = printf("printf:%hhld\n", -1);

	ft_printf("1:%llu\n", (long long)-42);
	printf("2:%llu\n", (long long)-42);
	return (0);
}
