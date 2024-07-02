/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:41:10 by cvarela-          #+#    #+#             */
/*   Updated: 2024/07/02 15:06:10 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_variable(char *str, int *pos)
{
	char	*variable;
	int		i;
	int		n;

	i = (*pos) + 1;
	n = 0;
	while (str[i] != '$' && str[i] != '=' && str[i] != ASPAS
		&& str[i] != PLICAS && str[i] != ' ' && str[i])
	{
		n++;
		i++;
	}
	(*pos) = i - 1;
	variable = malloc(sizeof(char) * n + 1);
	variable[n] = '\0';
	i = -1;
	while (n--)
		variable[++i] = str[(*pos) - n];
	return (variable);
}

char	*search_variable(char *command, int *pos, t_env *env)
{
	char	*var_name;
	char	*value;

	if (isquote(command[(*pos) + 1]) && command[(*pos) + 2] != '$'
		&& command[(*pos) + 2] != '\0')
		value = NULL;
	else if (command[(*pos) + 1] == '?')
	{
		(*pos) += 1;
		value = ft_itoa(g_exit_status);
	}
	else if (!ft_isalnum(command[(*pos) + 1]))
		value = "$";
	else
	{
		var_name = get_variable(command, pos);
		value = env_value(var_name, env);
		free(var_name);
	}
	(*pos) += 1;
	return (value);
}

char	*add_chars(char *expanding_str, char *str, int pos, int start)
{
	char	*new_str;
	char	*temp;

	new_str = NULL;
	temp = ft_substr(str, start, pos);
	write(1, "Y", 1);
	if (expanding_str && temp)
	{
		new_str = ft_strjoin(expanding_str, temp);
		free(expanding_str);
		free(temp);
		return (new_str);
	}
			write(1, "X", 1);
	free(expanding_str);
	return (temp);
}

char	*if_variable(char *new_str, t_commands *command, int *start, int *i)
{
	new_str = process_variable(command->token->str, i, new_str, command->env);
	(*start) = (*i);
	(*i)--;
	return (new_str);
}

char	*if_quotes(char *new_str, t_commands *command, int *start, int *i)
{
	char	*temp;
	char	*handling;

	search_for_redirs(command);
	handling = quote_handler(command->token->str, i, (*i) + 1, command->env);
	if (handling)
	{
		temp = new_str;
		if (temp)
		{
			new_str = ft_strjoin(temp, handling);
			if (temp && ft_strcmp(temp, "$"))
				free(temp);
			if (handling && ft_strcmp(handling, "$"))
				free(handling);
		}
		else
			new_str = handling;
	}
	(*start) = (*i);
	if (command->token->str[(*i) + 1])
		(*start)++;
	return (new_str);
}
