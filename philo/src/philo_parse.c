/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:05:28 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/12 21:01:04 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	validate_input(t_data *data)
{
	if (data->philo_num == -1 || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1)
	{
		throw_err(INVALID_ARGUMENT_ERROR, NULL);
		return (false);
	}
	if (data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60)
		return (time_err());
	if (data->philo_num <= 0 || data->philo_num >= 201)
	{
		throw_err(PHILO_ERROR, NULL);
		return (false);
	}
	return (true);
}

bool	parse_input(t_data *data, char **argv)
{
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		data->must_eat_count = ft_atoi(argv[5]);
		if (data->must_eat_count <= 0)
		{
			throw_err(INVALID_ARGUMENT_ERROR, NULL);
			return (false);
		}
	}
	else
		data->must_eat_count = -42;
	if (!validate_input(data))
		return (false);
	return (true);
}
