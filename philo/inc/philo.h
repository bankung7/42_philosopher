/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:56:19 by vnilprap          #+#    #+#             */
/*   Updated: 2022/10/26 12:01:42 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

// Structure
typedef struct s_data
{
	int				n;
	int				ttdie;
	int				tteat;
	int				ttsleep;
	int				goal;
	int				stop;
	ssize_t			stime;
	pthread_t		*tid;
	pthread_mutex_t	*fork;
	pthread_mutex_t	con;
	pthread_mutex_t	printer;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				left;
	int				right;
	int				round;
	ssize_t			dtime;
	pthread_mutex_t	meal;
	t_data			*data;
}	t_philo;

// setup.c
int		ft_destroy(t_data *data);
int		ft_clean(t_data *data, int res);
int		ft_setphilo(t_data *data, t_philo *philo);
int		ft_setup(t_data *data);
int		ft_getargs(t_data *data, int argc, char **argv);

// process.c
int		ft_onephilo(t_philo *philo);
int		ft_think(t_philo *philo);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);

// utils.c
int		ft_msg(t_philo *philo, ssize_t t, char *str);
int		ft_log(char *str, int res);
int		ft_atoi(char *str, long nbr);
int		ft_isstop(t_data *t_data);
int		ft_setstop(t_data *data);

// time.c
void	ft_wait(t_philo *philo, int t);
int		ft_timedif(ssize_t t1, ssize_t t2);
ssize_t	ft_gettime(void);

#endif
