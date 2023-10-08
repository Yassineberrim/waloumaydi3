/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 02:00:15 by slazar            #+#    #+#             */
/*   Updated: 2023/08/28 13:34:43 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *))
{
	t_lst	*head;
	t_lst	*temp;
	void	*contentcpy;

	head = NULL;
	while (lst)
	{
		contentcpy = f(lst->content);
		temp = ft_lstnew(contentcpy);
		if (!temp)
			del(contentcpy);
		ft_lstadd_back(&head, temp);
		lst = lst->next;
	}
	return (head);
}

// newlist = ft_lstmap(mylist, ft_strdup, free);
// dna Polymerase
