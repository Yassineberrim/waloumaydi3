/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:00:58 by yberrim           #+#    #+#             */
/*   Updated: 2023/10/02 16:17:35 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int	is_strdigits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_cmd *cmd)
{
	int		i;
	char	**argv;

	argv = cmd->cmd;
	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
		exit(g_exit_status);
	else if (i == 2)
	{
		if (is_strdigits(argv[1]))
			exit(ft_atoi(argv[1]));
		else
		{
			write(2, "minishell: exit: ", 17);
			g_exit_status = 255;
		}
	}
	else
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return (g_exit_status = 1);
	}
	return (0);
}
