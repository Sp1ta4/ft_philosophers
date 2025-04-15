/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semophore_getters_setters_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:05:55 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/15 21:56:45 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_boolean(sem_t *sem, bool *dest, bool value)
{
	sem_wait_safe(sem);
	*dest = value;
	sem_post_safe(sem);
}

bool	get_boolean(sem_t *sem, bool *src)
{
	bool	tmp = false;

	if (!sem || !src)
		return (false);
	
	sem_wait_safe(sem);
	tmp = *src;
	sem_post_safe(sem);
	return (tmp);
}

void	set_long(sem_t *sem, long *dest, long value)
{
	sem_wait_safe(sem);
	*dest = value;
	sem_post_safe(sem);
}

long	get_long(sem_t *sem, long *src)
{
	long	tmp = 0;

	if (!sem || !src)
		return (0);
	sem_wait_safe(sem);
	tmp = *src;
	sem_post_safe(sem);
	return (tmp);
}

bool	is_simulation_finished(t_data *data)
{
	return get_boolean(data->data_sem, &data->end_simulation);
}
