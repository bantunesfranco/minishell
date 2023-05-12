/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_analyze_syntax.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 14:40:23 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/12 09:55:13 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

bool	are_quotes_closed(char *word)
{
	size_t	i;

	while (*(word + i) != '\0')
	{
		if (*(word + i) == '\'' || *(word + i) == '"')
			i = skip_quotes(word, i);
		if (*(word + i) == '\0')
			return (false);
		i++;
	}
	return (true);
}

bool	are_exit_conditions_valid(t_token *temp, int *open_brackets)
{
	if (open_brackets != 0)
		return (false);
	if (temp->type != NEW_LINE)
		return (false);
	if (temp->prev->token_group == WORD)
		return (are_quotes_closed(temp->prev->word));
}

void	write_syntax_error(t_token *temp, int *open_brackets)
{
	if (*open_brackets == -1)
		
}

void	analyze_syntax(t_token *first_token, t_parsing_info *p_info)
{
	t_token	*temp;
	int		open_brackets;

	temp = first_token;
	while (temp->next != NULL)
	{
		if (!is_token_valid(temp, &open_brackets))
		{
			p_info->syntax_error = 1;
			break ;
		}
		temp = temp->next;
	}
	if (p_info->syntax_error == 0 && !are_exit_conditions_valid(temp, open_brackets))
		p_info->syntax_error = 1;
	if (p_info->syntax_error == 1)
		write_syntax_error(temp, open_brackets);
	printf("%d\n", p_info->syntax_error);
}
