/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:01:26 by jllarena          #+#    #+#             */
/*   Updated: 2023/09/22 12:40:19 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
/*
int main(void)
{
	char str[50] = "hola mundo";
	printf("el string es = %s", str);


	bzero(str, 3);
	write(1, "funcion original: ", 40);
	write(1, &str, 1);
	write(1, "\n", 3);
	
	char str1[50] = "hola mundo";

	ft_bzero(str1, 3);
	write(1, "funcion mia: ", 40);
	write(1, &str1, 1);
	write(1, "\n", 1);
}
	*/
