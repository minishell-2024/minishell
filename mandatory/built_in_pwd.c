/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:53:22 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/21 20:30:58 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type.h"
#include "minishell.h"

int	execute_pwd(t_process *process)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (error_occur("pwd", NULL, NULL, 0));
	ft_putendl_fd(path, STDIN_FILENO);
	free(path);
	return (0);
}
