#include "philo.h"

int	ft_isdie(t_data *data, t_philo *philo)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < data->n)
	{
		pthread_mutex_lock(&philo[i].meal);
		sum += philo[i].round;
		if (ft_gettime() > philo[i].dtime)
		{
			ft_msg(&philo[i], ft_gettime(), "died");
			pthread_mutex_lock(&data->con);
			data->stop = 1;
			pthread_mutex_unlock(&data->con);
		}
		pthread_mutex_unlock(&philo[i].meal);
		i++;
	}
	if (sum == 0)
	{
		pthread_mutex_lock(&data->con);
		data->stop = 1;
		pthread_mutex_unlock(&data->con);
	}
	return (sum);
}

int	ft_control(t_data *data, t_philo *philo)
{
	int	sum;

	while (1)
	{
		sum = ft_isdie(data, philo); 
		if (data->stop == 1)
			return (1);
	}
	return (0);
}

void	*ft_dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (ft_gettime() < philo->data->stime)
		usleep(100);
	if (philo->id % 2 == 1)
		ft_think(philo);
	while (philo->data->stop == 0)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (0);
}

int	ft_philosopher(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->n);
	if (!philo)
		return (ft_clean(data, 1));
	ft_setphilo(data, philo);
	data->stime = ft_gettime() + (data->n * 5);
	while (i < data->n)
	{
		philo[i].dtime = data->stime + data->ttdie;
		pthread_create(&data->tid[i], NULL, ft_dining, (void *)&philo[i]);
		i++;
	}
	ft_control(data, philo);
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
