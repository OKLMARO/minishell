/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:17:17 by oamairi           #+#    #+#             */
/*   Updated: 2025/04/19 16:17:17 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy_split(char *dest, const char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && src[i] != c)
	{
		dest[i] = src[i];
		i = i + 1;
	}
	dest[i] = '\0';
	return (dest);
}

int	str_len_split(const char *str, int i, char c)
{
	int	taille;

	taille = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		i++;
		taille++;
	}
	return (taille);
}

int	count_word(const char *str, char c)
{
	int	word;
	int	pre;
	int	i;

	word = 0;
	pre = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			pre = 1;
		else if (str[i] != c && pre == 1)
		{
			pre = 0;
			word++;
		}
		i++;
	}
	return (word);
}

void	free_split(char **res, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(res[j]);
		j++;
	}
	free(res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	res = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!res)
		return (0);
	while (i < count_word(s, c))
	{
		while (s[j] == c)
			j++;
		res[i] = malloc(sizeof(char) * (str_len_split(s, j, c) + 1));
		if (!res[i])
		{
			free_split(res, i);
			return (0);
		}
		ft_strcpy_split(res[i], &s[j], c);
		j = j + str_len_split(s, j, c);
		i++;
	}
	res[i] = NULL;
	return (res);
}
