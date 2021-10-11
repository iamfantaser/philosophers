#ifndef STRUCTURES_H
# define STRUCTURES_H
# include "libs.h"

typedef enum e_state
{
	HUNGRY,
	SLEEPING,
	THINKING,
	DEAD,
	SATISFIED,
}				t_state;

typedef struct s_philosopher
{
	char					hand[2];
	char					str[6];
	int						id;
	pid_t					pid;
	sem_t					*write_sem;
	sem_t					*death;
	pthread_t				*thread;
	t_state					state;
	long long				time_start;
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	long long				circle;
	long long				last_meal;
	long long				number_of_eat;
}				t_philosopher;

typedef struct s_info
{
	int						ready;
	int						count;
	int						eaters;
	int						cur;
	sem_t					*write_sem;
	sem_t					*sem;
	char					**forks_name;
	sem_t					*death;
	sem_t					*waiters;
	long long				t_start;
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	long long				number_of_eat;
	t_philosopher			*phil;
}							t_info;

#endif