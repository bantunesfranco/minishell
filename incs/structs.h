/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:57 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/04/20 12:40:51 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef	

typedef struct s_redirect
{
	int	input_or_utput;;
	char	*name;
	struct s_redirect	next;
}	t_redirect;

typedef struct s_cmd
{
	char				**cmd;
	char				*path;
	func				*built_in;
	struct s_redirect	*input;
	struct s_redirect	*output;
	struct s_cmd		*next;
	struct s_cmd		*prev;
}						t_cmd;

#endif
