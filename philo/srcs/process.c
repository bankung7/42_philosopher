#include "philo.h"

int ft_msg(t_philo *philo, unsigned long t, char *str)
{
    if (philo->data->stop == 1)
        return (1);
    printf("%ld\t%ld\t%ld\t%d %s\n", t % 10000, philo->dtime % 10000, ft_timedif(t, philo->data->stime), philo->id + 1, str);
    return (0);
}

int ft_pickfork(t_philo *philo, int fork)
{
    pthread_mutex_lock(&philo->data->fork[fork]);
    ft_msg(philo, ft_gettime(), "has taken a fork");
    return (0);
}

int ft_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->con);
    philo->round++;
    ft_msg(philo, ft_gettime(), "is eating");
    if (philo->round == philo->data->goal)
        philo->goal = 1;
    ft_wait(philo->data->eat);
    pthread_mutex_unlock(&philo->data->con);
    return (0);
}

int ft_releasefork(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->fork[philo->left]);
    pthread_mutex_unlock(&philo->data->fork[philo->right]);
    return (0);
}

int ft_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->con);
    ft_msg(philo, ft_gettime(), "is sleeping");
    pthread_mutex_unlock(&philo->data->con);
    ft_wait(philo->data->sleep);
    pthread_mutex_lock(&philo->data->con);
    ft_msg(philo, ft_gettime(), "is thinking");
    pthread_mutex_unlock(&philo->data->con);
    return (0);
}