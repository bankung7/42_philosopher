/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:04:53 by vnilprap          #+#    #+#             */
/*   Updated: 2022/10/24 22:04:56 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

// Structure
typedef struct s_data
{
	int			n;
	int			ttdie;
	int			tteat;
	int			ttsleep;
	int			goal;
	pid_t		*pid;
	sem_t		*sfork;
	sem_t		*scount;
	sem_t		*sprinter;
	ssize_t		stime;
	pthread_t	tid;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			round;
	sem_t		*meal;
	t_data		*data;
	ssize_t		dtime;
	pthread_t	tid;
}	t_philo;

// setup.c
int		ft_semclose(t_data *data);
int		ft_clean(t_data *data, t_philo *philo, int res);
t_philo	*ft_setphilo(t_data *data);
int		ft_setup(t_data *data);
int		ft_getargs(t_data *data, int argc, char **argv);

// process.c
int		ft_onephilo(t_philo *philo);
int		ft_think(t_philo *philo);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);

// utils.c
int		ft_isstop(t_philo *philo);
int		ft_msg(t_philo *philo, ssize_t t, char *str);
int		ft_log(char *str, int res);
int		ft_atoi(char *str);

// utils2.c
char	*ft_strjoin(char *s1, char *s2);

// time.c
void	ft_wait(int t);
int		ft_timedif(ssize_t t1, ssize_t t2);
ssize_t	ft_gettime(void);

// sem.c
int		ft_semunlink(void);
int		ft_semclose(t_data *data);
int 	ft_scount(t_data *data);
char *ft_semname(int  n);

#endif
