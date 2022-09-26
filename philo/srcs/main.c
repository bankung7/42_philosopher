#include "philo.h"

void	ft_control(t_data *data, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->n)
		{
			pthread_mutex_lock(&data->control);
			if (ft_gettime() > philo[i].lasteat + data->wait)
			{
				ft_msg("died", philo, ft_gettime());
				data->is_somedie = 1;
				return ;
			}
			pthread_mutex_unlock(&data->control);
			i++;
		}
	}
}

void	*ft_dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	while (1)
	{
		ft_pickfork(philo, philo->left);
		ft_pickfork(philo, philo->right);
		ft_msg("is eating", philo, ft_gettime());
		ft_sleep(philo->data->eat);
		philo->lasteat = ft_gettime();
		philo->round++;
		ft_dropfork(philo);
		ft_sleep(philo->data->sleep);
		ft_msg("is thinking", philo, ft_gettime());
		ft_sleep(philo->data->wait);
	}
	return (0);
}

int	ft_philo(t_data *data)
{
	int	i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->n);
	if (!philo)
		return (ft_exit("Something wrong", data, 0, 1));
	ft_setphilo(data, philo);
	data->stime = ft_gettime();
	while (i < data->n)
	{
		if (i % 2 != 0)
			usleep(1000);
		philo[i].lasteat = ft_gettime();
		pthread_create(&philo[i].tid, NULL, ft_dining, (void*)&philo[i]);
		pthread_detach(philo[i].tid);
		i++;
	}
	ft_control(data, philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (ft_exit("Argument not complete", 0, 0, 1));
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (ft_setup(data, argc, argv) == 1 || ft_setmutex(data) == 1)
		return(ft_exit("Some argument wrong", data, 0, 1));
	ft_philo(data);
	ft_exit(0, data, 0, 0);
	return (0);
}
