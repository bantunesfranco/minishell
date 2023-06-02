/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_assign_groups.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 13:11:32 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/24 16:04:58 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_structs.h"
#include <stdlib.h>

/*	tokens have certain functions they do, which can be grouped.
	this will make parsing and error checking more concise, cause we're lookign at groups instead of individual tokens*/

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

void	assign_token_groups(t_token *first_token)
{
	t_token	*temp;

	temp = first_token;
	while (temp != NULL)
	{
		assign_group(temp);
		temp = temp->next;
	}
}