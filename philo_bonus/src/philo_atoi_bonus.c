/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:52:14 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/15 09:52:02 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static char	*valid_number(char *str)
{
	char	*num;
	int		len;

	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-' || !ft_isdigit(*str))
		return (NULL);
	num = str;
	len = 0;
	while (ft_isdigit(*str))
	{
		len++;
		str++;
	}
	if (*str != '\0')
		return (NULL);
	if (len == 0 || len > 10)
		return (NULL);
	return (num);
}

int	ft_atoi(char *str)
{
	int	num;

	num = 0;
	str = valid_number(str);
	if (!str)
		return (-1);
	while (*str)
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX || num < 0)
		return (-1);
	return (num);
}
