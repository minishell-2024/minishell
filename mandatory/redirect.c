/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:51:51 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/29 13:15:02 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type.h"
#include "minishell.h"

void	redirect_input(t_redirection *redirect)
{
	redirect->fd = open(redirect->file_name, O_RDONLY);
	if (redirect->fd < 0)
		common_error(NULL, redirect->file_name, NULL, 0);
	// if (access(redirect->file_name, R_OK) < 0)
	// 	common_error(NULL, redirect->file_name, NULL, 0);
	if (dup2(redirect->fd, STDIN_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(redirect->fd);
}

void	redirect_heredoc(t_redirection *redirect)
{
	redirect->fd = open(redirect->file_name, O_RDONLY);
	if (redirect->fd < 0)
		common_error(NULL, redirect->file_name, NULL, 0);
	// if (access(redirect->file_name, R_OK) < 0)
	// 	common_error(NULL, redirect->file_name, NULL, 0);
	if (dup2(redirect->fd, STDIN_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(redirect->fd);
	// 이거 나중에 free 할 때 하는게 편할려나..
	if (unlink(redirect->file_name) < 0)
		common_error(NULL, redirect->file_name, NULL, 0);
}

void	redirect_append(t_redirection *redirect)
{
	redirect->fd =  open(redirect->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redirect->fd < 0)
		common_error(NULL, redirect->file_name, NULL, 0);
	// if (access(redirect->file_name, W_OK) < 0)
	// 	common_error(NULL, redirect->file_name, NULL, 0);
	if (dup2(redirect->fd, STDOUT_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(redirect->fd);
}

void	redirect_output(t_redirection *redirect)
{
	redirect->fd = open(redirect->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirect->fd < 0)
		common_error(NULL, redirect->file_name, NULL, 0);
	// if (access(redirect->file_name, W_OK) < 0)
	// 	common_error(NULL, redirect->file_name, NULL, 0);
	if (dup2(redirect->fd, STDOUT_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(redirect->fd);
}

void	redirect_setting(t_process *process)
{
	t_redirection	*redirect;

	redirect = process->redirect_node;
	while(redirect)
	{
		if (redirect->type == 0) // <
			redirect_input(redirect);
		else if (redirect->type == 1) // <<
			redirect_heredoc(redirect);
		else if (redirect->type == 2) // >
			redirect_output(redirect);
		else if (redirect->type == 3) // >>
			redirect_append(redirect);
		redirect = redirect->redirect_next;
	}
	return ;
}
