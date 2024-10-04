/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:11:41 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/04 18:15:28 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	char	*str;

	// 초기 parse
	// $?를 env에 추가...
	line = (t_line *)ft_calloc(sizeof(t_line), 1);
	if (!line)
		common_error("malloc", NULL, NULL, 1);
	init_env(line, envp);
	line->argc = argc;
	line->argv = argv;
	init_setting(line); // 기존 표준 입출력 복사.
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			ft_putendl_fd("exit", STDIN_FILENO);
			exit(0);
		}
		add_history(str);
		parse_main(str, line);
		pipex(line, line->proc);
		if (line->proc)
			wait_process(line);
		//  printf("%s\n", str);
		//  t_env *e_ptr = line->env;
		//  while (e_ptr)
		//  {
		//  	printf("%s=%s\n", e_ptr->key, e_ptr->value);
		//  	e_ptr = e_ptr->env_next;
		//  }
		t_process	*p = line->proc;
		char **cmd;
		// t_redirection *r_ptr;
		while (p){
			cmd = p->cmd;
			if (!cmd)
				ft_putendl_fd("no command", 1);
			int index = -1;
			while (cmd[++index])
			{
				ft_putendl_fd(cmd[index], 1);
				printf("%d : %d\n", index, ft_strlen(cmd[index]));
			}
			p = p->process_next;
		}
			// printf("user input : %s\n", str);
			// while (*cmd)
			// {
			// 	printf("%s", *cmd);
			// 	printf(" ");
			// 	cmd++;
			// }
			// printf("\nredir\n");
			// r_ptr = p->redirect_node;
			// while (r_ptr)
			// {
			// 	if (r_ptr->type == REDIR_INPUT)
			// 		printf("< %s ", r_ptr->file_name);
			// 	if (r_ptr->type == REDIR_DELIMIT)
			// 		printf("<< %s ", r_ptr->here_doc_eof);
			// 	if (r_ptr->type == REDIR_OUTPUT)
			// 		printf("> %s ", r_ptr->file_name);
			// 	if (r_ptr->type == REDIR_APPEND)
			// 		printf(">> %s ", r_ptr->file_name);
			// 	r_ptr = r_ptr->redirect_next;
			// }
			// if (p->process_next)
			// 	printf("| ");
		// 	p = p->process_next;
		// }
		// printf("\n");
		free(str);
		// system("leaks minishell");
		line->proc = 0;
		re_init_setting(line);
	}
	rl_clear_history();
	exit(errno);
}
