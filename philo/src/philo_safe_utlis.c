/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_safe_utlis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:34:45 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/13 16:58:32 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	handle_mutex_err(int status)
{
	if (status == 0)
		return (true);
	else
	{
		throw_err(PROGRAMM_ERROR, NULL);
		return (false);
	}
}

static bool	handle_thread_err(int status)
{
	if (status == 0)
		return (true);
	else
	{
		throw_err(PROGRAMM_ERROR, NULL);
		return (false);
	}
}

void	*safe_malloc(size_t bytes, t_data *data)
{
	void	*malloced;

	malloced = malloc(bytes);
	if (!malloced)
	{
		throw_err(PROGRAMM_ERROR, data);
		return (NULL);
	}
	return (malloced);
}

bool	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		return (handle_mutex_err(pthread_mutex_lock(mutex)));
	else if (opcode == UNLOCK)
		return (handle_mutex_err(pthread_mutex_unlock(mutex)));
	else if (opcode == INIT)
		return (handle_mutex_err(pthread_mutex_init(mutex, NULL)));
	else if (opcode == DESTROY)
		return (handle_mutex_err(pthread_mutex_destroy(mutex)));
	else
	{
		throw_err(PROGRAMM_ERROR, NULL);
		return (false);
	}
	return (true);
}

bool	safe_thread_handle(pthread_t *thread, void *(*fnc)(void *),
		void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		return (handle_thread_err(pthread_create(thread, NULL, fnc, data)));
	else if (opcode == JOIN)
		return (handle_thread_err(pthread_join(*thread, NULL)));
	else if (opcode == DETACH)
		return (handle_thread_err(pthread_detach(*thread)));
	else
		return (!throw_err(PROGRAMM_ERROR, NULL));
}
