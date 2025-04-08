/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:04:16 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/08 11:14:01 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <limits.h>

typedef struct s_table	t_table;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	t_table			*table;
}	t_philosopher;

typedef struct s_table
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				num_philosophers;
	int				simulation_running;
	long			start_time;
	pid_t 			*pids;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*death_sem;
	sem_t			*all_ate_sem;
	t_philosopher	*philosophers;

}	t_table;

int		is_valid(int argc);
int		ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
void	throw_err(int nerr, t_table *data);
void	init_data(t_table *data, int argc, char **argv);
void	create_philosophers(t_table *data);
void	log_action(t_philosopher *philo, const char *action,
			t_table *data, int is_death);
void	start_simulation(t_table *data);
void	wait_philosophers(t_philosopher *philosophers);
void	destroy_philo_mutexes(t_table *data);
void	free_data(t_table *data);
void	*philosopher_routine(void *arg);
long	get_time_in_ms(void);

#endif