/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:55:35 by vnilprap          #+#    #+#             */
/*   Updated: 2022/10/25 21:55:36 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_wait(t_philo *philo, int t)
{
	ssize_t	ft;

	ft = ft_gettime() + t;
	while (ft_gettime() < ft)
	{
		if (ft_isstop(philo->data) == 1)
			break ;
		usleep(100);
	}
}

int	ft_timedif(ssize_t t1, ssize_t t2)
{
	int	t;

	t = (int)(t1 - t2);
	return (t);
}

ssize_t	ft_gettime(void)
{
	ssize_t			time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}
