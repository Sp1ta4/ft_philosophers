/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:05:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/07 22:41:13 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_single_philo(t_philosopher *philo)
{
		log_action(philo, "has taken a fork", philo->table, 0);
		usleep(philo->table->time_to_die * 1000);
		log_action(philo, "died", philo->table, 1);
		philo->table->simulation_running = 0;
}

void	try_take_forks_and_eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(500);
	    pthread_mutex_lock(philo->right_fork);
	    log_action(philo, "has taken a fork", philo->table, 0);
	    pthread_mutex_lock(philo->left_fork);
	    log_action(philo, "has taken a fork", philo->table, 0);
	}
	else
	{
	    pthread_mutex_lock(philo->left_fork);
	    log_action(philo, "has taken a fork", philo->table, 0);
	    pthread_mutex_lock(philo->right_fork);
	    log_action(philo, "has taken a fork", philo->table, 0);
	}
	log_action(philo, "is eating", philo->table, 0);
    usleep(philo->table->time_to_eat * 1000);
     // Обновляем время последней еды
	pthread_mutex_lock(&philo->table->last_meal_time_mutex);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->table->last_meal_time_mutex);
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meals_mutex);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void* philosopher_routine(void* arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(&philo->table->last_meal_time_mutex);
	philo->last_meal_time = philo->table->start_time;
	pthread_mutex_unlock(&philo->table->last_meal_time_mutex);
	if (philo->table->num_philosophers == 1)
	{
		do_single_philo(philo);
		return (NULL);
	}

	while (1)
	{
		pthread_mutex_lock(&philo->table->simulation_mutex);
		if (!philo->table->simulation_running)
		{
			pthread_mutex_unlock(&philo->table->simulation_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->table->simulation_mutex);

		log_action(philo, "is thinking", philo->table, 0);
		try_take_forks_and_eat(philo);
		log_action(philo, "is sleeping", philo->table, 0);
		usleep(philo->table->time_to_sleep * 1000);
	}

	return NULL;
}


void	wait_philosophers(t_philosopher *philosophers)
{
	int	i = 0;

	while (i < philosophers[0].table->num_philosophers)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}




int main(int argc, char *argv[])
{
	t_table	data;
	if (is_valid(argc))
	{
		init_data(&data, argc, argv);
		start_simulation(&data);
		destroy_philo_mutexes(&data);
		pthread_mutex_destroy(&(data.log_mutex));
		pthread_mutex_destroy(&(data.simulation_mutex));
		pthread_mutex_destroy(&(data.last_meal_time_mutex));
		return (0);
	}
	return (1);
}