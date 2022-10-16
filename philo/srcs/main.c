#include "philo.h"

void	*ft_dining(void *arg)
{
    int i = 0;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
        if (ft_pickfork(philo) == 1)
            break ;

        ft_eat(philo);

        ft_msg(philo, ft_gettime(), "is sleeping");
        
        ft_releasefork(philo);

        ft_wait(philo->data->sleep);

        ft_msg(philo, ft_gettime(), "is thinking");
        i++;
	}
	return (0);
}

int	ft_philosopher(t_data *data)
{
	int		i;
	ssize_t	t;
	t_philo	*philo;

	i = 0;
	t = ft_gettime();
	philo = malloc(sizeof(t_philo) * data->n);
	if (!philo)
		return (ft_clean(data, 1));
	ft_setphilo(data, philo);
	while (i < data->n)
	{
		philo[i].stime = t;
		philo[i].dtime = t + data->think;
		pthread_create(&data->tid[i], NULL, ft_dining, (void *)&philo[i]);
		if (i % 2 == 0)
			usleep(100);
		i++;
	}
	i = 0;
	while (i < data->n)
		pthread_join(data->tid[i++], NULL);
	free(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_log("Incomplete Argument", 1));
	if (ft_getargs(&data, argc, argv) == 1 || ft_setup(&data) == 1)
		return (ft_log("Something wrong", 1));
	if (ft_philosopher(&data) == 1)
		return (ft_log("Something wrong", 1));
	ft_destroy(&data);
	ft_clean(&data, 0);
	return (0);
}
