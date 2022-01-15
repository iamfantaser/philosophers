#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "libs.h"
# include "structures.h"

void		ft_usleep(long long stop, long long pause);
int			ft_atoi(const char *str);
void		ft_error(char *str);
long long	ft_time(void);
void		philo_end_procedure(t_info *info, char *id);
int			philo_validation(int argc, char **argv);
int			philo_do_action(t_info *info, t_philosopher *philo);
int			philo_put_fork(t_info *info, t_philosopher *ptr);
int			philo_sleep(t_philosopher *ptr);
int			philo_action(t_info *info, t_philosopher *ptr);
int			philo_think(t_philosopher *ptr);
void		philo_print(t_philosopher *philo, char *str);
void		philo_terminate(t_info *info);
void		philo_clear_sem_all(t_info *info);
void		philo_free(t_info *info);
void		philo_init_semaphores(t_info *info);
void		*philo_wait(void *info);

#endif
