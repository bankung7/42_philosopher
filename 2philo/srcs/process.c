#include "philo.h"

void    ft_msg(char *str, t_philo *philo, int res)
{
    pthread_mutex_lock(&philo->data->printer);
    if (res >= 0 || philo->data->stage >= 0)
    {
        printf("%d\t%d %s\n", ft_timedif(ft_gettime(), philo->stime), philo->pid + 1, str);
        //pthread_mutex_lock(&philo->data->con);
        // if (res == 1)
        //     philo->data->stage = -1;
        //pthread_mutex_unlock(&philo->data->con);
    }
    pthread_mutex_unlock(&philo->data->printer);
}

void    ft_pickfork(t_philo *philo, int fork)
{
    pthread_mutex_lock(&philo->data->fork[fork]);
    pthread_mutex_lock(&philo->data->con);
    philo->stage = fork;
    pthread_mutex_unlock(&philo->data->con);
    ft_msg("has taken a fork", philo, 0);
}

void    ft_releasefork(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->con);
    philo->stage = 0;
    pthread_mutex_unlock(&philo->data->con);
    pthread_mutex_unlock(&philo->data->fork[philo->left]);
    pthread_mutex_unlock(&philo->data->fork[philo->right]);
}

void    ft_clearlock(t_data *data, t_philo *philo)
{
    int i;

    i = 0;
    while (i < data->n)
    {
        if (philo[i].stage == philo->right)
        {
            pthread_mutex_unlock(&data->fork[philo->right]);
            pthread_mutex_unlock(&data->fork[philo->left]);
        }
        else if (philo[i].stage == philo->left)
            pthread_mutex_unlock(&data->fork[philo->left]);
        i++;
    }
}