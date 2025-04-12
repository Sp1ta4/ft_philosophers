/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:04:45 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/12 13:28:58 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	
	if (argc == 5 || argc == 6)
	{
		parse_input(&data, argv);
		// printf("%d %d %d %d %d\n", data.philo_num, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.must_eat_count);
		// init_data();
		// start_simulation();
		clean(&data);
	}
	else
		return (throw_err(INVALID_ARG_CNT_ERROR, NULL));
	return (0);
}
