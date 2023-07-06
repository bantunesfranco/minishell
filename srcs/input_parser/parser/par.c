/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 15:21:06 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/06 10:07:42 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*word_state(t_token *temp, t_pipeline *cur_pipe, t_token **head)
{
	(void)temp;
	(void)head;
	(void)cur_pipe;
	return (temp->next);
}

t_token	*call_state(t_token *temp, t_pipeline *first_pipeline, t_token **head)
{
	t_curr_st_function	next_state[5];
	t_pipeline			*cur_pipe;

	next_state[0] = ctrl_op_st;
	next_state[1] = par_st;
	next_state[2] = red_st;
	next_state[3] = end_state;
	next_state[4] = word_state;
	cur_pipe = find_last_pipeline(first_pipeline);
	return (next_state[temp->token_group](temp, cur_pipe, head));
}

static void	setup_starting_point(t_pipeline **first_pipeline)
{
	t_pipeline	*first_node;

	first_node = make_new_pipeline(START);
	*first_pipeline = first_node;
}

void	parser(t_token **head, t_pipeline **first_pipeline)
{
	t_token	*temp;

	temp = *head;
	setup_starting_point(first_pipeline);
	while (temp != NULL)
		temp = call_state(temp, *first_pipeline, head);
}
