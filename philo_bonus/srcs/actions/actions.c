#include "../../includes/main.h"

int	philo_action(t_info *info, t_philosopher *philo)
{
	sem_wait(info->waiters);
	sem_wait(info->sem);
	philo_print(philo, "has taken a fork\n");
	sem_wait(info->sem);
	philo->last_meal = ft_time();
	philo_print(philo, "has taken a fork\n");
	philo_print(philo, "is eating\n");
	if (philo->number_of_eat == LLONG_MIN)
		philo->number_of_eat = -1;
	else
		philo->number_of_eat--;
	ft_usleep(ft_time() + info->time_to_eat * 1000);
	sem_post(info->sem);
	sem_post(info->sem);
	sem_post(info->waiters);
	philo->circle = ft_time();
	if (philo->number_of_eat == 0)
		return (4);
	return (1);
}

int	philo_sleep(t_philosopher *philo)
{
	philo_print(philo, "is sleeping\n");
	ft_usleep(ft_time() + philo->time_to_sleep * 1000);
	return (2);
}

int	philo_think(t_philosopher *philo)
{
	philo_print(philo, "is thinking\n");
	philo->state = HUNGRY;
	return (0);
}
