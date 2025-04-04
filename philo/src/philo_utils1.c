/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:24:24 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/04 16:44:57 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, &(*s), 1);
		s++;
	}
}
void	throw_err(int nerr, t_table *data)
{
	(void)data;
	// if (data)
	// 	free_data(data);
	if (nerr == 0)
	{
		ft_putstr_fd("Error: Insufficient arguments.\n", 2);
		ft_putstr_fd("Usage: number_of_philosophers time_to_die time_to_eat", 2);
		ft_putstr_fd(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 2);
	}
	exit(1);
}

long get_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000L) + (tv.tv_usec / 1000L);
}

void log_action(t_philosopher *philo, const char *action, t_table *data)
{
    long timestamp_in_ms;

	timestamp_in_ms = get_time_in_ms() - data->start_time;
    pthread_mutex_lock(&data->log_mutex);
    printf("%ld %d %s\n", timestamp_in_ms, philo->id + 1, action);
    pthread_mutex_unlock(&data->log_mutex);
}

