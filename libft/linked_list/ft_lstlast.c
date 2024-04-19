/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:41:55 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/15 18:17:37 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// 1. Loop through list as long as the current nodes 'next' pointer isn't NULL
// 2. When loop exits, 'lst' will point to the last node in the list,
//    because the last nodes next pointer is NULL

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst -> next;
	}
	return (lst);
}
