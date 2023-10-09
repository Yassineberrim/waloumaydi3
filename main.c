/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:24:41 by slazar            #+#    #+#             */
/*   Updated: 2023/10/10 00:05:03 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_sp_tab(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (*line ? 1 : 0);
}
int	check_space(char *line)
{
	if (*line == '\0' || only_sp_tab(line) == 0)
		return (0);
	return (1);
}
void	join_in_quote_and_word(t_lexer *lx)
{
	t_node	*tmp;
	t_node	*cur;

	cur = lx->head;
	while (cur)
	{
		if (cur->next && ((cur->type == QOUTE || cur->type == DOUBLE_QUOTE
					|| cur->type == WORD) && (cur->next->type == QOUTE
					|| cur->next->type == DOUBLE_QUOTE
					|| cur->next->type == WORD)))
		{
			tmp = cur->next;
			cur->content = ft_strjoin(cur->content, tmp->content);
			cur->len = ft_strlen(cur->content);
			cur->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = cur;
			free(tmp->content);
			free(tmp);
			lx->size -= 1;
			cur = lx->head;
		}
		cur = cur->next;
	}
}
int	ft_count_cmd(t_lexer *lx)
{
	t_node	*tmp;
	int		count;

	count = 0;
	tmp = lx->head;
	while (tmp)
	{
		if (tmp->type == PIPE_LINE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
void	init_cmd_struct(t_cmd **cmd)
{
	(*cmd)->cmd = NULL;
	(*cmd)->fd_in = 0;
	(*cmd)->fd_out = 1;
	// (*cmd)->redir.in_file = NULL;
	// (*cmd)->redir.out_file = NULL;
}
void	redirect(t_node **cur, t_cmd *cmd)
{
	if ((*cur)->type == REDIR_IN)
	{
		if (cmd->in_file)
			free(cmd->in_file);
		cmd->in_file = ft_strdup((*cur)->next->content);
		cmd->in_redir_type = READIN;
	}
	else if ((*cur)->type == REDIR_OUT)
	{
		if (cmd->out_file)
			free(cmd->out_file);
		cmd->out_file = ft_strdup((*cur)->next->content);
		cmd->out_redir_type = WRITEOUT;
	}
	else if ((*cur)->type == D_REDIR_OUT)
	{
		if (cmd->out_file)
			free(cmd->out_file);
		cmd->out_file = ft_strdup((*cur)->next->content);
		cmd->out_redir_type = APPENDOUT;
	}
	(*cur) = (*cur)->next->next;
}

void	check_next_next(t_node *cur)
{
	int	tmp_fd;

	if (cur->next->next && (cur->next->next->type == REDIR_IN
			|| cur->next->next->type == REDIR_OUT
			|| cur->next->next->type == D_REDIR_OUT))
	{
		tmp_fd = open(cur->next->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
		close(tmp_fd);
	}
}
void here_doc(t_node **cur, t_cmd **cmd)
{
    int        fd;
    char    *line;
    char    *tmp;

    fd = open("/tmp/heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    while (1)
    {
        line = readline(">");
        if (ft_strcmp(line, (*cur)->next->content) == 0)
        {
            free(line);
            break ;
        }
        tmp = ft_strjoin(line, "\n");
        write(fd, tmp, ft_strlen(tmp));
        free(tmp);
    }
    close(fd);
    (*cmd)->in_file = ft_strdup("/tmp/heredoc");
    (*cmd)->in_redir_type = HEREDOC;
    (*cur) = (*cur)->next->next;
}
void	create_cmd(t_lexer *lx, t_cmd *cmd)
{
	t_node	*cur;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cur = lx->head;
	cmd->fd_out = 1;
	while (cur)
	{
		if(cur->type == HERE_DOC)
        {
            here_doc(&cur, &cmd);
            continue ;
        }
		if (cur->type == REDIR_IN || cur->type == REDIR_OUT
			|| cur->type == D_REDIR_OUT)
		{
			check_next_next(cur);
			redirect(&cur, cmd);
			continue ;
		}
		if (cur->type == PIPE_LINE)
		{
			cmd->cmd = malloc(sizeof(char *) * (j + 1));
			cmd->cmd[j] = NULL;
			cmd->next = malloc(sizeof(t_cmd));
			ft_memset(cmd->next, 0, sizeof(t_cmd));
			cmd = cmd->next;
			i++;
			cmd->fd_out = 1;
			j = 0;
		}
		else
			j++;
		cur = cur->next;
	}
	cmd->cmd = malloc(sizeof(char *) * (j + 1));
	cmd->cmd[j] = NULL;
	cmd->next = NULL;
}

t_cmd	*commands(t_lexer *lx)
{
	t_node	*cur;
	t_cmd	*cmd;
	t_cmd	*head;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = malloc(sizeof(t_cmd) * (ft_count_cmd(lx) + 1));
	ft_memset(cmd, 0, sizeof(t_cmd));
	head = cmd;
	create_cmd(lx, cmd);
	cur = lx->head;
	while (cur)
	{
		if (cur->type == PIPE_LINE)
		{
			cmd->cmd[j] = NULL;
			i++;
			j = 0;
			cmd = cmd->next;
		}
		else if (cur->type == REDIR_IN || cur->type == REDIR_OUT
			|| cur->type == D_REDIR_OUT || cur->type == HERE_DOC
			|| (cur->type == WORD && cur->prev && (cur->prev->type == REDIR_IN
					|| cur->prev->type == REDIR_OUT
					|| cur->prev->type == D_REDIR_OUT
					|| cur->prev->type == HERE_DOC)))
		{
			cur = cur->next->next;
			continue ;
		}
		else
		{
			cmd->cmd[j] = ft_strdup(cur->content);
			free(cur->content);
			j++;
		}
		cur = cur->next;
	}
	cmd->cmd[j] = NULL;
	return (head);
}

void	print_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(", ");
		i++;
	}
	printf("\n");
}

char	*print_redir_token(out_redirs out, in_redirs in)
{
	if (out == WRITEOUT)
		return (">");
	if (out == APPENDOUT)
		return (">>");
	if (in == READIN)
		return ("<");
	if (in == HEREDOC)
		return ("<<");
	return (NULL);
}

void	print_list(t_cmd *cmd)
{
	while (cmd)
	{
		printf("argv: ");
		print_argv(cmd->cmd);
		printf("fd_in: %i\n", cmd->fd_in);
		printf("fd_out: %i\n", cmd->fd_out);
		printf("input redirections: %s\n", print_redir_token(0,
				cmd->in_redir_type));
		printf("output redirections: %s\n",
			print_redir_token(cmd->out_redir_type, 0));
		// if (cmd->in_file)
		printf("input file: %s\n", cmd->in_file);
		// if (cmd->out_file)
		printf("output file: %s\n", cmd->out_file);
		if (cmd->next)
			printf("=======================\n");
		cmd = cmd->next;
	}
}

void	sig_handler(int i)
{
	if (i == SIGINT)
	{
		printf("\n");
		rl_initialize();
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	setup_signal_handlers(void)
{
	struct sigaction	sa;

	signal(SIGINT, sig_handler);
	sa.sa_handler = sig_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void ft_free_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
	if (array)
    	free(array);
}

void    destroy_cmd(t_cmd *cmd)
{
    t_cmd    *tmp;

    while (cmd)
    {
        tmp = cmd->next;
        ft_free_array(cmd->cmd);
		if (cmd->in_file)
			free(cmd->in_file);
		if (cmd->out_file)
			free(cmd->out_file);
        free(cmd);
        cmd = tmp;
    }
}

void destroy_t_node(t_lexer *lx)
{
    t_node *tmp;
    t_node *cur;
// ft_print_lexer(&lx->head);
    cur = lx->head;
    while (cur)
    {
        tmp = cur->next;
        // if (cur->content)
        //     free(cur->content);
        free(cur);
        cur = tmp;
    }
    lx->head = NULL;
// ft_print_lexer(&lx->head);
}
int access_check(t_cmd *cmd)
{
	t_cmd *cur;

	cur = cmd;
	while (cur)
	{
		if (cur->in_redir_type == APPENDOUT || cur->in_redir_type == WRITEOUT)
		{
			if (access(cur->in_file, F_OK) == -1)
			{
				printf("minishell: %s: No such file or directory\n", cur->in_file);
				return (1);
			}
		}
		else if (cur->in_redir_type == READIN)
		{
			if (access(cur->in_file, F_OK) == -1)
			{
				printf("minishell: %s: No such file or directory\n", cur->in_file);
				return (1);
			}
		}
		cur = cur->next;
	}
	return (0);
}
int	main(int __unused ac, char __unused **av, char **envirement)
{
	char	*line;
	t_env	*env;
	t_lexer	lx;
	t_cmd	*cmd;

	cmd = NULL;
	ft_variables(&env, envirement);
	setup_signal_handlers();
	while (1)
	{
		
		ft_initialisation(&lx);
		line = readline("minishell $-> ");
		if (!line)
			return (1);
		else if (check_space(line) == 0)
			continue ;
		else
		{
			add_history(line);
			if (lexer(line, &lx, env))
				continue ;
			else
			{
				join_quotes(&lx);
				join_in_quote_and_word(&lx);
				delete_white_space(&lx);
				cmd = commands(&lx);
				if(access_check(cmd))
				{
					destroy_cmd(cmd);
					continue ;
				}
				cmd->env = env;
				char **str = lincke_list_toaraay(env);
				execution_proto(cmd, str);
				free_double(str);
				destroy_cmd(cmd);
			}
		}
		destroy_t_node(&lx);
		if (line)
			free(line);
	}
}
