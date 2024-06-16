/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:29:11 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/02 17:47:42 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str1;
	int		i;
	int		size;

	i = 0;
	size = ft_strlen(s1);
	str1 = malloc(sizeof (char) * (size + 1));
	if (!str1)
	{
		return (0);
	}
	while (s1[i] != '\0')
	{
		str1[i] = s1[i];
		i++;
	}
	str1[i] = s1[i];
	return (str1);
}

/*
int main(void)
{
   printf("%s\n", ft_strdup("hola Mundo!!")); 
   printf("%s\n", strdup("hola Mundo!!"));  
   return (0);
}*/