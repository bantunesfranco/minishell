/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:57 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/04/21 15:10:53 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_token
{
	PIPE,
	GREAT,
	LESS,
	GREAT_GREAT,
	LESS_LESS,
}	t_token;

typedef struct s_lexer
{
	char			*word;
	t_token			token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_gen
{
	char	**env;
	char	*pwd;
	char	*oldpwd;
	char	**path;
	t_lexer	**lexer_list;
}	t_gen;


typedef struct s_redirect
{
	int					fd;
	char				*name;
	struct s_redirect	*next;
}	t_redirect;

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
