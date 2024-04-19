/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:49:02 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// 1. The loop goes through each node in the list
// 2. It stores the 'next_node' so we don"t lose it's reference when
//    the current node is deleted
// 3. It calls the 'del' function to free the content of the current node
// 4. Then it frees the memory of the current node 
// 5. Then it moves to the next node
// 6. After all nodes have been freed, the pointer that points to the head
//    of the linked list is set to NULL, indicating the list is empty

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*next_node;

	temp = *lst;
	while (temp)
	{
		next_node = temp -> next;
		del(temp -> content);
		free(temp);
		temp = next_node;
	}
	*lst = NULL;
}
