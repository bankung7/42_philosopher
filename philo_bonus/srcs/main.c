#include "philo_bonus.h"

int ft_dining(t_philo *philo)
{
	sem_unlink("/sem_meal");
	philo->meal = sem_open("/sem_meal", O_CREAT, 180, 1);
	pthread_create(&philo->tid, NULL, ft_dcheck, (void*)philo);
	while (ft_gettime() < philo->data->stime)
		usleep(100);
	if (philo->data->n == 1)
		return (ft_onephilo(philo));
	if (philo->id % 2 == 1)
		ft_wait(philo, philo->data->ttdie / 2);
	while (1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (0);
}

int ft_philosopher(t_data *data)
{
	int i;
	pid_t id;
	t_philo *philo;

	i = 0;
	philo = ft_setphilo(data);
	data->stime = ft_gettime() + (data->n * 10 * 5);
	if (!philo)
		return (1);
	while (i < data->n)
	{
		id = fork();
		if (id == -1)
			return (0);
		else if (id == 0)
		{
			philo[i].dtime = data->stime + data->ttdie;
			ft_dining(&philo[i]);
			exit(0);
		}
		else
			data->pid[i] = id;
		i++;
	}
	pthread_create(&data->tid, NULL, ft_counting, (void*)data);
	pthread_detach(data->tid);
	sem_wait(data->sdie);
	ft_killproc(data);
	while (--i >= 0)
		waitpid(data->pid[i], 0, 0);
	free(philo);
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc < 5 || argc > 6)
		return (ft_log("Incomplete Argument", 1));
	if (ft_getargs(&data, argc, argv) == 1)
		return (ft_log("Invalid Argument", 1));
	if (ft_setup(&data) == 1)
		return (ft_log("Something wrong", 1));
	if (ft_philosopher(&data) == 1)
		return (ft_log("Something wrong", 1));
	free(data.pid);
	return (0);
}