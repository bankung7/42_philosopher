#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

// structure

typedef struct  s_data
{
    int n;
    int twait;
    int teat;
    int tsleep;
    int goal;
    int stage;
    int print;
    pthread_t   *tid;
    pthread_mutex_t *fork;
    pthread_mutex_t mcon;
    pthread_mutex_t mprint;
}   t_data;

typedef struct  s_philo
{
    int pid;
    int left;
    int right;
    int stage;
    int round;
    int goal;
    unsigned long tstart;
    unsigned long tlasteat;
    unsigned long tdie;
    t_data *data;
}   t_philo;


// process.c
void ft_msg(t_philo *philo, char *str, int status);
void ft_pickfork(t_philo *philo, int fork);
void    ft_releasefork(t_philo *philo);
void    ft_wait(int t);

// setup.c
int ft_setup(t_data *data);
int ft_setdata(t_data *data, int argc, char **argv);
t_philo *ft_setphilo(t_data *data);

// utils.c
int ft_atoi(char *s);
int ft_clean(t_data *data, int res);
int ft_timedif(unsigned long t1, unsigned long t2);
unsigned long   ft_gettime(void);
int ft_clean(t_data *data, int res);

#endif
