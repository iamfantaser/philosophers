#include "../../includes/main.h"

void	ft_error(char *str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	write (2, str, len);
	exit(3);
}

void	philo_free(t_info *info)
{
	int i;

	i = 0;
	free(info->sem);
	free(info->phil);
	while (i < info->count)
		free(info->forks_name[i++]);
	free(info->forks_name);
}

char *philo_fork_name(int n)
{
	char	*str;
	char 	*result;
	int		i;
	int		j;
	
	i = 5;
	j = 0;
	result = malloc(sizeof(char) * 12);
	str = ft_ltoa_base(n, 10);
	result[0] = 'f';
	result[1] = 'o';
	result[2] = 'r';
	result[3] = 'k';
	result[4] = 's';
	while (str[j])
	{
		result[i] = str[j];
		i++;
		j++;
	}
	result[i] = '\0';
	free(str);
	return (result);
}

void	philo_wait(t_info *info)
{
	int 	status;
	pid_t	child;

	child = waitpid(0, &status, 0);
	status = WEXITSTATUS(status);
	if (status == 1)
	{
		philo_terminate(child, info);
		info->eaters = 0;
		philo_wait(info);
	}
	else if (status > 1 && info->eaters)
	{
		info->eaters -=1;
		philo_wait(info);
	}
}

