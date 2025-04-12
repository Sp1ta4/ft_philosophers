/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:32:09 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/12 13:32:58 by ggevorgi         ###   ########.fr       */
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

typedef struct s_data	t_data;
typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	int			id;
	int			meals_count;
	int			last_meal_time;
	bool		is_eat_full;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
	t_data		*data;
	pthread_t	thread_id;
}	t_philo;

struct s_data
{
	int		philo_num;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		must_eat_count;
	int		start_simulation;
	bool	end_simulation;
	t_mtx	*forks;
	t_philo	*philosophers;
	t_mtx	log_mutex;
};

int		throw_err(int err_type, t_data *data);
void	clean(t_data *data);
bool	parse_input(t_data *data, char **argv);
bool	time_err(void);
int		ft_atoi(char *str);
#endif