/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_assign_groups.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 13:11:32 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/04 10:09:43 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_structs.h"
#include <stdlib.h>

static void	assign_group(t_token *temp)
{
	if (temp->type >= 0 && temp->type <= 2)
		temp->token_group = CONTROL_OPERATOR;
	else if (temp->type >= 3 && temp->type <= 4)
		temp->token_group = PARENTHESIS;
	else if (temp->type >= 5 && temp->type <= 8)
		temp->token_group = REDIRECTION;
	else if (temp->type >= 9 && temp->type <= 11)
		temp->token_group = WHITESPACE;
	else
		temp->token_group = WORD;
}

void	assign_token_groups(t_token *head)
{
	t_token	*temp;

	temp = head;
	while (temp != NULL)
	{
		assign_group(temp);
		temp = temp->next;
	}
}
