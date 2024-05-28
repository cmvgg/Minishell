/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:44:09 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/03 10:53:18 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
		{
			return (&str[i]);
		}
		i++;
	}
	if ((unsigned char)c == '\0')
	{
		return (&str[i]);
	}
	return (0);
}
/*
int main(void)
{
	char str = 0;
	char i;
	i = 'o';
	printf("el resultadi es: %s\n", ft_strchr(str, i));
}*/
