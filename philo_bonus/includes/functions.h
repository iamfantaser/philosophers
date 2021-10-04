#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "libs.h"
#include "structures.h"

void		philo_death_procedure(int id);
void		ft_usleep(long long time);
int			ft_atoi(const char *str);
int 		ft_strlen(char *str);
long long	ft_time(void);
long long	ft_get_diff_time(long long start);
char		*ft_itoa_base(unsigned int num, int base);
char		*ft_ltoa_base(unsigned long long num, int base);
int			philo_validation(int argc, char **argv);
int			philo_do_action(t_philosopher *philo);
int			philo_put_fork(t_philosopher *ptr);
int			philo_sleep(t_philosopher *philosopher);
int			philo_take_fork(t_philosopher *philosopher);
int			philo_eat(t_philosopher *philosopher);
int			philo_think(t_philosopher *philosopher);
void		philo_print(char *str, char *id);
void		philo_terminate(void);

#endif