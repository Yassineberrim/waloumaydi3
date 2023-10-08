/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 03:41:24 by slazar            #+#    #+#             */
/*   Updated: 2023/08/28 13:34:43 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_lst **lst, void (*del)(void	*))
{
	t_lst	*ptr;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		ptr = ((*lst)->next);
		ft_lstdelone(*lst, del);
		(*lst) = ptr;
	}
}
