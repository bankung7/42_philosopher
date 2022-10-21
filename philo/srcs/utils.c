#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	nbr;
	int	sign;

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
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

int	ft_log(char *str, int res)
{
	printf("%s\n", str);
	return (res);
}

int	ft_msg(t_philo *philo, ssize_t t, char *str)
{
	if (ft_isstop(philo->data) == 1)
		return (1);
	pthread_mutex_lock(&philo->data->printer);
	printf("%d\t%d %s\n", ft_timedif(t, philo->data->stime), philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->printer);
	return (0);
}

int ft_setstop(t_data *data)
{
	pthread_mutex_lock(&data->con);
	data->stop = 1;
	pthread_mutex_unlock(&data->con);
	return (0);
}

int ft_isstop(t_data *data)
{
	int t;

	t = 0;
	pthread_mutex_lock(&data->con);
	if (data->stop == 1)
		t = 1;
	pthread_mutex_unlock(&data->con);
	return (t);
}