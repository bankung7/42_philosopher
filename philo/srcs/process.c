#include "philo.h"

int	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->con);
	if (philo->data->stage == 1)
	{
		pthread_mutex_unlock(&philo->data->con);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->con);
	return (0);
}

int	ft_pickfork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->left]);
	pthread_mutex_lock(&philo->data->con);
	philo->data->ifork[philo->left] = philo->id;
	ft_msg(philo, ft_gettime(), "has taken a fork", philo->data->stage);
	pthread_mutex_unlock(&philo->data->con);
	pthread_mutex_lock(&philo->data->fork[philo->right]);
	pthread_mutex_lock(&philo->data->con);
	philo->data->ifork[philo->right] = philo->id;
	ft_msg(philo, ft_gettime(), "has taken a fork", philo->data->stage);
	pthread_mutex_unlock(&philo->data->con);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	ssize_t	t;

	t = ft_gettime();
	pthread_mutex_lock(&philo->data->con);
	philo->dtime = t + philo->data->think;
	ft_msg(philo, ft_gettime(), "is eating", philo->data->stage);
	if (philo->round > 0)
		philo->round--;
	pthread_mutex_unlock(&philo->data->con);
	ft_wait(philo->data->eat);
	return (0);
}

int	ft_clearfork(t_philo *philo)
{
	if (philo->data->ifork[philo->left] == philo->id)
	{
		philo->data->ifork[philo->left] = -1;
		pthread_mutex_unlock(&philo->data->fork[philo->left]);
	}
	if (philo->data->ifork[philo->right] == philo->id)
	{
		philo->data->ifork[philo->right] = -1;
		pthread_mutex_unlock(&philo->data->fork[philo->right]);
	}
	return (0);
}

int	ft_releasefork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->con);
	ft_msg(philo, ft_gettime(), "is sleeping", philo->data->stage);
	ft_clearfork(philo);
	pthread_mutex_unlock(&philo->data->con);
	ft_wait(philo->data->sleep);
	pthread_mutex_lock(&philo->data->con);
	ft_msg(philo, ft_gettime(), "is thinking", philo->data->stage);
	pthread_mutex_unlock(&philo->data->con);
	return (0);
}
