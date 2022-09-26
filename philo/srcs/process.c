#include "philo.h"

void	ft_msg(char *str, t_philo *philo, unsigned long t)
{
	pthread_mutex_lock(&philo->data->printer);
	printf("%d\t%d %s\n", ft_timedif(t, philo->data->stime), philo->pid + 1, str);
	pthread_mutex_unlock(&philo->data->printer);
}

void	ft_pickfork(t_philo *philo, int fork)
{
	pthread_mutex_lock(&philo->data->fork[fork]);
	ft_msg("has taken a fork", philo, ft_gettime());
}

void	ft_dropfork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork[philo->left]);
	pthread_mutex_unlock(&philo->data->fork[philo->right]);
	ft_msg("is sleeping", philo, ft_gettime());
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
