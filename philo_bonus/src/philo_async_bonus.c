/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_async_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:59:56 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/17 18:00:17 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_philosopher_death(t_philo *philo)
{
	long	delta_time;
	long	last_time;

	last_time = get_long(&philo->philo_sem, &philo->last_meal_time);
	delta_time = get_time_in_ms() - last_time;
	if (delta_time > philo->data->time_to_die)
	{
		log_action("died", philo);
		sem_wait_safe(philo->data->log_sem);
		set_boolean(philo->data->data_sem, &philo->data->end_simulation, true);
		return (-1);
	}
	return (0);
}

void	log_action(const char *action, t_philo *philo)
{
	long	timestamp_in_ms;

	timestamp_in_ms = get_time_in_ms() - philo->data->start_simulation;
	if (!is_simulation_finished(philo->data))
	{
		sem_wait_safe(philo->data->log_sem);
		printf("%ld %d %s\n", timestamp_in_ms, philo->id, action);
		sem_post_safe(philo->data->log_sem);
	}
}

void	*monitor_simulation(void *arg)
{
	t_philo	*philo;
	int		*status;

	philo = (t_philo *)arg;
	status = safe_malloc(sizeof(int), philo->data);
	*status = 0;
	while (!is_simulation_finished(philo->data))
	{
		if (get_boolean(&philo->philo_sem, &philo->is_eat_full))
		{
			set_boolean(philo->data->data_sem,
				&philo->data->end_simulation, true);
			*status = 1;
			return ((void *)status);
		}
		if (check_philosopher_death(philo) == -1)
		{
			*status = -1;
			return ((void *)status);
		}
	}
	return ((void *)status);
}
