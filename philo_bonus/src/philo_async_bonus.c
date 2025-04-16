/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_async_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                           a                     +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:22:43 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/15 21:11:44 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	check_philosopher_death(t_philo *philo)
{
	long	delta_time;
	long	last_time;

	if (get_boolean(&philo->philo_sem, &philo->is_eat_full))
		exit(0);
	last_time = get_long(&philo->philo_sem, &philo->last_meal_time);
	delta_time = get_time_in_ms() - last_time;
	if (delta_time > philo->data->time_to_die)
	{
		log_action("died", philo);
		sem_wait_safe(philo->data->log_sem);
		exit(1);
	}
	return (false);
}


void	log_action(const char *action, t_philo *philo)
{
	long	timestamp_in_ms;

	timestamp_in_ms = get_time_in_ms() - philo->data->start_simulation;
	sem_wait_safe(philo->data->log_sem);
	if (!is_simulation_finished(philo->data))
		printf("%ld %d %s\n", timestamp_in_ms, philo->id, action);
	sem_post_safe(philo->data->log_sem);
}


void	*monitor_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_simulation_finished(philo->data))
	{
		if (get_boolean(&philo->philo_sem, &philo->is_eat_full))
			exit(0);
		check_philosopher_death(philo);
	}
	return (NULL);
}
