/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:41:38 by jllarena          #+#    #+#             */
/*   Updated: 2024/06/07 10:15:06 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "inc/libft/01-Libft/libft.h"
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


void		ft_quote(char **result);
char	**ft_splitquote(char const *s, char c);
char	**ft_splitmeta(char const *s, char c);
char	*expand_variable(char *variable_name);
char	**split_by_pipes(const char *line);
bool	is_builtin(const char *cmd);
char	*find_in_path(const char *cmd);
bool	is_executable_file(const char *cmd);
int		open_file(const char *filename);
void	free_ft_splitmeta(char **array);
char **ft_split_flags(char **split, int space_flag, char **result);
int ft_check(char **result, int quote);

