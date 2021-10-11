#include "../../includes/main.h"

void	ft_error(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write (2, str, len);
	exit(3);
}

void	philo_free(t_info *info)
{
	int	i;

	i = 0;
	free(info->sem);
	free(info->phil);
}

void	philo_init_semaphores(t_info *info)
{
	int	i;

	i = 0;
	sem_unlink("str_wr");
	info->write_sem = sem_open("str_wr", O_CREAT, 0777, 1);
	sem_unlink("wai");
	info->waiters = sem_open("wai", O_CREAT, 0777, info->count / 2);
	sem_unlink("exi5t");
	info->death = sem_open("exi5t", O_CREAT, 0777, 0);
}

void	*philo_wait(void *in)
{
	int		status;
	pid_t	child;
	t_info	*info;

	info = (t_info *)in;
	child = waitpid(0, &status, 0);
	status = WEXITSTATUS(status);
	if (status > 1 && info->eaters)
	{
		info->eaters -= 1;
		philo_wait(info);
	}
	else
		sem_post(info->death);
	return ((void *) 0);
}

int	ft_atoi(const char *str)
{
	char	neg;
	int		i;
	int		res;

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
