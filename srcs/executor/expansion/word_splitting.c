/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_splitting.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 18:44:53 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 19:01:28 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"

static int	get_word_end(char *str, int i, t_quote_mark **head)
{
	while (*(str + i) != ' ' && *(str + i) != '\t' && \
			*(str + i) != '\n' && *(str + i) != '\0')
	{
		if (*(str + i) == '"' || *(str + i) == '\'')
			i = skip_quotes_if_neccesarry(i, head);
		i++;
	}
	return (i);
}

static void	decrement_index_in_list(t_quote_mark *head)
{
	while (head != NULL)
	{
		(head->word_index_2)--;
		head = head->next;
	}
}

static void	split_str(char **split_word, char *str, t_quote_mark *head)
{
	size_t	i;
	int		j;
	int		word_end;

	j = 0;
	i = 0;
	while (*(str + i))
	{
		if (*(str + i) != ' ' && *(str + i) != '\t' && *(str + i) != '\n')
		{
			word_end = get_word_end(str, i, &head);
			*(split_word + j) = ft_substr(str, i, word_end - i);
			if (*(split_word + j) == NULL)
				err_msg(NULL, "expander");
			j++;
			i = word_end - 1;
		}
		else
			decrement_index_in_list(head);
		i++;
	}
}

static int	count_words(char *str, t_quote_mark *head)
{
	size_t	i;
	int		word_count;

	i = 0;
	word_count = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) != ' ' && *(str + i) != '\t' && *(str + i) != '\n')
		{
			word_count++;
			while (*(str + i) != ' ' && *(str + i) != '\t' && \
					*(str + i) != '\n' && *(str + i) != '\0')
			{
				if (*(str + i) == '"' || *(str + i) == '\'')
					i = skip_quotes_if_neccesarry(i, &head);
				i++;
			}
		}
		if (*(str + i) != '\0')
			i++;
	}
	return (word_count);
}

char	**word_splitting(char *str, t_quote_mark *head)
{
	char	**split_word;
	int		word_count;

	if (!str)
		return (NULL);
	word_count = count_words(str, head);
	split_word = ft_calloc(sizeof(char *), word_count + 1);
	if (!split_word)
		err_msg(NULL, "expander");
	split_str(split_word, str, head);
	return (split_word);
}
