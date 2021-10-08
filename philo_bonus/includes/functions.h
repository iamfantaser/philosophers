#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "libs.h"
#include "structures.h"

void		ft_usleep(long long time);
int			ft_atoi(const char *str);
int 		ft_strlen(char *str);
void		ft_error(char *str);
long long	ft_time(void);
long long	ft_get_diff_time(long long start);
char		*ft_itoa_base(unsigned int num, int base);
char		*ft_ltoa_base(unsigned long long num, int base);
void		philo_end_procedure(t_info *info, char *id);
int			philo_validation(int argc, char **argv);
int			philo_do_action(t_info *info, t_philosopher *philo);
int			philo_put_fork(t_info *info, t_philosopher *ptr);
int			philo_sleep(t_philosopher *ptr);
int			philo_take_fork(t_info *info, t_philosopher *ptr);
int			philo_eat(t_info *info, t_philosopher *ptr);
int			philo_think(t_philosopher *ptr);
void		philo_print(t_philosopher *philo, char *str);
void		philo_terminate(pid_t expetion_pid, t_info *info);
void		philo_clear_sem_all(t_info *info);
void		philo_free(t_info *info);
char 		*philo_fork_name(int n);
void		philo_wait(t_info *info);
void		*philo_big_bro(void *ph);

#endif