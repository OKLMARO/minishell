/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 23:42:01 by oamairi           #+#    #+#             */
/*   Updated: 2025/04/15 23:42:01 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*res;
	size_t			j;

	if (s == NULL)
		return (0);
	i = start;
	if (start < ft_strlen(s))
	{
		while (s[i] && (i - start) < len)
			i++;
		res = malloc((i - start + 1) * sizeof(char));
		if (!res)
			return (0);
		j = 0;
		while (s[start] && j < len)
		{
			res[j] = s[start];
			j++;
			start++;
		}
		res[j] = '\0';
		return (res);
	}
	return (ft_strdup(""));
}
