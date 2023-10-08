/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:18:37 by yberrim           #+#    #+#             */
/*   Updated: 2023/10/09 00:53:19 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char *ft_genv(t_env *env, char *str)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, str))
			return (tmp->value);
		tmp = tmp->next;
	}
	// printf("minishell: %s: No such file or directory\n", str);
	return (NULL);
}
size_t ft_envsize(t_env *env)
{
	size_t i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}


char** lincke_list_toaraay(t_env *env)
{
	t_env *tmp;
	char **env_arr;
	int i;
	
	i = 0;
	env_arr = malloc(sizeof(char *) * (ft_envsize(env) + 1));
	tmp = env;
	while (tmp)
	{
		env_arr[i] = ft_strdup(tmp->name);
		env_arr[i] = ft_strjoin(env_arr[i], "=");
		env_arr[i] = ft_strjoin(env_arr[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	return (env_arr);
}
char	*find_abs_path(t_env *env ,char *cmd)
{
	char *raw_path;
	char **path_arr;
	int i;

	i = 0;
	raw_path = ft_genv(env, "PATH");
	path_arr = ft_split(raw_path, ':');
	if (cmd && cmd[0] == '/' && ft_strlen(cmd) > 1)
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd && cmd[0] == '.' && cmd[1] == '/' && ft_strlen(cmd) > 2)
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (NULL);
	}
	while (path_arr && path_arr[i])
	{
		char *fwd_slash = ft_strjoin(path_arr[i], "/");
		char *abs_path = ft_strjoin(fwd_slash, cmd);
		if (access(abs_path, F_OK) == 0)
		{
			free(path_arr);
			return (abs_path);
		}
		free(abs_path);
		i++;
	}

	return (NULL);
}