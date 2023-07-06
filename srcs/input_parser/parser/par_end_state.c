/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_end_state.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 18:45:25 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 13:26:59 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*end_state(t_token *temp, t_pipeline *cur_pipe, t_token **head)
{
	close_cmd(temp, cur_pipe, head);
	cur_pipe->next_control_operator = END;
	free(temp->word);
	free(temp);
	*head = NULL;
	return (NULL);
}
