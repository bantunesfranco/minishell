/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_splitting.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 18:44:53 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/17 17:54:54 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

static int	get_word_end(char *str, int i)
{
	while (*(str + i) != ' ' && *(str + i) != '\t' && \
			*(str + i) != '\n' && *(str + i) != '\0')
	{
		if (*(str + i) == '"' || *(str + i) == '\'')
			i = skip_quotes(str, i);
		i++;
	}
	return (i);
}

static int	split_str(char **split_word, char *str)
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
			word_end = get_word_end(str, i);
			*(split_word + j) = ft_substr(str, i, word_end - i);
			if (*(split_word + j) == NULL)
				return (0);
			j++;
			i = word_end - 1;
		}
		i++;
	}
	return (1);
}

static int	count_words(char *str)
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
					i = skip_quotes(str, i);
				i++;
			}
		}
		if (*(str + i) != '\0')
			i++;
	}
	return (word_count);
}

char	**split_word(char *str)
{
	char	**split_word;
	int		word_count;

	if (!str)
		return (NULL);
	word_count = count_words(str);
	// if (word_count == 0)
	// 	return (NULL)
	split_word = ft_calloc(sizeof(char *), word_count + 1);
	if (!split_word)
		err_msg(NULL, "expander");
	if (split_str(split_word, str) == 0)
		free_arr(split_word);
	return (split_word);
}
