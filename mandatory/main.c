/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:11:41 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 13:11:16 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	char	*str;

	line = (t_line *)malloc(sizeof(t_line));
	ft_bzero(line, sizeof(t_line));
	line->argc = argc;
	line->argv = argv;
	line->envp = envp;
	while (1)
	{
		str = readline("minishell$ ");
		add_history(str);
		parse(str, line);
		// printf("%s\n", str);
		// parse_input
		//
		// t_env *e_ptr = line->env;
		// while (e_ptr)
		// {
		// 	printf("%s=%s\n", e_ptr->key, e_ptr->value);
		// 	e_ptr = e_ptr->env_next;
		// }
		t_process	*p = line->proc;
		char **cmd;
		t_redirection *r_ptr;
		while (p){
			cmd = p->cmd;
			// printf("user input : %s\n", str);
			while (*cmd)
			{
				printf("%s", *cmd);
				printf(" ");
				cmd++;
			}
			r_ptr = p->redirect_node;
			while (r_ptr)
			{
				if (r_ptr->type == REDIR_INPUT)
					printf("< %s ", r_ptr->file_name);
				if (r_ptr->type == REDIR_DELIMIT)
					printf("<< %s ", r_ptr->here_doc_eof);
				if (r_ptr->type == REDIR_OUTPUT)
					printf("> %s ", r_ptr->file_name);
				if (r_ptr->type == REDIR_APPEND)
					printf(">> %s ", r_ptr->file_name);
				r_ptr = r_ptr->redirect_next;
			}
			if (p->process_next)
				printf("| ");
			p = p->process_next;
		}
		printf("\n");
		free(str);
	}
}
