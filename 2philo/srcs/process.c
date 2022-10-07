#include "philo.h"

void    ft_msg(t_philo *philo, char *str)
{
    pthread_mutex_lock(&philo->data->printer);
    printf("%d\t%d %s\n", ft_timedif(ft_gettime(), philo->stime), philo->pid + 1, str);
    pthread_mutex_unlock(&philo->data->printer);
}

void    ft_pickfork(t_philo *philo, int fork)
{
    pthread_mutex_lock(&philo->data->fork[fork]);
    pthread_mutex_lock(&philo->data->fcon);
    philo->data->ifork[fork] = 1;
    pthread_mutex_unlock(&philo->data->fcon);
    ft_msg(philo, "has taken a fork");
}

int    ft_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->con);
    philo->etime = ft_gettime();
    philo->round += 1;
    if (philo->round >= philo->data->goal)
        philo->stage = 1;
    if (philo->data->stage == 1)
    {
        pthread_mutex_unlock(&philo->data->con);
        ft_releasefork(philo);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->con);
    ft_msg(philo, "is eating");
    ft_wait(philo->data->eat);
    return (0);
}

void    ft_releasefork(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->fork[philo->left]);
    pthread_mutex_unlock(&philo->data->fork[philo->right]);
    pthread_mutex_lock(&philo->data->fcon);
    philo->data->ifork[philo->left] = 0;
    philo->data->ifork[philo->right] = 0;
    pthread_mutex_unlock(&philo->data->fcon);
}

void    ft_sleeping(t_philo *philo)
{
    ft_msg(philo, "is sleeping");
    ft_wait(philo->data->sleep);
    ft_msg(philo, "is thinking");
}