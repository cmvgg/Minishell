/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:35:41 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/04 11:09:15 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		str = malloc(1);
		if (!str)
			return (0);
		str[0] = '\0';
		return (str);
	}
	if (len > s_len - start)
		len = s_len - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	ft_strlcpy(str, &s[start], len + 1);
	return (str);
}

/*
int main()
{
    char *original = 0;
    char *substring;

    substring = ft_substr(original, 7, 69); 
    printf("Substring: %s\n", substring);
}*/