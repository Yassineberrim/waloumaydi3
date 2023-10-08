/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 19:02:01 by slazar            #+#    #+#             */
/*   Updated: 2023/09/18 22:21:36 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*cnc;
	int		i;
	char* tmp;
	
	tmp = s1;
	i = 0;
	cnc = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!cnc)
		return (0);
	while (s1 && *s1)
	{
		cnc[i] = *s1;
		s1++;
		i++;
	}
	if(tmp)
		free(tmp);
	while (s2 && *s2)
	{
		cnc[i] = *s2;
		s2++;
		i++;
	}
	cnc[i] = 0;
	return (cnc);
}
