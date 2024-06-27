/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:38:15 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/25 11:52:58 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*form_variable(char *name, char *value)
{
	char	*str;
	char	*temp;

	temp = ft_strjoin(name, "=");
	str = ft_strjoin(temp, value);
	free(name);
	free(value);
	free(temp);
	return (str);
}

static int	env_exists(t_env *head, char *new_env, char *env_value)
{
	int		pos;
	char	*env_name;

	while (head)
	{
		pos = search_ops_in_str(head->str, "=");
		env_name = ft_substr(head->str, 0, pos);
		if (!ft_strcmp(new_env, env_name))
		{
			if (head->was_added)
				free(head->str);
			head->str = form_variable(new_env, env_value);
			head->was_added = 1;
			free(env_name);
			return (1);
		}
		head = head->next;
		free(env_name);
	}
	return (0);
}

static int	check_env_name(char *name)
{
	if (!ft_strlen(name) || ft_isdigit(name[0]) || !ft_strcmp(name, "$"))
	{
		printf("%s\n", NAI);
		free(name);
		return (0);
	}
	return (1);
}

void	export(t_commands *command)
{
	t_env	*new;
	t_env	*env_head;
	int		pos;
	char	*env_value;
	char	*env_name;

	env_head = command->env;
	while (command->token && command->token->str)
	{
		if (ft_strchr(command->token->str, '='))
		{
			pos = search_ops_in_str(command->token->str, "=");
			env_name = ft_substr(command->token->str, 0, pos);
			if (!check_env_name(env_name))
				return ;
			env_value = ft_substr(command->token->str, pos + 1,
					ft_strlen(command->token->str) - ft_strlen(env_name) - 1);
			if (!env_exists(env_head, env_name, env_value))
			{
				new = lstnew_env(form_variable(env_name, env_value), 1);
				lstadd_back_env(&command->env, new);
			}
		}
		command->token = command->token->next;
	}
}
