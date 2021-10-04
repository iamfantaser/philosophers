#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libs.h"

typedef enum e_state
{
	HUNGRY,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	SATISFIED,
}				t_state;

typedef struct s_philosopher
{
	char					current_fork;
	short					hand[2];
	int						id;
	long long				circle;
	long long				last_meal;
	long long				number_of_eat;
	pthread_t				*thread;
	pthread_mutex_t			*fork;
	t_state					state;
}				t_philosopher;

typedef int	(*t_ft_states)(int id);

typedef struct s_info
{
	int						ready;
	int						count;
	int						all_alive;
	int						eaters;
	pthread_mutex_t			*w_mutex;
	t_ft_states				actions[8];
	long long				t_start;
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	long long				number_of_eat;
	t_philosopher			*phil;
}							t_info;

t_info		*g_info;

#endif