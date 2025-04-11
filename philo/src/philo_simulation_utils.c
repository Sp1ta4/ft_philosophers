/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:40:53 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/11 10:19:02 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philosopher_death(t_philosopher *philo, long current_time)
{
	int		has_died;
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->table->last_meal_time_mutex);
	has_died = 0;
	if (current_time - philo->last_meal_time > table->time_to_die)
	{
		pthread_mutex_lock(&table->simulation_mutex);
		if (table->simulation_running)
		{
			log_action(philo, "died", philo->table, 1);
			table->simulation_running = 0;
			has_died = 1;
		}
		pthread_mutex_unlock(&table->simulation_mutex);
	}
	pthread_mutex_unlock(&philo->table->last_meal_time_mutex);
	return (has_died);
}

static int	has_eaten_enough(t_philosopher *philo, int must_eat_count)
{
	int	enough;

	pthread_mutex_lock(&philo->meals_mutex);
	enough = (philo->meals_eaten >= must_eat_count);
	pthread_mutex_unlock(&philo->meals_mutex);
	return (enough);
}

static int	check_all_ate_enough(t_table *table)
{
	int	eaten_enough_count;
	int	i;

	if (table->must_eat_count <= 0)
		return (0);
	eaten_enough_count = 0;
	i = 0;
	while (i < table->num_philosophers)
	{
		if (has_eaten_enough(&table->philosophers[i], table->must_eat_count))
			eaten_enough_count++;
		i++;
	}
	if (eaten_enough_count == table->num_philosophers)
	{
		pthread_mutex_lock(&table->simulation_mutex);
		table->simulation_running = 0;
		pthread_mutex_unlock(&table->simulation_mutex);
		return (1);
	}
	return (0);
}

static void	*monitor_deaths(void *arg)
{
	int		i;
	long	current_time;
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		current_time = get_time_in_ms();
		i = 0;
		while (i < table->num_philosophers)
		{
			if (check_philosopher_death(&table->philosophers[i], current_time))
				return (NULL);
			i++;
		}
		if (check_all_ate_enough(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	start_simulation(t_table *data)
{
	pthread_t	monitor_thread;

	data->simulation_running = 1;
	data->start_time = get_time_in_ms();
	create_philosophers(data);
	if (data->num_philosophers > 1)
		pthread_create(&monitor_thread, NULL, monitor_deaths, data);
	wait_philosophers(data->philosophers);
	if (data->num_philosophers > 1)
		pthread_join(monitor_thread, NULL);
}
