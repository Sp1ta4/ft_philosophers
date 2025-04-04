/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:04:16 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/04 16:42:12 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#	include <string.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <unistd.h>
#	include <sys/time.h>
#	include <pthread.h>

typedef struct s_table t_table;

typedef struct	s_philosopher {
    int				id;
    int				meals_eaten;
    long			last_meal_time;
    t_table			*table;
	pthread_t		thread;
    pthread_mutex_t	*left_fork;
    pthread_mutex_t	*right_fork;
} t_philosopher;

typedef struct	s_table {
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
    pthread_mutex_t	log_mutex;
} t_table;

int		is_valid(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
void	throw_err(int nerr, t_table *data);
void	init_data(t_table *data, int argc, char **argv);
void	create_philosophers(t_table *data);
void*	philosopher_routine(void* arg);
long	get_time_in_ms(void);
void	log_action(t_philosopher *philo, const char *action, t_table *data);
void	destroy_forks(t_table *data);

#endif