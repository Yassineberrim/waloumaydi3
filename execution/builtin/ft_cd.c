/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:40:58 by yberrim           #+#    #+#             */
/*   Updated: 2023/10/02 15:37:42 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int	change_directory(const char *path, int fd)
{
	if (path == NULL)
	{
		ft_putstr_fd("cd: Path not set\n", fd);
		return (g_exit_status = 1);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: No such file or directory\n", fd);
		return (g_exit_status = 1);
	}
	return (0);
}

int	ft_cd(t_cmd *cmd, int fd)
{
	char	*old_pwd;

	old_pwd = getenv("OLDPWD");
	if (cmd->cmd[1] == NULL)
		return (change_directory(getenv("HOME"), fd));
	else if (ft_strcmp(cmd->cmd[1], "-") == 0)
		return (change_directory(old_pwd, fd));
	else
		return (change_directory(cmd->cmd[1], fd));
}
