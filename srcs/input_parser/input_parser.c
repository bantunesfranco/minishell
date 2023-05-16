/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/16 15:21:03 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"

t_cmd_list	*parse_line(char *line)
{
	t_cmd_list		*first_cmd;
	t_token			*first_token;
	t_parsing_info	p_info;

	first_cmd = NULL;
	init_struct(&p_info);
	lexer(line, &p_info, &first_token); // mallocs a list of nodes with malloced words, first_token will point to the first node
	parser(&p_info, first_token, &first_cmd);
	free_token_list(first_token);
	return (first_cmd);
}
