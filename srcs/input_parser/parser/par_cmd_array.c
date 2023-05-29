/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_cmd_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 08:22:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/29 08:38:37 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parsing_structs.h"
#include <stdlib.h>
#include "libft.h"

static int	count_words(t_token *temp, t_token *first_token)
{
	int	i;

	i = 0;
	while (first_token != temp)
	{
		i++;
		first_token = first_token->next;
	}
	return (i);
}

char	**create_cmd_array(t_token *temp, t_token *first_token)
{
	int		word_count;
	int		i;
	char	**cmd_array;

	word_count = count_words(temp, first_token);
	if (word_count == 0)
		return (NULL);
	cmd_array = ft_calloc((word_count + 1), sizeof(char *));
	if (cmd_array == NULL)
		exit (1);						//malloc failure
	i = 0;
	while (first_token != temp)
	{
		cmd_array[i] = first_token->word;
		first_token = first_token->next;
		i++;
	}
	return (cmd_array);
}

