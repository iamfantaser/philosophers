#include "../includes/main.h"


void	*philo_big_bro(void *ph)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)ph;
	while (1)
	{
		usleep(500);
		if ((ft_time() - philo->last_meal) / 1000 >= philo->time_to_die)
		{
			philo->state = DEAD;
			sem_wait(philo->write_sem);
			printf("%lld %d died\n", (ft_time() - philo->time_start) / 1000,
				philo->id);
			exit(1);
			break ;
		}
	}
	return ((void *)0);
}

void	philo_life(t_philosopher *philo, t_info *info)
{
	pthread_t	thread;

	while (info->lifes->__align != info->count)
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(500);
	philo->time_start = ft_time();
	philo->last_meal = ft_time();
	if (pthread_create(&thread, NULL, philo_big_bro, philo))
		ft_error("Pthread Error");
	pthread_detach(thread);
	while (philo->state < 4)
	{
		philo->circle = ft_time();
		philo->state = philo_do_action(info, philo);
		if (philo->state > 4)
			break ;
		usleep(100);
	}
	if (philo->state == DEAD)
		exit(1);
	exit(2);
}

void	philo_init_philosophers(t_info *info)
{
	int i;

	i = 0;
	info->phil = malloc(sizeof(t_philosopher) * info->count);
	info->eaters = info->count;
	while (i < info->count)
	{
		info->phil[i].number_of_eat = info->number_of_eat;
		info->phil[i].state = HUNGRY;
		info->phil[i].hand[0] = !((i + 1 )% 2);
		info->phil[i].hand[1] = (i + 1) % 2;
		info->phil[i].write_sem = info->write_sem;
		info->phil[i].time_to_eat = info->time_to_eat;
		info->phil[i].time_to_die = info->time_to_die;
		info->phil[i].time_to_sleep = info->time_to_sleep;
		info->phil[i].id = i + 1;
		i++;
	}
}

void	philo_init_semaphores(t_info *info)
{
	int	i;

	i = 0;
	sem_unlink("writer");
	sem_unlink("lifes");
	info->forks_name = malloc(sizeof(char *) * (info->count + 1));
	info->sem = malloc(sizeof(sem_t *) * (info->count + 1));
	while (i < info->count)
	{
		info->forks_name[i] = philo_fork_name(i);
		sem_unlink(info->forks_name[i++]);
	}
	i = 0;
	while (i < info->count)
	{
		info->sem[i] = sem_open(info->forks_name[i], O_CREAT, O_RDWR, 1);
		i++;
	}
	info->sem[i] = info->sem[0];
	info->forks_name[i] = 0;
	info->lifes = sem_open("lifes", O_CREAT, O_RDWR, 0);
	info->write_sem = sem_open("writer", O_CREAT, O_RDWR, 1);
}

void	philo_create_band(t_info *info)
{
	int	i;

	philo_init_semaphores(info);
	philo_init_philosophers(info);
	i = 0;
	while (i < info->count)
	{
		info->phil[i].pid = fork();
		if  (0 == info->phil[i].pid)
		{
			sem_post(info->lifes);
			philo_life(&info->phil[i], info);
		}
		else
			i++;
	}
	philo_wait(info);
}

int main(int argc, char *argv[])
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


// void	*philo_big_bro(void *ph)
// {
// 	t_info	*info;

// 	info = (t_info *)ph;
// 	while (1)
// 	{
// 		usleep(500);
// 		if ((ft_time() - info->phil[info->cur - 1].last_meal) / 1000 >= info->time_to_die)
// 		{
// 			printf(" delta = %lld real = %lld last_meal = %lld\n", 
// 				ft_time() - info->phil[info->cur - 1].last_meal / 1000, 
// 				ft_time(), info->phil[info->cur - 1].last_meal);
// 			info->phil[info->cur - 1].state = DEAD;
// 			sem_wait(info->write_sem);
// 			printf("%lld %d died\n", (ft_time() - info->phil[info->cur - 1].time_start) / 1000,
// 				info->phil[info->cur - 1].id);
// 			exit(1);
// 			break ;
// 		}
// 	}
// 	return ((void *)0);
// }
