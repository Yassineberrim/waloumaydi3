/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:45:30 by yberrim           #+#    #+#             */
/*   Updated: 2023/10/02 15:46:55 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

void	add_new_var(t_env *env, char **var)
{
	t_env	*new;
	t_env	*head;

	new = malloc(sizeof(t_env));
	new->name = ft_strdup(var[0]);
	new->value = ft_strdup(var[1]);
	new->next = NULL;
	if (!env)
		env = new;
	else
	{
		head = env;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

int	check_if_exist(t_cmd *cmd, char **var)
{
	t_env	*env;

	env = cmd->env;
	while (env)
	{
		if (ft_strcmp(env->name, var[0]) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	index_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	**ssplit(char *s)
{
	char	**new;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (!ft_strchr(s, '='))
	{
		new = malloc(sizeof(char *) * 2);
		new[0] = ft_strdup(s);
		new[1] = NULL;
		return (new);
	}
	new = malloc(sizeof(char *) * 3);
	while (s[i++])
	{
		if (s[i] == '=')
		{
			new[0] = ft_substr(s, 0, i);
			new[1] = ft_substr(s, i + 1, ft_strlen(s));
			new[2] = NULL;
			return (new);
		}
	}
	return (new);
}

char	**check_invalid_var(char *str)
{
	int	i;

	if (str[0] && !ft_isalpha(str[0]) && str[0] != '_')
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (NULL);
	}
	i = 0;
	index_equal(str);
	if (str[i - 1] == '-')
	{
		perror("bash: export: `-': not a valid identifier\n");
		return (NULL);
	}
	return (ssplit(str));
}
