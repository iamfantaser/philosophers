#include "../../includes/main.h"

void	ft_usleep(long long stop_time, long long time)
{
	struct timeval	step;
	long long		dong;

	usleep(time * 900);
	dong = 0;
	while (dong < stop_time)
	{
		usleep(100);
		gettimeofday(&step, NULL);
		dong = (step.tv_sec) * 1000 * 1000
			+ (step.tv_usec);
	}
}

long long	ft_time(void)
{
	struct timeval	tv;
	long long		millis;

	gettimeofday(&tv, NULL);
	millis = (tv.tv_sec * 1000 * 1000 + tv.tv_usec);
	return (millis);
}
