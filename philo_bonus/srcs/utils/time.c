#include "../../includes/main.h"

void	ft_usleep(long long stop_time)
{
	struct timeval	step;
	long long		dong;

	while (1)
	{
		usleep(100);
		gettimeofday(&step, NULL);
		dong = (step.tv_sec) * 1000 * 1000
			+ (step.tv_usec);
		if (dong >= stop_time)
			break ;
	}
}

long long	ft_get_diff_time(long long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec) * 1000 * 1000 + (tv.tv_usec)) - start);
}

long long	ft_time(void)
{
	struct timeval	tv;
	long long		millis;

	gettimeofday(&tv, NULL);
	millis = (tv.tv_sec * 1000 * 1000 + tv.tv_usec);
	return (millis);
}
