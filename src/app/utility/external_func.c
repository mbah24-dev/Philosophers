/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbah <mbah@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 23:07:04 by mbah              #+#    #+#             */
/*   Updated: 2025/04/04 23:31:53 by mbah             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/philosophers.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}
