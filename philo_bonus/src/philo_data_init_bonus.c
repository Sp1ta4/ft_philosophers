/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:36:32 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/08 11:14:35 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_philosophers(t_table *data)
{
	int		i;
	pid_t	pid;

	data->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
			* data->num_philosophers);
	if (!data->philosophers)
		exit(2);
	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].last_meal_time = 0;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].table = data;
		pid = fork();
		pid = fork();
		if (pid == 0)
			philosopher_routine(&(data->philosophers[i]));
		else if (pid > 0)
			data->pids[i] = pid;
		else
			throw_err(5, data);
		i++;
	}
}

static void	create_forks(t_table *data)
{
	if (sem_init(data->forks_sem, 1, data->num_philosophers - 1) != 0)
		throw_err(1, data);
}

void	init_data(t_table *data, int argc, char **argv)
{
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->num_philosophers = ft_atoi(argv[1]);
	data->pids = malloc(sizeof(pid_t) * data->num_philosophers);
	if (!data->pids)
		throw_err(1, NULL);
	data->simulation_running = 0;
	data->start_time = 0;
	data->philosophers = NULL;
	data->forks_sem = NULL;
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || data->must_eat_count == 0)
		throw_err(3, NULL);
	if (data->num_philosophers <= 0 || data->num_philosophers > 200)
		throw_err(4, NULL);
	sem_init(data->all_ate_sem)
	create_forks(data);
}
