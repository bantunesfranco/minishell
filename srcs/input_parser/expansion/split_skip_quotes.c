/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_skip_quotes.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 16:47:01 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/08 18:48:04 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_arr(char **arr)
{
	int	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	return (NULL);
}

static int	get_word_end(const char *str, char sep, int i)
{
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

static int	get_arr(char **arr, const char *str, char sep)
{
	int	i;
	int	word_end;

	i = 0;
	while (str[i])
	{
		if (str[i] != sep)
		{
			word_end = get_word_end(str, sep, i);
			*arr = ft_calloc(sizeof(**arr), word_end - i + 1);
			if (!*arr)
				return (0);
			ft_memcpy(*arr, str + i, word_end - i);
			arr++;
			i = word_end - 1;
		}
		i++;
	}
	return (1);
}

static int	count_words(const char *str, char sep)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (str[i] == sep)
		i++;
	while (str[i])
	{
		if (str[i] != sep)
		{
			nb_words++;
			while (str[i] && str[i] != sep)
				i++;
		}
		if (str[i])
			i++;
	}
	return (nb_words);
}

char	**ft_split(const char *str, char sep)
{
	char	**arr;

	if (!str)
		return (NULL);
	arr = ft_calloc(sizeof(*arr), count_words(str, sep) + 1);
	if (!arr)
		return (NULL);
	if (!get_arr(arr, str, sep))
		return (free_arr(arr));
	return (arr);
}
