/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 23:11:51 by slazar            #+#    #+#             */
/*   Updated: 2023/10/02 20:33:01 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *env)
{
	int		i;
	char	*name;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	name = malloc(sizeof(char) * i + 1);
	i = 0;
	while (env[i] && env[i] != '=')
	{
		name[i] = env[i];
		i++;
	}
	name[i] = 0;
	return (name);
}
char	*get_var_value(char *env)
{
	int		i;
	int		j;
	char	*value;

	j = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	value = malloc(ft_strlen(env + i));
	i++;
	while (env[i])
	{
		value[j] = env[i];
		j++;
		i++;
	}
	value[j] = 0;
	return (value);
}
void	ft_variables(t_env **env, char **envirement)
{
	int		i;
	t_env	*new;
	t_env	*head;

	g_exit_status = 0;
	i = 0;
	*env = 0;
	while (envirement[i])
	{
		new = malloc(sizeof(t_env));
		new->value = get_var_value(envirement[i]);
		new->name = get_var_name(envirement[i]);
		new->next = NULL;
		if (!*env)
		{
			*env = new;
			head = new;
		}
		else
		{
			(*env)->next = new;
			*env = (*env)->next;
		}
		i++;
	}
	*env = head;
}
void	print_env(t_env *env, char *cmd)
{
	while (env)
	{
		if (ft_strcmp(cmd, "env") == 0)
		{
			if (env->value && ft_strlen(env->value) > 0)
				printf("%s=%s\n", env->name, env->value);
		}
		if (ft_strcmp(cmd, "export") == 0)
		{
			if (env->value && ft_strlen(env->value) > 0)
				printf("declare -x %s=\"%s\"\n", env->name, env->value);
			else
				printf("declare -x %s\n", env->name);
		}
		env = env->next;
	}
}

void	take_env(char *str, int *i, t_lexer *lx)
{
	int start;
	char *var;
	start = *i;
	(*i)++;
	while (!is_digits(str[*i]) || !is_alphabet(str[*i]) || str[*i] == '_'
		|| str[*i] == '?')
		(*i)++;
	var = ft_strdup_2(str, start, (*i) - 1);
	add_node_to_lexer(lx, var, ENV, GENERAL);
}