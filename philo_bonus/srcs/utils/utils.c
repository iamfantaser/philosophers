#include "../../includes/main.h"

void	philo_print(t_philosopher *philo, char *str)
{
	sem_wait(philo->write_sem);
	printf("%lld %d %s", (ft_time() - philo->time_start) / 1000,
		philo->id, str);
	sem_post(philo->write_sem);
}

void	philo_clear_sem_all(t_info *info)
{
	sem_close(info->write_sem);
	sem_close(info->death);
	sem_close(info->waiters);
}

void	philo_terminate(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->count)
	{
		kill(info->phil[i].pid, SIGTERM);
		i++;
	}
}

int	philo_validation(int argc, char **argv)
{
	int	i;
	int	j;
	int	res;

	i = 1;
	res = 1;
	if (argc < 5 || argc > 6)
		res = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9' )
				res = 0;
			j++;
		}
		i++;
	}
	if (res == 0)
		return (write(2, "Args ERROR\n", 15) == 0);
	else
		return (1);
}

int	philo_do_action(t_info *info, t_philosopher *philo)
{
	if (philo->state == HUNGRY)
		return (philo_action(info, philo));
	else if (philo->state == SLEEPING)
		return (philo_sleep(philo));
	else if (philo->state == THINKING)
		return (philo_think(philo));
	return (3);
}
