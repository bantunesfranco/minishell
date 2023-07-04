/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_end_state.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 18:45:25 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/04 09:41:26 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

t_token	*end_state(t_token *temp, t_pipeline *curr_pipeline, t_token **head)
{
	close_simple_cmd(temp, curr_pipeline, head);
	curr_pipeline->next_control_operator = END;
	free(temp->word);
	free(temp);
	*head = NULL;
	return (NULL);
}
