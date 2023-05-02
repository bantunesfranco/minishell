/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:57 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/04/24 13:05:34 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// struct s_gen
// {
// 	pwd;
// 	oldpwd;
// 	env;
	
// };


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
