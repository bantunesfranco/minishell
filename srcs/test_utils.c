/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:20:03 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/03 10:31:44 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

void	print_token(t_token_type type, char *word)
{
	if (type == PIPE)
		printf("PIPE			|\n");
	else if (type == GREAT)
		printf("GREAT			>\n");
	else if (type == LESS)
		printf("LESS			<\n");
	else if (type == AMPERSAND)
		printf("AMPERSAND		&\n");
	else if (type == WHITESPACE)
		printf("WHITESPACE		[]\n");
	else if (type == NEW_LINE)
		printf("NEW_LINE		\\n\n");
	else if (type == WORD)
		printf("WORD			%s\n", word);
	else
		printf("somethings wrong	");
	if ((type >= 0 && type <= 5) && word != NULL)
		printf("somethings wrong	");
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
