#include "philo_bonus.h"

int ft_atoi(char *str)
{
    int i;
    int nbr;
    int sign;

    if (!str)
        return (-1);
    i = 0;
    nbr = 0;
    sign = 1;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
        nbr = nbr * 10 + (str[i] - '0');
        i++;
    }
    return (nbr * sign);
}

int ft_log(char *str, int res)
{
    printf("%s\n", str);
    return (res);
}

int ft_msg(t_philo *philo, ssize_t t, char *str)
{
    sem_wait(philo->data->sprinter);
    printf("%d\t%d %s\n", ft_timedif(t, philo->data->stime), philo->id + 1, str);
    sem_post(philo->data->sprinter);
    return (0);
}

void *ft_dcheck(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        sem_wait(philo->meal);
        if (ft_gettime() > philo->dtime)
        {
            sem_wait(philo->data->sprinter);
            printf("%d\t%d %s\n", ft_timedif(ft_gettime(), philo->data->stime), philo->id + 1, "died");
            sem_post(philo->data->sdie);
            sem_close(philo->meal);
            return (0);
        }
        sem_post(philo->meal);
        usleep(100);
    }
    return (0);
}

void *ft_counting(void *arg)
{
    int i;
    t_data *data;

    i = 0;
    data = (t_data *)arg;
    while (i < data->n)
    {
        sem_wait(data->sgoal);
        i++;
    }
    sem_wait(data->sprinter);
    sem_post(data->sdie);
    return (0);
}

int ft_killproc(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n)
    {
        kill(data->pid[i], SIGQUIT);
        i++;
    }
    sem_post(data->sdie);
    return (0);
}
