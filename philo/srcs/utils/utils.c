#include "../../includes/main.h"

void	philo_death_procedure(int id)
{
	int	i;

	i = 0;
	g_info->all_alive = 0;
	printf("%llu %d %s\n", (ft_time() - g_info->t_start) / 1000, id, "died");
	while (i < g_info->count - 1)
	{
		g_info->phil[i].number_of_eat = 0;
		g_info->phil[i++].state = DEAD;
	}
	g_info->ready = 0;
}

void	philo_print(char *str, int id)
{
	pthread_mutex_lock(g_info->w_mutex);
	if (g_info->all_alive != 0)
		printf("%llu %d %s\n", (ft_time() - g_info->t_start) / 1000, id, str);
	pthread_mutex_unlock(g_info->w_mutex);
}

void	philo_terminate(void)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(g_info->w_mutex);
	while (i < g_info->count)
	{
		pthread_mutex_destroy(g_info->phil[i].fork);
		free(g_info->phil[i].fork);
		free(g_info->phil[i].thread);
		i++;
	}
	free(g_info->phil);
	free(g_info->w_mutex);
	free(g_info);
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

int	philo_do_action(t_philosopher *philosopher)
{
	return (g_info->actions[philosopher->state](philosopher->id));
}
