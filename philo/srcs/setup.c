#include "philo.h"

int ft_clean(t_data *data, int res)
{
    int i;

    i = 0;
    if (data->tid)
        free(data->tid);
    if (data->ifork)
        free(data->ifork);
    if (data->fork && res == 1)
        free(data->fork);
    else
    {
        while (i < data->n)
            pthread_mutex_destroy(&data->fork[i++]);
        pthread_mutex_destroy(&data->con);
        pthread_mutex_destroy(&data->printer);
        free(data->fork);
    }
    return (res);
}

int ft_setvar(t_data *data, int argc, char **argv)
{
    data->n = ft_atoi(argv[1]);
    data->think = ft_atoi(argv[2]);
    data->eat = ft_atoi(argv[3]);
    data->sleep = ft_atoi(argv[4]);
    data->stop = 0;
    data->goal = -1;
    if (argc == 6)
        data->goal = ft_atoi(argv[5]);
    if (data->n <= 0 || data->think < 0 || data->eat < 0 \
        || data->sleep < 0 || (argc == 6 && data->goal < 0))
        return (1);
    // printf("%d %d %d %d\n", data->n, data->think, data->eat, data->sleep);
    return (0);
}

int ft_setup(t_data *data)
{
    int i;

    i = 0;
    data->tid = malloc(sizeof(pthread_t) * data->n);
    data->fork = malloc(sizeof(pthread_mutex_t) * data->n);
    data->ifork = malloc(sizeof(int) * data->n);
    if (!data->tid || !data->fork || !data->ifork)
        return (ft_clean(data, 1));
    while (i < data->n)
    {
        if (pthread_mutex_init(&data->fork[i], NULL))
            return (ft_clean(data ,2));
        data->ifork[i] = 0;
        i++;
    }
    if (pthread_mutex_init(&data->con, NULL))
        return (ft_clean(data, 2));
    if (pthread_mutex_init(&data->printer, NULL))
        return (ft_clean(data, 2));
    return (0);
}

int ft_setphilo(t_data *data, t_philo *philo)
{
    int i;

    i = 0;
    while (i < data->n)
    {
        memset(&philo[i], 0, sizeof(t_philo));
        philo[i].id = i;
        philo[i].stage = 0;
        philo[i].left = i;
        philo[i].right = (i + 1) % data->n;
        philo[i].data = data;
        i++;
    }
    return (0);
}