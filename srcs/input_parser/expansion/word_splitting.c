/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_splitting.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 18:44:53 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/08 19:43:21 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// char	**split_word(char *word)
// {
// 	(void)word;
// }

// static char	**free_arr(char **arr)
// {
// 	int	i;

// 	if (!arr)
// 		return (NULL);
// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		arr[i] = NULL;
// 		i++;
// 	}
// 	free(arr);
// 	return (NULL);
// }

// static int	get_word_end(const char *str, char sep, int i)
// {
// 	while (str[i] && str[i] != sep)
// 		i++;
// 	return (i);
// }

// static int	get_arr(char **arr, const char *str, char sep)
// {
// 	int	i;
// 	int	word_end;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != sep)
// 		{
// 			word_end = get_word_end(str, sep, i);
// 			*arr = ft_calloc(sizeof(**arr), word_end - i + 1);
// 			if (!*arr)
// 				return (0);
// 			ft_memcpy(*arr, str + i, word_end - i);
// 			arr++;
// 			i = word_end - 1;
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// static int	count_words(const char *str)
// {
// 	size_t	i;
// 	int		word_count;

// 	i = 0;
// 	word_count = 0;
// 	while (*(str + i) != '\0')
// 	{
// 		if (*(str + i) != ' ' && *(str + i) != '\t' && *(str + i) != '\n')
// 		{
// 			word_count++;
// 			while (str[i] && str[i] != sep)
// 				i++;
// 		}
// 		if (str[i])
// 			i++;
// 	}
// 	return (word_count);
// }

// char	**ft_split(const char *str)
// {
// 	char	**arr;

// 	if (!str)
// 		return (NULL);
// 	arr = ft_calloc(sizeof(*arr), count_words(str, sep) + 1);
// 	if (!arr)
// 		return (NULL);
// 	if (!get_arr(arr, str, sep))
// 		return (free_arr(arr));
// 	return (arr);
// }
