/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_async.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:22:43 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/14 21:15:35 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_philosopher_death(t_philo *philo)
{
	long	delta_time;
	long	last_time;

	if (get_boolean(&philo->philo_mutex, &philo->is_eat_full))
		return (false);
	last_time = get_long(&philo->philo_mutex, &philo->last_meal_time);
	delta_time = get_time_in_ms() - last_time;
	if (delta_time > philo->data->time_to_die)
	{
		log_action("died", philo);
		set_boolean(&philo->data->data_mutex,
			&philo->data->end_simulation, true);
		return (true);
	}
	return (false);
}

void	log_action(const char *action, t_philo *philo)
{
	long	timestamp_in_ms;

	if (get_boolean(&philo->philo_mutex, &philo->is_eat_full))
		return ;
	timestamp_in_ms = get_time_in_ms() - philo->data->start_simulation;
	safe_mutex_handle(&philo->data->log_mutex, LOCK);
	if (!is_simulation_finished(philo->data))
		printf("%ld %d %s\n", timestamp_in_ms, philo->id, action);
	safe_mutex_handle(&philo->data->log_mutex, UNLOCK);
}

void	*monitor_simulation(void *arg)
{
	t_data	*data;
	long	eat_enough;
	int		i;

	data = (t_data *)arg;
	while (!is_simulation_finished(data))
	{
		i = -1;
		eat_enough = 0;
		while (++i < data->philo_num)
		{
			if (check_philosopher_death(&data->philosophers[i]))
				break ;
			if (get_boolean(&data->philosophers[i].philo_mutex,
					&data->philosophers[i].is_eat_full))
				eat_enough++;
		}
		if (eat_enough == data->philo_num)
		{
			set_boolean(&data->data_mutex, &data->end_simulation, true);
			return (NULL);
		}
	}
	return (NULL);
}
