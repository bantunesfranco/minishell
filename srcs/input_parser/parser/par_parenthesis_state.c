/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_parenthesis_state.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 15:00:55 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 13:31:11 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	close_par_st(t_token *temp, t_pipeline *cur_pipe, t_token **head)
{
	t_subshell	*new_subshell;
	t_pipeline	*new_pipeline;

	close_cmd(temp, cur_pipe, head);
	cur_pipe->next_control_operator = CLOSE;
	new_pipeline = make_new_pipeline(CLOSE);
	new_subshell = make_new_subshell_struct(CLOSE);
	new_pipeline->subshell = new_subshell;
	cur_pipe->next = new_pipeline;
}

t_token	*par_st(t_token *temp, t_pipeline *cur_pipe, t_token **head)
{
	t_token	*next_token;

	if (temp->type == OPEN_PAR)
		open_par_st(temp, cur_pipe, head);
	else
		close_par_st(temp, cur_pipe, head);
	next_token = temp->next;
	remove_token(head, temp);
	return (next_token);
}
