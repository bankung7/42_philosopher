#include "philo.h"

int	ft_isdie(t_data *data, t_philo *philo, ssize_t t)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < data->n)
	{
		sum += philo[i].round;
		if (t > philo[i].dtime)
		{
			printf("%d\t%d died\n", ft_timedif(t, philo[i].stime), i + 1);
			data->stage = 1;
			ft_clearfork(&philo[i]);
			return (-(data->n + 1));
		}
		i++;
	}
	return (sum);
}

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
		pthread_mutex_lock(&data->con);
		sum = ft_isdie(data, philo, t);
		if (sum == 0 || (data->n + sum == -1))
		{
			data->stage = 1;
			return (pthread_mutex_unlock(&data->con));
		}
		pthread_mutex_unlock(&data->con);
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
	ft_destroy(&data);
	ft_clean(&data, 0);
	return (0);
}
