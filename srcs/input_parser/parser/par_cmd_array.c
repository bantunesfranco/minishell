/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_cmd_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 08:22:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/04 09:41:26 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parsing_structs.h"
#include "minishell.h"

static int	count_words(t_token *temp, t_token *head)
{
	int	i;

	i = 0;
	while (head != temp)
	{
		i++;
		head = head->next;
	}
	return (i);
}

char	**create_cmd_array(t_token *temp, t_token *head)
{
	int		word_count;
	int		i;
	char	**cmd_array;

	word_count = count_words(temp, head);
	if (word_count == 0)
		return (NULL);
	cmd_array = ft_calloc((word_count + 1), sizeof(char *));
	if (cmd_array == NULL)
		err_msg(NULL, "parser");
	i = 0;
	while (head != temp)
	{
		cmd_array[i] = head->word;
		head = head->next;
		i++;
	}
	return (cmd_array);
}

