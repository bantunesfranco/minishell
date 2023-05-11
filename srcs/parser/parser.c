/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:23:43 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/11 11:23:43 by jmolenaa      ########   odam.nl         */
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

	init_struct(&p_info);
	first_cmd = NULL;
	lexer(line, &p_info, &first_token); // mallocs a list of nodes with malloced words, first_token will point to the first node
	return (first_cmd);
}
