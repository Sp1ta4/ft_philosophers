/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_data_init_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:36:32 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/09 13:31:34 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void init_semaphore(sem_t **sem, const char *name, int value, t_table *data)
{
    sem_unlink(name);
    *sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
    if (*sem == SEM_FAILED)
        throw_err(SEMAPHORE_ERROR, data);
}

void init_data(t_table *data, int argc, char **argv)
{
    if (argc < 5 || argc > 6)
        throw_err(ARGUMENT_ERROR, NULL);
    data->num_philosophers = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->must_eat_count = (argc == 6) ? ft_atoi(argv[5]) : -1;
    if (data->num_philosophers <= 0 || data->num_philosophers > MAX_PHILOS ||
        data->time_to_die <= 0 || data->time_to_eat <= 0 ||
        data->time_to_sleep <= 0 || (argc == 6 && data->must_eat_count <= 0))
        throw_err(VALUE_ERROR, NULL);
    data->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * data->num_philosophers);
    if (!data->philosophers)
        throw_err(MALLOC_ERROR, NULL);
    data->pids = (pid_t *)malloc(sizeof(pid_t) * data->num_philosophers);
    if (!data->pids)
    {
        free(data->philosophers);
        throw_err(MALLOC_ERROR, NULL);
    }
    init_semaphore(&data->forks_sem, FORKS_SEM_NAME, data->num_philosophers, data);
    init_semaphore(&data->last_meal_sem, LAST_MEAL_SEM_NAME, 1, data);
    init_semaphore(&data->print_sem, PRINT_SEM_NAME, 1, data);
    init_semaphore(&data->death_sem, DEATH_SEM_NAME, 0, data);
}
