/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:16:31 by jllarena          #+#    #+#             */
/*   Updated: 2024/05/21 16:10:58 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str12;
	size_t	size_str12;
	//char	*str1;

	if (s1 == 0 || s2 == 0)
		return (0);
	//str1 = (char *)s1;
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