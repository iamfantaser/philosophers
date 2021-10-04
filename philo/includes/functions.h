#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "libs.h"
# include "structures.h"

char				*ft_itoa_base(unsigned int num, int base);
char				*ft_ltoa_base(unsigned long long num, int base);
int					ft_atoi(const char *str);
long long			ft_time(void);
void				ft_usleep(long long stop_time);
void				philo_terminate(void);
void				philo_print(char *str, int id);
void				philo_death_procedure(int id);
int					philo_do_action(t_philosopher *philosopher);
int					philo_validation(int argc, char **argv);
int					philo_take_fork(int id);
int					philo_put_fork(int id);
int					philo_eat(int id);
int					philo_sleep(int id);
int					philo_think(int id);
int					philo_die(char *str, int id);

#endif