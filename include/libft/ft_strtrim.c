/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oamairi <oamairi@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:36:08 by oamairi           #+#    #+#             */
/*   Updated: 2025/04/19 15:36:08 by oamairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_trim(char s1, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*res;
	int		debut;
	int		fin;

	debut = 0;
	fin = ft_strlen(s1) - 1;
	while (is_trim(s1[debut], set))
		debut++;
	while (is_trim(s1[fin], set))
		fin--;
	if (fin < debut)
		debut = 0;
	res = malloc((fin - debut + 2) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (debut <= fin)
	{
		res[i] = s1[debut];
		i++;
		debut++;
	}
	res[i] = '\0';
	return (res);
}

/*int	main(void)
{
	printf("%s\n", ft_strtrim("   xxx   xxx", " x"));
	return (0);
}*/
