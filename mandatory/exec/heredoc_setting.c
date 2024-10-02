/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_setting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:17:25 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 21:09:07 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	make_temp_file(t_redirection *redirect)
{
	char	*dummy;
	int		num;
	dummy = (char *)ft_calloc(10, 1);
	if (!dummy)
		common_error("malloc", NULL, NULL, 1);
	ft_strlcpy(dummy, "/tmp/temp", 10);
	redirect->file_name = ft_strdup(dummy);
	if (!redirect->file_name)
		common_error("malloc", NULL, NULL, 1);
	num = 0;
	while (access(redirect->file_name, F_OK) == 0)
	{
		free(redirect->file_name);
		redirect->file_name = ft_strjoin(dummy, ft_itoa(num++));
		if (!redirect->file_name)
			common_error("malloc", NULL, NULL, 1);
	}
	free(dummy);
}

void	here_doc_check(t_redirection *redirect)
{
	// char	*temp_filename;
	char	*context;

	redirect->fd = open(redirect->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirect->fd < 0)
		common_error(NULL, redirect->file_name, NULL, 1);
	context = get_next_line(0);
	while (context)
	{
		if (!ft_strncmp(context, redirect->here_doc_eof, ft_strlen(redirect->here_doc_eof) + 1)
			&& (!context[ft_strlen(redirect->here_doc_eof)]
				|| context[ft_strlen(redirect->here_doc_eof)] == '\n'))
		{
			free(context);
			break ;
		}
		ft_putstr_fd(context, redirect->fd);
		free(context);
		context = get_next_line(0);
	}
	close(redirect->fd);
}

void	heredoc_setting(t_process *process)
{
	t_redirection	*redirect;

	redirect = process->redirect_node;
	while (redirect)
	{
		if (redirect->type == 1) // <<
		{
			make_temp_file(redirect);
			here_doc_check(redirect);
		}
		redirect = redirect->redirect_next;
	}
}
