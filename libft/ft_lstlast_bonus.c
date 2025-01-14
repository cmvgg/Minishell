/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:00:11 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/23 11:24:30 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next != NULL)
		lst = lst -> next;
	return (lst);
}
/*int main(void)
{
	t_list  *nodo1;
    t_list  *nodo2;
    t_list  *nodo3;
	t_list  *last;
	char str_last[] = "hola";

    nodo1 = malloc(sizeof(t_list) * 1);
    nodo2 = malloc(sizeof(t_list) * 1);
    nodo3 = malloc(sizeof(t_list) * 1);
    nodo1 -> next = nodo2;
    nodo2 -> next = nodo3;
    nodo3 -> content = (void *)str_last;
	nodo3 -> next = NULL;
	last = ft_lstlast(nodo1); 
	printf("el resultado es: %s", last -> content);
}*/