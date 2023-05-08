/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:57 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/08 12:47:06 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	PIPE,
	OR,
	AND,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	AMPERSAND,
	WHITESPACE,
	// SPACE,
	// TAB,
	NEW_LINE,
	WORD,
}	t_token_type;

// typedef enum e_control_operator
// {
// 	PIPE,
// 	OR,
// 	AND,
// 	OPEN_PAR,
// 	CLOSE_PAR
// }	t_control_operator;

typedef enum e_redirect_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_redirect_type;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_gen
{
	char	**env;
	char	*pwd;
	char	*oldpwd;
	char	**path;
	t_token	**lexer_list;
}			t_gen;

typedef struct s_redirect
{
	int					fd;
	char				*name;
	t_redirect_type		type;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_pipeline
{
	char				**cmd;
	char				*path;
	int					(*builtin)(char **, struct s_cmd *);
	struct s_redirect	*input;
	struct s_redirect	*output;
	struct s_cmd		*next;
	struct s_cmd		*prev;
	int					error_code;
	int					subshell;
}						t_pipeline;

typedef struct s_cmd_list
{
	int	error_code;
	// enum				control_operator;
	
	int					subshell;
	int					cmd_count;
	int					(*builtin)(char **, struct s_cmd *);
	struct s_cmd		*first_cmd; // pipeline
	struct s_redirect	*input;
	struct s_redirect	*output;
	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;
}	t_cmd_list;

#endif
