/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:05:07 by vnilprap          #+#    #+#             */
/*   Updated: 2022/10/26 12:08:54 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_control(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (ft_gettime() < philo->data->stime)
		usleep(1000);
	while (1)
	{
		sem_wait(philo->meal);
		if (ft_gettime() >= philo->dtime)
		{
			ft_msg(philo, ft_gettime(), "died", 1);
			ft_setdie(philo->data);
			break ;
		}
		if (philo->round == 0)
		{
			sem_post(philo->data->scount);
			sem_post(philo->meal);
			break ;
		}
		sem_post(philo->meal);
		usleep(1000);
	}
	return (0);
}

int	ft_dining(t_philo *philo)
{
	sem_wait(philo->data->scount);
	if (pthread_create(&philo->tid, NULL, ft_control, (void *)philo) != 0)
		return (ft_setdie(philo->data));
	pthread_detach(philo->tid);
	while (ft_gettime() < philo->data->stime)
		usleep(100);
	if (philo->id % 2 == 1)
		ft_think(philo);
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (0);
}

int	ft_philosopher(t_data *data, int i)
{
	t_philo	*philo;

	philo = ft_setphilo(data);
	if (!philo)
		return (ft_clean(data, 0, 1));
	data->stime = ft_gettime() + (data->n * 3);
	while (i < data->n)
	{
		philo[i].dtime = data->stime + data->ttdie;
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (ft_clean(data, philo, 1));
		else if (data->pid[i] == 0)
		{
			ft_dining(&philo[i]);
			exit(0);
		}
		i++;
	}
	while (ft_gettime() < philo->data->stime)
		usleep(100);
	ft_scount(data);
	ft_semclose(data);
	ft_clean(data, philo, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_log("Incomplete Argument", 1));
	if (ft_getargs(&data, argc, argv) == 1)
		return (ft_log("Invalid Argument", 1));
	if (ft_setup(&data) == 1)
		return (ft_log("Something wrong", 1));
	if (ft_philosopher(&data, 0) == 1)
		return (ft_log("Something wrong", 1));
	return (0);
}
