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
	pthread_mutex_lock(&philo->data->printer);
	if (philo->data->iprint == 0)
		printf("%d\t%d %s\n", ft_timedif(t, philo->stime), philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->printer);
	return (0);
}
