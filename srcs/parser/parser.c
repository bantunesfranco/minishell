/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/02 11:55:29 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"

void	add_token_to_back(t_token **first_token, t_token *new_token)
{
	t_token	*temp;

	temp = *first_token;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_token;
	}
	else
		*first_token = new_token;
}

t_token	*lexer(char *line)
{
	t_token	*first_token;

	first_token = NULL;
	
}

t_cmd	*parse_line(char *line)
{
	t_cmd	*first_cmd;
	t_token	*first_token;

	first_cmd = NULL;
	first_token = lexer(line);

}
