#include "../../includes/main.h"

void	philo_death_procedure(int id)
{
	int		i;
	char	*time;

	i = 0;
	g_info.all_alive = 0;
	sem_wait(g_info.write_sem);
	time = ft_ltoa_base(ft_time() - g_info.t_start  / 1000, 10);
	write(1, time, ft_strlen(time));
	write(1, id, ft_strlen(id));
	write(1, "died\n", 5);
	sem_post(g_info.write_sem);
	while (i < g_info.count - 1)
	{
		kill(g_info.phil[i].pid, SIGKILL);
		g_info.phil[i++].state = DEAD;
	}
	g_info.ready = 0;
}

void	philo_print(char *str, char *id)
{
	char *time;

	sem_wait(g_info.write_sem);
	if (g_info.all_alive)
	{
		time = ft_ltoa_base(ft_time() - g_info.t_start  / 1000, 10);
		write(1, time, ft_strlen(time));
		write(1, id, ft_strlen(id));
		write(1, str, ft_strlen(str));
	}
	sem_post(g_info.write_sem);
}

void	philo_terminate(void)
{
	int i;

	i = 0;
	sem_close(g_info.write_sem);
	while (i < g_info.count)
	{
		sem_close(&g_info.sem[i]);
		i++;
	}
	free(g_info.phil);
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

int	philo_do_action(t_philosopher *philo)
{
	return (g_info.actions[philo->state](philo));
}
