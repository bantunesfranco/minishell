/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_tester.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 18:45:01 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/24 20:22:41 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"
#include "parsing.h"
#include "lexer.h"

int	main(int argc, char *argv[])
{
	t_token			*first_token;
	t_parsing_info	p_info;

	(void)argc;
	(void)first_token;
	(void)argv;
	init_struct(&p_info);
	lexer(argv[1], &p_info, &first_token);
}
