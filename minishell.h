/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:41:38 by jllarena          #+#    #+#             */
/*   Updated: 2024/06/07 10:04:43 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "inc/libft/01-Libft/libft.h"

int     ft_quote(char **result);
char	**ft_splitquote(char const *s, char c);
char	**ft_splitmeta(char const *s, char c);
char    *expand_variable(char *variable_name);

/*y*/
