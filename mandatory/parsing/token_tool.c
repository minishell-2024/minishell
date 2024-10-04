/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:07:37 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/04 11:27:24 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_pipe(void)
{
	char	*pipe;

	pipe = ft_strdup("|");
	if (!pipe)
		common_error("malloc", 0, 0, 0);
	return (pipe);
}

char	*reset_buf(int *sq_flag)
{
	char	*new_buf;

	*sq_flag = 0;
	new_buf = ft_strdup("");
	if (!new_buf)
		common_error("malloc", 0, 0, 0);
	return (new_buf);
}
