#include "philo.h"

t_philo *ft_setphilo(t_data *data)
{
    int i;
    t_philo *philo;

    i = 0;
    philo = malloc(sizeof(t_philo) * data->n);
    if (!philo)
        return (0);
    while (i < data->n)
    {
        philo[i].pid = i;
        philo[i].round = 0;
        philo[i].left = i;
        philo[i].right = (i + 1) % data->n;
        philo[i].stage = 0;
        philo[i].goal = 0;
        philo[i].data = data;
        i++;
    }
    return (philo);
}

int ft_setup(t_data *data)
{
    int i;

    i = 0;
    data->tid = malloc(sizeof(pthread_t) * data->n);
    data->fork = malloc(sizeof(pthread_mutex_t) * data->n);
    if (!data->tid || !data->fork)
        return (1);
    while (i < data->n)
        pthread_mutex_init(&data->fork[i++], NULL);
    pthread_mutex_init(&data->mcon, NULL);
    pthread_mutex_init(&data->mprint, NULL);
    return (0);
}

int ft_setdata(t_data *data, int argc, char **argv)
{
    data->n = ft_atoi(argv[1]);
    data->twait = ft_atoi(argv[2]);
    data->teat = ft_atoi(argv[3]);
    data->tsleep = ft_atoi(argv[4]);
    if (argc == 6)
        data->goal = ft_atoi(argv[5]);
    else
        data->goal = -1;
    data->stage = 0;
    data->print = 0;
    return (0);
}