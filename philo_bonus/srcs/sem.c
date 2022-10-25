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

int ft_scount(t_data *data)
{
    int i;

    i = 0;
    while (i < data->n)
    {
        sem_wait(data->scount);
        printf("here %d\n", i);
        i++;
    }
    i = 0;
    while (i < data->n)
        kill(data->pid[i++], SIGKILL);
    i = 0;
    while (i < data->n)
        printf("%d\n", waitpid(data->pid[i++], 0, 0));
    printf("all child are back\n");
    return (0);
}

char *ft_semname(int n)
{
    int i;
    int num;
    char    *tmp;
    char    *output;

    i = 0;
    num = n;
    if (num == 0)
        return (ft_strjoin("/sem_m", "0"));
    while (num > 0)
    {
        num /= 10;
        i++;
    }
    if (num == 0)
        i++;
    tmp = malloc(sizeof(char) * (i + 1));
    if (!tmp)
        return (0);
    tmp[--i] = 0;
    while (--i >= 0)
    {
        tmp[i] = (n % 10) + '0';
        n /= 10;
    }
    output = ft_strjoin("/sem_m", tmp);
    free(tmp);
    return (output);
}