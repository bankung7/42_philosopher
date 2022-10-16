#include "philo.h"

int	ft_monitor(t_data *data, t_philo *philo)
{
	int		i;
	int		sum;
	ssize_t	t;

	usleep(data->think / 2);
	while (1)
	{
		i = 0;
		sum = 0;
		t = ft_gettime();
		while (i < data->n)
		{
			pthread_mutex_lock(&data->con);
			sum += philo[i].round;
			if (t > philo[i].dtime)
			{
				printf("%d\t%d died\n", ft_timedif(t, philo[i].stime), i + 1);
				data->stage = 1;
				if (data->ifork[philo[i].left] == i)
				{
					data->ifork[philo[i].left] = -1;
					pthread_mutex_unlock(&data->fork[philo[i].left]);
				}
				if (data->ifork[philo[i].right] == i)
				{
					data->ifork[philo[i].right] = -1;
					pthread_mutex_unlock(&data->fork[philo[i].right]);
				}
				pthread_mutex_unlock(&data->con);
				return (1);
			}
			pthread_mutex_unlock(&data->con);
			i++;
		}
		if (sum == 0)
		{
			pthread_mutex_lock(&data->con);
			data->stage = 1;
			pthread_mutex_unlock(&data->con);
			return (1);
		}
	}
	return (0);
}

void	*ft_dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_think(philo) == 1)
			break ;
		ft_pickfork(philo);
		ft_eat(philo);
		ft_releasefork(philo);
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
	ft_monitor(data, philo);
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
	ft_clean(&data, 0);
	return (0);
}
