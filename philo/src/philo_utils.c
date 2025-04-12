/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:25:34 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/12 13:28:25 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	destroy_mutexes(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < data->philo_num)
// 	{
// 		if (pthread_mutex_destroy(&(data->forks[i])) != 0)
// 			throw_err(PROGRAMM_ERROR, data);
// 		// if (pthread_mutex_destroy(&(data->philosophers[i].meals_mutex)) != 0)
// 		// 	throw_err(PROGRAMM_ERROR, data);
// 	}
// 	// pthread_mutex_destroy(&data->simulation_mutex);
// 	// pthread_mutex_destroy(&data->last_meal_time_mutex);
// 	// pthread_mutex_destroy(&data->log_mutex);
// }

void	clean(t_data *data)
{
	if (!data)
		return ;
	// destroy_mutexes(data);
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (data->philosophers)
	{
		free(data->philosophers);
		data->philosophers = NULL;
	}
}
