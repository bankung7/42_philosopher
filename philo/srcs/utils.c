#include "philo.h"

int ft_error(char *str, int res)
{
    printf("%s\n", str);
    return (res);
}

int ft_atoi(char *str)
{
    int i;
    int n;
    int sign;

    i = 0;
    n = 0;
    sign = 1;
    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (-1);
        n = n * 10 + (str[i] - '0');
        i++;
    }
    return (n * sign);
}

unsigned long ft_gettime(void)
{
    struct timeval t;

    gettimeofday(&t, NULL);
    return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

unsigned long ft_timedif(unsigned long t1, unsigned long t2)
{
    return ((t1 - t2));
}

void    ft_wait(int t)
{
    unsigned long ft;

    ft = ft_gettime() + t;
    while (ft_gettime() < ft)
        usleep(t / 1000);
}