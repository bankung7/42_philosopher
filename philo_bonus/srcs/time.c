#include "philo_bonus.h"

int ft_setstop(t_philo *philo)
{
    //sem_wait(philo->meal);
    philo->stop = 1;
    //sem_post(philo->meal);
    return (0);
}

int ft_isstop(t_philo *philo)
{
    int t;

    sem_wait(philo->meal);
    t = philo->stop;
    sem_post(philo->meal);
    return (t);
}

void	ft_wait(t_philo *philo, int t)
{
	ssize_t	ft;

	ft = ft_gettime() + t;
	while (ft_gettime() < ft)
	{
		if (ft_isstop(philo) == 1)
			break ;
		usleep(100);
	}
}

int	ft_timedif(ssize_t t1, ssize_t t2)
{
	int	t;

	t = (int)(t1 - t2);
	return (t);
}

ssize_t	ft_gettime(void)
{
	ssize_t			time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}
