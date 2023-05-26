/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   subshell_struct_functions.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:23:27 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/25 12:25:27 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

t_subshell	*make_new_subshell_struct(void)
{
	t_subshell	*new;

	new = malloc(sizeof(t_subshell));
	if (new == NULL)
		return (NULL);
	new->pipe_input = 0;
	new->pipe_output = 0;
	new->input = NULL;
	new->output = NULL;
}
