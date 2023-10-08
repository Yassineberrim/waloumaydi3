/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:22:13 by slazar            #+#    #+#             */
/*   Updated: 2022/10/30 12:55:42 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_numbers(int n)
{
	int	c;

	c = 0;
	if (n < 0)
		c = 1;
	while (n)
	{
		n = n / 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		c;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	c = count_numbers(n) + 1;
	str = (char *)malloc(c);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	str [c - 1] = '\0';
	while (n)
	{
		str[c - 2] = n % 10 + '0';
		n = n / 10;
		c--;
	}
	return (str);
}
