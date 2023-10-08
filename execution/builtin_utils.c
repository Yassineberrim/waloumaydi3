/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:09:50 by yberrim           #+#    #+#             */
/*   Updated: 2023/10/02 16:25:56 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../minishell.h"

int	is_buildin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0 || ft_strcmp(cmd->cmd[0],
			"pwd") == 0 || ft_strcmp(cmd->cmd[0], "cd") == 0
		|| ft_strcmp(cmd->cmd[0], "export") == 0 || ft_strcmp(cmd->cmd[0],
			"unset") == 0 || ft_strcmp(cmd->cmd[0], "env") == 0
		|| ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (1);
	else
		return (0);
}

int	execution_builtin(t_cmd *cmd, int i)
{
	int	check;

	check = 0;
	if (!ft_strcmp(cmd[i].cmd[0], "echo"))
		check = ft_echo(cmd, cmd[i].fd_out);
	else if (!ft_strcmp(cmd[i].cmd[0], "pwd"))
		check = ft_pwd(cmd[i].fd_out);
	else if (!ft_strcmp(cmd[i].cmd[0], "env"))
		print_env(cmd[i].env, cmd->cmd[0]);
	else if (!ft_strcmp(cmd[i].cmd[0], "cd"))
		check = ft_cd(cmd, cmd[i].fd_out);
	else if (!ft_strcmp(cmd[i].cmd[0], "export"))
		check = ft_export(cmd);
	else if (!ft_strcmp(cmd[i].cmd[0], "exit"))
		check = ft_exit(cmd);
	else if (!ft_strcmp(cmd[i].cmd[0], "unset"))
		check = ft_unset(cmd);
	return (check);
}
