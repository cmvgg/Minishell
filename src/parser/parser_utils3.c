/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:41:19 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/26 15:19:48 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_tokens *token)
{
	t_TokenType	type;
	t_TokenType	type_next;

	type = token->type;
	if (type == 9)
		return (0);
	if (type >= 5 && type <= 8)
	{
		if (!token->next)
			return (0);
		type_next = token->next->type;
		if (type_next >= 5 && type_next <= 8)
			return (0);
	}
	return (1);
}

int	check_redir(t_commands *command)
{
	t_tokens	*head;

	head = command->token;
	while (command->token)
	{
		if (!command->token->was_quoted)
		{
			if (!check_syntax(command->token))
			{
				command->token = head;
				return (0);
			}
		}
		if (command->token->next)
			command->token = command->token->next;
		else
			break ;
	}
	command->token = head;
	return (1);
}

int	has_in_out(t_commands *command, t_tokens *head)
{
	int	len;

	len = ft_strlen(command->token->str);
	if (!has_open_quotes(command->token->str, len))
	{
		if (ft_strnstr(command->token->str, "<>", len))
		{
			command->token = head;
			printf("%s\n", SE);
			return (1);
		}
	}
	return (0);
}

void	search_for_redirs(t_commands *command)
{
	int		i;
	char	**ops;

	i = -1;
	ops = fill_ops();
	while (ops[++i])
	{
		if (ft_strnstr(command->token->str, ops[i],
				ft_strlen(command->token->str)))
		{
			command->token->was_quoted = 1;
			break ;
		}
	}
	free(ops);
	return ;
}

int	function(t_commands *command)
{
	if (!search_ops_in_str(command->token->str, ".")
		|| !search_ops_in_str(command->token->str, "/"))
	{
		if (!is_bin(command->token->str))
			exit(g_exit_status);
		return (run_cmd(command->token->str, command->token, command->env, 0));
	}
	if (lstsize_tokens(command->token, 1) != lstsize_tokens(command->token, 0))
	{
		if (!handle_redir(command->token))
		{
			exit(g_exit_status);
			return (1);
		}
	}
	if (!is_redirect(command->token->str, command->token->was_quoted))
	{
		if (!check_builtins(command)
			&& !check_bins(command->token, command->env))
			{
			free_structs(command, 1);
			return (0);
			}
	}
	exit(g_exit_status);
	return (1);
}
