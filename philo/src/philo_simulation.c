/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:53:06 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/14 21:07:38 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_philo_is_ready(t_data *data)
{
	while (!get_boolean(&data->data_mutex, &(data->all_threads_ready)))
		;
}

static void	do_single_philo(t_philo *philo)
{
	log_action("has taken a fork", philo);
	ft_usleep(philo->data->time_to_die);
	log_action("died", philo);
	set_boolean(&philo->data->data_mutex, &philo->data->end_simulation, true);
}

void	try_eat(t_philo *philo)
{
	safe_mutex_handle(philo->first_fork, LOCK);
	log_action("has taken a fork", philo);
	safe_mutex_handle(philo->second_fork, LOCK);
	log_action("has taken a fork", philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time_in_ms());
	inc_long(&philo->philo_mutex, &philo->meals_count);
	log_action("is eating", philo);
	ft_usleep(philo->data->time_to_eat);
	if (philo->data->must_eat_count > 0
		&& get_long(&philo->philo_mutex, &philo->meals_count)
		>= philo->data->must_eat_count)
		set_boolean(&philo->philo_mutex, &philo->is_eat_full, true);
	safe_mutex_handle(philo->first_fork, UNLOCK);
	safe_mutex_handle(philo->second_fork, UNLOCK);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_philo_is_ready(philo->data);
	if (philo->data->philo_num == 1)
		do_single_philo(&philo->data->philosophers[0]);
	else
	{
		if (philo->id % 2 == 0)
			ft_usleep(100);
		while (!is_simulation_finished(philo->data))
		{
			try_eat(philo);
			log_action("is sleeping", philo);
			ft_usleep(philo->data->time_to_sleep);
			log_action("is thinking", philo);
		}
	}
	return (NULL);
}

bool	start_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		if (!safe_thread_handle(&data->philosophers[i].thread_id,
				philo_routine, &data->philosophers[i], CREATE))
			break ;
	}
	data->start_simulation = get_time_in_ms();
	set_boolean(&data->data_mutex, &data->all_threads_ready, true);
	if (data->philo_num > 1)
		safe_thread_handle(&data->monitor, monitor_simulation, data, CREATE);
	i = -1;
	while (++i < data->philo_num)
		safe_thread_handle(&data->philosophers[i].thread_id, NULL, NULL, JOIN);
	if (data->philo_num > 1)
		safe_thread_handle(&data->monitor, NULL, NULL, JOIN);
	set_boolean(&data->data_mutex, &data->end_simulation, true);
	return (true);
}
