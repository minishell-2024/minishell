/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:27:55 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 19:18:24 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static unsigned long	ft_strtol(char *str, int sign, int *check_error)
{
	unsigned long	i;
	unsigned long	ans;
	unsigned long	before;

	i = 0;
	ans = 0;
	before = 0;
	*check_error = 1;
	while (str[i] && ft_isdigit(str[i]))
	{
		check_error = 0;
		ans = ans * 10 + str[i] - '0';
		if (before > ans || (ans >= (long)9223372036854775807 && sign == 1)
			|| (ans > (long)9223372036854775807 && sign == -1))
		{
			*check_error = 1;
			return (0);
		}
		before = ans;
		i++;
	}
	return (sign * ans);
}

static int	ft_exit_atoi(const char *str, int *check_error)
{
	int	i;
	int	sign;
	int	ans;

	sign = 1;
	i = 0;
	ans = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return ((int)ft_strtol((char *)(str + i), sign, check_error));
}

int	execute_exit(t_line *line, t_process *process)
{
	int	exit_code;
	int	check_num_error;

	redirect_setting(process);
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!process->cmd[1])
		exit(0);
	check_num_error = 0;
	exit_code = ft_exit_atoi(process->cmd[1], &check_num_error);
	if (check_num_error == 1)
		common_error("exit", process->cmd[1], "numeric argument required", 255);
	if (process->cmd[2])
		return (error_occur("exit", NULL, "too many arguments", 1));
	exit((unsigned char)exit_code); // 캐스팅 잘되는지 나중에 확인해보기
}
