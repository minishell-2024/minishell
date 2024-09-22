/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 03:35:38 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/22 04:46:49 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef	enum e_tokentype
{
	TOKEN_END,
	TOKEN_COMMAND,
	TOKEN_OPTION,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_STRING,
	TOKEN_PIPE,
	TOKEN_INPUT,
	TOKEN_OUTPUT,
	TOKEN_DELIMIT,
	TOKEN_APPEND
}	t_tokentype;

typedef struct s_token
{
	char			*word;
	t_tokentype		token_type;
	struct s_token	*next;
}	t_token;

typedef struct s_suffix
{
	char	*body;
	struct s_suffix	*next;
}	t_suffix;

typedef struct s_simple_cmd
{
	char	*cmd;
	char	*option;
	t_suffix	*suffix;
}	t_simple_cmd;

typedef struct s_redirect
{
	t_tokentype	type;
	t_suffix	*suffix;
	struct s_redirect	*redir;
}	t_redirect;

typedef struct s_command
{
	t_simple_cmd	*simple_cmd;
	t_redirect	*redirect;
	char	**argv;
}	t_command;

typedef struct s_pipeline
{
	t_command	*cmd;
	struct s_pipeline	*pipe;
}	t_pipeline;