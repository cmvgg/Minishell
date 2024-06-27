/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:16:31 by jllarena          #+#    #+#             */
/*   Updated: 2024/06/24 14:59:15 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str12;
	size_t	size_str12;

	if (s1 == 0 || s2 == 0)
		return (0);
	size_str12 = ft_strlen(s1) + ft_strlen(s2) + 1;
	str12 = malloc(sizeof (char) * size_str12);
	if (!str12)
		return (0);
	ft_strlcpy(str12, s1, ft_strlen(s1) + 1);
	ft_strlcat(str12, s2, size_str12);
	return (str12);
}

/*
int main(void)
{
    char *st1 = 0;
    char st2[] = "adios";

    printf("la funcion mia: %s\n", ft_strjoin(st1, st2));
}*/