/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:52:08 by yberrim           #+#    #+#             */
/*   Updated: 2023/10/09 19:53:30 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i++] != '-')
		return (0);
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd, int fd_out)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (cmd->cmd[i])
	{
		while (check_flag(cmd->cmd[i]))
		{
			n = 1;
			i++;
		}
	}
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], fd_out);
		if (cmd->cmd[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
	if (n == 0)
		ft_putstr_fd("\n", fd_out);
	return (0);
}
