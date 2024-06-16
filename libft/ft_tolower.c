/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:30:09 by jllarena          #+#    #+#             */
/*   Updated: 2023/09/22 13:39:28 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	while (c > 64 && c < 91)
	{
		c = c + 32;
	}
	return (c);
}
/*
int main(void)
{
	int i = 'A';

	printf("la letra es: %c\n", i);
	printf("despues es: %c\n", ft_tolower(i));
}*/
