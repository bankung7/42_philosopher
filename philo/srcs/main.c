#include "philo.h"

int ft_control(t_data *data, t_philo *philo)
{
    int i;
    int sum;
    unsigned long t;

    usleep(data->think / 2);
    while (1)
    {
        i = 0;
        sum = 0;
        t = ft_gettime();
        pthread_mutex_lock(&data->con);
        while (i < data->n)
        {
            sum += philo[i].goal;
            if (philo[i].stage != 1 && philo[i].dtime < t)
            {
                ft_msg(&philo[i], t, "died");
                data->stop = 1;
                pthread_mutex_unlock(&data->con);
                //printf("======== > main die here\n");
                return (0);
            }
            i++;
        }
        if ((data->goal > 0 && sum == data->n))
        {
            data->stop = 1;
            pthread_mutex_unlock(&data->con);
            //printf("======== > main end here\n");
            return (0);
        }
        pthread_mutex_unlock(&data->con);
        usleep(200);
    }
    return (0);
}

void *ft_dining(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;

    while (1)
    {
        if (ft_think(philo) == 1 || ft_eat(philo) == 1)
            break ;
        ft_releasefork(philo);
        ft_sleep(philo);
    }
    ft_releasefork(philo);
    //printf("%d ====> end\n", philo->id);
    return (0);
}

int ft_philosopher(t_data *data)
{
    int i;
    t_philo *philo;

    i = 0;
    philo = malloc(sizeof(t_philo) * data->n);
    if (!philo)
        return (ft_clean(data, 2));
    ft_setphilo(data, philo);
    data->stime = ft_gettime();
    printf("curt\tdtime\tintv\tactivity\n");
    while (i < data->n)
    {
        philo[i].dtime = data->stime + data->think;
        pthread_create(&data->tid[i], NULL, &ft_dining, (void *)&philo[i]);
        if (i % 2 == 0)
            usleep(100);
        i++;
    }
    ft_control(data, philo);
    i = 0;
    while (i < data->n)
        pthread_join(data->tid[i++], NULL);
    free(philo);
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 5 || argc > 6)
        return (ft_error("Invalid Argument", 1));
    if (ft_setvar(&data, argc, argv) != 0)
        return (ft_error("Some argument was wrong", 1));
    if (ft_setup(&data) != 0)
        return (ft_error("Something wrong", 1));
    if (ft_philosopher(&data) != 0)
        return (ft_error("Philo error", 1));
    return (ft_clean(&data, 0));
}