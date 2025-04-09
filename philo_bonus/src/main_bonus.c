/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:05:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/09 13:38:42 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void free_data(t_table *data)
{
	if (!data)
		return ;
	if (data->philosophers)
	{
		free(data->philosophers);
		data->philosophers = NULL;
	}
	if (data->pids)
	{
		free(data->pids);
		data->pids = NULL;
	}
	
	sem_close(data->forks_sem);
	sem_close(data->death_sem);
	sem_close(data->print_sem);
	sem_unlink(FORKS_SEM_NAME);
	sem_unlink(DEATH_SEM_NAME);
	sem_unlink(PRINT_SEM_NAME);
}

static void	try_take_forks_and_eat(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
		usleep(500);
	sem_wait(philo->table->forks_sem);
	log_action(philo, "has taken a fork", philo->table, 0);
	sem_wait(philo->table->forks_sem);
	log_action(philo, "has taken a fork", philo->table, 0);
	log_action(philo, "is eating", philo->table, 0);
	usleep(philo->table->time_to_eat * 1000);
	sem_wait(philo->table->last_meal_sem);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	sem_post(philo->table->last_meal_sem);
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
}

void	philosopher_routine(t_philosopher *philo)
{
	philo->last_meal_time = philo->table->start_time;
	if (philo->table->num_philosophers == 1)
		do_single_philo(philo);
	while (1)
	{
		log_action(philo, "is thinking", philo->table, 0);
		try_take_forks_and_eat(philo);
		if (philo->table->must_eat_count > 0 &&
	    philo->meals_eaten >= philo->table->must_eat_count)
			exit(EXIT_SUCCESS);
		log_action(philo, "is sleeping", philo->table, 0);
		usleep(philo->table->time_to_sleep * 1000);
	}
}

// static void *monitor_death(void *arg)
// {
// 	t_philosopher *philo = (t_philosopher *)arg;
// 	int last_meal_time;
	
// 	while (1)
// 	{
// 		usleep(1000);
// 		sem_wait(philo->table->last_meal_sem);
// 		last_meal_time = get_time_in_ms() - philo->last_meal_time;
// 		sem_post(philo->table->last_meal_sem);
// 		if (last_meal_time > philo->table->time_to_die)
// 		{
// 			log_action(philo, "died", philo->table, 1); // 1 — означает смерть
// 			sem_post(philo->table->death_sem);
// 			exit(EXIT_FAILURE); // Завершаем процесс философа
// 		}
// 	}
// 	return NULL;
// }

void create_philosophers(t_table *data)
{
    int i;
    pid_t pid;

    i = 0;
    data->start_time = get_time_in_ms();
    while (i < data->num_philosophers)
    {
        data->philosophers[i].id = i + 1;
        data->philosophers[i].last_meal_time = data->start_time;
        data->philosophers[i].meals_eaten = 0;
        data->philosophers[i].table = data;
        pid = fork();
        if (pid == 0)
        {
			// pthread_create(&data->philosophers[i].monitoring_thread, NULL, monitor_death, &data->philosophers[i]);
			// pthread_detach(data->philosophers[i].monitoring_thread);
            philosopher_routine(&data->philosophers[i]);
            exit(EXIT_SUCCESS);
        }
        else if (pid > 0)
            data->pids[i] = pid;
        else
            throw_err(FORK_ERROR, data);
        i++;
    }
}

void start_simulation(t_table *data)
{
	int	i;

	create_philosophers(data);
	i = -1;
	while(++i < data->num_philosophers)
	{
		waitpid(data->pids[i], NULL, 0);
	}
}

int	main(int argc, char *argv[])
{
	t_table	data;
	
	init_data(&data, argc, argv);
	start_simulation(&data);
	for (int i = 0; i < data.num_philosophers; i++)
    	kill(data.pids[i], SIGKILL);
	free_data(&data);
	return (0);
}
