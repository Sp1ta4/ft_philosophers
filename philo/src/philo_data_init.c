/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:36:32 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/07 22:39:56 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philosophers(t_table *data)
{
	int	i;

	data->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
			* data->num_philosophers);
	if (!data->philosophers)
		exit(2);
	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].last_meal_time = 0;
		data->philosophers[i].left_fork = &(data->forks[i]);
		data->philosophers[i].right_fork = &(data->forks[(i + 1)
				% data->num_philosophers]);
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].table = data;
		pthread_mutex_init(&(data->philosophers[i].meals_mutex), NULL);
		pthread_create(&(data->philosophers[i].thread),
			NULL, philosopher_routine, &(data->philosophers[i]));
		i++;
	}
}

static void	create_forks(t_table *data)
{
	int	i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_philosophers);
	if (!data->forks)
		exit(2);
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&(data->forks[i++]), NULL) != 0)
			throw_err(1, data);
	}
}

void	destroy_philo_mutexes(t_table *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_destroy(&(data->forks[i])) != 0)
			throw_err(1, data);
		if (pthread_mutex_destroy(&(data->philosophers[i].meals_mutex)) != 0)
			throw_err(1, data);
		i++;
	}
}

void	init_data(t_table *data, int argc, char **argv)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_philosophers = ft_atoi(argv[1]);
	data->simulation_running = 0;
	data->start_time = 0;
	data->philosophers = NULL;
	data->forks = NULL;
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || data->must_eat_count == 0)
		throw_err(3, NULL);
	if (data->num_philosophers <= 0 || data->num_philosophers > 200)
		throw_err(4, NULL);
	pthread_mutex_init(&(data->simulation_mutex), NULL);
	pthread_mutex_init(&(data->last_meal_time_mutex), NULL);
	pthread_mutex_init(&(data->log_mutex), NULL);
	create_forks(data);
}
