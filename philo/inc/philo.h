#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

// Structure
typedef struct s_data
{
    int n;
    int think;
    int eat;
    int sleep;
    int goal;
    int stage;
    pthread_t *tid;
    pthread_mutex_t *fork;
    pthread_mutex_t con;
}   t_data;

typedef struct s_philo
{
    int id;
    int left;
    int right;
    int round;
    ssize_t stime;
    ssize_t dtime;
    t_data *data;
}   t_philo;

// setup.c
int ft_log(char *str, int res);
int ft_clean(t_data *data, int res);
int ft_setphilo(t_data *data, t_philo *philo);
int ft_setup(t_data *data);
int ft_getargs(t_data *data, int argc, char **argv);

// utils.c
int ft_atoi(char *str);

#endif
