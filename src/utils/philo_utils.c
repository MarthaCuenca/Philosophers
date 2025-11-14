#include "philo.h"
#include <stdlib.h>

unsigned long  ft_conversion(unsigned long long src, int factor, char op)
{
	 unsigned long   target;

	target = 0;
	if (op == '*')
		target = src * factor;
	else if (op == '/')
		target = src / factor;
	return (target);
}
