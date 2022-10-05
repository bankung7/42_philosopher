#include "philo.h"

void    *ft_control(t_data *data, t_philo *philo)
{
    int i;

    i = 0;
    while (1)
    {
        while (i < data->n)
        {
            pthread_mutex_lock(&data->con);
            if (ft_gettime() > (philo[i].etime + philo[i].data->wait))
            {
                ft_msg("died", &philo[i], 1);
                data->stage = -1;
                pthread_mutex_unlock(&data->con);
                //printf("con end\n");
                return (0);
            }
            pthread_mutex_unlock(&data->con);
        }
        usleep(100);
    }
    return (0);
}

void    *ft_dining(void *arg)
{
    t_philo *philo;

    philo = (t_philo*)arg;

    while (1)
    {
        pthread_mutex_lock(&philo->data->con);
        if (philo->data->stage < 0)
        {
            pthread_mutex_unlock(&philo->data->con);
            return (0);
        }
        pthread_mutex_unlock(&philo->data->con);
        ft_pickfork(philo, philo->left);
        ft_pickfork(philo, philo->right);
        pthread_mutex_lock(&philo->data->con);
        philo->etime = ft_gettime();
        philo->round += 1;
        ft_msg("is eating", philo, 0);
        pthread_mutex_unlock(&philo->data->con);
        ft_wait(philo->data->eat);
        ft_releasefork(philo);
        ft_msg("is sleeping", philo, 0);
        ft_wait(philo->data->sleep);
        ft_msg("is thinking", philo, 0);
    }
    //printf("%d end\n", philo->pid);
    return (0);
}

int ft_philosopher(t_data *data)
{
    int i;
    t_philo *philo;

    i = 0;
    philo = malloc(sizeof(t_philo) * data->n);
    if (!philo)
        return (1);
    ft_setphilo(data, philo);
    while (i < data->n)
    {
        philo[i].stime = ft_gettime();
        philo[i].etime = philo[i].stime;
        pthread_create(&data->tid[i], NULL, ft_dining, (void*)&philo[i]);
        if (i % 2 == 0)
            usleep(300);
        i++;
    }
    ft_control(data, philo);
    i = 0;
    while (i < data->n)
        pthread_join(data->tid[i++], NULL);
    free(philo);
    //ft_clearlock(data, philo);
    return (0);
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
    //ft_clean(&data, 0);
    return (0);
}