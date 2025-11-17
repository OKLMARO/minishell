/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:27:11 by oamairi           #+#    #+#             */
/*   Updated: 2025/03/31 15:27:11 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*pointer_c;
	size_t	i;

	pointer_c = (char *) s;
	i = 0;
	while (i < n)
	{
		pointer_c[i] = c;
		i++;
	}
	return (s);
}
