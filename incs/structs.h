
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

typedef enum e_control_operator
{
	PIPELINE,
	AND,
	OR
}	t_control_operator;

typedef enum e_redirect_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_redirect_type;

typedef struct s_gen
{
	char	**env;
	char	*pwd;
	char	*oldpwd;
	char	**path;
}			t_gen;

typedef struct s_redirect
{
	int					fd;
	char				*name;
	t_redirect_type		type;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_subshell
{
	int					pipe; // this is a identifier to know if we need to get inpiut from a pipe
	struct s_cmd_list	*subshell_cmd_list; // this is a pointer to a t_cmd_list that contains the next couple pipeline
	struct s_redirect	*input; // this is a pointer to a list of redirects that redirect the whole input or output of the subshell
	struct s_redirect	*output; // this is a pointer to a list of redirects that redirect the whole input or output of the subshell
}	t_subshell;

typedef struct s_pipeline
{
	char				**cmd;
	char				*path;
	int					(*builtin)(char **, struct s_pipeline *);
	int					cmd_count;
	struct s_redirect	*input;
	struct s_redirect	*output;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_pipeline;

typedef struct s_cmd_list
{
	int					error_code; // this is the error code of our current pipeline, might be unnesecary if we have it in the geeral struct
	t_control_operator	next_control_operator; // This is the control operator after the pipeline or after the subshell
	t_control_operator	prev_control_operator; // This is the control operator before the pipeline or before the subshell
	t_subshell			*subshell; // This exist if we want to fork
	t_pipeline			*first_cmd; // This is NULL if there is a subshell
	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;
}	t_cmd_list;

#endif
