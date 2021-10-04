#include "../../includes/main.h"

int	philo_take_fork(t_philosopher *philo)
{
	int n;

	n = philo->hand[0];
	sem_wait(&g_info.sem[philo->id - 1 + n]);
	philo_print("take a fork", philo->id);
	n = philo->hand[1];
	sem_wait(&g_info.sem[philo->id - 1 + n]);
	philo_print("take a fork", philo->id);
	return (1);
}

int	philo_put_fork(t_philosopher *philo)
{
	int n;

	n = philo->hand[1];
	sem_post(&g_info.sem[philo->id - 1 + n]);
	n = philo->hand[0];
	sem_post(&g_info.sem[philo->id - 1 + n]);
	return (0);
}

int	philo_eat(t_philosopher *philo)
{
	philo->last_meal = ft_time();
	if (philo->number_of_eat == LLONG_MIN)
		philo->number_of_eat = -1;
	else
		philo->number_of_eat--;
	philo_print("is eating", philo->str_id);
	ft_usleep(philo->circle + g_info.time_to_eat * 1000);
	philo->circle = ft_time();
	if (philo->number_of_eat == 0)
		return (5);
	return (2);
}

int	philo_sleep(t_philosopher *philo)
{
	philo_print("is sleeping", philo->str_id);
	ft_usleep(philo->circle + g_info.time_to_sleep * 1000);
	return (3);
}

int	philo_think(t_philosopher *philo)
{
	philo_print("is thinking", philo->str_id);
	philo->state = HUNGRY;
	return (0);
}
