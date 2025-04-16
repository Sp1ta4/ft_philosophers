/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:53:06 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/16 14:54:16 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	do_single_philo(t_philo *philo)
{
	log_action("has taken a fork", philo);
	ft_usleep(philo->data->time_to_die);
	log_action("died", philo);
	set_boolean(philo->data->data_sem, &philo->data->end_simulation, true);
	exit(0);
}

void    try_eat(t_philo *philo)
{
    sem_wait_safe(philo->data->forks);
    log_action("has taken a fork", philo);
    sem_wait_safe(philo->data->forks);
    log_action("has taken a fork", philo);
    set_long(&philo->philo_sem, &philo->last_meal_time, get_time_in_ms());
    inc_long(&philo->philo_sem, &philo->meals_count);
    log_action("is eating", philo);
    ft_usleep(philo->data->time_to_eat);
    if (philo->data->must_eat_count > 0
        && get_long(&philo->philo_sem, &philo->meals_count)
        >= philo->data->must_eat_count)
        set_boolean(&philo->philo_sem, &philo->is_eat_full, true);
    sem_post_safe(philo->data->forks);
    sem_post_safe(philo->data->forks);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_num == 1)
		do_single_philo(&philo->data->philosophers[0]);
	else
	{
		if (philo->id % 2 == 0)
			ft_usleep(100);
		pthread_create(&philo->monitor_thread, NULL,
		(void *)monitor_simulation, philo);
		pthread_detach(philo->monitor_thread);
		while (!is_simulation_finished(philo->data))
		{
			try_eat(philo);
			log_action("is sleeping", philo);
			ft_usleep(philo->data->time_to_sleep);
			log_action("is thinking", philo);
		}
	}
	return (NULL);
}

bool	start_simulation(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	data->start_simulation = get_time_in_ms();

	while (++i < data->philo_num)
	{
		if (!safe_fork_handle(&data->pids[i], FORK))
			break;
		if (data->pids[i] == 0)
		{
			sem_wait(data->all_threads_ready);
			philo_routine(&data->philosophers[i]);
			exit(0);
		}
	}
	i = -1;
	while (++i < data->philo_num)
		sem_post(data->all_threads_ready);

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
	set_boolean(data->data_sem, &data->end_simulation, true);
	return (true);
}
