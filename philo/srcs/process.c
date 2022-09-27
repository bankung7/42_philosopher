#include "philo.h"

void	ft_msg(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->printer);
	if (philo->data->is_somedie == 1)
		return ;
	printf("%d\t%d %s\n", ft_timedif(ft_gettime(), philo->data->stime), philo->pid + 1, str);
	pthread_mutex_unlock(&philo->data->printer);
}

void	ft_pickfork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->fork[fork]);
	ft_msg("has taken a fork", philo);
}

void	ft_dropfork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork[philo->left]);
	pthread_mutex_unlock(&philo->data->fork[philo->right]);
	ft_msg("is sleeping", philo);
}

void	ft_sleep(int time)
{
	unsigned long	ftime;
	
	ftime = ft_gettime() + time;
	while (1)
	{
		if (ft_gettime() >= ftime)
			return ;
		usleep(time / 100000);
	}
}
