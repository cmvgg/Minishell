/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:40:54 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/24 19:40:55 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	red_count(char *str, int c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count);
}

t_TokenType	which_red(char *str)
{
	if (red_count(str, '>') == 1)
		return (RED_OUT);
	if (red_count(str, '<') == 1)
		return (RED_IN);
	if (red_count(str, '>') == 2 && red_count(str, '<') == 0)
		return (APPEND_OUT);
	if (red_count(str, '<') == 2 && red_count(str, '>') == 0)
		return (HEREDOC);
	return (ERRO);
}
