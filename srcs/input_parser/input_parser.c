/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/01 15:03:26 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"
#include "lexer.h"

bool	line_is_only_whitespace(char *line)
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
	t_pipeline		*first_pipeline;
	t_token			*first_token;
	t_parsing_info	p_info;

	(void)gen;
	if (line_is_only_whitespace(line))
		return (NULL);
	first_pipeline = NULL;
	init_struct(&p_info);
	lexer(line, &p_info, &first_token); // mallocs a list of nodes with malloced words, first_token will point to the first node
	if (p_info.syntax_error == 1)
	{
		free_token_list(first_token);
		return (NULL);
	}
	// expansions here 90%
	parser(&p_info, &first_token, &first_pipeline);
	// print_tokens(first_token);
	return (first_pipeline);
}