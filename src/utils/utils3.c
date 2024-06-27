/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:56:52 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/25 12:14:25 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_digit_signal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (0);
		i += 1;
	}
	return (1);
}

int	crazy(char *line)
{
	if (!ft_strcmp(line, "crazy"))
	{
		printf("\nCrazy? I was crazy once\n");
		printf("They locked me in a room, a rubber room\n");
		printf("A rubber room with rats, and rats make me crazy\n\n");
		return (1);
	}
	return (0);
}
