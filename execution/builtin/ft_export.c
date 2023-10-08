/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 21:50:34 by yberrim           #+#    #+#             */
/*   Updated: 2023/10/02 15:47:42 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

char	update_env(t_env *env, char **str)
{
	while (env)
	{
		if (ft_strcmp(env->name, str[0]) == 0)
		{
			if (env->value && !str[1])
			{
				return (0);
			}
			free(env->value);
			env->value = ft_strdup(str[1]);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	ft_export(t_cmd *cmd)
{
	int		i;
	char	**var;

	i = 1;
	var = NULL;
	if (cmd->cmd[1] == NULL)
	{
		print_env(cmd->env, cmd->cmd[0]);
		return (0);
	}
	while (cmd->cmd[i])
	{
		var = check_invalid_var(cmd->cmd[i]);
		if (var)
		{
			if (!check_if_exist(cmd, var))
				add_new_var(cmd->env, var);
			if (check_if_exist(cmd, var))
				update_env(cmd->env, var);
		}
		i++;
	}
	return (0);
}
