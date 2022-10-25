/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:55:19 by vnilprap          #+#    #+#             */
/*   Updated: 2022/10/25 21:55:21 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (res);
}

int	ft_setphilo(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
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
		if (pthread_mutex_init(&philo[i].meal, NULL) != 0)
			return (1);
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
	if (!data->tid || !data->fork)
		return (ft_clean(data, 1));
	i = 0;
	while (i < data->n)
	{
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
	data->ttdie = ft_atoi(argv[2]);
	data->tteat = ft_atoi(argv[3]);
	data->ttsleep = ft_atoi(argv[4]);
	data->goal = -1;
	data->stop = 0;
	if (argc == 6)
		data->goal = ft_atoi(argv[5]);
	if (data->n <= 0 || data->ttdie < 0 || data->tteat < 0 \
		|| data->ttsleep < 0 || (argc == 6 && data->goal < 0))
		return (1);
	return (0);
}
