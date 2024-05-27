/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:29:25 by jllarena          #+#    #+#             */
/*   Updated: 2023/09/26 11:08:31 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	lon_needle;
	char	*str1;
	char	*str2;

	str1 = (char *)haystack;
	str2 = (char *)needle;
	lon_needle = ft_strlen(str2);
	if (lon_needle == 0)
		return (str1);
	i = 0;
	while (i < len && str1[i])
	{
		if (str1[i] == str2[0] && (i + lon_needle) <= len)
		{
			if (ft_strncmp(&str1[i], str2, lon_needle) == 0)
			{
				return (&str1[i]);
			}
		}
		i++;
	}
	return (NULL);
}

/*
int main(void)
{
	char str1[] = "foo bar baz";
	char str2[] = "bar";

	printf("la funcion hace: %s\n", ft_strnstr(str1, str2, 7));
	return (0);
} */