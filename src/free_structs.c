/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:57:41 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/26 09:50:19 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_tokens *token)
{
	int			size;
	int			i;
	t_tokens	*node;

	i = -1;
	size = lstsize_tokens(token, 0);
	while (++i < size)
	{
		node = token;
		token = token->next;
		if (node->str)
		{
			free(node->str);
			node->str = NULL;
		}
		free(node);
	}
}

void	free_env(t_env *env)
{
	int		i;
	int		size;
	t_env	*node;

	i = -1;
	size = env_len(env);
	while (++i < size)
	{
		node = env;
		env = env->next;
		if (node->was_added)
			free(node->str);
	}
}

void	free_structs(t_commands *commands, int flag)
{
	int			size;
	int			i;
	t_commands	*node;

	i = -1;
	if (flag)
		free_env(commands->env);
	size = lstsize_commands(commands);
	while (++i < size)
	{
		node = commands;
		free_tokens(commands->token);
		commands = commands->next;
		free(node);
	}
}

void	free_tokens_s(t_tokens *token)
{
	int			size;
	int			i;
	t_tokens	*node;

	i = -1;
	size = lstsize_tokens(token, 0);
	while (++i < size)
	{
		node = token;
		token = token->next;
		if (node->str)
		{
			node->str = NULL;
		}
		free(node);
	}
}

void	free_structs2(t_commands *commands)
{
	int			size;
	int			i;
	t_commands	*node;

	i = -1;
	size = lstsize_commands(commands);
	while (++i < size)
	{
		node = commands;
		free_tokens_s(commands->token);
		commands = commands->next;
		free(node);
	}
}
