/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slazar <slazar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:23:17 by yberrim           #+#    #+#             */
/*   Updated: 2023/10/07 11:47:49 by slazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_redirections(t_cmd *cmd)
{
	if (cmd->out_redir_type == WRITEOUT)
		cmd->fd_out = open(cmd->out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->out_redir_type == APPENDOUT)
		cmd->fd_out = open(cmd->out_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (cmd->in_redir_type == READIN || cmd->in_redir_type == HEREDOC)
		cmd->fd_in = open(cmd->in_file, O_RDONLY);
}
