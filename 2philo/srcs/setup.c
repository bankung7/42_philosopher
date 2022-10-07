#include "philo.h"

void    ft_setphilo(t_data *data, t_philo *philo)
{
    int i;

    i = 0;
    while (i < data->n)
    {
        memset(&philo[i], 0, sizeof(t_philo));
        philo[i].pid = i;
        if (i % 2 == 0)
        {
            philo[i].left = (i + 1) % data->n;
            philo[i].right = i;
        }
        else
        {
            philo[i].left = i;
            philo[i].right = (i + 1) % data->n;
        }
        philo[i].data = data;
        i++;
    }
}

int    ft_setup(t_data *data, int argc, char **argv)
{
    int i;

    i = 0;
    data->n = ft_atoi(argv[1]);
    data->wait = ft_atoi(argv[2]);
    data->eat = ft_atoi(argv[3]);
    data->sleep = ft_atoi(argv[4]);
    data->goal = -1;
    if (argc == 6)
        data->goal = ft_atoi(argv[5]);
    data->stage = 0;
    data->tid = malloc(sizeof(pthread_t) * data->n);
    data->fork = malloc(sizeof(pthread_mutex_t) * data->n);
    data->ifork = malloc(sizeof(int) * data->n);
    if (!data->tid || !data->fork || !data->ifork)
        return (1);
    while (i < data->n)
        data->ifork[i++] = 0;
    i = 0;
    while (i < data->n)
        pthread_mutex_init(&data->fork[i++], NULL);
    pthread_mutex_init(&data->fcon, NULL);
    pthread_mutex_init(&data->con, NULL);
    pthread_mutex_init(&data->printer, NULL);
    return (0);
}
