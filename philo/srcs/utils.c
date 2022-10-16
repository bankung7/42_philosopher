#include "philo.h"

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
        nbr = nbr * 10 + (str[i] - '0');
        i++;
    }
    return (nbr * sign);
}