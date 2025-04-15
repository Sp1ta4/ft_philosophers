/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_err_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:27:06 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/15 10:26:50 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_error(const char *err, const char *msg)
{
	if (msg)
		printf("\033[1;31m%s\033[0m%s", err, msg);
	else
		printf("\033[1;31m%s\033[0m", err);
	return (4);
}

static void	print_success(const char *scs, const char *msg)
{
	if (msg)
		printf("\033[1;32m%s\033[0m %s", scs, msg);
	else
		printf("\033[1;32m%s\033[0m", scs);
}

bool	time_err(void)
{
	print_error("Error: Invalid arguments.\n",
		"Your time arguments need to be greater then 60ms\n");
	return (false);
}

int	throw_err(int err_type, t_data *data)
{
	if (data)
		clean(data);
	if (err_type == INVALID_ARG_CNT_ERROR)
	{
		print_error("Error: Insufficient arguments.\n", NULL);
		print_success("Usage:", "philo_number time_to_die time_to_eat"
			" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (INVALID_ARG_CNT_ERROR);
	}
	else if (err_type == INVALID_ARGUMENT_ERROR)
	{
		print_error("Error: Invalid arguments.\n",
			"Your arguments need to be an unsigned integer\n");
		return (INVALID_ARGUMENT_ERROR);
	}
	else if (err_type == PHILO_ERROR)
	{
		print_error("Error: Invalid number of Philosophers.\n", NULL);
		print_success("Num of philo must be 1-200\n", NULL);
		return (PHILO_ERROR);
	}
	else
		return (print_error("Programm error!\n", NULL));
}
