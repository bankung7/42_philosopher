#include "philo.h"

int ft_atoi(char *s)
{
    int i;
    int sign;
    int num;

    i = 0;
    sign = 1;
    num = 0;
    while (s[i] && (s[i] == ' ' || s[i] == '\t'))
        i++;
    if (s[i] == '+' || s[i] == '-')
    {
        if (s[i] == '-')
            sign = -1;
        i++;
    }
    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            return (-1);
        num = num * 10 + (s[i] - '0');
        i++;
    }
    return (num * sign);
}

int ft_clean(t_data *data, int res)
{
    int i;

    i = 0;
    if (data->tid)
        free(data->tid);
    if (data->fork)
    {
        while (i < 0)
            pthread_mutex_destroy(&data->fork[i++]);
        pthread_mutex_destroy(&data->mcon);
        pthread_mutex_destroy(&data->mprint);
        free(data->fork);
    }
    return (res);
}

int ft_timedif(unsigned long t1, unsigned long t2)
{
    return ((int)(t1- t2));
}

unsigned long   ft_gettime(void)
{
    struct timeval t;

    gettimeofday(&t, NULL);
    return (t.tv_sec * 1000 + t.tv_usec / 1000);
}