/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   par_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 14:24:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/26 19:31:00 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include "parsing.h"
#include "parsing_structs.h"
#include <stdlib.h>

t_cmd	*find_curr_cmd(t_pipeline *curr_pipeline)
{
	t_cmd	*temp;

	temp = curr_pipeline->first_cmd;
	if (temp != NULL)
	{
		while (temp->next != NULL)
			temp = temp->next;
	}
	return (temp);
}

t_pipeline	*find_curr_pipeline(t_pipeline *first_pipeline)
{
	t_pipeline	*temp;

	temp = first_pipeline;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

int	count_words(t_token *temp, t_token *first_token)
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

void	close_simple_cmd(t_token *temp, t_pipeline *curr_pipeline, t_token *first_token)
{
	t_cmd	*current_cmd;

	current_cmd = find_curr_cmd(curr_pipeline);
	if (current_cmd == NULL)
	{
		current_cmd = make_new_simple_cmd();
		if (current_cmd == NULL)
			exit (1);								// malloc failure
		curr_pipeline->first_cmd = current_cmd;
	}
	current_cmd->cmd = create_cmd_array(temp, first_token); //could eventually make it go till a control operator
	if (current_cmd->cmd == NULL)
		printf("no cmd\n");
	else
		print_array(current_cmd->cmd);
}
