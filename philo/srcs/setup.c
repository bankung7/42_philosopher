#include "philo.h"

int	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
		pthread_mutex_destroy(&data->fork[i++]);
	return (0);
}

int	ft_clean(t_data *data, int res)
{
	if (data->tid)
		free(data->tid);
	if (data->fork)
		free(data->fork);
	if (data->ifork)
		free(data->ifork);
	return (res);
}

int	ft_setphilo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		memset(&philo[i], 0, sizeof(t_philo));
		philo[i].id = i;
		if (i % 2 == 1)
		{
			philo[i].left = i;
			philo[i].right = (i + 1) % data->n;
		}
		else
		{
			philo[i].left = (i + 1) % data->n;
			philo[i].right = i;
		}
		philo[i].round = data->goal;
		philo[i].data = data;
		i++;
	}
	return (0);
}

int	ft_setup(t_data *data)
{
	int	i;

	data->tid = malloc(sizeof(pthread_t) * data->n);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n);
	data->ifork = malloc(sizeof(int) * data->n);
	if (!data->tid || !data->fork || !data->ifork)
		return (ft_clean(data, 1));
	i = 0;
	while (i < data->n)
	{
		data->ifork[i] = -1;
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (ft_clean(data, 1));
		i++;
	}
	if (pthread_mutex_init(&data->con, NULL) != 0)
		return (ft_clean(data, 1));
	if (pthread_mutex_init(&data->printer, NULL) != 0)
		return (ft_clean(data, 1));
	return (0);
}

int	ft_getargs(t_data *data, int argc, char **argv)
{
	data->n = ft_atoi(argv[1]);
	data->think = ft_atoi(argv[2]);
	data->eat = ft_atoi(argv[3]);
	data->sleep = ft_atoi(argv[4]);
	data->goal = -1;
	data->stage = 0;
	if (argc == 6)
		data->goal = ft_atoi(argv[5]);
	if (data->n <= 0 || data->think < 0 || data->eat < 0 \
		|| data->sleep < 0 || (argc == 6 && data->goal < 0))
		return (1);
	return (0);
}
