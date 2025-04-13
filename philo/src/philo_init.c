/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:37:00 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/13 19:03:32 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_mutexes(t_data *data)
{
	if (!safe_mutex_handle(&data->log_mutex, INIT))
		return (false);
	if (!safe_mutex_handle(&data->data_mutex, INIT))
		return (false);
	return (true);
}

static void	philo_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].is_eat_full = false;
		data->philosophers[i].meals_count = 0;
		data->philosophers[i].first_fork = &data->forks[(i + 1) % data->philo_num];
		data->philosophers[i].second_fork = &data->forks[i];
		if (data->philosophers[i].id % 2)
		{
			data->philosophers[i].first_fork = &data->forks[i];
			data->philosophers[i].second_fork = &data->forks[(i + 1) % data->philo_num];
		}
		safe_mutex_handle(&data->philosophers[i].philo_mutex, INIT);
		set_long(&data->philosophers[i].philo_mutex, &data->philosophers[i].last_meal_time, get_time_in_ms());
		data->philosophers[i].data = data;
	}
}

bool	init_data(t_data *data)
{
	int	i;

	data->end_simulation = false;
	data->all_threads_ready = false;
	data->is_cleaned = false;
	data->philosophers = safe_malloc(sizeof(t_philo) * data->philo_num, data);
	if (!data->philosophers)
		return (false);
	data->forks = safe_malloc(sizeof(t_mtx) * data->philo_num, data);
	if (!data->forks)
		return (false);
	i = -1;
	while (++i < data->philo_num)
	{
		if(!safe_mutex_handle(&data->forks[i], INIT))
			return (false);
	}
	if (!init_mutexes(data))
		return (false);
	philo_init(data);
	return (true);
}
