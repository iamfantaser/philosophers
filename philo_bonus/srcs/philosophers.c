#include "../includes/main.h"

static void	philo_big_bro(void)
{
	int	i;

	i = 0;
	while (!g_info.ready)
		usleep(10);
	while (1)
	{
		usleep(500);
		if ((g_info.phil[i].number_of_eat != 0 && (g_info.time_to_die
					- ((ft_time() - g_info.phil[i].last_meal) / 1000)) <= 0))
		{
			// philo_death_procedure(g_info.phil[i - 1].id);
			// break ;
		}
		else
		{
			i++;
			if (i == g_info.count - 1)
				i = 0;
			if (g_info.eaters == g_info.count)
				break ;
		}
	}
}

void	philo_life(t_philosopher *philo)
{
	int	i;

	if (philo->id % 2 == 0)
		usleep(100);
		write(1, "child", 5);
	philo->last_meal = ft_time();
	while (g_info.all_alive)
	{
		i = 0;
		philo->circle = ft_time();
		philo->state = philo_do_action(philo);
		if (philo->state > 4)
			break ;
		usleep(100);
	}
	g_info.eaters += 1;
	while (g_info.ready)
		usleep(100);
}

char	**philo_get_all_strings()
{

}

void	philo_create_band()
{
	int 	i;
	char	**collection;

	i = 0;
	g_info.phil = malloc(sizeof(t_philosopher) * g_info.count);
	g_info.sem = malloc(sizeof(sem_t) * g_info.count);
	g_info.write_sem = malloc(sizeof(sem_t));
	g_info.t_start = ft_time();
	g_info.all_alive = 1;
	g_info.actions[0] = philo_take_fork;
	g_info.actions[1] = philo_eat;
	g_info.actions[2] = philo_sleep;
	g_info.actions[3] = philo_think;
	collection = philo_get_all_strings();
	while (i < g_info.count)
	{
		g_info.phil[i].number_of_eat = g_info.number_of_eat;
		g_info.phil[i].state = HUNGRY;
		g_info.phil[i].last_meal = g_info.t_start;
		g_info.phil[i].collection_str = collection;
		g_info.phil[i].id = i + 1;
		g_info.phil[i].str_id = ft_itoa_base(i + 1, 10);
		i++;
	}
	while (i < g_info.count)
	{
		g_info.phil[i].pid = fork();
		if  (0 == g_info.phil[i].pid)
			philo_life(&g_info.phil[i]);
		else
			i++;
	}
	g_info.ready = 1;
}

int main(int argc, char *argv[])
{
	if (!philo_validation(argc, argv))
		return (1);
	g_info.count = ft_atoi(argv[1]);
	g_info.time_to_die = ft_atoi(argv[2]);
	g_info.time_to_eat = ft_atoi(argv[3]);
	g_info.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_info.number_of_eat = ft_atoi(argv[5]);
	else
		g_info.number_of_eat = -1;
	philo_create_band();
	philo_big_bro();
	philo_terminate();
	return (0);
}