#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

// structure
typedef struct s_data
{
    int n;
    int wait;
    int eat;
    int sleep;
    int goal;
    int stage;
    int iprint;
    int *ifork;
    pthread_t *tid;
    pthread_mutex_t *fork;
    pthread_mutex_t fcon;
    pthread_mutex_t con;
    pthread_mutex_t printer;
}   t_data;

typedef struct s_philo
{
    int pid;
    int left;
    int right;
    int round;
    int stage;
    unsigned long stime;
    unsigned long dtime;
    t_data *data;
}   t_philo;

// process.c
int    ft_msg(t_philo *philo, char *str);
int    ft_pickfork(t_philo *philo, int fork);
int    ft_eat(t_philo *philo);
void    ft_releasefork(t_philo *philo);
void    ft_sleeping(t_philo *philo);

// setup.c
void    ft_setphilo(t_data *data, t_philo *philo);
int    ft_setup(t_data *data, int argc, char **argv);

// utils.c
int ft_atoi(char *str);
int ft_clean(t_data *data, int res);
unsigned long   ft_gettime(void);
int ft_timedif(unsigned long t1, unsigned long t2);
void    ft_wait(int t);

#endif
