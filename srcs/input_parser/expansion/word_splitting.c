/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_splitting.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 18:44:53 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/19 13:17:07 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "libft.h"
#include "parsing.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		err_msg(NULL, "expander");
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	err_msg(NULL, "expander");
}

int	get_word_end(char *str, int i, t_quote_mark **head)
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

void	decrement_index_in_list(t_quote_mark *head)
{
	while (head != NULL)
	{
		(head->word_index_2)--;
		head = head->next;
	}
}

int	split_str(char **split_word, char *str, t_quote_mark *head)
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
				return (0);
			j++;
			i = word_end - 1;
		}
		else
			decrement_index_in_list(head);
		i++;
	}
	return (1);
}

int	count_words(char *str, t_quote_mark *head)
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

char	**split_word(char *str, t_quote_mark *head)
{
	char	**split_word;
	int		word_count;

	if (!str)
		return (NULL);
	word_count = count_words(str, head);
	// printf("%d\n", word_count);
	// if (word_count == 0)
	// 	return (NULL);
	split_word = ft_calloc(sizeof(char *), word_count + 1);
	if (!split_word)
		err_msg(NULL, "expander");
	if (split_str(split_word, str, head) == 0)
		free_arr(split_word);
	return (split_word);
}
