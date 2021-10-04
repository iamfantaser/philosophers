#include "../../includes/main.h"

int ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_atoi(const char *str)
{
	char neg;
	int i;
	int res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			neg = -1;	
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res < INT_MIN / 10)
			return (0);
		else if (res > INT_MAX / 10)
			return (-1);
		res = res * 10 + neg * (str[i++] - '0');
	}
	return (res);
}