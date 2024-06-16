/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:30:07 by jllarena          #+#    #+#             */
/*   Updated: 2024/05/22 17:17:51 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	if (s == 0)
		return (0);
	i = 0;
	str = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (str == 0)
		return (0);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = 0;
	return (str);
}

/*char funcioncreada(unsigned int i, char str) 
{
	(void)i;
    if (isupper(str)) 
		return tolower(str); 
    else 
    	return str; 
}
int main(void)
{
	char st[] = "HOLA";
	printf("el string es: %s\n", st);
	char *res = ft_strmapi(st, funcioncreada);
	printf("despues es: %s\n",res);

}*/