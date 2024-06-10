/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:08:11 by jllarena          #+#    #+#             */
/*   Updated: 2023/09/22 13:39:07 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c > 96 && c < 123)
	{
		c = c - 32;
	}
	return (c);
}
/*
int main(void)
{
	int i = 'z';

	printf("la letr inicial es: %c\n", i);
	printf("la letr despues de la funcion es: %c\n", ft_toupper(i));
}	*/
