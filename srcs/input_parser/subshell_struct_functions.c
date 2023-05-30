/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subshell_struct_functions.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:23:27 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/29 18:22:13 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

t_subshell	*make_new_subshell_struct(t_control_operator type)
{
	t_subshell	*new;

	new = malloc(sizeof(t_subshell));
	if (new == NULL)
		err_msg(NULL, "parser");
	new->pipe_input = 0;
	new->pipe_output = 0;
	new->open_close = type;
	new->input = NULL;
	new->output = NULL;
	return (new);
}
