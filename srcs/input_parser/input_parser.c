/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/30 10:17:54 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"
#include "lexer.h"

t_pipeline	*parse_line(char *line)
{
	t_pipeline		*first_pipeline;
	t_token			*first_token;
	t_parsing_info	p_info;

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
