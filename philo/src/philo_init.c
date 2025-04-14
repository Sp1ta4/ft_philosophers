/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:37:00 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/14 21:09:13 by ggevorgi         ###   ########.fr       */
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
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->philo_num)
	{
		philo = &data->philosophers[i];
		philo->id = i + 1;
		philo->is_eat_full = false;
		philo->meals_count = 0;
		philo->first_fork = &data->forks[(i + 1) % data->philo_num];
		philo->second_fork = &data->forks[i];
		if (philo->id % 2)
		{
			philo->first_fork = &data->forks[i];
			philo->second_fork = &data->forks[(i + 1) % data->philo_num];
		}
		safe_mutex_handle(&philo->philo_mutex, INIT);
		set_long(&philo->philo_mutex, &philo->last_meal_time, get_time_in_ms());
		philo->data = data;
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
		if (!safe_mutex_handle(&data->forks[i], INIT))
			return (false);
	}
	if (!init_mutexes(data))
		return (false);
	philo_init(data);
	return (true);
}
