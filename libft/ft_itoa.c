/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:18:53 by oamairi           #+#    #+#             */
/*   Updated: 2025/04/19 16:18:53 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_base(long int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * -1;
		i++;
	}
	while (nb != 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*dest;
	int			len_base_to;
	long int	nb;

	nb = n;
	len_base_to = len_base(nb);
	dest = malloc(sizeof(char) * (len_base_to) + 1);
	if (!dest)
		return (0);
	dest[len_base_to] = '\0';
	if (nb < 0)
	{
		nb = nb * -1;
		dest[0] = '-';
	}
	if (nb == 0)
		dest[0] = '0';
	while (nb)
	{
		len_base_to--;
		dest[len_base_to] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (dest);
}
