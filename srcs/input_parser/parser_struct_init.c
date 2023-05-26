/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_struct_init.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 19:32:47 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/05/26 07:52:42 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "parsing_structs.h"
#include <stdlib.h>

/*	double array of strings with how the tokens look
	the characters that have a double version and a single version have the double version first
	this is because we're using strcmp, which means f.e. if the single pipe is first it will always see that first*/

static void	setup_token_array(char *token_array[13])
{
	token_array[0] = "||";
	token_array[1] = "|";
	token_array[2] = "&&";
	token_array[3] = "(";
	token_array[4] = ")";
	token_array[5] = "<<";
	token_array[6] = "<";
	token_array[7] = ">>";
	token_array[8] = ">";
	token_array[9] = " ";
	token_array[10] = "\t";
	token_array[11] = "\n";
	token_array[12] = NULL;
}

/*	these are all the possible metacharacters, which when unquoted will separate our various words
	ampersand is missing, we handle it separately since a single ampersand is considered a normal character, 
	but double separates words*/

static void	setup_meta_characters(char meta_characters[8])
{
	meta_characters[0] = '|';
	meta_characters[1] = '(';
	meta_characters[2] = ')';
	meta_characters[3] = '<';
	meta_characters[4] = '>';
	meta_characters[5] = ' ';
	meta_characters[6] = '\t';
	meta_characters[7] = '\n';
	meta_characters[8] = '\0';
}

void	init_struct(t_parsing_info *p_info)
{
	setup_meta_characters(p_info->metacharacters);
	setup_token_array(p_info->token_array);
	p_info->syntax_error = 0;
}
