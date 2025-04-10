/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:05:01 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/11 10:35:19 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	data;

	if (argc < 5 || argc > 6)
		throw_err(ARGUMENT_ERROR, NULL);
	init_data(&data, argc, argv);
	start_simulation(&data);
	free_data(&data);
	return (0);
}
