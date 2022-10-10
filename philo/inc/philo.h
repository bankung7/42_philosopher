#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <string.h>

# define DIE -1
# define THINK 0
# define EAT 1
# define SLEEP 2

// structure
typedef struct s_data
{
    int n;
    int think;
    int eat;
    int sleep;
    int goal;
    int stop;
    int *ifork;
    unsigned long stime;
    pthread_t   *tid;
    pthread_mutex_t *fork;
    pthread_mutex_t con;
    pthread_mutex_t printer;
}   t_data;

typedef struct s_philo
{
    int id;
    int left;
    int right;
    int round;
    int goal;
    int stage;
    unsigned long dtime;
    t_data *data;
}   t_philo;


// process.c
int ft_msg(t_philo *philo, unsigned long t, char *str);
int ft_think(t_philo *philo);
int ft_pickfork(t_philo *philo);
int ft_eat(t_philo *philo);
int ft_releasefork(t_philo *philo);
int ft_sleep(t_philo *philo);


// setup.c
int ft_clean(t_data *data, int res);
int ft_setvar(t_data *data, int argc, char **argv);
int ft_setup(t_data *data);
int ft_setphilo(t_data *data, t_philo *philo);

// utils.c
int ft_error(char *str, int res);
int ft_atoi(char *str);
unsigned long ft_gettime(void);
unsigned long ft_timedif(unsigned long t1, unsigned long t2);
void    ft_wait(int t);

#endif
