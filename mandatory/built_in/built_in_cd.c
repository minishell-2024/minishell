/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:07:01 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/04 17:44:15 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	check_is_dir(t_process *process, char *path)
{
	struct stat	st;

	if (access(path, F_OK) < 0)
		return(error_occur(process->cmd[0], path, NULL, 0));
	else if (stat(path, &st) < 0)
		return(error_occur(process->cmd[0], path, NULL, 0));
	else if (S_ISDIR(st.st_mode) == 0)
		return(error_occur(process->cmd[0], path, "Not a directory", 1)); // not dir 라고 해야하나...
	else if (access(path, X_OK) < 0)
		return(error_occur(process->cmd[0], path, NULL, 0));
	return (0);
}

int	change_env(t_line *line, t_process *process, char *key, char *path)
{
	t_env	*env;
	char	*value;

	env = find_env(line, key);
	if (env)
	{
		if (!path)
			value = 0;
		else
		{
			value = ft_strdup(path);
			if (!value)
				common_error(process->cmd[0], "malloc", NULL, 0);
		}
		if (env->value)
			free(env->value);
		env->value = value;
		return (0);
	}
	else
		return (insert_env(line, key, path)); // 이부분 미완... 함수 있으면 이용할 것. // strdup 써야할듯.
}

int	change_env_pwd(t_line *line, t_process *process)
{
	char	*value;
	int		exit_code1;
	int		exit_code2;

	value = getcwd(NULL, 0);
	if (!value)
		return (error_occur("pwd", NULL, NULL, 0));
	exit_code1 = change_env(line, process, "OLDPWD", find_env_value(line, "PWD"));
	exit_code2 = change_env(line, process, "PWD", value);
	if (value)
		free(value);
	if (exit_code1 > exit_code2)
		return (exit_code1);
	else
		return (exit_code2);
}

int	execute_cd(t_line *line, t_process *process)
{
	t_env	*env;
	char	*path;
	int		error_num;

	redirect_setting(process);
	if (!process->cmd[1] || !ft_strncmp(process->cmd[1], "~", 2)) // ~ 이랑 사실상 동일 ~ 은 고민중
	{
		env = find_env(line, "HOME");
		if (!env)
			return (error_occur(process->cmd[0], NULL, "HOME not set", 1));
		path = find_env_value(line, "HOME");
		if (!path)
			return (0); // 이유는 모르겠는데, HOME="" 이면 에러x
		// else
		// 	return (change_env_pwd(line, process, path));
	}
	else
		path = process->cmd[1];
	error_num = check_is_dir(process, path);
	if (error_num)
		return (error_num);
	if (chdir(path) < 0)
		return (error_occur(process->cmd[0], path, NULL, 0));
	return (change_env_pwd(line, process));
}
