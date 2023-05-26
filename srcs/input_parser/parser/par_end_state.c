/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_end_state.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 18:45:25 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/26 19:37:13 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	remove_tokens(t_token *temp, t_token **first_token)
{
	t_token	*temp2;

	temp2 = *first_token;
	while (temp2 != temp)
	{
		temp2 = temp2->next;
		remove_token(first_token, temp2->prev);
	}
	remove_token(first_token, temp);
}

t_token	*end_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	t_token	*next_token;

	close_simple_cmd(temp, curr_pipeline, *first_token);
	// print_array(curr_pipeline->first_cmd->cmd);
	next_token = temp->next;
	// free_token_list(*first_token);
	remove_tokens(temp, first_token);
	return (NULL);
}