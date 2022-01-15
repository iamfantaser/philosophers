#include "../../includes/main.h"

int	philo_take_fork(int id)
{
	int	n;

	n = g_info->phil[id - 1].hand[1];
	pthread_mutex_lock(g_info->phil[id - 1 + n].fork);
	philo_print("has taken a fork", id);
	n = g_info->phil[id - 1].hand[0];
	pthread_mutex_lock(g_info->phil[id - 1 + n].fork);
	philo_print("has taken a fork", id);
	return (1);
}

int	philo_put_fork(int id)
{
	int	n;

	n = g_info->phil[id - 1].hand[0];
	pthread_mutex_unlock(g_info->phil[id - 1 + n].fork);
	n = g_info->phil[id - 1].hand[1];
	pthread_mutex_unlock(g_info->phil[id - 1 + n].fork);
	return (0);
}

int	philo_eat(int id)
{	
	g_info->phil[id - 1].last_meal = ft_time();
	if (g_info->phil[id - 1].number_of_eat == LLONG_MIN)
		g_info->phil[id - 1].number_of_eat = -1;
	else
		g_info->phil[id - 1].number_of_eat--;
	philo_print("is eating", id);
	ft_usleep(g_info->phil[id - 1].circle + g_info->time_to_eat * 1000, g_info->time_to_eat);
	philo_put_fork(id);
	g_info->phil[id - 1].circle = ft_time();
	if (g_info->phil[id - 1].number_of_eat == 0)
		return (5);
	return (2);
}

int	philo_sleep(int id)
{
	philo_print("is sleeping", id);
	ft_usleep(g_info->phil[id - 1].circle + g_info->time_to_sleep * 1000, g_info->time_to_eat);
	return (3);
}

int	philo_think(int id)
{
	philo_print("is thinking", id);
	g_info->phil[id - 1].state = HUNGRY;
	return (0);
}
