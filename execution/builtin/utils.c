/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:08:28 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/21 12:51:24 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*cnc;
	int		i;

	if (!s1 && !s2)
		return (0);
	i = 0;
	cnc = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!cnc)
		return (0);
	while (*s1)
	{
		cnc[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		cnc[i] = *s2;
		s2++;
		i++;
	}
	cnc[i] = 0;
	if (s1)
		free((char *)s1);
	return (cnc);
}
