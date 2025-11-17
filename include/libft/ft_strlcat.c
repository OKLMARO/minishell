/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:40:24 by oamairi           #+#    #+#             */
/*   Updated: 2025/04/09 16:40:24 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;
	size_t	len_dest;

	if (siz == 0)
		return (ft_strlen((char *) src));
	i = 0;
	while (dst[i] && i < siz)
		i++;
	len_dest = i;
	j = 0;
	while (src[j] && i < siz - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (i < siz)
		dst[i] = '\0';
	return (len_dest + ft_strlen((char *) src));
}
