/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 10:00:52 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/09 15:24:36 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	do_single_philo(t_philosopher *philo)
{
	log_action(philo, "has taken a fork", philo->table, 0);
	usleep(philo->table->time_to_die * 1000);
	log_action(philo, "died", philo->table, 1);
	exit(1);
}
