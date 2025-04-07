/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:40:53 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/07 22:45:10 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Проверяет, умер ли философ от голода
static int check_philosopher_death(t_philosopher *philo, long current_time)
{
    t_table *table = philo->table;
    pthread_mutex_lock(&philo->table->last_meal_time_mutex);
    int has_died = 0;
    
    if (current_time - philo->last_meal_time > table->time_to_die)
    {
        pthread_mutex_lock(&table->simulation_mutex);
        if (table->simulation_running)
        {
            log_action(philo, "died", philo->table, 1);
            table->simulation_running = 0;
            has_died = 1;
        }
        pthread_mutex_unlock(&table->simulation_mutex);
    }
    
    pthread_mutex_unlock(&philo->table->last_meal_time_mutex);
    return has_died;
}

// Проверяет, наелся ли философ (достиг ли must_eat_count)
static int has_eaten_enough(t_philosopher *philo, int must_eat_count)
{
    pthread_mutex_lock(&philo->meals_mutex);
    int enough = (philo->meals_eaten >= must_eat_count);
    pthread_mutex_unlock(&philo->meals_mutex);
    return enough;
}

// Проверяет завершение симуляции по условию "все наелись"
static int check_all_ate_enough(t_table *table)
{
    if (table->must_eat_count <= 0)
        return 0;
        
    int eaten_enough_count = 0;
    
    for (int i = 0; i < table->num_philosophers; i++)
    {
        if (has_eaten_enough(&table->philosophers[i], table->must_eat_count))
            eaten_enough_count++;
    }
    
    if (eaten_enough_count == table->num_philosophers)
    {
        pthread_mutex_lock(&table->simulation_mutex);
        table->simulation_running = 0;
        pthread_mutex_unlock(&table->simulation_mutex);
        return 1;
    }
    
    return 0;
}

// Основная функция монитора
void* monitor_deaths(void* arg)
{
    t_table *table = (t_table *)arg;
	long	current_time;
    while (1)
    {    
		current_time = get_time_in_ms();
        for (int i = 0; i < table->num_philosophers; i++)
        {
            if (check_philosopher_death(&table->philosophers[i], current_time))
                return (NULL);
        }
         if (check_all_ate_enough(table))
            return (NULL);
            
        usleep(1000);
    }
    
    return (NULL);
}

void start_simulation(t_table *data)
{
	pthread_t monitor_thread;

	data->simulation_running = 1;
	data->start_time = get_time_in_ms();
	create_philosophers(data);
	if (data->num_philosophers > 1)
		pthread_create(&monitor_thread, NULL, monitor_deaths, data);
	wait_philosophers(data->philosophers);
	if (data->num_philosophers > 1)
		pthread_join(monitor_thread, NULL);
}