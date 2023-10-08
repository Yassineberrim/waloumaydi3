/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 22:14:34 by slazar            #+#    #+#             */
/*   Updated: 2023/08/28 13:34:43 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst	*ptr ;

	ptr = (t_lst *) malloc(sizeof(t_lst));
	if (!ptr)
		return (0);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}
