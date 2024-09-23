/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 03:35:38 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/09/23 16:16:36 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

typedef enum e_state
{
	STATE_GENERAL,
	STATE_SQUOTE,
	STATE_DQUOTE,
}	t_state;
typedef enum e_tokentype
{
	TOKEN_END,
	TOKEN_COMMAND,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_STRING,
	TOKEN_PIPE,
	TOKEN_INPUT,
	TOKEN_OUTPUT,
	TOKEN_DELIMIT,
	TOKEN_APPEND
}	t_tokentype;

typedef enum e_nodetype
{
	NODE_COMMAND,
	NODE_SIMPLE_CMD,
	NODE_REDIRECT,
	NODE_PIPE
}	t_nodetype;

typedef struct s_token
{
	char			*word;
	t_tokentype		token_type;
	struct s_token	*next;
}	t_token;

typedef struct s_simple_cmd
{
	char				*argv;
	struct s_simple_cmd	*next_simple_cmd;
}	t_simple_cmd;

typedef struct s_redirect
{
	t_tokentype			type;
	char				*argv;
	struct s_redirect	*next_redir;
}	t_redirect;

typedef struct s_command
{
	t_simple_cmd	*simple_cmd;
	t_redirect		*redirect;
}	t_command;

typedef struct s_ast_node
{
	t_nodetype			type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	void				*data;
}	t_ast_node;

#endif