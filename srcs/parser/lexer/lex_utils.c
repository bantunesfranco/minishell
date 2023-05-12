/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 19:56:00 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/05/12 14:15:55 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "libft.h"
#include <stdlib.h>

/*	these functions are kind of self explanatory*/

void	add_new_token_to_back(t_token **first_token, t_token *new_token)
{
	t_token	*temp;

	temp = *first_token;
	if (temp == NULL)
		*first_token = new_token;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_token;
		new_token->prev = temp;
	}
}

t_token	*make_new_token(char *word, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->word = word;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/*	skips the quotes by storing which ones we encountered in c and then looping till the next c or \0 */

size_t	skip_quotes(char *line, size_t i)
{
	char	c;

	c = *(line + i);
	i++;
	while (*(line + i) != c && *(line + i) != '\0')
		i++;
	return (i);
}

/*	writes an error based on what mistake the sintax has, either a token is in the wrong position
	or we have unclosed parenthesis or brackets*/

void	lex_error_function(char *word, int syntax_erorr)
{
	if (syntax_erorr == 1)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, word, ft_strlen(word));
		write(2, "'\n", 2);
	}
	else
	{
		write(2, "minishell: unexpected newline while looking for matching `", 59);
		write(2, word, 1);
		write(2, "'\n", 2);
	}
}
