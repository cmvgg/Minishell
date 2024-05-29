/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:07:27 by jllarena          #+#    #+#             */
/*   Updated: 2024/05/29 13:23:45 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "inc/libft/01-Libft/libft.h"

char *expand_variable(char *variable_name)
{
    char *value = getenv(variable_name);
    if (value)
        return ft_strdup(value); 
    else 
        return ""; 
}


