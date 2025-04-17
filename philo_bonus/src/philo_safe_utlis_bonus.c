/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_safe_utlis_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:34:45 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/17 17:58:52 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	safe_semaphore_init(sem_t **sem, const char *name, int value)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (*sem == SEM_FAILED)
	{
		print_error("Program error!\n", "Failed to create semaphore\n");
		return (false);
	}
	return (true);
}

bool	sem_wait_safe(sem_t *sem)
{
	if (sem == NULL)
		return (false);
	if (sem_wait(sem) == -1)
	{
		print_error("Program error!\n", "sem_wait failed\n");
		return (false);
	}
	return (true);
}

bool	sem_post_safe(sem_t *sem)
{
	if (sem == NULL)
		return (false);
	if (sem_post(sem) == -1)
	{
		print_error("Program error!\n", "sem_post failed\n");
		return (false);
	}
	return (true);
}

bool	sem_destroy_safe(sem_t *sem, const char *name)
{
	if (sem == NULL)
		return (false);
	if (sem_close(sem) == -1)
	{
		print_error("Program error!\n", "sem_close failed\n");
		return (false);
	}
	sem_unlink(name);
	return (true);
}

bool	safe_fork_handle(pid_t *pid, t_opcode op)
{
	if (op == FORK)
	{
		*pid = fork();
		if (*pid < 0)
			return (!print_error("Programm error!\n", "Failed create fork\n"));
		return (true);
	}
	else if (op == WAIT)
	{
		if (waitpid(*pid, NULL, 0) < 0)
			return (!print_error("Programm error!\n", "Failed fork waiting\n"));
		return (true);
	}
	else if (op == KILL)
	{
		if (kill(*pid, SIGTERM) < 0)
			return (!print_error("Programm error!\n", "Failed kill fork\n"));
		return (true);
	}
	return (!print_error("Programm error!\n", "Unknown error\n"));
}
