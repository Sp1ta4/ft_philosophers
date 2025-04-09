/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:04:16 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/10 09:31:56 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#define MAX_PHILOS 200
#define FORKS_SEM_NAME "/forks_sem"
#define PRINT_SEM_NAME "/print_sem"
#define DEATH_SEM_NAME "/death_sem"
#define EACH_EAT_SEM_NAME "/each_eat_sem"
#define LAST_EAT_TIME_SEM_NAME "/last_eat_time_sem"

#define ARGUMENT_ERROR 0
#define VALUE_ERROR 1
#define PHILO_ERROR 2
#define MALLOC_ERROR 3
#define SEMAPHORE_ERROR 4
#define FORK_ERROR 5

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

typedef struct s_table	t_table;

typedef struct s_philosopher
{
	int					id;
	int					meals_eaten;
	long long			last_meal_time;
	pthread_t			monitoring_thread;
	t_table				*table;
}	t_philosopher;

typedef struct s_table
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				num_philosophers;
	long			start_time;
	pid_t 			*pids;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*each_eat_sem;
	sem_t			*last_eat_time_sem;
	sem_t			*death_sem;
	t_philosopher	*philosophers;

}	t_table;

int		ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
void	throw_err(int nerr, t_table *data);
void	init_data(t_table *data, int argc, char **argv);
void	create_philosophers(t_table *data);
void	log_action(t_philosopher *philo, const char *action,
			t_table *data, int is_death);
void	start_simulation(t_table *data);
void	free_data(t_table *data);
void	philosopher_routine(t_philosopher *philo);
long	get_time_in_ms(void);
void	do_single_philo(t_philosopher *philo);

#endif