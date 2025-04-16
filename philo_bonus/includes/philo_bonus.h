/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:32:09 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/16 14:43:32 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>

# define MAX_PHILO 200
# define MIN_TIME 60

# define FORKS_SEM_NAME "/forks_sem"
# define PRINT_SEM_NAME "/print_sem"
# define DATA_SEM_NAME "/data"
# define PHILO_SEM_NAME "/philo"
# define ALL_READY_SEM_NAME "/all_ready"

# define SEM_PERMISSIONS 0644
# define PROGRAMM_ERROR 0
# define PHILO_ERROR 1
# define INVALID_ARG_CNT_ERROR 2
# define INVALID_ARGUMENT_ERROR 3

typedef enum e_opcode
{
	WAIT,
	POST,
	KILL,
	FORK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}	t_opcode;

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	long		meals_count;
	long		last_meal_time;
	bool		is_eat_full;
	sem_t		philo_sem;
	t_data		*data;
	pthread_t	monitor_thread;
}	t_philo;

struct s_data
{
	int			philo_num;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		start_simulation;
	long		must_eat_count;
	bool		end_simulation;
	bool		is_cleaned;
	sem_t		*all_threads_ready;
	sem_t		*data_sem;
	sem_t		*log_sem;
	sem_t		*forks;
	t_philo		*philosophers;
	pid_t		*pids;
};

int		throw_err(int err_type, t_data *data);
int		ft_atoi(char *str);
void	inc_long(sem_t *semaphore, long *dest);
void	*safe_malloc(size_t bytes, t_data *data);
long	get_time_in_ms(void);
void	set_long(sem_t *semaphore, long *dest, long value);
void	set_boolean(sem_t *semaphore, bool *dest, bool value);
void	ft_usleep(long long time);
void	log_action(const char *action, t_philo *philo);
void	*monitor_simulation(void *arg);
long	get_long(sem_t *semaphore, long *value);
bool	get_boolean(sem_t *semaphore, bool *value);
bool	start_simulation(t_data *data);
bool	clean(t_data *data);
bool	parse_input(t_data *data, char **argv);
bool	time_err(void);
bool	safe_fork_handle(pid_t *pid, t_opcode op);
bool	init_data(t_data *data);
int		print_error(const char *err, const char *msg);
bool	sem_wait_safe(sem_t *sem);
bool	sem_post_safe(sem_t *sem);
bool	safe_semaphore_init(sem_t **sem, const char *name, int value);
bool	sem_destroy_safe(sem_t *sem, const char *name);
bool	is_simulation_finished(t_data *data);
bool	safe_thread_handle(pthread_t *thread, void *(*fnc)(void *),
			void *data, t_opcode opcode);
#endif