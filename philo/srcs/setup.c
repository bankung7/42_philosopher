#include "philo.h"

int	ft_setphilo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		philo[i].pid = i;
		philo[i].left = i;
		philo[i].right = (i + 1) % data->n;
		philo[i].round = 0;
		philo[i].is_die = 0;
		philo[i].data = data;
		i++;
	}
	return (0);
}

int	ft_setmutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n);
	if (!data->fork)
		return (1);
	while (i < data->n)
		pthread_mutex_init(&data->fork[i++], NULL);
	pthread_mutex_init(&data->printer, NULL);
	pthread_mutex_init(&data->control, NULL);
	return (0);	
}

int	ft_setup(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->n = ft_atoi(argv[1]);
	data->wait = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	data->musteat = -1;
	if (argc == 6)
		data->musteat = ft_atoi(argv[5]);
	if (data->n <= 0 || data->wait <= 0 || data->eat <= 0 \
			|| data->sleep <= 0)
		return (1);
	return (0);
}
