/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:14:13 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/04 15:14:58 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int symbol)
{
	return (symbol == ' ' || (symbol >= '\t' && symbol <= '\r'));
}

static char	*ft_trim_start(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	return (&str[i]);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int		result;
	char	*nptr_cpy;
	int		is_negative;

	result = 0;
	nptr_cpy = ft_trim_start((char *)nptr);
	is_negative = 1;
	if (*nptr_cpy == '-' || *nptr_cpy == '+')
	{
		if (*nptr_cpy == '-')
			is_negative = -1;
		++nptr_cpy;
	}
	while (ft_isdigit(*nptr_cpy))
	{
		result = result * 10 + (*nptr_cpy - 48);
		nptr_cpy++;
	}
	return (result * is_negative);
}
