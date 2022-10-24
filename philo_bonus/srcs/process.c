#include "philo_bonus.h"

int	ft_onephilo(t_philo *philo)
{
	sem_wait(philo->data->sfork);
	ft_msg(philo, ft_gettime(), "has taken a fork");
	ft_wait(philo, philo->data->ttdie * 2);
	sem_post(philo->data->sfork);
	return (0);
}

int	ft_think(t_philo *philo)
{
	ssize_t	wtime;

	if (philo->data->ttdie - philo->data->tteat - philo->data->ttsleep < 100)
		return (0);
	wtime = philo->data->ttdie - (philo->dtime - ft_gettime());
	ft_wait(philo, wtime / 2);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	sem_wait(philo->data->sfork);
	ft_msg(philo, ft_gettime(), "has taken a fork");
	sem_wait(philo->data->sfork);
	ft_msg(philo, ft_gettime(), "has taken a fork");
	sem_wait(philo->meal);
	philo->dtime = ft_gettime() + philo->data->ttdie;
	sem_post(philo->meal);
	ft_msg(philo, ft_gettime(), "is eating");
	sem_wait(philo->meal);
	if (philo->round >= 0)
		philo->round--;
	if (philo->round == 0)
		sem_post(philo->data->sgoal);
	sem_post(philo->meal);
	ft_wait(philo, philo->data->tteat);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_msg(philo, ft_gettime(), "is sleeping");
	sem_post(philo->data->sfork);
	sem_post(philo->data->sfork);
	ft_wait(philo, philo->data->ttsleep);
	ft_msg(philo, ft_gettime(), "is thinking");
	return (0);
}
