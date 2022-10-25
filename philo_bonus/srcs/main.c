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

int	ft_dining(t_philo *philo)
{
	// create thread to check first
	printf("%d\n", philo->id + 1);
	sleep(philo->id);
	printf("I'm %d out\n", philo->id + 1);
	sem_post(philo->data->scount);
	return (0);
}

int	ft_philosopher(t_data *data)
{
	int	i;
	t_philo *philo;

	i = 0;
	philo = ft_setphilo(data);
	if (!philo)
		return (ft_clean(data, 0, 1));
	data->stime = ft_gettime() + (data->n * 2);
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
	ft_scount(data);
	ft_semclose(data);
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
	if (ft_philosopher(&data) == 1)
		return (ft_log("Something wrong", 1));
	return (0);
}
