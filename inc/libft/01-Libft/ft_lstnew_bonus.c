/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:00:50 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/23 11:26:49 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list) * 1);
	if (list == 0)
		return (0);
	list -> content = content;
	list -> next = 0;
	return (list);
}
/*int main(void)
{
    t_list *nodo;
    nodo = malloc (sizeof(t_list) * 1);
    nodo -> content = "hola";
    
    ft_lstnew((void *)nodo -> content);
    printf("el nodo: %s", nodo -> content);
}*/