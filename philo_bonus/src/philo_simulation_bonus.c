/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:04:54 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/10 16:45:16 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_die(t_philosopher *philo)
{
	sem_wait(philo->table->last_eat_time_sem);
	if (get_time_in_ms() - philo->last_meal_time > philo->table->time_to_die)
	{
		log_action(philo, "died", philo->table, 1);
		free_data(philo->table);
		exit(1);
	}
	sem_post(philo->table->last_eat_time_sem);
}

void	check_eat(t_philosopher *philo)
{
	sem_wait(philo->table->each_eat_sem);
	if (philo->meals_eaten == philo->table->must_eat_count)
	{
		sem_post(philo->table->each_eat_sem);
		exit (0);
	}
	sem_post(philo->table->each_eat_sem);
}

void	start_simulation(t_table *data)
{
	int	status;
	int	i;

	create_philosophers(data);
	i = -1;
	while (++i < data->philo_num)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) > 0)
		{
			i = -1;
			while (++i < data->philo_num)
				kill(data->pids[i], SIGKILL);
			break ;
		}
	}
	free_data(data);
}
