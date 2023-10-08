/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:46:56 by slazar            #+#    #+#             */
/*   Updated: 2023/10/02 14:16:58 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	len_word(const char *s, char c, int i)
{
	int	len_s;

	len_s = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len_s++;
	}
	return (len_s);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		len_s;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!s)
		return (0);
	tab = (char **)ft_calloc(word(s, c) + 1, sizeof(char *));
	if (!tab)
		return (0);	
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		len_s = len_word(s, c, i);
		if (++j < word(s, c))
			tab[j] = ft_substr(s, i, len_s);
		while (s[i] && s[i] != c)
			i++;
	}
	return (tab);
}
