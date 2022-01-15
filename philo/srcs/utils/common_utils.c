#include "../../includes/main.h"

int	ft_atoi(const char *str)
{
	char	neg;
	int		res;
	int		i;

	neg = 1;
	i = 0;
	res = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > INT_MAX / 10)
			return (-1);
		else if (res < INT_MIN / 10)
			return (0);
		res = res * 10 + neg * str[i++] - '0';
	}
	return (res);
}

char	*ft_ltoa_base(unsigned long long num, int base)
{
	int					len;
	unsigned long long	tmp;
	char				*result;

	len = 0;
	tmp = num;
	while (tmp)
	{
		tmp /= base;
		len++;
	}
	result = malloc(sizeof(char) * len + 1);
	result[len] = '\0';
	while (len)
	{
		tmp = num % base;
		if (tmp < 10)
			result[len - 1] = tmp + '0';
		else
			result[len - 1] = tmp + '0' - 10;
		num /= base;
		len--;
	}
	return (result);
}

void	ft_usleep(long long stop_time, long long time)
{
	long long		dong;

	usleep(time * 900);
	dong = ft_time();
	while (dong < stop_time)
	{
		usleep(100);
		dong = ft_time();
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
