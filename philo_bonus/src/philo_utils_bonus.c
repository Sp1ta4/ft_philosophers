/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:25:34 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/17 17:52:53 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	inc_long(sem_t *semaphore, long *dest)
{
	sem_wait_safe(semaphore);
	(*dest)++;
	sem_post_safe(semaphore);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = get_time_in_ms();
	while ((get_time_in_ms() - start) < time)
		usleep(500);
}

static bool	close_semaphores(t_data *data)
{
	if (data->forks)
		sem_destroy_safe(data->forks, FORKS_SEM_NAME);
	if (data->log_sem)
		sem_destroy_safe(data->log_sem, PRINT_SEM_NAME);
	if (data->data_sem)
		sem_destroy_safe(data->data_sem, DATA_SEM_NAME);
	if (data->all_threads_ready)
		sem_destroy_safe(data->all_threads_ready, ALL_READY_SEM_NAME);
	return (true);
}

bool	clean(t_data *data)
{
	int	i;

	if (!data || data->is_cleaned)
		return (true);
	data->is_cleaned = true;
	if (!close_semaphores(data))
		return (false);
	if (data->philosophers)
	{
		i = -1;
		while (++i < data->philo_num)
			sem_destroy(&(data->philosophers[i].philo_sem));
		free(data->philosophers);
		data->philosophers = NULL;
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	if (data)
		free(data);
	return (true);
}
