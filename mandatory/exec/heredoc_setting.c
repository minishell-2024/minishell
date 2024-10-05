/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_setting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:17:25 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 06:42:31 by yuyu             ###   ########.fr       */
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

// void	here_doc_check(t_redirection *redirect)
// {
// 	// char	*temp_filename; // readline 으로 수정 필요
// 	char	*context;

// 	redirect->fd = open(redirect->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (redirect->fd < 0)
// 		common_error(NULL, redirect->file_name, NULL, 1);
// 	context = get_next_line(0);
// 	while (context)
// 	{
// 		if (!ft_strncmp(context, redirect->here_doc_eof, ft_strlen(redirect->here_doc_eof) + 1)
// 			&& (!context[ft_strlen(redirect->here_doc_eof)]
// 				|| context[ft_strlen(redirect->here_doc_eof)] == '\n'))
// 		{
// 			free(context);
// 			break ;
// 		}
// 		ft_putstr_fd(context, redirect->fd);
// 		free(context);
// 		context = get_next_line(0);
// 	}
// 	close(redirect->fd);
// }

int	here_doc_check(t_line *line, t_redirection *redirect)
{
	char	*context;

	redirect->fd = open(redirect->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirect->fd < 0)
		common_error(NULL, redirect->file_name, NULL, 1);
	while (1)
	{
		context = readline("> ");
		ft_putstr_fd("escape??", 1);
		if (g_signal == 1)
		{
			if (context)  // 이미 할당된 메모리가 있으면 해제
                free(context);
            close(redirect->fd);
            g_signal = 0;
            rl_done = 0;
			change_exit_code(line, 1);
			return (0);
		}
		if (!context)
		{
			ft_putstr_fd("\033[A\033[K", STDOUT_FILENO);
			ft_putstr_fd("> ", STDOUT_FILENO);
			break ;
		}
		context = key_to_value(context, line);
		if (!ft_strncmp(context, redirect->here_doc_eof, ft_strlen(redirect->here_doc_eof) + 1)
			&& (!context[ft_strlen(redirect->here_doc_eof)]
				|| context[ft_strlen(redirect->here_doc_eof)] == '\n'))
		{
			free(context);
			break ;
		}
		ft_putendl_fd(context, redirect->fd);
		free(context);
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
			if (redirect->type == 1) // <<
			{
				set_heredoc_signal();
				make_temp_file(redirect);
				if (!here_doc_check(line, redirect)) // ctrl + c
					return (0);
				ignore_signal(); // 굳이 싶기는 함.
			}
			redirect = redirect->redirect_next;
		}
		process = process->process_next;
	}
	ignore_signal();
	return (1);
}
