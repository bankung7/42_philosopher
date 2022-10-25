/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:05:50 by vnilprap          #+#    #+#             */
/*   Updated: 2022/10/24 22:05:51 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!tmp)
		return (0);
	while (s1 && s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		tmp[i + j] = s2[j];
		j++;
	}
	tmp[i + j] = 0;
	return (tmp);
}

char	*ft_semname(int n, int i)
{
	int		num;
	char	*tmp;
	char	*output;

	num = n;
	if (num == 0)
		i++;
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (0);
	tmp[i] = 0;
	while (--i >= 0)
	{
		tmp[i] = (n % 10) + '0';
		n /= 10;
	}
	output = ft_strjoin("/sem_m", tmp);
	free(tmp);
	return (output);
}
