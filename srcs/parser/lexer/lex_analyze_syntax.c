/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_analyze_syntax.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 14:40:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/12 07:46:14 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

void	analyze_syntax(t_token	*first_token, t_parsing_info *p_info)
{
	t_token	*temp;
	int		open_brackets;

	temp = first_token;
	while (temp->next->type != NEW_LINE)
	{
		if (!is_token_valid(temp, &open_brackets))
		{
			p_info->syntax_error = 1;
			break ;
		}
		temp = temp->next;
	}
	
	printf("%d\n", p_info->syntax_error);
}

