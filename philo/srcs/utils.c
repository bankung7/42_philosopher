#include "philo.h"

int	ft_timedif(unsigned long t1, unsigned long t2)
{
	return ((int)(t1- t2));
}

unsigned long ft_gettime(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

int	ft_atoi(char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
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
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		num = num * 10 + (str[i] -'0');
		i++;
	}
	return (num * sign);
}

int	ft_exit(char *str, t_data *data, t_philo *philo, int res)
{
	if (data)
	{
		if (data->fork)
			free(data->fork);
		free(data);
	}
	if (philo)
		free(philo);
	if (str != 0)
		printf("%s\n", str);
	return (res);
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
		pthread_mutex_destroy(&data->fork[i++]);
	pthread_mutex_destroy(&data->printer);
	pthread_mutex_destroy(&data->control);
}
