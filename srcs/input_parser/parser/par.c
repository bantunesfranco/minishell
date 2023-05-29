/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 15:21:06 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/29 08:39:55 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"

t_token	*parenthesis_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	(void)temp;
	(void)first_token;
	(void)curr_pipeline;
	printf("%d\n", temp->token_group);
	t_token	*next_token;

	next_token = temp->next;
	remove_token(first_token, temp);
	return (next_token);
}

t_token	*word_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token)
{
	(void)temp;
	(void)first_token;
	(void)curr_pipeline;
	return (temp->next);
}

t_token	*call_state(t_token *temp, t_pipeline *first_pipeline, t_token **first_token)
{
	t_current_state_function	next_state[5];
	t_pipeline					*curr_pipeline;

	next_state[0] = control_operator_state;
	next_state[1] = parenthesis_state;
	next_state[2] = redirection_state;
	next_state[3] = end_state;
	next_state[4] = word_state;
	curr_pipeline = find_curr_pipeline(first_pipeline);
	return(next_state[temp->token_group](temp, curr_pipeline, first_token));
}

void	setup_starting_point(t_pipeline **first_pipeline)
{
	t_pipeline	*first_node;

	first_node = make_new_pipeline(START);
	if (first_node == NULL)
		exit(1);					//malloc failure function
	*first_pipeline = first_node;
}

void	parser(t_parsing_info *p_info, t_token **first_token, t_pipeline **first_pipeline)
{
	(void)p_info;
	t_token	*temp;

	temp = *first_token;
	setup_starting_point(first_pipeline);
	while (temp != NULL)
	{
		temp = call_state(temp, *first_pipeline, first_token);
		// temp = temp->next;
	}
	// print_redirects(*first_pipeline);
	// printf("%p\n", (*first_pipeline)->first_cmd->cmd);
	// printf("%s\n", (*first_pipeline)->first_cmd->cmd[0]);
	// print_array((*first_pipeline)->first_cmd->cmd);
	print_commands(*first_pipeline);
	free_cmds(*first_pipeline);
}
