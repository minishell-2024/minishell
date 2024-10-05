/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:51:51 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 17:22:30 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	redirect_input(t_redirection *redirect, int is_built_in)
{
	if (is_built_in)
	{
		redirect->fd = open(redirect->file_name, O_RDONLY);
		if (redirect->fd < 0)
			return (error_occur(NULL, redirect->file_name, NULL, 1));
		if (dup2(redirect->fd, STDIN_FILENO) < 0)
			return (error_occur(NULL, "dup2", NULL, 0));
		close(redirect->fd);
		return (0);
	}
	redirect->fd = open(redirect->file_name, O_RDONLY);
	if (redirect->fd < 0)
		common_error(NULL, redirect->file_name, NULL, 1);
	if (dup2(redirect->fd, STDIN_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(redirect->fd);
	return (0);
}

int	redirect_heredoc(t_redirection *redirect, int is_built_in)
{
	if (is_built_in)
	{
		redirect->fd = open(redirect->file_name, O_RDONLY);
		if (redirect->fd < 0)
			return (error_occur(NULL, redirect->file_name, NULL, 1));
		if (dup2(redirect->fd, STDIN_FILENO) < 0)
			return (error_occur(NULL, "dup2", NULL, 0));
		close(redirect->fd);
		if (unlink(redirect->file_name) < 0)
			return (error_occur(NULL, redirect->file_name, NULL, 0));
		return (0);
	}
	redirect->fd = open(redirect->file_name, O_RDONLY);
	if (redirect->fd < 0)
		common_error(NULL, redirect->file_name, NULL, 1);
	if (dup2(redirect->fd, STDIN_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(redirect->fd);
	if (unlink(redirect->file_name) < 0)
		common_error(NULL, redirect->file_name, NULL, 0);
	return (0);
}

int	redirect_append(t_redirection *redirect, int is_built_in)
{
	if (is_built_in)
	{
		redirect->fd =  open(redirect->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (redirect->fd < 0)
			return (error_occur(NULL, redirect->file_name, NULL, 1));
		if (dup2(redirect->fd, STDOUT_FILENO) < 0)
			return (error_occur(NULL, "dup2", NULL, 0));
		close(redirect->fd);
		return (0);
	}
	redirect->fd =  open(redirect->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redirect->fd < 0)
		common_error(NULL, redirect->file_name, NULL, 1);
	if (dup2(redirect->fd, STDOUT_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(redirect->fd);
	return (0);
}

int	redirect_output(t_redirection *redirect, int is_built_in)
{
	if (is_built_in)
	{
		redirect->fd = open(redirect->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (redirect->fd < 0)
			return (error_occur(NULL, redirect->file_name, NULL, 1));
		if (dup2(redirect->fd, STDOUT_FILENO) < 0)
			return (error_occur(NULL, "dup2", NULL, 0));
		close(redirect->fd);
		return (0);
	}
	redirect->fd = open(redirect->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirect->fd < 0)
		common_error(NULL, redirect->file_name, NULL, 1);
	if (dup2(redirect->fd, STDOUT_FILENO) < 0)
		common_error(NULL, "dup2", NULL, 0);
	close(redirect->fd);
	return (0);
}

int	redirect_setting(t_process *process, int is_built_in)
{
	t_redirection	*redirect;
	int				return_val;

	redirect = process->redirect_node;
	return_val = 0;
	while(redirect)
	{
		if (redirect->type == 0) // <
			return_val = redirect_input(redirect, is_built_in);
		else if (redirect->type == 1) // <<
			return_val = redirect_heredoc(redirect, is_built_in);
		else if (redirect->type == 2) // >
			return_val = redirect_output(redirect, is_built_in);
		else if (redirect->type == 3) // >>
			return_val = redirect_append(redirect, is_built_in);
		if (return_val)
			return (return_val);
		redirect = redirect->redirect_next;
	}
	return (0);
}
