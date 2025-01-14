/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:38:24 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/24 19:38:27 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <linux/limits.h>

void	update_oldpwd(char *dir, t_env *env)
{
	int		pos;
	char	*env_name;
	t_env	*head;

	head = env;
	while (env)
	{
		pos = search_ops_in_str(env->str, "=");
		env_name = ft_substr(env->str, 0, pos);
		if (!ft_strcmp(env_name, "OLDPWD"))
		{
			if (env->was_added)
				free(env->str);
			env->str = form_variable(env_name, dir);
			env->was_added = 1;
			break ;
		}
		free(env_name);
		env = env->next;
	}
	env = head;
}

static void	update_pwds(char *oldpwd, t_env *env)
{
	int		pos;
	char	value[PATH_MAX];
	char	*env_name;
	char	*pwd;
	t_env	*head;

	head = env;
	pwd = ft_strdup(getcwd(value, PATH_MAX));
	while (env)
	{
		pos = search_ops_in_str(env->str, "=");
		env_name = ft_substr(env->str, 0, pos);
		if (!ft_strcmp(env_name, "PWD"))
		{
			if (env->was_added)
				free(env->str);
			env->str = form_variable(env_name, pwd);
			env->was_added = 1;
			break ;
		}
		free(env_name);
		env = env->next;
	}
	env = head;
	update_oldpwd(oldpwd, env);
}

int	change_dir(t_tokens *token, t_env *env)
{
	char	value[PATH_MAX];
	char	*dir;
	char	*oldpwd;

	dir = NULL;
	oldpwd = getcwd(value, PATH_MAX);
	if (!token->next || (token->next->str && !ft_strcmp(token->next->str, "~")))
		dir = env_value("HOME", env);
	else if (token->next->str && !ft_strcmp(token->next->str, "-"))
	{
		dir = env_value("OLDPWD", env);
		printf("%s\n", dir);
	}
	else if (token->next->str)
		dir = ft_strdup(token->next->str);
	if (dir && chdir(dir))
	{
		g_exit_status = 1;
		printf("%s\n", UNKNOWN);
	}
	else
		update_pwds(ft_strdup(oldpwd), env);
	if (dir)
		free(dir);
	return (1);
}
