#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "libs.h"

typedef enum	e_state
{
	HUNGRY,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
}				t_state;

typedef struct s_philosopher
{
	char					current_fork;
	char					hand[2];
	int						id;
	char					*str_id;
	char					**collection_str;
	pid_t					pid;
	t_state					state;
	long long				circle;
	long long				after_eat;
	long long				after_sleep;
	long long				after_think;
	long long				last_meal;
	long long				number_of_eat;
}				t_philosopher;

typedef int	(*ft_states)(t_philosopher *ph);

typedef struct				s_info
{
	int						ready;
	int						count;
	int						all_alive;
	int						eaters;
	sem_t					*write_sem;
	sem_t					*sem;
	ft_states				actions[8];
	long long				t_start;
	long long				time_to_die;
	long long				time_to_eat;
	long long				time_to_sleep;
	long long				number_of_eat;
	t_philosopher			*phil;
}							t_info;

t_info	g_info;

#endif