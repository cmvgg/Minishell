/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:41:27 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/27 19:56:13 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	adding_new_token(t_tokens *token, int pos, char *op)
{
	char		*original_str;
	t_tokens	*new_token;
	t_tokens	*next;

	if (ft_strlen(token->str) > ft_strlen(op))
	{
		original_str = ft_strdup(token->str);
		next = token->next;
		if (search_content(original_str, op, 0))
			handle_content_before(token, pos, op, original_str);
		if (search_content(original_str, op, 1))
		{
			new_token = handle_content_after(original_str, pos, op, token);
			new_token->next = next;
		}
		free(original_str);
	}
}

static void	check_tokens(t_tokens *token)
{
	int			i;
	char		**ops;

	ops = fill_ops();
	while (token)
	{
		if (!token->was_quoted && token->str)
		{
			i = -1;
			while (ops[++i] && ft_strcmp(token->str, ops[i]))
			{
				if (search_ops_in_str(token->str, ops[i]) > -1)
				{
					adding_new_token(token,
						search_ops_in_str(token->str, ops[i]), ops[i]);
					break ;
				}
			}
		}
		if (token->next)
			token = token->next;
		else
			break ;
	}
	free(ops);
}

int	process_tokens(t_commands *command)
{
	int			temp;
	pid_t		pid;
	t_tokens	*head;

	head = command->token;
	if (!check(command))
	{
		pid = fork();
		handle_cmd_signals();
		if (pid == 0)
			return (function(command));
		waitpid(pid, &temp, 0);
		g_exit_status = temp >> 8;
		handle_global_signals();
	}
	command->token = head;
	return (1);
}

char	*process_argument(t_commands *c)
{
	int		i;
	int		start;
	char	*new_str;

	i = 0;
	start = 0;
	new_str = NULL;
	while (c->token->str[i])
	{
		while (c->token->str[i] && c->token->str[i] != '$'
			&& !isquote(c->token->str[i]))
			i++;
		if (i - start > 0)
			new_str = add_chars(new_str, c->token->str, i - start, start);
		if (!c->token->str[i])
			break ;
		if (c->token->str[i] == '$' && is_accepted(c->token))
			new_str = if_variable(new_str, c, &start, &i);
		else if (isquote(c->token->str[i]))
			new_str = if_quotes(new_str, c, &start, &i);
		else if (!ft_strcmp(c->token->str, "$?"))
			return (free(new_str), c->token->str);
		i++;
	}
	return (free(c->token->str), new_str);
}

void	parser(t_commands *command)
{
	t_tokens	*head;

	head = command->token;
	while (command->token)
	{
		if (has_in_out(command, head))
		{
			if (command->token->str)
				free(command->token->str);
			return ;
		}
		if (has_open_quotes(command->token->str,
				ft_strlen(command->token->str)))
		{
			g_exit_status = 2;
			command->token = head;
			if (command->token->str)
				free(command->token->str);
			return ((void)printf("%s\n", EPROMPT));
		}
		command->token->str = process_argument(command);
		command->token = command->token->next;
	}
	command->token = head;
	check_tokens(command->token);
	if (!check_redir(command))
		return ((void)printf("%s\n", SE));
	if (process_tokens(command))
		return ;
	if (command->token->str)
		free(command->token->str);
	printf("%s\n", CNF);
	exit(g_exit_status);
}
