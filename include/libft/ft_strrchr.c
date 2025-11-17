/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:16:58 by oamairi           #+#    #+#             */
/*   Updated: 2025/03/19 16:16:58 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	int		i;
	char	*str_temp;

	i = 0;
	res = NULL;
	str_temp = (char *) s;
	while (str_temp[i])
	{
		if (str_temp[i] == (char) c)
			res = &str_temp[i];
		i++;
	}
	if (str_temp[i] == (char) c)
		return (&str_temp[i]);
	return (res);
}
