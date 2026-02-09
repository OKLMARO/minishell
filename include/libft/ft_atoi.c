/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student.42.fr>             +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:14:50 by oamairi           #+#    #+#             */
/*   Updated: 2025/02/27 11:12:30 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_good(char str)
{
	if (str == '\t')
		return (1);
	else if (str == '\n')
		return (1);
	else if (str == '\v')
		return (1);
	else if (str == '\f')
		return (1);
	else if (str == '\r')
		return (1);
	else if (str == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (ft_isdigit(nptr[i]) == 0)
		return (-1);
	while (nptr[i] != '\0' && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res = res * 10 + (nptr[i] - '0');
		i = i + 1;
	}
	if (nptr[i] && ft_isdigit(nptr[i]) == 0)
		return (-1);
	return (res);
}
