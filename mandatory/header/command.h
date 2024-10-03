/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:12:52 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/03 14:52:13 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H


//==================== main.c ====================

//==================== process_utiles.c ====================
void	change_exit_code(t_line *line, int return_val);
void    re_init_setting(t_line *line);
void    init_setting(t_line *line);
void	wait_process(t_line *line);

//==================== command_execute.c ====================
void	execute_command(char *path, char **cmd, t_env *env);
void	check_execute(t_line *line, t_process *process);
char	**parse_path(t_env *env, int unset_path);
void	check_command(t_line *line, t_process *process);

//==================== env_utiles.c ====================
t_env	*find_env(t_line *line, char *key);
char	*find_env_value(t_line *line, char *key);
void	swap_env(t_env *env1, t_env *env2); // key, value만 swap
void	free_env(t_env *env);
int     delete_env(t_line *line, char *key);

//==================== error_control.c ====================
void	common_error(char *cmd, char *file_name, char *custom_msg, int error_code);
void	command_error(char *str);
int		error_occur(char *cmd, char *file_name, char *custom_msg, int error_code);

//==================== heredoc_setting.c ====================
void	heredoc_setting(t_process *process);
void	here_doc_check(t_redirection *redirect);
void	make_temp_file(t_redirection *redirect);

//==================== pipex.c ====================
void	pipex(t_line *line, t_process *process);
int     check_built_in(t_line *line, t_process *process);


//==================== redirect.c ====================
void	redirect_setting(t_process *process);
void	redirect_output(t_redirection *redirect);
void	redirect_append(t_redirection *redirect);
void	redirect_heredoc(t_redirection *redirect);
void	redirect_input(t_redirection *redirect);

//==================== signal.c ====================
void    print_empty_line_move_next(int sign);
void    set_normal_signal();
void    ignore_signal();
void	set_origin_signal(void);

//==================== signal_heredoc.c ====================
void    print_empty_line(int sign);
void    do_heredoc_sigint(int sign);
void    set_heredoc_signal();

//==================== split_path.c ====================
char	**split_path(char const *s, char c);
void	free_all(char **ans, char index);
// built_in
//==================== built_in_cd.c ====================
int     execute_cd(t_line *line, t_process *process);
int     change_env_pwd(t_line *line, t_process *process);
int     change_env(t_line *line, t_process *process, char *key, char *path);
int     check_is_dir(t_process *process, char *path);

//==================== built_in_echo.c ====================
int     execute_echo(t_process *process);

//==================== built_in_exit.c ====================
int     execute_exit(t_process *process);

//==================== built_in_export.c ====================
int     execute_export(t_line *line, t_process *process);
t_env	*divide_env_key_value(char *str); // 미완

//==================== built_in_pwd.c ====================
int     execute_pwd(t_process *process);

//==================== built_in_unset.c ====================
int     execute_unset(t_line *line, t_process *process);

//==================== built_in_utiles.c ====================
int     env_len(t_line *line);
int     is_identifier(char *str);

//==================== built_in_env.c ====================
int     execute_env(t_line *line, t_process *process);

#endif
