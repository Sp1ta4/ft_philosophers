/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:14:13 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/10 16:37:47 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_isspace(int symbol)
{
	return (symbol == ' ' || (symbol >= '\t' && symbol <= '\r'));
}

static char	*ft_trim_start(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	return (&str[i]);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		result;
	char	*nptr_cpy;

	result = 0;
	nptr_cpy = ft_trim_start((char *)nptr);
	if (*nptr_cpy == '-')
		throw_err(VALUE_ERROR, NULL);
	if (*nptr_cpy == '+')
		nptr_cpy++;
	while (ft_isdigit(*nptr_cpy))
	{
		if (result > (INT_MAX / 10)
			|| (result == INT_MAX / 10
				&& *nptr_cpy - '0' > INT_MAX % 10))
			throw_err(VALUE_ERROR, NULL);
		result = result * 10 + (*nptr_cpy - '0');
		nptr_cpy++;
	}
	if (*nptr_cpy != '\0' && !ft_isdigit(*nptr_cpy))
		throw_err(VALUE_ERROR, NULL);
	return (result);
}

void	free_data(t_table *data)
{
	if (!data)
		return ;
	if (data->philosophers)
	{
		free(data->philosophers);
		data->philosophers = NULL;
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (data->forks_sem)
		sem_close(data->forks_sem);
	if (data->print_sem)
		sem_close(data->print_sem);
	if (data->each_eat_sem)
		sem_close(data->each_eat_sem);
	if (data->last_eat_time_sem)
		sem_close(data->last_eat_time_sem);
	sem_unlink(FORKS_SEM_NAME);
	sem_unlink(PRINT_SEM_NAME);
	sem_unlink(EACH_EAT_SEM_NAME);
	sem_unlink(LAST_EAT_TIME_SEM_NAME);
}
