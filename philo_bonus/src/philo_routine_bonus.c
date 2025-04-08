/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:00:52 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/08 11:11:10 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*do_single_philo(t_philosopher *philo)
{
	log_action(philo, "has taken a fork", philo->table, 0);
	usleep(philo->table->time_to_die * 1000);
	log_action(philo, "died", philo->table, 1);
	philo->table->simulation_running = 0;
	return (NULL);
}

static void	try_take_forks_and_eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	sem_wait(philo->table->forks);
	log_action(philo, "has taken a fork", philo->table, 0);
	sem_wait(philo->table->forks);
	log_action(philo, "has taken a fork", philo->table, 0);
	log_action(philo, "is eating", philo->table, 0);
	usleep(philo->table->time_to_eat * 1000);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	philo->last_meal_time = philo->table->start_time;
	if (philo->table->num_philosophers == 1)
		return (do_single_philo(philo));
	while (1)
	{
		if (!philo->table->simulation_running)
			break ;
		log_action(philo, "is thinking", philo->table, 0);
		try_take_forks_and_eat(philo);
		log_action(philo, "is sleeping", philo->table, 0);
		usleep(philo->table->time_to_sleep * 1000);
	}
	return (NULL);
}

void wait_philosophers(t_philosopher *philosophers)
{
	int i;
	int status;

	i = 0;
	while (i < philosophers[0].table->num_philosophers)
	{
		if (waitpid(philosophers->table->pids[i], &status, 0) == -1)
		{
			ft_putstr_fd("waitpid failed\n", 2);
			exit(1);
		}
		i++;
	}
}

