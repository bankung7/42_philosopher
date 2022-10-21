#include "philo.h"

int	ft_onephilo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->left]);
	ft_msg(philo, ft_gettime(), "has taken a fork");
	ft_wait(philo, philo->data->ttdie * 2);
	pthread_mutex_unlock(&philo->data->fork[philo->left]);
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
	pthread_mutex_lock(&philo->data->fork[philo->left]);
	ft_msg(philo, ft_gettime(), "has taken a fork");
	pthread_mutex_lock(&philo->data->fork[philo->right]);
	ft_msg(philo, ft_gettime(), "has taken a fork");
	pthread_mutex_lock(&philo->meal);
	philo->dtime = ft_gettime() + philo->data->ttdie;
	pthread_mutex_unlock(&philo->meal);
	ft_msg(philo, ft_gettime(), "is eating");
	ft_wait(philo, philo->data->tteat);
	pthread_mutex_lock(&philo->meal);
	if (philo->round > 0)
		philo->round--;
	pthread_mutex_unlock(&philo->meal);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_msg(philo, ft_gettime(), "is sleeping");
	pthread_mutex_unlock(&philo->data->fork[philo->left]);
	pthread_mutex_unlock(&philo->data->fork[philo->right]);
	ft_wait(philo, philo->data->ttsleep);
	ft_msg(philo, ft_gettime(), "is thinking");
	return (0);
}
