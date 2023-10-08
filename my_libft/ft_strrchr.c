/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:35:00 by slazar            #+#    #+#             */
/*   Updated: 2022/10/20 17:22:59 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	sl;

	sl = ft_strlen(s);
	while (sl + 1)
	{
		if (s[sl] == (char)c)
			return ((char *)&s[sl]);
		sl--;
	}
	return (0);
}
