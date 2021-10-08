#include "../../includes/main.h"

int	philo_take_fork(t_info *info, t_philosopher *philo)
{
	int n;

	n = philo->hand[0];
	philo_print(philo, "take a fork\n");
	sem_wait(info->sem[philo->id - 1 + n]);
	n = philo->hand[1];
	sem_wait(info->sem[philo->id - 1 + n]);
	if (info->lifes->__align != info->count)
		return (5);
	philo_print(philo, "take a fork\n");
	return (1);
}

int	philo_put_fork(t_info *info, t_philosopher *philo)
{
	int n;
	n = philo->hand[1];
	sem_post(info->sem[philo->id - 1 + n]);
	n = philo->hand[0];
	sem_post(info->sem[philo->id - 1 + n]);
	return (0);
}

int	philo_eat(t_info *info, t_philosopher *philo)
{
	philo->last_meal = ft_time();
	if (philo->number_of_eat == LLONG_MIN)
		philo->number_of_eat = -1;
	else
		philo->number_of_eat--;
	philo_print(philo, "is eating\n");
	ft_usleep(philo->circle + philo->time_to_eat * 1000);
	philo_put_fork(info, philo);
	philo->circle = ft_time();
	if (philo->number_of_eat == 0)
		return (5);
	return (2);
}

int	philo_sleep(t_philosopher *philo)
{
	philo_print(philo, "is sleeping\n");
	ft_usleep(philo->circle + philo->time_to_sleep * 1000);
	return (3);
}

int	philo_think(t_philosopher *philo)
{
	philo_print(philo, "is thinking\n");
	philo->state = HUNGRY;
	return (0);
}
