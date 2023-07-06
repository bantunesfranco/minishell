/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_cmd_arrays.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 15:26:08 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 21:31:19 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"

size_t	copy_array(char **dst, char **src)
{
	size_t	i;

	i = 0;
	while (*(src + i) != NULL)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	return (i);
}

static int	count_words(char **split_word, char **cmd_array)
{
	int	word_count;
	int	i;

	word_count = 0;
	i = 0;
	while (*(split_word + i) != NULL)
	{
		i++;
		word_count++;
	}
	i = 0;
	while (*(cmd_array + i) != NULL)
	{
		i++;
		word_count++;
	}
	return (word_count - 1);
}

void	insert_into_array(char **split_word, char ***cmd_array, size_t i)
{
	int		word_count;
	char	**new_cmd_array;
	size_t	j;

	word_count = count_words(split_word, *cmd_array);
	new_cmd_array = ft_calloc((word_count + 1), sizeof(char *));
	j = 0;
	while (j != i)
	{
		*(new_cmd_array + j) = *(*cmd_array + j);
		j++;
	}
	j = j + copy_array(new_cmd_array + j, split_word); 
	j = j + copy_array(new_cmd_array + j, *cmd_array + i + 1);
	free(*cmd_array);
	*cmd_array = new_cmd_array;
}

size_t	expand_single_word(char ***cmd_array, size_t i, t_gen *gen)
{
	t_quote_mark	*head;
	char			*word;
	char			**split_word;

	head = NULL;
	word = expand_env(*(*cmd_array + i), gen, 0, &head);
	split_word = word_splitting(word, head);
	quote_removal(split_word, head);
	insert_into_array(split_word, cmd_array, i);
	i = i + ft_arrlen(split_word);
	free(split_word);
	free(word);
	free_quote_list(head);
	return (i);
}

void	expand_pipeline(t_cmd *cmd, t_gen *gen)
{
	size_t	i;

	while (cmd != NULL)
	{
		i = 0;
		while (cmd->cmd != NULL && *(cmd->cmd + i) != NULL)
		{
			i = expand_single_word(&(cmd->cmd), i, gen);
			if (*cmd->cmd == NULL)
			{
				free(cmd->cmd);
				cmd->cmd = NULL;
				break ;
			}
		}
		i = 0;
		while (cmd->cmd != NULL && *(cmd->cmd + i) != NULL)
			i = expand_wildcards(&(cmd->cmd), *(cmd->cmd + i), i);
		cmd = cmd->next;
	}
}
