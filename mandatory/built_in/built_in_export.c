/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:12:03 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/05 15:52:58 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	sort_export_by_key(t_line *return_line)
{
	t_env		*temp;
	t_env		*dummy;

	temp = return_line->env;
	while (temp)
	{
		dummy = temp->env_next;
		while (dummy)
		{
			if (ft_strncmp(temp->key, dummy->key, ft_strlen(temp->key) + 1) > 0)
				swap_env(temp, dummy);
			dummy = dummy->env_next;
		}
		temp = temp->env_next;
	}
}

static t_env	*sort_export(t_line *line)
{
	t_line	*return_line;
	t_env	*env;

	return_line = (t_line *)ft_calloc(sizeof(t_line), 1);
	if (!return_line)
		return (0);
	env = line->env;
	while (env)
	{
		insert_env(return_line, env->key, env->value);
		env = env->env_next;
	}
	sort_export_by_key(return_line);
	env = return_line->env;
	free(return_line);
	return (env);
}

static int	print_env_with_quote(t_line *line)
{
	t_env	*head;
	t_env	*env;

	head = sort_export(line);
	while (head)
	{
		if (ft_strncmp(head->key, "?", 2) != 0 && ft_strncmp(head->key, "_", 2) != 0)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			if (!head->value) // 파싱부에서 a="" 와 a의 차이를 head->value를 null이나 "" -> malloc(0)이냐로 구분해줘야 할듯?
				ft_putendl_fd(head->key, STDOUT_FILENO);
			else
			{
				ft_putstr_fd(head->key, STDOUT_FILENO);
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(head->value, STDOUT_FILENO);
				ft_putendl_fd("\"", STDOUT_FILENO);
			}
		}
		env = head;
		head = head->env_next;
		free_env(env);
	}
	return (0);
}

int	check_insert_env(t_line *line, char *key, char *value)
{
	t_env	*env;
	char	*replace_value;

	replace_value = value;
	env = find_env(line, key);
	if (env)
	{
		if (value)
		{
			replace_value = ft_strdup(value);
			if (!replace_value)
				common_error("malloc", NULL, NULL, 1);
			if (env->value)
				free(env->value);
			env->value = replace_value;
		}
		return (0);
	}
	else
		return (!insert_env(line, key, value));
}

int	execute_export(t_line *line, t_process *process)
{
	int		i;
	int		val;
	int		return_val;
	t_env	*env;

	i = 0;
	val = 0;
	return_val = 0;
	if (!process->cmd[1])
		return (print_env_with_quote(line));
	while (process->cmd[++i])
	{
		env = divide_env_key_value(process->cmd[i]); // 파싱부에서 env나눠주는거 써야할듯?
		if (!env)
			common_error("export", "malloc", NULL, 1);
		else if (!is_identifier(env->key))
			val = error_occur("export", NULL, "not a valid identifier", 1);
		else
			val = check_insert_env(line, env->key, env->value); // return 여부 생각해보기
		free_env(env); // insert_env_by_str에서 strdup한다고 가정
		if (return_val < val)
			return_val = val;
	}
	return (return_val);
}
