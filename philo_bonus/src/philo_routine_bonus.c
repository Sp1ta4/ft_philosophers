/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:00:52 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/11 11:27:10 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	do_single_philo(t_philosopher *philo)
{
	log_action(philo, "has taken a fork", philo->table, 0);
	usleep(philo->table->time_to_die * 1000);
	log_action(philo, "died", philo->table, 1);
	free_data(philo->table);
	exit(1);
}

static void	try_take_forks_and_eat(t_philosopher *philo)
{
	sem_wait(philo->table->forks_sem);
	log_action(philo, "has taken a fork", philo->table, 0);
	sem_wait(philo->table->forks_sem);
	log_action(philo, "has taken a fork", philo->table, 0);
	log_action(philo, "is eating", philo->table, 0);
	got_eat_time(philo);
	usleep(philo->table->time_to_eat * 1000);
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
	sem_wait(philo->table->each_eat_sem);
	philo->meals_eaten++;
	sem_post(philo->table->each_eat_sem);
}

static void	*monitor_death(t_philosopher *philo)
{
	while (1)
	{
		check_die(philo);
		check_eat(philo);
		usleep(1000);
	}
	return (NULL);
}

static void	philosopher_routine(t_philosopher *philo)
{
	if (philo->table->philo_num == 1)
		do_single_philo(philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	got_eat_time(philo);
	pthread_create(&philo->monitoring_thread, NULL,
		(void *)monitor_death, philo);
	pthread_detach(philo->monitoring_thread);
	while (1)
	{
		try_take_forks_and_eat(philo);
		log_action(philo, "is sleeping", philo->table, 0);
		usleep(philo->table->time_to_sleep * 1000);
		log_action(philo, "is thinking", philo->table, 0);
		usleep(100);
	}
	exit(0);
}

void	create_philosophers(t_table *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].last_meal_time = data->start_time;
		data->philosophers[i].meals_eaten = 0;
		data->philosophers[i].table = data;
		data->start_time = get_time_in_ms();
		data->pids[i] = fork();
		if (data->pids[i] == 0)
			philosopher_routine(&data->philosophers[i]);
		else if (data->pids[i] == -1)
			throw_err(FORK_ERROR, data);
	}
}
