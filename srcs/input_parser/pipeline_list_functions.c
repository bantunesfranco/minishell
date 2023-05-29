/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeline_list_functions.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 10:25:22 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/29 08:14:50 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

t_pipeline	*make_new_pipeline(t_control_operator type)
{
	t_pipeline	*new_node;

	new_node = malloc(sizeof(t_pipeline));
	if (new_node == NULL)
		return (NULL);
	new_node->next_control_operator = 0;
	new_node->prev_control_operator = type;
	new_node->subshell = NULL;
	new_node->first_cmd = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_pipeline_back(t_pipeline **head, t_pipeline *new_pipeline)
{
	t_pipeline	*temp;

	temp = *head;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_pipeline;
	}
	else
		*head = new_pipeline;
}
