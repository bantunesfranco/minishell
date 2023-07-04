/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/07/04 10:38:21 by jmolenaa      ########   odam.nl         */
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

static bool	line_is_only_whitespace(char *line)
{
	int	i;

	i = 0;
	while (*(line + i) != '\0')
	{
		if (*(line + i) != ' ' || (*(line + i) >= '\t' && *(line + i) <= '\r'))
			return (false);
		i++;
	}
	return (true);
}

t_pipeline	*parse_line(char *line, t_gen *gen)
{
	t_pipeline	*first_pipeline;
	t_token		*head;
	t_par_info	p_info;

	if (line == NULL || line_is_only_whitespace(line))
		return (NULL);
	first_pipeline = NULL;
	init_struct(&p_info);
	lexer(line, &p_info, &head);
	if (read_all_heredocs(head, p_info.error_token) != 0)
	{
		gen->status = 1;
		free_token_list(head);
		return (NULL);
	}
	if (p_info.syntax_error == 1)
	{
		gen->status = 258;
		free_token_list(head);
		return (NULL);
	}
	setup_signal_handlers_and_terminal_non_interactive();
	parser(&p_info, &head, &first_pipeline);
	return (first_pipeline);
}
