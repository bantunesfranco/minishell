/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeline_list_functions.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 10:25:22 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/04 09:04:44 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minishell.h"

t_pipeline	*make_new_pipeline(t_control_operator type)
{
	t_pipeline	*new_node;

	new_node = malloc(sizeof(t_pipeline));
	if (new_node == NULL)
		err_msg(NULL, "parser");
	new_node->next_control_operator = 0;
	new_node->prev_control_operator = type;
	new_node->subshell = NULL;
	new_node->first_cmd = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
