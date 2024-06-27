/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvarela- <cvarela-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:37:04 by cvarela-          #+#    #+#             */
/*   Updated: 2024/06/24 19:38:56 by cvarela-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static int	is_executable(char *bin_path, struct stat f)
{
	if (f.st_mode & __S_IFREG)
	{
		if (f.st_mode & S_IXUSR)
			return (1);
		else
		{
			g_exit_status = 126;
			printf("%s\n", PD);
		}
	}
	free(bin_path);
	return (0);
}

int	check_bins(t_tokens *token, t_env *env)
{
	int			i;
	char		*bin_path;
	char		**path;
	struct stat	f;

	path = get_path(env);
	if (!path)
		return (0);
	i = -1;
	while (path && path[++i])
	{
		bin_path = get_bin_path(path[i], token->str);
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else if (is_executable(bin_path, f))
		{
			while (path[++i])
				free(path[i]);
			free(path);
			return (run_cmd(bin_path, token, env, 1));
		}
	}
	free(path);
	return (0);
}

static int	free_values(char *bin_path, char **args,
	char **env_matrix, int flag)
{
	int	i;

	i = -1;
	if (flag)
		free(bin_path);
	while (args[++i])
		free(args[i]);
	free(args);
	i = -1;
	while (env_matrix[++i])
		free(env_matrix[i]);
	free(env_matrix);
	return (1);
}

int	run_cmd(char *bin_path, t_tokens *token, t_env *env, int flag)
{
	char		**args;
	char		**env_matrix;

	args = fill_args(token);
	env_matrix = fill_env_matrix(env);
	execve(bin_path, args, env_matrix);
	return (free_values(bin_path, args, env_matrix, flag));
}
