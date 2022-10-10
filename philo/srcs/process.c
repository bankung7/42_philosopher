#include "philo.h"

int ft_msg(t_philo *philo, unsigned long t, char *str)
{
    pthread_mutex_lock(&philo->data->printer);
    if (philo->data->stop == 1)
        return (pthread_mutex_unlock(&philo->data->printer));
    printf("%ld\t%d %s\n", ft_timedif(t, philo->data->stime), philo->id + 1, str);
    pthread_mutex_unlock(&philo->data->printer);
    return (0);
}

int ft_think(t_philo *philo)
{
    while (1)
    {
        pthread_mutex_lock(&philo->data->con);
        if (philo->data->stop == 1)
        {
            pthread_mutex_unlock(&philo->data->con);
            return (1);
        }
        if (philo->data->ifork[philo->left] == 0 && philo->data->ifork[philo->right] == 0)
        {
            philo->stage = 1;
            philo->data->ifork[philo->left] = 1;
            philo->data->ifork[philo->right] = 1;
            pthread_mutex_unlock(&philo->data->con);
            return (0);
        }
        pthread_mutex_unlock(&philo->data->con);
        usleep(500);
    }
    return (0);
}

int ft_pickfork(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->con);
    if (philo->stage == 1)
    {
        pthread_mutex_lock(&philo->data->fork[philo->left]);
        ft_msg(philo, ft_gettime(), "has taken a fork");
        if (philo->data->n < 2)
        {
            philo->stage = -1;
            pthread_mutex_unlock(&philo->data->fork[philo->left]);
            pthread_mutex_unlock(&philo->data->con);
            return (1);
        }
        pthread_mutex_lock(&philo->data->fork[philo->right]);
        ft_msg(philo, ft_gettime(), "has taken a fork");
    }
    pthread_mutex_unlock(&philo->data->con);
    return (0);
}

int ft_eat(t_philo *philo)
{
    unsigned long t;

    t = ft_gettime();
    ft_msg(philo, t, "is eating");
    pthread_mutex_lock(&philo->data->con);
    philo->dtime = t + philo->data->think;
    philo->round++;
    if (philo->data->goal > 0 && philo->round == philo->data->goal)
        philo->goal = 1;
    pthread_mutex_unlock(&philo->data->con);
    ft_wait(philo->data->eat);
    return (0);
}

int ft_releasefork(t_philo *philo)
{
    pthread_mutex_unlock(&philo->data->fork[philo->left]);
    pthread_mutex_unlock(&philo->data->fork[philo->right]);
    pthread_mutex_lock(&philo->data->con);
    philo->data->ifork[philo->left] = 0;
    philo->data->ifork[philo->right] = 0;
    pthread_mutex_unlock(&philo->data->con);
    return (0);
}

int ft_sleep(t_philo *philo)
{
    ft_msg(philo, ft_gettime(), "is sleeping");
    ft_wait(philo->data->sleep);
    pthread_mutex_lock(&philo->data->con);
    philo->stage = 0;
    pthread_mutex_unlock(&philo->data->con);
    ft_msg(philo, ft_gettime(), "is thinking");
    return (0);
}