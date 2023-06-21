/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_parenthesis_state.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 15:00:55 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/21 11:43:13 by jmolenaa      ########   odam.nl         */
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

t_token	*add_redirection(t_subshell *new_subshell, t_token *temp, t_token **first_token)
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
	remove_token(first_token, temp->next);
	remove_token(first_token, temp);
	return (next_token);
}

void	handle_subshell_redirections(t_subshell *new_subshell, t_token *open_par, t_token **first_token)
{
	t_token	*temp;

	temp = skip_to_close_parenthesis(open_par);
	temp = temp->next;
	while (1)
	{
		if (temp->token_group == REDIRECTION)
			temp = add_redirection(new_subshell, temp, first_token);
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

void	open_parenthesis_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	t_subshell	*new_subshell;
	t_pipeline	*new_pipeline;

	new_subshell = make_new_subshell_struct(OPEN);
	if (curr_pipeline->prev_control_operator == PIPELINE)
		new_subshell->pipe_input = 1;
	curr_pipeline->subshell = new_subshell;
	handle_subshell_redirections(curr_pipeline->subshell, temp, first_token);
	add_standard_in_out_nodes(curr_pipeline->subshell);
	curr_pipeline->next_control_operator = OPEN;
	new_pipeline = make_new_pipeline(OPEN);
	new_pipeline->prev = curr_pipeline;			//maybe remove this, the prev thing I mean
	curr_pipeline->next = new_pipeline;
}

void	close_parenthesis_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	t_subshell	*new_subshell;
	t_pipeline	*new_pipeline;

	close_simple_cmd(temp, curr_pipeline, first_token);
	curr_pipeline->next_control_operator = CLOSE;
	new_pipeline = make_new_pipeline(CLOSE);
	new_subshell = make_new_subshell_struct(CLOSE);
	new_pipeline->subshell = new_subshell;
	new_pipeline->prev = curr_pipeline;
	curr_pipeline->next = new_pipeline;
}

t_token	*parenthesis_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	t_token	*next_token;

	if (temp->type == OPEN_PAR)
		open_parenthesis_state(temp, curr_pipeline, first_token);
	else
		close_parenthesis_state(temp, curr_pipeline, first_token);
	next_token = temp->next;
	remove_token(first_token, temp);
	return (next_token);
}
