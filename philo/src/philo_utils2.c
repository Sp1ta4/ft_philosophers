/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:14:13 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/11 10:00:48 by ggevorgi         ###   ########.fr       */
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

	result = 0;
	nptr_cpy = ft_trim_start((char *)nptr);
	if (*nptr_cpy == '-')
		throw_err(VALUE_ERROR, NULL);
	if (*nptr_cpy == '+')
		nptr_cpy++;
	while (ft_isdigit(*nptr_cpy))
	{
		if (result > (INT_MAX / 10)
			|| (result == INT_MAX / 10
				&& *nptr_cpy - '0' > INT_MAX % 10))
			throw_err(VALUE_ERROR, NULL);
		result = result * 10 + (*nptr_cpy - '0');
		nptr_cpy++;
	}
	if (*nptr_cpy != '\0' && !ft_isdigit(*nptr_cpy))
		throw_err(VALUE_ERROR, NULL);
	return (result);
}
