#include "../includes/main.h"

static void	*philo_big_bro(void *ph)
{
	t_info	*info;

	info = (t_info *)ph;
	usleep(3000);
	while (1)
	{
		usleep(500);
		if (((ft_time() - info->phil[info->cur - 1].last_meal) / 1000 )
			>= info->time_to_die)
		{
			info->phil[info->cur - 1].state = DEAD;
			sem_wait(info->write_sem);
			printf("%lld %d died\n", (ft_time()
					- info->phil[info->cur - 1].time_start) / 1000,
				info->phil[info->cur - 1].id);
			sem_post(info->death);
		}
	}
	return ((void *)0);
}

static void	philo_life(t_philosopher *philo, t_info *info)
{
	pthread_t	thread;

	info->cur = philo->id;
	philo->time_start = ft_time();
	philo->last_meal = ft_time();
	if (pthread_create(&thread, NULL, philo_big_bro, info))
		ft_error("Pthread Error");
	pthread_detach(thread);
	while (philo->state < 3)
	{
		philo->state = philo_do_action(info, philo);
		if (philo->state > 4)
			break ;
		usleep(100);
	}
	exit(2);
}

static void	philo_init_philosophers(t_info *info)
{
	int	i;

	i = 0;
	info->phil = malloc(sizeof(t_philosopher) * info->count);
	info->eaters = info->count;
	while (i < info->count)
	{
		info->phil[i].number_of_eat = info->number_of_eat;
		info->phil[i].state = HUNGRY;
		info->phil[i].write_sem = info->write_sem;
		info->phil[i].time_to_eat = info->time_to_eat;
		info->phil[i].time_to_die = info->time_to_die;
		info->phil[i].time_to_sleep = info->time_to_sleep;
		info->phil[i].id = i + 1;
		i++;
	}
}

static void	philo_create_band(t_info *info)
{
	int			i;
	pthread_t	thread;

	thread = NULL;
	philo_init_semaphores(info);
	philo_init_philosophers(info);
	i = 0;
	while (i < info->count)
	{
		info->phil[i].pid = fork();
		if (0 == info->phil[i].pid)
			philo_life(&info->phil[i], info);
		else
			i++;
	}
	pthread_create(&thread, NULL, philo_wait, info);
	pthread_detach(thread);
	sem_wait(info->death);
	if (info->eaters)
		philo_terminate(info);
}

int	main(int argc, char *argv[])
{
	t_info	info;

	if (!philo_validation(argc, argv))
		return (1);
	info.count = ft_atoi(argv[1]);
	info.time_to_die = ft_atoi(argv[2]);
	info.time_to_eat = ft_atoi(argv[3]);
	info.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info.number_of_eat = ft_atoi(argv[5]);
	else
		info.number_of_eat = -1;
	philo_create_band(&info);
	philo_clear_sem_all(&info);
	philo_free(&info);
	return (0);
}
