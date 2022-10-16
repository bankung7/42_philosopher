#include "philo.h"

int ft_philosopher(t_data *data)
{
    t_philo *philo;

    philo = malloc(sizeof(t_philo) * data->n);
    if (!philo)
        return (ft_clean(data, 1));

    ft_setphilo(data, philo);


    free(philo);
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 5 || argc > 6)
        return (ft_log("Incomplete Argument", 1));

    // get argument
    if (ft_getargs(&data, argc, argv) == 1 || ft_setup(&data) == 1)
        return (ft_log("Something wrong", 1));

    if (ft_philosopher(&data) == 1)
        return (ft_log("Something wrong", 1));

    ft_clean(&data, 0);
    return (0);
}