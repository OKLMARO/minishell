/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:27:54 by oamairi           #+#    #+#             */
/*   Updated: 2025/04/09 16:27:54 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	if (n == 0)
		return (0);
	s1_temp = (unsigned char *) s1;
	s2_temp = (unsigned char *) s2;
	i = 0;
	while (i < n - 1 && s1_temp[i] == s2_temp[i])
		i++;
	return (s1_temp[i] - s2_temp[i]);
}
