#include "philo_bonus.h"

int ft_semclose(t_data *data)
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