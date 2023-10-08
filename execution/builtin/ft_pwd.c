/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yberrim <yberrim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:33:51 by yberrim           #+#    #+#             */
/*   Updated: 2023/09/21 17:12:40 by yberrim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../minishell.h"

int	ft_pwd(int fd_out)
{
	char	current_dir[100];

	if (getcwd(current_dir, 100))
	{
		ft_putstr_fd(current_dir, fd_out);
		write(fd_out, "\n", 1);
		return (1);
	}
	ft_putstr_fd(current_dir, fd_out);
	write(fd_out, "\n", 1);
	return (0);
}
