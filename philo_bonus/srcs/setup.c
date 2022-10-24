#include "philo_bonus.h"

int	ft_semclose(t_data *data)
{
	sem_close(data->sfork);
	sem_close(data->sprinter);
	sem_close(data->sdie);
	sem_close(data->sgoal);
	sem_unlink("/sem_sfork");
	sem_unlink("/sem_sprinter");
	sem_unlink("/sem_sdie");
	sem_unlink("/sem_sgoal");
	return (0);
}

int	ft_clean(t_data *data, t_philo *philo, int res)
{
	if (data->pid)
		free(data->pid);
	if (philo)
		free(philo);
	return (res);
}

t_philo	*ft_setphilo(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->n);
	if (!philo)
		return (0);
	while (i < data->n)
	{
		philo[i].id = i;
		philo[i].round = data->goal;
		philo[i].stop = 0;
		philo[i].data = data;
		i++;
	}
	return (philo);
}

int	ft_setup(t_data *data)
{
	sem_unlink("/sem_sfork");
	sem_unlink("/sem_sprinter");
	sem_unlink("/sem_sdie");
	sem_unlink("/sem_sgoal");
	data->sfork = sem_open("/sem_sfork", O_CREAT, 180, data->n);
	data->sprinter = sem_open("/sem_sprinter", O_CREAT, 180, 1);
	data->sdie = sem_open("/sem_sdie", O_CREAT, 180, 0);
	data->sgoal = sem_open("/sem_sgoal", O_CREAT, 180, 0);
	if (data->sfork == SEM_FAILED || data->sprinter == SEM_FAILED
		|| data->sdie == SEM_FAILED || data->sgoal == SEM_FAILED)
		return (1);
	data->pid = malloc(sizeof(pid_t) * data->n);
	if (!data->pid)
		return (1);
	return (0);
}

int	ft_getargs(t_data *data, int argc, char **argv)
{
	data->n = ft_atoi(argv[1]);
	data->ttdie = ft_atoi(argv[2]);
	data->tteat = ft_atoi(argv[3]);
	data->ttsleep = ft_atoi(argv[4]);
	data->goal = -1;
	if (argc == 6)
		data->goal = ft_atoi(argv[5]);
	if (data->n <= 0 || data->ttdie < 0 || data->tteat < 0 \
		|| data->ttsleep < 0 || (argc == 6 && data->goal < 0))
		return (1);
	return (0);
}
