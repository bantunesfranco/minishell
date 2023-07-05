/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:57 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 17:33:14 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_control_operator
{
	OR,
	PIPELINE,
	AND,
	OPEN,
	CLOSE,
	START,
	END
}	t_control_operator;

typedef enum e_redirect_type
{
	HEREDOC,
	INPUT,
	APPEND,
	OUTPUT,
	NONE
}	t_redirect_type;

typedef struct s_gen
{
	char	**env;
	char	**path;
	int		status;
}			t_gen;

typedef struct s_redirect
{
	int					fd;
	char				*name;
	char				*str;
	t_redirect_type		type;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_subshell
{
	t_control_operator	open_close;
	int					pipe_input;
	int					pipe_output;
	struct s_redirect	*input;
	struct s_redirect	*output;
}						t_subshell;

typedef struct s_cmd
{
	char				**cmd;
	char				*path;
	int					(*builtin)(t_gen *, struct s_cmd *);
	struct s_redirect	*input;
	struct s_redirect	*output;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_pipeline
{
	int					error_code;
	t_control_operator	next_control_operator;
	t_control_operator	prev_control_operator;
	t_subshell			*subshell;
	t_cmd				*first_cmd; 
	struct s_pipeline	*next;
	struct s_pipeline	*prev;
}						t_pipeline;

#endif
