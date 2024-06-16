/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:16:26 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/05 12:31:57 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	size(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		sn;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	sn = size(n);
	str = malloc(sizeof(char) * (sn + 1));
	if (!str)
		return (0);
	str[sn] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	sn--;
	while (n > 0)
	{
		str[sn] = ((n % 10) + 48);
		n /= 10;
		sn--;
	}
	return (str);
}
/*
int main(void)
{
	char *num;
	int n;

	n = atoi("-9");
	num = ft_itoa(n);
    printf("size: %d\n", size(n));
    printf("number: %s\n", num);
    printf("c: %c\n", num[1]);
    return (0);
}*/