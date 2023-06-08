/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 09:32:31 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/08 19:43:36 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

/*	skips the quotes by storing which ones we encountered in c and then looping till the next c or \0 */

// size_t	skip_quotes(char *line, size_t i)
// {
// 	char	c;

// 	c = *(line + i);
// 	i++;
// 	while (*(line + i) != c && *(line + i) != '\0')
// 		i++;
// 	return (i);
// }

// /*	similar to the function from creating words*/

// bool	are_quotes_closed(char *word)
// {
// 	size_t	i;
// 	char	c;

// 	i = 0;
// 	while (*(word + i) != '\0')
// 	{
// 		if (*(word + i) == '\'' || *(word + i) == '"')
// 		{
// 			c = *(word + i);
// 			i = skip_quotes(word, i);
// 		}
// 		if (*(word + i) == '\0')
// 		{
// 			lex_error_function(&c, 2);
// 			return (false);
// 		}
// 		i++;
// 	}
// 	return (true);
// }
