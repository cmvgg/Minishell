/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jllarena <jllarena@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:01:12 by jllarena          #+#    #+#             */
/*   Updated: 2023/10/23 11:27:47 by jllarena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}
/*int main(void)
{
    t_list  *nodo1;
    t_list  *nodo2;
    t_list  *nodo3;

    nodo1 = malloc(sizeof(t_list) * 1);
    nodo2 = malloc(sizeof(t_list) * 1);
    nodo3 = malloc(sizeof(t_list) * 1);
    nodo1 -> next = nodo2;
    nodo2 -> next = nodo3;
    nodo3 -> next = NULL;
	
	printf("el numero de nodods es: %d", ft_lstsize(nodo1));

}*/