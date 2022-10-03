#include "philo.h"

void ft_control(t_data *data, t_philo *philo)
{
    int i;
    int sum;

    i = 0;
    while (1)
    {
        i = 0;
        sum = 0;
        while (i < data->n)
        {
            pthread_mutex_lock(&data->mcon);
            if (ft_gettime() > (philo[i].tlasteat + data->twait))
            {
                data->stage = -1;
                ft_msg(&philo[i], "died", 1);
                pthread_mutex_unlock(&data->mcon);
                return;
            }
            sum += philo[i].goal;
            if (sum == data->n)
                return ;
            pthread_mutex_unlock(&data->mcon);
            i++;
        }
        usleep(1000);
    }
}

void *ft_dinner(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (philo->data->stage == 0 && philo->goal != 1)
    {
        ft_pickfork(philo, philo->left);
        ft_pickfork(philo, philo->right);
        pthread_mutex_lock(&philo->data->mcon);
        philo->tlasteat = ft_gettime();
        ft_msg(philo, "is eating", 0);
        philo->round += 1;
        if (philo->round >= philo->data->goal)
            philo->goal = 1;
        pthread_mutex_unlock(&philo->data->mcon);
        ft_wait(philo->data->teat);
        ft_releasefork(philo);
        ft_msg(philo, "is sleeping", 0);
        ft_wait(philo->data->tsleep);
        ft_msg(philo, "is thinking", 0);
    }
    printf("%d stop looping\n", philo->pid + 1);
    return (0);
}

int ft_philosopher(t_data *data)
{
    int i;
    t_philo *philo;
    unsigned long time;

    i = 0;
    philo = ft_setphilo(data);
    if (!philo)
        return (ft_clean(data, 1));
    time = ft_gettime();
    while (i < data->n)
    {
        if (i % 2 == 1)
            usleep(100);
        philo[i].tstart = time;
        philo[i].tlasteat = time;
        philo[i].tdie = philo[i].tlasteat + data->twait;
        pthread_create(&data->tid[i], NULL, ft_dinner, (void *)&philo[i]);
        //pthread_detach(data->tid[i]);
        i++;
    }
    ft_control(data, philo);
    i = 0;
    while (i < data->n)
        pthread_join(data->tid[i++], NULL);
    free(philo);
    return (ft_clean(data, 0));
}

int main(int argc, char **argv)
{
    t_data data;

    // get argument
    if (argc < 5 || argc > 6)
        return (0);
    // set data
    if (ft_setdata(&data, argc, argv) == 1)
        return (1);

    // build thread and mutex
    if (ft_setup(&data) == 1)
        return (ft_clean(&data, 1));

    // run
    ft_philosopher(&data);
    return (0);
}