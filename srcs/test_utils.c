/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:20:03 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/11 10:23:52 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "structs.h"
#include "parsing_structs.h"



void	print_token(t_token_type type, char *word)
{
	if (type == PIPE)
		printf("PIPE				%s\n", word);
	else if (type == PIPE_PIPE)
		printf("PIPE_PIPE			%s\n", word);
	else if (type == AMPERSAND_AMPERSAND)
		printf("AMPERSAND_AMPERSAND		%s\n", word);
	else if (type == OPEN_PAR)
		printf("OPEN_PAR			%s\n", word);
	else if (type == CLOSE_PAR)
		printf("CLOSE_PAR			%s\n", word);
	else if (type == LESS)
		printf("LESS				%s\n", word);
	else if (type == LESS_LESS)
		printf("LESS_LESS			%s\n", word);
	else if (type == GREAT)
		printf("GREAT				%s\n", word);
	else if (type == GREAT_GREAT)
		printf("GREAT_GREAT			%s\n", word);
	else if (type == SPACE_)
		printf("SPACE				[%s]\n", word);
	else if (type == TAB_)
		printf("TAB			[%s]\n", word);
	else if (type == NEW_LINE)
		printf("NEW_LINE			[%s]\n", word);
	else if (type == CHARACTERS)
		printf("WORD				%s\n", word);
	else
		printf("somethings wrong	\n");
}

void	print_tokens(t_token *first_token)
{
	t_token	*temp;

	temp = first_token;
	while (temp != NULL)
	{
		print_token(temp->type, temp->word);
		temp = temp->next;
	}
}

void	print_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
