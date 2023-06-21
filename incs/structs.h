
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:57 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/26 21:19:54 by bfranco       ########   odam.nl         */
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
	int					pipe_input; // this is a identifier to know if we need to get inpiut from a pipe
	int					pipe_output; // this is a identifier to know if the output needs to go into a pipe
	struct s_redirect	*input; // this is a pointer to a list of redirects that redirect the whole input or output of the subshell
	struct s_redirect	*output; // this is a pointer to a list of redirects that redirect the whole input or output of the subshell
}						t_subshell;

typedef struct s_cmd
{
	char				**cmd;
	char				*path;
	int					(*builtin)(t_gen *, struct s_cmd *);
	int					cmd_count;
	struct s_redirect	*input;
	struct s_redirect	*output;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

typedef struct s_pipeline
{
	int					error_code; // this is the error code of our current pipeline, might be unnesecary if we have it in the geeral struct
	t_control_operator	next_control_operator; // This is the control operator after the pipeline or after the subshell
	t_control_operator	prev_control_operator; // This is the control operator before the pipeline or before the subshell
	t_subshell			*subshell; // This exist if we want to fork
	t_cmd				*first_cmd; // This is NULL if there is a subshell
	struct s_pipeline	*next;
	struct s_pipeline	*prev;
}						t_pipeline;

#endif
