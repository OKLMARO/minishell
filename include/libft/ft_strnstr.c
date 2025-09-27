/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:21:11 by oamairi           #+#    #+#             */
/*   Updated: 2025/04/10 17:21:11 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init(size_t *i, size_t *j, size_t *to_find_len, char *temp_find)
{
	*j = 0;
	*i = 0;
	*to_find_len = ft_strlen(temp_find);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	j;
	size_t	i;
	size_t	to_find_len;
	char	*temp_find;
	char	*temp_str;

	temp_find = (char *) little;
	temp_str = (char *) big;
	init(&i, &j, &to_find_len, temp_find);
	if (temp_find[0] == '\0')
		return (temp_str);
	while (temp_str[i] != '\0' && i < len)
	{
		while (temp_str[i + j] == temp_find[j] && temp_str[i + j] != '\0')
		{
			if ((i + j) >= len)
				return (0);
			j = j + 1;
		}
		if (temp_find[j] == '\0' && j == to_find_len)
			return (&temp_str[i]);
		i = i + 1;
		j = 0;
	}
	return (0);
}
