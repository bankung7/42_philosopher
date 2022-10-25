#include "philo_bonus.h"

int	ft_semunlink(void)
{
	sem_unlink("/sem_sfork");
	sem_unlink("/sem_sprinter");
	sem_unlink("/sem_scount");
	return (0);
}

int	ft_semclose(t_data *data)
{
	sem_close(data->sfork);
	sem_close(data->scount);
	sem_close(data->sprinter);
	return (0);
}

int	ft_setdie(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		sem_post(data->scount);
		i++;
	}
	return (0);
}

int	ft_killall(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
		kill(data->pid[i++], SIGKILL);
	return (0);
}

int	ft_scount(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		sem_wait(data->scount);
		i++;
	}
	ft_killall(data);
	i = 0;
	while (i < data->n)
		waitpid(data->pid[i++], 0, 0);
	return (0);
}
