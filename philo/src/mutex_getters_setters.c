/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_getters_setters.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:05:55 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/14 21:15:52 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_boolean(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_boolean(t_mtx *mutex, bool *value)
{
	bool	tmp;

	safe_mutex_handle(mutex, LOCK);
	tmp = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (tmp);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	tmp;

	safe_mutex_handle(mutex, LOCK);
	tmp = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (tmp);
}

bool	is_simulation_finished(t_data *data)
{
	return (get_boolean(&data->data_mutex, &data->end_simulation));
}
