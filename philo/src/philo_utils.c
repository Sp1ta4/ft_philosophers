/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:25:34 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/13 21:29:04 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	inc_long(t_mtx *mutex, long *dest)
{
	safe_mutex_handle(mutex, LOCK);
	(*dest)++;
	safe_mutex_handle(mutex, UNLOCK);
}


void	ft_usleep(long long time)
{
	long long	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < time)
		usleep(500);
}

static bool	destroy_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		if (!safe_mutex_handle(&data->forks[i], DESTROY))
			return (false);
	}
	safe_mutex_handle(&data->data_mutex, DESTROY);
	safe_mutex_handle(&data->log_mutex, DESTROY);
	return (true);
}

bool clean(t_data *data)
{
	if (!data || data->is_cleaned)
		return true;
	data->is_cleaned = true;
	if (!destroy_mutexes(data))
		return (false);
	if (data->forks)
		free(data->forks);
	if (data->philosophers)
		free(data->philosophers);
	if (data)
		free(data);
	return (true);
}

