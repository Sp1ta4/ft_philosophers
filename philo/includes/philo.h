/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:32:09 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/13 21:29:11 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

# define MAX_PHILO 200
# define MIN_TIME 60

# define PROGRAMM_ERROR 0
# define PHILO_ERROR 1
# define INVALID_ARG_CNT_ERROR 2
# define INVALID_ARGUMENT_ERROR 3
// # define INVALID_TIME_ERROR 4

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	int			id;
	long		meals_count;
	long		last_meal_time;
	bool		is_eat_full;
	t_mtx		*first_fork;
	t_mtx		*second_fork;
	t_mtx		philo_mutex;
	t_data		*data;
	pthread_t	thread_id;
}	t_philo;

struct s_data
{
	int		philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	start_simulation;
	long	must_eat_count;
	bool	end_simulation;
	bool	is_cleaned;
	bool	all_threads_ready;
	t_mtx	data_mutex;
	t_mtx	log_mutex;
	t_mtx	*forks;
	t_philo	*philosophers;
	pthread_t	monitor;
};

int		throw_err(int err_type, t_data *data);
int		ft_atoi(char *str);
void	inc_long(t_mtx *mutex, long *dest);
void	*safe_malloc(size_t bytes, t_data *data);
long	get_time_in_ms(void);
void	set_long(t_mtx *mutex, long *dest, long value);
void	set_boolean(t_mtx *mutex, bool *dest, bool value);
void	ft_usleep(long long time);
void	log_action(const char *action, t_philo *philo);
void	*monitor_simulation(void *arg);
long	get_long(t_mtx *mutex, long *value);
bool	get_boolean(t_mtx *mutex, bool *value);
bool	start_simulation(t_data *data);
bool	clean(t_data *data);
bool	parse_input(t_data *data, char **argv);
bool	time_err(void);
bool	init_data(t_data *data);
bool	is_simulation_finished(t_data *data);
bool	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
bool	safe_thread_handle(pthread_t *thread, void *(*fnc)(void *),
			void *data, t_opcode opcode);
#endif