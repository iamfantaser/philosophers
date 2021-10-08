#include "../../includes/main.h"

void	philo_print(t_philosopher *philo, char *str)
{
	sem_wait(philo->write_sem);
	printf("%lld %d %s", (ft_time() - philo->time_start) / 1000,
		philo->id , str);
	sem_post(philo->write_sem);
}

void	philo_clear_sem_all(t_info *info)
{
	int i;

	i = 0;
	sem_close(info->write_sem);
	sem_close(info->lifes);
	sem_unlink("writer");
	sem_unlink("lifes");
	while (i < info->count)
	{
		sem_close(info->sem[i]);
		sem_unlink(info->forks_name[i++]);
	}
}

void	philo_terminate(pid_t expetion_pid, t_info *info)
{
	int i;

	i = 0;
	while (i < info->count)
	{
		if (info->phil[i].pid != expetion_pid)
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
		return (philo_take_fork(info, philo));
	else if (philo->state == EATING)
		return (philo_eat(info, philo));
	else if (philo->state == SLEEPING)
		return (philo_sleep(philo));
	else if (philo->state == THINKING)
		return (philo_think(philo));
	return (4);
}
