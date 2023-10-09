/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:18:37 by yberrim           #+#    #+#             */
/*   Updated: 2023/10/09 19:51:03 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

int	chek_path(char *cmd)
{
	if (cmd && cmd[0] == '/' && ft_strlen(cmd) > 1)
	{
		if (access(cmd, F_OK) == 0)
			return (1);
		return (0);
	}
	if (cmd && cmd[0] == '.' && cmd[1] == '/' && ft_strlen(cmd) > 2)
	{
		if (access(cmd, F_OK) == 0)
			return (1);
		return (0);
	}
	return (-1);
}

char	*find_abs_path(t_env *env, char *cmd)
{
	char	*raw_path;
	char	**path_arr;
	int		i;
	char	*fwd_slash;
	char	*abs_path;

	i = 0;
	raw_path = ft_genv(env, "PATH");
	path_arr = ft_split(raw_path, ':');
	chek_path(cmd);
	while (path_arr && path_arr[i])
	{
		fwd_slash = ft_strjoin(path_arr[i], "/");
		abs_path = ft_strjoin(fwd_slash, cmd);
		if (access(abs_path, F_OK) == 0)
		{
			return (abs_path);
		}
		i++;
	}
	free_double(path_arr);
	return (NULL);
}
