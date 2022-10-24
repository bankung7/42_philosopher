#include "philo_bonus.h"

void	*ft_dcheck(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->meal);
		if (ft_gettime() > philo->dtime)
		{
			sem_wait(philo->data->sprinter);
			printf("%d\t%d %s\n", ft_timedif(ft_gettime(),
					philo->data->stime), philo->id + 1, "died");
			sem_post(philo->data->sdie);
			return (0);
		}
		sem_post(philo->meal);
	}
	return (0);
}

void	*ft_counting(void *arg)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)arg;
	while (i < data->n)
	{
		sem_wait(data->sgoal);
		i++;
	}
	sem_wait(data->sprinter);
	sem_post(data->sdie);
	return (0);
}

int	ft_killproc(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
		kill(data->pid[i++], SIGQUIT);
	sem_post(data->sdie);
	return (0);
}
