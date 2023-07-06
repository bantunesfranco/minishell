/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_parenthesis_state.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 13:21:05 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 13:40:00 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*skip_to_close_parenthesis(t_token *open_par)
{
	t_token	*temp;
	int		currently_open;

	currently_open = 1;
	temp = open_par;
	while (currently_open > 0)
	{
		temp = temp->next;
		if (temp->type == OPEN_PAR)
			currently_open++;
		else if (temp->type == CLOSE_PAR)
			currently_open--;
	}
	return (temp);
}

t_token	*add_redir(t_subshell *new_subshell, t_token *temp, t_token **head)
{
	t_redirect	*new_redirect;
	t_token		*next_token;

	new_redirect = make_new_redirect_node(temp->next->word, temp->type - 5, -1);
	new_redirect->str = temp->str;
	if (new_redirect->type == HEREDOC || new_redirect->type == INPUT)
		add_redirect_back(&(new_subshell->input), new_redirect);
	else
		add_redirect_back(&(new_subshell->output), new_redirect);
	next_token = temp->next->next;
	remove_token(head, temp->next);
	remove_token(head, temp);
	return (next_token);
}

void	handle_subshell_redir(t_subshell *new_subshell, \
								t_token *open_par, t_token **head)
{
	t_token	*temp;

	temp = skip_to_close_parenthesis(open_par);
	temp = temp->next;
	while (1)
	{
		if (temp->token_group == REDIRECTION)
			temp = add_redir(new_subshell, temp, head);
		else
		{
			if (temp->type == PIPE)
				new_subshell->pipe_output = 1;
			break ;
		}
	}
}

static void	add_standard_in_out_nodes(t_subshell *new_subshell)
{
	if (new_subshell->input == NULL)
		new_subshell->input = make_new_redirect_node(NULL, INPUT, 0);
	if (new_subshell->output == NULL)
		new_subshell->output = make_new_redirect_node(NULL, OUTPUT, 1);
}

void	open_par_st(t_token *temp, t_pipeline *cur_pipe, t_token **head)
{
	t_subshell	*new_subshell;
	t_pipeline	*new_pipeline;

	new_subshell = make_new_subshell_struct(OPEN);
	if (cur_pipe->prev_control_operator == PIPELINE)
		new_subshell->pipe_input = 1;
	cur_pipe->subshell = new_subshell;
	handle_subshell_redir(cur_pipe->subshell, temp, head);
	add_standard_in_out_nodes(cur_pipe->subshell);
	cur_pipe->next_control_operator = OPEN;
	new_pipeline = make_new_pipeline(OPEN);
	cur_pipe->next = new_pipeline;
}
