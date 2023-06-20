/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_removal.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 12:23:16 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/19 14:51:45 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "libft.h"
#include "parsing.h"

size_t	quote_removal_single_word(char *word, size_t i, t_quote_mark **head, size_t *removed_quotes)
{
	size_t	k;
	// (void)removed_quotes;
	// printf("word|%s|", word);
	// printf("strlen %zu\n", ft_strlen(word));
	// printf("%zu\n", i);
	k = 0;
	while (*(word + k) != '\0' && *head != NULL)
	{
		if (k + i + *removed_quotes == (*head)->word_index_2)
		{
			// printf(" k %zu char %c\n", k, *(word + k));
			ft_memmove(word + k, word + k + 1, ft_strlen(word+ k));
			// printf("word|%s|\n", word);
			*head = (*head)->next;
			(*removed_quotes)++;
			continue ;
		}
		k++;
	}
	// printf("return %zu\n", i + k);
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
		i = quote_removal_single_word(*(split_word + j), i, &head, &removed_quotes);
		// printf("%zu\n", i);
		j++;
	}
}

// "asd"
// ""

// asd"
// "asd"
// "asd ' asd '"asd""
// asd ' asd 'asd