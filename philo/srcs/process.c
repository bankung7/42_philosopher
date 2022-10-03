#include "philo.h"

void ft_msg(t_philo *philo, char *str, int status)
{
    if (philo->data->print == 1)
        return ;
    pthread_mutex_lock(&philo->data->mprint);
    printf("%d\t%d %s\n", ft_timedif(ft_gettime(), philo->tstart), philo->pid + 1,str);
    philo->data->print = status;
    pthread_mutex_unlock(&philo->data->mprint);
}

void ft_pickfork(t_philo *philo, int fork)
{
    pthread_mutex_lock(&philo->data->fork[fork]);
    ft_msg(philo, "has taken a fork", 0);
}

void    ft_releasefork(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->fork[philo->left]);
    pthread_mutex_unlock(&philo->data->fork[philo->right]);
}

void    ft_wait(int t)
{
    unsigned long   ftime;

    ftime = ft_gettime() + t;
    while (ft_gettime() < ftime)
        usleep(100);
}