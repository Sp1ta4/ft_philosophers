/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:45:32 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/10 16:45:43 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
