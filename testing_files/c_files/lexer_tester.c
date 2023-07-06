/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_tester.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 18:45:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/04 10:07:45 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"
#include "lexer.h"

static void	lexer(char *line, t_par_info *p_info, t_token **head)
{
	create_token_list(line, p_info, head);
	assign_token_groups(*head);
	validate_syntax(*head, p_info);
}

void	print_toks(t_token *head)
{
	t_token	*temp;

	temp = head;
	printf("%s", temp->word);
	temp = temp->next;
	while (temp->type != NEW_LINE)
	{
		printf(" ");
		printf("%s", temp->word);
		temp = temp->next;
	}
	printf("\n");
}

int	main(int argc, char *argv[])
{
	t_token		*head;
	t_par_info	p_info;

	(void)argc;
	(void)head;
	(void)argv;
	init_struct(&p_info);
	lexer(argv[1], &p_info, &head);
	print_toks(head);
}
