/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:05:37 by vnilprap          #+#    #+#             */
/*   Updated: 2022/10/26 12:07:17 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str, long nbr)
{
	int	i;
	int	sign;

	if (!str)
		return (-1);
	i = 0;
	sign = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nbr = nbr * 10 + (str[i] - '0');
		if (nbr < -2147483648 || nbr > 2147483647)
			return (-1);
		i++;
	}
	return (nbr * sign);
}

int	ft_log(char *str, int res)
{
	printf("%s\n", str);
	return (res);
}

int	ft_msg(t_philo *philo, ssize_t t, char *str, int stop)
{
	sem_wait(philo->data->sprinter);
	printf("%d\t%d %s\n", ft_timedif(t, philo->data->stime), philo->id + 1, str);
	if (stop == 1)
		return (0);
	sem_post(philo->data->sprinter);
	return (0);
}
