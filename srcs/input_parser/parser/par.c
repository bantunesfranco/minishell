/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 15:21:06 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/16 20:18:24 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"

void	call_state(t_token *temp, t_cmd_list *first_cmd)
{
	t_current_state_function	next_state[5];

	next_state[0] = control_operator_state;
	next_state[3] = parenthesis_state;
	next_state[1] = redirection_state;
	next_state[3] = end_state;
	next_state[2] = word_state;
}

void	parser(t_parsing_info *p_info, t_token *first_token, t_cmd_list **first_cmd)
{
	(void)p_info;
	(void)first_token;
	(void)first_cmd;
	t_token	*temp;

	temp = first_cmd;
	first_cmd = NULL;
	while (temp != NULL)
	{
		call_state(temp, first_cmd);
		temp = temp->next;
	}
}
