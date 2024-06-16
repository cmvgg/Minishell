/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:40:20 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/05 12:33:06 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
#include "ft_strlcpy.c"
#include "ft_strlen.c"
#include "ft_strdup.c"
#include "ft_substr.c"*/

int	ft_check(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	ini;
	size_t	final;

	if (s1 == 0 || set == 0)
		return (0);
	ini = 0;
	while (ini <= ft_strlen(s1) && ft_check(s1[ini], set) == 1)
		ini++;
	if (ini == ft_strlen(s1))
		return (ft_strdup(""));
	ini = 0;
	final = ft_strlen(s1);
	final--;
	while (ini <= (ft_strlen(s1) / 2) && ft_check(s1[ini], set) == 1)
		ini++;
	while (final >= (ft_strlen(s1) / 2) && ft_check(s1[final], set) == 1)
		final--;
	final++;
	if (ini == 0 && final == ft_strlen(s1))
		return (ft_strdup(s1));
	return (ft_substr(s1, ini, (final - ini)));
}

/*int main(void)
{
	printf("%s\n", ft_strtrim("erttre", "tre"));
	return (0);
}*/