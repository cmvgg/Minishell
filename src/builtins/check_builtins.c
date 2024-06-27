/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:38:33 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/26 09:54:38 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <linux/limits.h>
#include "minishell.h"

int	check(t_commands *command)
{
	if (command->token->str == NULL)
		return (0);
	if (!ft_strcmp(command->token->str, "exit"))
		return (exit_terminal(command));
	if (!ft_strcmp(command->token->str, "env"))
		return (env(command->env, 0));
	if (!ft_strcmp(command->token->str, "unset"))
		return (unset(command->token, command->env));
	if (!ft_strcmp(command->token->str, "export"))
	{
		if (command->token->next && command->token->next->str)
		{
			command->token = command->token->next;
			export(command);
			return (1);
		}
		return (env(command->env, 1));
	}
	if (!ft_strcmp(command->token->str, "cd"))
		return (change_dir(command->token, command->env));
	return (0);
}

static int	is_exit_status(char *str)
{
	int		res;
	char	*new_str;
	char	*new_str1;

	res = 0;
	new_str = ft_strtrim(str, "\"");
	new_str1 = ft_strtrim(new_str, "'");
	free(new_str);
	if (!ft_strcmp(new_str1, "$?"))
		res = 1;
	free (new_str1);
	return (res);
}

int	check_builtins(t_commands *command)
{
	char	value[PATH_MAX];

	if (command->token->str == NULL)
		return (0);
	if (!ft_strcmp(command->token->str, "echo"))
		return (print(command->token->next));
	if (is_exit_status(command->token->str))
	{
		printf("%lld: %s\n", g_exit_status, CNF);
		return (1);
	}
	if (!ft_strcmp(command->token->str, "pwd"))
	{
		printf("%s\n", getcwd(value, PATH_MAX));
		return (1);
	}
	return (0);
}
