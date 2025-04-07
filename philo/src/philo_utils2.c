/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:14:13 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/04/07 21:34:41 by ggevorgi         ###   ########.fr       */
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

int ft_atoi(const char *nptr)
{
    int result;
    char *nptr_cpy;

    result = 0;
    nptr_cpy = ft_trim_start((char *)nptr);
    
    // Проверяем, что число не отрицательное
    if (*nptr_cpy == '-')
        throw_err(3, NULL);  // Ошибка, если число отрицательное
    
    if (*nptr_cpy == '+')
        nptr_cpy++;  // Пропускаем знак плюс
    
    while (ft_isdigit(*nptr_cpy))
    {
        // Проверка переполнения
        if (result > (INT_MAX / 10) || (result == INT_MAX / 10 && *nptr_cpy - '0' > INT_MAX % 10))
            throw_err(3, NULL);  // Переполнение

        result = result * 10 + (*nptr_cpy - '0');
        nptr_cpy++;
    }

    // Проверяем, что строка завершилась корректно
    if (*nptr_cpy != '\0' && !ft_isdigit(*nptr_cpy))
        throw_err(3, NULL);

    return result;
}

