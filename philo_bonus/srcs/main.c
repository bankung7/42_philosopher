/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:05:07 by vnilprap          #+#    #+#             */
/*   Updated: 2022/10/24 22:05:08 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_control(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_create(&data->tid, NULL, ft_counting, (void *)data);
	pthread_detach(data->tid);
	sem_wait(data->sdie);
	ft_killproc(data);
	while (i < data->n)
		waitpid(data->pid[i++], 0, 0);
	ft_clean(data, philo, 0);
	return (0);
}

int	ft_dining(t_philo *philo)
{
	sem_unlink("/sem_meal");
	philo->meal = sem_open("/sem_meal", O_CREAT, 180, 1);
	pthread_create(&philo->tid, NULL, ft_dcheck, (void *)philo);
	pthread_detach(philo->tid);
	while (ft_gettime() < philo->data->stime)
		usleep(100);
	if (philo->data->n == 1)
		return (ft_onephilo(philo));
	if (philo->id % 2 == 1)
		ft_wait(philo, philo->data->ttdie / 2 - (philo->data->ttdie % 100));
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
	pid_t	id;
	t_philo	*philo;

	philo = ft_setphilo(data);
	if (!philo)
		return (ft_clean(data, 0, 1));
	data->stime = ft_gettime() + (data->n * 10 * 5);
	while (i < data->n)
	{
		id = fork();
		if (id == -1)
			return (ft_clean(data, philo, 1));
		else if (id == 0)
		{
			philo[i].dtime = data->stime + data->ttdie;
			ft_dining(&philo[i]);
			exit(0);
		}
		else
			data->pid[i] = id;
		i++;
	}
	ft_control(data, philo);
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
