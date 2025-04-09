/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:24:24 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/09 13:19:57 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (data)
		free_data(data);
	if (nerr == 0)
	{
		ft_putstr_fd("Error: Insufficient arguments.\n", 2);
		ft_putstr_fd("Usage: number_of_philosophers", 2);
		ft_putstr_fd(" time_to_die time_to_eat", 2);
		ft_putstr_fd(" time_to_sleep", 2);
		ft_putstr_fd(" [number_of_times_each_philosopher_must_eat]\n", 2);
	}
	else if (nerr == 1)
		ft_putstr_fd("Programm error!\n", 2);
	else if (nerr == 3)
	{
		ft_putstr_fd("Error: Invalid arguments.\n", 2);
		ft_putstr_fd("Your arguments need to be an unsigned integer\n", 2);
	}
	else if (nerr == 4)
	{
		ft_putstr_fd("Error: Invalid number of Philosophers.\n", 2);
		ft_putstr_fd("Num of philo must be 1-200\n", 2);
	}
	exit(1);
}

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	log_action(t_philosopher *philo, const char *action, t_table *table, int is_death)
{
	sem_wait(table->print_sem);
	printf("%ld %d %s\n", get_time_in_ms() - table->start_time, philo->id, action);
	if (!is_death)
		sem_post(table->print_sem);
}

