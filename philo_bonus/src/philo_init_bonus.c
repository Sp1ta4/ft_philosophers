/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:37:00 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/16 14:44:12 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	init_semaphores(t_data *data)
{
	if (!safe_semaphore_init(&(data->forks), FORKS_SEM_NAME, data->philo_num))
		return (false);
	if (!safe_semaphore_init(&(data->log_sem), PRINT_SEM_NAME, 1))
		return (false);
	if (!safe_semaphore_init(&(data->data_sem), DATA_SEM_NAME, 1))
		return (false);
	if (!safe_semaphore_init(&(data->all_threads_ready), ALL_READY_SEM_NAME, 0))
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
		sem_init(&(philo->philo_sem), 0, 1);
		set_long(&philo->philo_sem, &philo->last_meal_time, get_time_in_ms());
		philo->data = data;
	}
}

bool	init_data(t_data *data)
{
	data->end_simulation = false;
	data->is_cleaned = false;
	data->philosophers = safe_malloc(sizeof(t_philo) * data->philo_num, data);
	if (!data->philosophers)
		return (false);
	data->pids = safe_malloc(sizeof(pid_t) * data->philo_num, data);
	if (!data->pids)
		return (false);
	if (!init_semaphores(data))
		return (false);
	philo_init(data);
	return (true);
}
