/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:03:51 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/04 15:17:42 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid(int argc, char **argv)
{	(void) argv;
	if (argc < 5 || argc > 6)
		throw_err(0, NULL);
	return (1);
}
