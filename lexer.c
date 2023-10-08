/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 10:09:30 by slazar            #+#    #+#             */
/*   Updated: 2023/10/03 18:44:10 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node_to_lexer(t_lexer *lx, char *word, enum e_token token,
		enum e_state state)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return ;
	new->content = word;
	new->type = token;
	new->len = ft_strlen(word);
	new->next = NULL;
	new->prev = NULL;
	new->state = state;
	if (lx->tail)
	{
		lx->tail->next = new;
		new->prev = lx->tail;
	}
	lx->tail = new;
	if (!lx->head)
		lx->head = new;
	lx->size += 1;
}

void	take_token(char *str, int *i, t_lexer *lx)
{
	char	*token;

	if (str[*i] == ENV)
	{
		take_env(str, i, lx);
		return ;
	}
	token = ft_strdup_2(str, *i, *i);
	if (str[*i] == WHITE_SPACE)
		add_node_to_lexer(lx, token, WHITE_SPACE, GENERAL);
	else if (str[*i] == NEW_LINE)
		add_node_to_lexer(lx, token, NEW_LINE, GENERAL);
	else if (str[*i] == QOUTE)
		add_node_to_lexer(lx, token, QOUTE, GENERAL);
	else if (str[*i] == DOUBLE_QUOTE)
		add_node_to_lexer(lx, token, DOUBLE_QUOTE, GENERAL);
	else if (str[*i] == ESCAPE)
		add_node_to_lexer(lx, token, ESCAPE, GENERAL);
	else if (str[*i] == PIPE_LINE)
		add_node_to_lexer(lx, token, PIPE_LINE, GENERAL);
	else if (str[*i] == TAB)
		add_node_to_lexer(lx, token, TAB, GENERAL);
	else if (str[*i] == REDIR_IN && str[(*i) + 1] != REDIR_IN && str[(*i)
		- 1] != REDIR_IN)
		add_node_to_lexer(lx, token, REDIR_IN, GENERAL);
	else if (str[*i] == REDIR_OUT && str[(*i) + 1] != REDIR_OUT && str[(*i)
		- 1] != REDIR_OUT)
		add_node_to_lexer(lx, token, REDIR_OUT, GENERAL);
	else if (str[*i] == REDIR_OUT && str[(*i) + 1] == REDIR_OUT)
	{
		add_node_to_lexer(lx, ">>", D_REDIR_OUT, GENERAL);
		(*i)++;
	}
	else if (str[*i] == REDIR_IN && str[(*i) + 1] == REDIR_IN)
	{
		add_node_to_lexer(lx, "<<", HERE_DOC, GENERAL);
		(*i)++;
	}
	(*i)++;
}

int	is_alphabet(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'z'))
		return (0);
	return (1);
}
void	take_word(char *str, int *i, t_lexer *lx)
{
	int		start;
	char	*word;

	start = *i;
	while (str[*i] && if_token(str[*i]) == 1)
		(*i)++;
	word = ft_strdup_2(str, start, *i - 1);
	add_node_to_lexer(lx, word, WORD, GENERAL);
}
void	give_state(t_lexer *lx)
{
	t_node	*cur;

	cur = lx->head;
	while (cur && cur->next)
	{
		if (cur->type == DOUBLE_QUOTE && cur->next)
		{
			cur = cur->next;
			while (cur && cur->type != DOUBLE_QUOTE)
			{
				cur->state = IN_DQUOTE;
				cur = cur->next;
			}
		}
		else if (cur->type == QOUTE && cur->next)
		{
			cur = cur->next;
			while (cur && cur->type != QOUTE)
			{
				cur->state = IN_SQUOTE;
				cur = cur->next;
			}
		}
		if (cur)
			cur = cur->next;
	}
}
void	free_list(t_lexer *lst)
{
	t_node	*tmp;

	if (!lst)
		return ;
	tmp = lst->head;
	while (tmp)
	{
		free(tmp->content);
		free(tmp);
		tmp = tmp->next;
	}
}

int	if_redirection(enum e_token type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == D_REDIR_OUT
		|| type == HERE_DOC)
		return (1);
	return (0);
}

t_node	*skip_spaces(t_node *elem, char direction)
{
	while (elem && (elem->type == WHITE_SPACE || elem->type == TAB))
	{
		if (direction == 'l')
			elem = elem->prev;
		else if (direction == 'r')
			elem = elem->next;
	}
	return (elem);
}
int	pipe_err(t_node *elem)
{
	t_node	*next;
	t_node	*prev;

	next = skip_spaces(elem->next, 'r');
	prev = skip_spaces(elem->prev, 'l');
	if (!next || !prev || (next->type != WORD
			&& if_redirection(next->type) == 0))
		return (1);
	return (0);
}
int	ft_perr(char *str, char *token)
{
	write(1, str, ft_strlen(str));
	if (token)
		write(1, token, ft_strlen(token));
	write(1, "\n", 1);
	return (1);
}
char	*get_token(enum e_token type)
{
	if (type == HERE_DOC)
		return ("<<");
	else if (type == REDIR_OUT)
		return (">");
	else if (type == D_REDIR_OUT)
		return (">>");
	else if (type == REDIR_IN)
		return ("<");
	return (".");
}
int	redir_err(t_node *ptr)
{
	t_node	*nxt;

	nxt = skip_spaces(ptr->next, 'r');
	if (!nxt || (nxt->type != WORD && nxt->type != ENV
			&& nxt->type != DOUBLE_QUOTE && nxt->type != QOUTE))
		return (1);
	return (0);
}
t_node	*check_quotes(t_node **node, enum e_token quote)
{
	while (*node)
	{
		*node = (*node)->next;
		if (!*node || (*node)->type == quote)
			break ;
	}
	if (!*node)
		write(1, "minishell: unclosed quotes detected.\n",
			ft_strlen("minishell: unclosed quotes detected.\n"));
	return (*node);
}

int	syntax_error(t_lexer *lst)
{
	t_node	*cur;

	cur = lst->head;
	while (cur)
	{
		if (cur->type == PIPE_LINE)
		{
			if (pipe_err(cur))
				return (ft_perr("minishell: syntax error near "
								"unexpected token `|'",
								0));
		}
		else if (if_redirection(cur->type))
		{
			if (redir_err(cur))
				return (ft_perr("minishell: syntax error near "
								"unexpected token ",
								get_token(cur->type)));
		}
		else if (cur->type == DOUBLE_QUOTE || cur->type == QOUTE)
		{
			if (!check_quotes(&cur, cur->type))
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}
void	Join_node(char *content, t_node **first, t_node **last,
		enum e_state state, t_lexer *lx)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->content = ft_substr(content, 0, ft_strlen(content));
	new->next = NULL;
	new->prev = NULL;
	new->len = ft_strlen(new->content);
	if (state == IN_DQUOTE)
		new->type = DOUBLE_QUOTE;
	else
		new->type = QOUTE;
	new->state = state;
	if (*first)
		(*first)->next = new;
	new->prev = (*first);
	new->next = (*last);
	if (*last)
		(*last)->prev = new;
	if (!(*first))
		lx->head = new;
}
void	take_in_dq(t_node **cur, enum e_state state, t_lexer *lx)
{
	char	*new_cont;
	t_node	*tmp;
	t_node	*ptr;

	tmp = (*cur);
	new_cont = ft_calloc(1, 1);
	(*cur) = (*cur)->next;
	while ((*cur) && (*cur)->state == state)
	{
		new_cont = ft_strjoin(new_cont, (*cur)->content);
		(*cur) = (*cur)->next;
	}
	Join_node(new_cont, &tmp->prev, cur, state, lx);
	while (tmp && tmp->state == state)
	{
		free(tmp->content);
		ptr = tmp->next;
		free(tmp);
		tmp = ptr;
		lx->size -= 1;
	}
}
void	join_quotes(t_lexer *lx)
{
	t_node	*cur;

	cur = lx->head;
	while (cur)
	{
		if (cur->type == DOUBLE_QUOTE)
			take_in_dq(&cur, IN_DQUOTE, lx);
		else if (cur->type == QOUTE)
			take_in_dq(&cur, IN_SQUOTE, lx);
		else
			cur = cur->next;
	}
}
void	delete_white_space(t_lexer *lx)
{
	t_node	*cur;
	t_node	*tmp;

	cur = lx->head;
	while (cur)
	{
		if (cur->type == WHITE_SPACE || cur->type == TAB || (cur->type == QOUTE
				&& !cur->len) || (cur->type == DOUBLE_QUOTE && !cur->len))
		{
			tmp = cur->next;
			if (cur->prev)
				cur->prev->next = cur->next;
			if (cur->next)
				cur->next->prev = cur->prev;
			if (cur == lx->head)
				lx->head = cur->next;
			if (cur == lx->tail)
				lx->tail = cur->prev;
			free(cur->content);
			free(cur);
			lx->size -= 1;
			cur = tmp;
		}
		else
			cur = cur->next;
	}
}
char	*get_env(t_env *env, char *str)
{
	t_env	*cur;
	char	*s;

	s = ft_strdup(str + 1);
	cur = env;
	while (cur)
	{
		if (!ft_strncmp(cur->name, (str + 1), ft_strlen(s)))
			return (cur->value);
		cur = cur->next;
	}
	free(s);
	return (NULL);
}

void	var_from_env(t_env *env, t_lexer *lx)
{
	t_node	*cur;

	cur = lx->head;
	while (cur)
	{
		if (cur->type == ENV && (cur->state == GENERAL
				|| cur->state == IN_DQUOTE) && ft_strlen(cur->content) > 1)
		{
			if (cur->content[1] == '?')
			{
				cur->content = ft_strjoin(ft_itoa(g_exit_status), cur->content
						+ 2);
				cur->len = ft_strlen(cur->content);
				cur->type = ENV;
			}
			else
			{
				cur->content = ft_strdup(get_env(env, cur->content));
				cur->len = ft_strlen(cur->content);
				cur->type = ENV;
			}
		}
		cur = cur->next;
	}
}

int	lexer(char *str, t_lexer *lx, t_env *env)
{
	int	i;

	i = 0;
	(void)env;
	while (str && str[i])
	{
		if (str[i] && if_token(str[i]) == 1)
			take_word(str, &i, lx);
		else if (if_token(str[i]) == 0)
			take_token(str, &i, lx);
		else
			i++;
	}
	give_state(lx);
	var_from_env(env, lx);
	if (syntax_error(lx))
		return (g_exit_status = 258, 1);
	return (g_exit_status = 0, 0);
}
void	ft_initialisation(t_lexer *lx)
{
	lx->head = NULL;
	lx->tail = NULL;
	lx->size = 0;
}
void	ft_print_lexer(t_node **head)
{
	t_node	*cur;
	char	*state;

	cur = *head;
	char general[] = "GENERAL";
	char in_s_quote[] = "IN_S_QUOTE";
	char in_d_quote[] = "IN_D_QUOTE";
	printf("-----------------------------------------------------------\n");
	printf("|%-17s|%3s|%15s|      token    |\n", "content", "len", "state");
	printf("-----------------------------------------------------------\n");
	while (cur)
	{
		if (cur->state == IN_DQUOTE)
			state = in_d_quote;
		else if (cur->state == IN_SQUOTE)
			state = in_s_quote;
		else if (cur->state == GENERAL)
			state = general;
		printf("|%-17s|%4d|%-15s|", cur->content, cur->len, state);
		if (cur->type == WORD)
			printf("      WORD    |\n");
		else if (cur->type == WHITE_SPACE)
			printf("      WHITE_SPACE    |\n");
		else if (cur->type == NEW_LINE)
			printf("       NEW_LINE     |\n");
		else if (cur->type == QOUTE)
			printf("      QOUTE    |\n");
		else if (cur->type == DOUBLE_QUOTE)
			printf("     DOUBLE_QUOTE     |\n");
		else if (cur->type == ESCAPE)
			printf("      ESCAPE     |\n");
		else if (cur->type == ENV)
			printf("     ENV    |\n");
		else if (cur->type == PIPE_LINE)
			printf("     PIPE_LINE     |\n");
		else if (cur->type == REDIR_IN)
			printf("    REDIR_IN     |\n");
		else if (cur->type == TAB)
			printf("    TAB     |\n");
		else if (cur->type == REDIR_OUT)
			printf("     REDIR_OUT    |\n");
		else if (cur->type == D_REDIR_OUT)
			printf("     DREDIR_OUT     |\n");
		else if (cur->type == HERE_DOC)
			printf("    HERE_DOC    |\n");
		printf("-----------------------------------------------------------\n");
		cur = cur->next;
	}
}
