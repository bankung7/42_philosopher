#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

// struct
typedef struct	s_data
{
	int	n;
	int	wait;
	int	eat;
	int	sleep;
	int	musteat;
	int	is_somedie;
	int	fin_eat;
	unsigned long	stime;
	pthread_t *thd;
	pthread_mutex_t *fork;
	pthread_mutex_t printer;
	pthread_mutex_t control;
}	t_data;

typedef struct	s_philo
{
	int	pid;
	int	left;
	int	right;
	int	round;
	int	is_die;
	unsigned long	lasteat;
	t_data	*data;
}	t_philo;

// process.c
void	ft_msg(char *str, t_philo *philo);
void	ft_pickfork(t_philo *philo, int fork);
void	ft_dropfork(t_philo *philo);
void	ft_sleep(int time);

// utils.c
int	ft_atoi(char *str);
unsigned long	ft_gettime(void);
int	ft_timedif(unsigned long t1, unsigned long t2);
int	ft_exit(char *str, t_data *data, t_philo *philo, int res);
void	ft_destroy(t_data *data);

// setup.c
int	ft_setup(t_data *data, int argc, char **argv);
int	ft_setmutex(t_data *data);
int	ft_setphilo(t_data *data, t_philo *philo);

#endif
