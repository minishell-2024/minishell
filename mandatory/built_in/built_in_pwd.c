/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 19:53:22 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/02 19:18:24 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	execute_pwd(t_process *process)
{
	char	*path;

	redirect_setting(process);
	path = getcwd(NULL, 0);
	if (!path)
		return (error_occur("pwd", NULL, NULL, 0));
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	return (0);
}
