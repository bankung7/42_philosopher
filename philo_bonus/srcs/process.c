/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:05:13 by vnilprap          #+#    #+#             */
/*   Updated: 2022/10/26 11:34:14 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_think(t_philo *philo)
{
	ssize_t	t;

	t = philo->dtime - ft_gettime();
	if (t < 100)
		return (0);
	if (t / 2 > philo->data->tteat)
		ft_wait(philo->data->tteat);
	else
		ft_wait(t / 2);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	sem_wait(philo->data->sfork);
	ft_msg(philo, ft_gettime(), "has taken a fork", 0);
	sem_wait(philo->data->sfork);
	ft_msg(philo, ft_gettime(), "has taken a fork", 0);
	ft_msg(philo, ft_gettime(), "is eating", 0);
	sem_wait(philo->meal);
	philo->dtime = ft_gettime() + philo->data->ttdie;
	if (philo->round > 0)
		philo->round--;
	sem_post(philo->meal);
	ft_wait(philo->data->tteat);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_msg(philo, ft_gettime(), "is sleeping", 0);
	sem_post(philo->data->sfork);
	sem_post(philo->data->sfork);
	ft_wait(philo->data->ttsleep);
	ft_msg(philo, ft_gettime(), "is thinking", 0);
	return (0);
}
