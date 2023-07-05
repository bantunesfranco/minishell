/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_removal.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 12:23:16 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 19:01:47 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"

static size_t	remove_quotes(char *word, size_t i, \
							t_quote_mark **head, size_t *removed_quotes)
{
	size_t	k;

	k = 0;
	while (*(word + k) != '\0' && *head != NULL)
	{
		if (k + i + *removed_quotes == (*head)->word_index_2)
		{
			ft_memmove(word + k, word + k + 1, ft_strlen(word + k));
			*head = (*head)->next;
			(*removed_quotes)++;
			continue ;
		}
		k++;
	}
	return (i + ft_strlen(word));
}

void	quote_removal(char **split_word, t_quote_mark *head)
{
	size_t	j;
	size_t	i;
	size_t	removed_quotes;

	j = 0;
	i = 0;
	removed_quotes = 0;
	while (*(split_word + j) != NULL)
	{
		i = remove_quotes(*(split_word + j), i, &head, &removed_quotes);
		j++;
	}
}
