/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:54:38 by jllarena          #+#    #+#             */
/*   Updated: 2023/09/28 11:34:28 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	lon;

	str = (char *)s;
	lon = ft_strlen(str) + 1;
	while (lon--)
	{
		if (str[lon] == (unsigned char)c)
		{
			return (&str[lon]);
		}
	}
	return (0);
}
/*
int main(void)
{
	char str[] = "holapoota";
	char i;
	i = 'o';
	printf("el resultado es: %s\n", ft_strrchr(str, i));
}*/
