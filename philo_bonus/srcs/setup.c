/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:05:19 by vnilprap          #+#    #+#             */
/*   Updated: 2022/10/24 22:05:20 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_clean(t_data *data, t_philo *philo, int res)
{
	if (data->pid)
		free(data->pid);
	if (philo)
		free(philo);
	return (res);
}

t_philo	*ft_setphilo(t_data *data)
{
	int		i;
	char	*name;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->n);
	if (!philo)
		return (0);
	while (i < data->n)
	{
		name = ft_semname(i);
		philo[i].id = i;
		philo[i].round = data->goal;
		sem_unlink(name);
		philo[i].meal = sem_open(name, O_CREAT, 0644, 1);
		philo[i].data = data;
		free(name);
		i++;
	}
	return (philo);
}

int	ft_setup(t_data *data)
{
	ft_semunlink();
	data->sfork = sem_open("/sem_sfork", O_CREAT, 0644, data->n);
	data->sprinter = sem_open("/sem_sprinter", O_CREAT, 0644, 1);
	data->scount = sem_open("/sem_scount", O_CREAT, 0644, 0);
	if (data->sfork == SEM_FAILED || data->sprinter == SEM_FAILED
		|| data->scount == SEM_FAILED)
		return (1);
	data->pid = malloc(sizeof(pid_t) * data->n);
	if (!data->pid)
		return (1);
	return (0);
}

int	ft_getargs(t_data *data, int argc, char **argv)
{
	data->n = ft_atoi(argv[1]);
	data->ttdie = ft_atoi(argv[2]);
	data->tteat = ft_atoi(argv[3]);
	data->ttsleep = ft_atoi(argv[4]);
	data->goal = -1;
	if (argc == 6)
		data->goal = ft_atoi(argv[5]);
	if (data->n <= 0 || data->ttdie < 0 || data->tteat < 0 \
		|| data->ttsleep < 0 || (argc == 6 && data->goal < 0))
		return (1);
	return (0);
}
