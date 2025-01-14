/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:33:56 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/19 13:38:43 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (s == 0 || f == 0)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void ft_change(unsigned int i, char *str)
{
	(void)i;
    if (islower(*str)) 
    {
        *str = toupper(*str); 
    }
}

int main(void)
{
    char string[] = "Holaag";
    printf("string sin modificar = %s\n", string);
    ft_striteri(string, ft_change);
	printf("string modificado = %s\n", string);
    return(0);
}*/
