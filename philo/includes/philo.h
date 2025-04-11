/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:04:16 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/11 09:53:23 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_PHILOS 200
# define FORKS_SEM_NAME "/forks_sem"
# define PRINT_SEM_NAME "/print_sem"
# define EACH_EAT_SEM_NAME "/each_eat_sem"
# define LAST_EAT_TIME_SEM_NAME "/last_eat_time_sem"
# define ARGUMENT_ERROR 0
# define VALUE_ERROR 1
# define PHILO_ERROR 2
# define MALLOC_ERROR 3
# define PROGRAMM_ERROR 4

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_table	t_table;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	t_table			*table;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meals_mutex;

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
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	simulation_mutex;
	pthread_mutex_t	last_meal_time_mutex;
	pthread_mutex_t	log_mutex;
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