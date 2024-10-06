/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_setting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:17:25 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/06 13:02:51 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	make_temp_file(t_redirection *redirect)
{
	char	*dummy;
	char	*num_str;
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
		num_str = ft_itoa(num++);
		if (!num_str)
			common_error("malloc", NULL, NULL, 1);
		redirect->file_name = ft_strjoin(dummy, num_str);
		if (!redirect->file_name)
			common_error("malloc", NULL, NULL, 1);
		free(num_str);
	}
	free(dummy);
}

int	here_doc_g_signal(t_line *line, t_redirection *redirect, char **context)
{
	if (*context)
		free(*context);
	g_signal = 0;
	close(redirect->fd);
	change_exit_code(line, 1);
	ignore_signal();
	return (0);
}

int	loop_readline(t_line *line, t_redirection *redirect)
{
	char	*context;

	context = readline("> ");
	if (g_signal == 1)
		return (here_doc_g_signal(line, redirect, &context));
	if (!context)
	{
		ft_putstr_fd("\033[A\033[K", STDOUT_FILENO);
		ft_putstr_fd("> ", STDOUT_FILENO);
		return (1);
	}
	context = key_to_value(context, line);
	if (!ft_strncmp(context, redirect->here_doc_eof
			, ft_strlen(redirect->here_doc_eof) + 1)
		&& (!context[ft_strlen(redirect->here_doc_eof)]
			|| context[ft_strlen(redirect->here_doc_eof)] == '\n'))
	{
		free(context);
		return (1);
	}
	ft_putendl_fd(context, redirect->fd);
	free(context);
	return (2);
}

int	here_doc_check(t_line *line, t_redirection *redirect)
{
	int	check_val;

	redirect->fd
		= open(redirect->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirect->fd < 0)
		common_error(NULL, redirect->file_name, NULL, 1);
	while (1)
	{
		check_val = loop_readline(line, redirect);
		if (check_val == 0)
			return (0);
		else if (check_val == 1)
			break ;
	}
	close(redirect->fd);
	return (1);
}

int	heredoc_setting(t_line *line, t_process *process)
{
	t_redirection	*redirect;

	while (process)
	{
		redirect = process->redirect_node;
		while (redirect)
		{
			if (redirect->type == 1)
			{
				set_heredoc_signal();
				make_temp_file(redirect);
				if (!here_doc_check(line, redirect))
					return (0);
				ignore_signal();
			}
			redirect = redirect->redirect_next;
		}
		process = process->process_next;
	}
	ignore_signal();
	return (1);
}
