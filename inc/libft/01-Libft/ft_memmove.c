/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:18:14 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/05 13:26:06 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest;
	unsigned const char	*origen;
	size_t				i;

	i = 0;
	dest = (unsigned char *)dst;
	origen = (unsigned char *)src;
	if (dest > origen)
	{
		while (len--)
		{
			dest[len] = origen[len];
		}
	}
	if (dest < origen)
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((const char *)src)[i];
			i++;
		}
	}
	return (dst);
}
/*
int main(void)
{
	char str[50] = "holamutdo123";
	char dst1[50]= "1234567";
	printf("el string origen es: %s\n", str);
	printf("el string destino es: %s\n", dst1);
	memmove(dst1, str, 4);
	printf("la funcion original es: %s\n", dst1);

	char str2[50] = "holamutdo123";
	char dst2[50] = "1234567";
	printf("el string origen es: %s\n", str2);
	printf("el string1 destino es: %s\n", dst2);
	ft_memmove(dst2, str2, 4);

	printf("la funcion original es: %s\n", dst2);

}*/
