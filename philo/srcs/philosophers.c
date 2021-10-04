#include "../includes/main.h"

static void	philo_big_bro(void)
{
	int	i;

	i = 0;
	while (!g_info->ready)
		usleep(10);
	while (1)
	{
		usleep(500);
		if ((g_info->phil[i].number_of_eat != 0 && (g_info->time_to_die
					- ((ft_time() - g_info->phil[i].last_meal) / 1000)) <= 0))
		{
			philo_death_procedure(g_info->phil[i - 1].id);
			break ;
		}
		else
		{
			i++;
			if (i == g_info->count - 1)
				i = 0;
			if (g_info->eaters == g_info->count)
				break ;
		}
	}
}

static void	*ft_life(void *philosopher)
{
	t_philosopher	*ptr;

	ptr = (t_philosopher *)philosopher;
	pthread_detach(*ptr->thread);
	while (!g_info->ready)
		usleep(10);
	if (ptr->id % 2 == 0)
		usleep(100);
	ptr->last_meal = ft_time();
	while (g_info->all_alive)
	{
		ptr->circle = ft_time();
		ptr->state = philo_do_action(ptr);
		if (ptr->state > 4)
			break ;
		usleep(100);
	}
	g_info->eaters += 1;
	while (g_info->ready)
		usleep(100);
	return ((void *)0);
}

static void	philo_init(t_philosopher *tmp, int i)
{
	tmp->fork = malloc(sizeof(pthread_mutex_t));
	tmp->thread = malloc(sizeof(pthread_t));
	tmp->id = i + 1;
	tmp->hand[0] = !(tmp->id % 2);
	tmp->hand[1] = tmp->id % 2;
	tmp->state = HUNGRY;
	tmp->circle = 0;
	tmp->number_of_eat = g_info->number_of_eat;
	pthread_mutex_init(tmp->fork, NULL);
}

static int	philo_create_band(void)
{
	int	i;

	g_info->eaters = 0;
	g_info->ready = 0;
	g_info->all_alive = 1;
	g_info->phil = malloc(sizeof(t_philosopher) * (g_info->count + 1));
	g_info->actions[0] = philo_take_fork;
	g_info->actions[1] = philo_eat;
	g_info->actions[2] = philo_sleep;
	g_info->actions[3] = philo_think;
	g_info->w_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(g_info->w_mutex, NULL);
	i = -1;
	printf("count = %d\n", g_info->count);
	while (++i < g_info->count)
		philo_init(&g_info->phil[i], i);
	g_info->phil[i] = g_info->phil[0];
	i = -1;
	while (++i < g_info->count)
		pthread_create(g_info->phil[i].thread, NULL, ft_life, &g_info->phil[i]);
	g_info->t_start = ft_time();
	g_info->ready = 1;
	return (0);
}

int	main(int argc, char **argv)
{
	if (!philo_validation(argc, argv))
		return (1);
	g_info = (t_info *)malloc(sizeof(t_info));
	g_info->count = ft_atoi(argv[1]);
	g_info->time_to_die = ft_atoi(argv[2]);
	g_info->time_to_eat = ft_atoi(argv[3]);
	g_info->time_to_sleep = ft_atoi(argv[4]);
	if (g_info->count == 1)
	{
		printf("1 1 take a fork 1\n%s 1 died\n", argv[2]);
		return (0);
	}
	if (argc == 6)
		g_info->number_of_eat = ft_atoi(argv[5]);
	else
		g_info->number_of_eat = -1;
	philo_create_band();
	philo_big_bro();
	philo_terminate();
	return (0);
}
