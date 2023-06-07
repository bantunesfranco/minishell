/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_end_state.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 18:45:25 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/06 10:21:10 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

t_token	*end_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	close_simple_cmd(temp, curr_pipeline, first_token);
	curr_pipeline->next_control_operator = END;
	free(temp->word);
	free(temp);
	*first_token = NULL;
	return (NULL);
}
