#include "philo.h"

int ft_isdie(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->con);
    if (ft_gettime() > philo->dtime || philo->data->stage == 1)
    {
        if (philo->data->stage != 1)
        {
            ft_msg(philo, ft_gettime(), "died");
            philo->data->stage = 1;
        }
        pthread_mutex_lock(&philo->data->printer);
        philo->data->iprint = 1;
        pthread_mutex_unlock(&philo->data->printer);
        pthread_mutex_unlock(&philo->data->con);
        ft_releasefork(philo);
        return (1);
    }
    pthread_mutex_unlock(&philo->data->con);
    return (0);
}

int ft_pickfork(t_philo *philo)
{
    int i;
    int side;

    i = 0;
    while (i < 2)
    {
        if (ft_isdie(philo) == 1)
            return (1);
        if (i % 2 == 0)
            side = philo->left;
        else
            side = philo->right;
        pthread_mutex_lock(&philo->data->cfork);
        if (philo->data->ifork[side] == -1)
        {
            philo->data->ifork[side] = philo->id;
            pthread_mutex_unlock(&philo->data->cfork);
            pthread_mutex_lock(&philo->data->fork[side]);
            ft_msg(philo, ft_gettime(), "has taken a fork");
            i++;
        }
        else
            pthread_mutex_unlock(&philo->data->cfork);
    }
    return (0);
}

int ft_eat(t_philo *philo)
{
    ft_msg(philo, ft_gettime(), "is eating");
    pthread_mutex_lock(&philo->data->con);
    philo->dtime = ft_gettime() + philo->data->think;
    if (philo->round-- > 0)
        philo->data->count--;
    if (philo->data->count == 0)
        philo->data->stage = 1;
    pthread_mutex_unlock(&philo->data->con);
    ft_wait(philo->data->eat);
    return (0);
}

int ft_releasefork(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->cfork);
    if (philo->data->ifork[philo->right] == philo->id)
    {
        pthread_mutex_unlock(&philo->data->fork[philo->right]);
        philo->data->ifork[philo->right] = -1;
    }
    if (philo->data->ifork[philo->left] == philo->id)
    {
        pthread_mutex_unlock(&philo->data->fork[philo->left]);
        philo->data->ifork[philo->left] = -1;
    }
    pthread_mutex_unlock(&philo->data->cfork);
    return (0);
}
