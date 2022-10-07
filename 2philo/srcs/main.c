#include "philo.h"

void    ft_control(t_data *data, t_philo *philo)
{
    int i;
    int sum;
    
    while (1)
    {
        i = 0;
        sum = 0;
        while (i < data->n)
        {
            pthread_mutex_lock(&data->con);
            sum += philo[i].stage; 
            pthread_mutex_unlock(&data->con);
            i++;
        }
        if (sum == data->n)
        {
            pthread_mutex_lock(&data->con);
            data->stage = 1;
            pthread_mutex_unlock(&data->con);
            break;
        }
        usleep(100);
    }
}

void    *ft_dining(void *arg)
{
    t_philo *philo;

    philo = (t_philo*)arg;
    while (1)
    {
        ft_pickfork(philo, philo->left);
        ft_pickfork(philo, philo->right);
        if (ft_eat(philo) == 1)
            break ;
        ft_releasefork(philo);
        ft_sleeping(philo);
    }
    return (0);
}

int ft_philosopher(t_data *data)
{
    int i;
    t_philo *philo;
    unsigned long   stime;

    i = 0;
    philo = malloc(sizeof(t_philo) * data->n);
    if (!philo)
        return (1);
    ft_setphilo(data, philo);
    stime = ft_gettime();
    while (i < data->n)
    {
        philo[i].stime = stime;
        pthread_create(&data->tid[i], NULL, ft_dining, (void*)&philo[i]);
        if (i % 2== 0)
            usleep(100);
        i++;
    }
    ft_control(data, philo);
    i = 0;
    while (i < data->n)
        pthread_join(data->tid[i++], NULL);
    free(philo);
    return (1);   
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 5 || argc > 6)
        return (0);
    if (ft_setup(&data, argc, argv) == 1)
        return (ft_clean(&data, 1));
    if (ft_philosopher(&data) == 1)
        return (ft_clean(&data, 1));
    return (0);
}