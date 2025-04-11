/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:36:32 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/11 11:25:53 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_semaphore(sem_t **sem, const char *name,
		int value, t_table *data)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (*sem == SEM_FAILED)
		throw_err(SEMAPHORE_ERROR, data);
}

void	init_data(t_table *data, int argc, char **argv)
{
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || (argc == 6 && data->must_eat_count <= 0))
		throw_err(VALUE_ERROR, NULL);
	if (data->philo_num <= 0 || data->philo_num > MAX_PHILOS)
		throw_err(PHILO_ERROR, NULL);
	data->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
			* data->philo_num);
	if (!data->philosophers)
		throw_err(MALLOC_ERROR, data);
	data->pids = (pid_t *)malloc(sizeof(pid_t)
			* data->philo_num);
	if (!data->pids)
		throw_err(MALLOC_ERROR, data);
	init_semaphore(&data->forks_sem, FORKS_SEM_NAME, data->philo_num, data);
	init_semaphore(&data->each_eat_sem, EACH_EAT_SEM_NAME, 1, data);
	init_semaphore(&data->last_eat_time_sem, LAST_EAT_TIME_SEM_NAME, 1, data);
	init_semaphore(&data->print_sem, PRINT_SEM_NAME, 1, data);
}
