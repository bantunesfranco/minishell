/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:57 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/02 12:45:52 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token_type
{
	PIPE,
	WORD,
	GREAT,
	LESS,
	AMPERSAND,
	// GREAT_GREAT,
	// LESS_LESS
}	t_token_type;

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

typedef struct s_cmd
{
	char				**cmd;
	char				*path;
	int					(*builtin)(char **, struct s_cmd *);
	struct s_redirect	*input;
	struct s_redirect	*output;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

#endif
