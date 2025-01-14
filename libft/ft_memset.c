/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:09:42 by jllarena          #+#    #+#             */
/*   Updated: 2023/09/22 12:38:52 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = b;
	while (i < len)
	{
		str[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
/*
int main(void)
{
	char str[50] = "hola mundo y adios mundo";
	
	printf("el string original: %s\n", str);
	memset(str, '5', 6);
	printf("el string despues de la funcion original: %s\n", str);
	
	char str1[50] = "hola mundo y adios mundo";

	printf("el string original: %s\n", str1);
	ft_memset(str1, '5', 6);
	printf("el string despues de mi funcion: %s\n", str1);

}*/
