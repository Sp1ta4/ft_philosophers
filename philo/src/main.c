/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:04:45 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/13 16:59:01 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc == 5 || argc == 6)
	{
		data = safe_malloc(sizeof(t_data), NULL);
		if (!parse_input(data, argv))
			return (1);
		if (!init_data(data))
			return (2);
		if (!start_simulation(data))
			return (3);
		if (!clean(data))
			return (4);
	}
	else
		return (throw_err(INVALID_ARG_CNT_ERROR, NULL));
	return (0);
}
