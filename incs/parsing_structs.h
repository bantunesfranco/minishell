/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_structs.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 19:16:12 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/05/10 19:55:01 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_STRUCTS_H
# define PARSING_STRUCTS_H

typedef enum e_token_type
{
	PIPE,
	PIPE_PIPE,
	AMPERSAND_AMPERSAND,
	OPEN_PAR,
	CLOSE_PAR,
	LESS,
	LESS_LESS,
	GREAT,
	GREAT_GREAT,
	SPACE_,
	TAB_,
	NEW_LINE,
	CHARACTERS
}	t_token_type;

typedef enum e_token_group
{
	CONTROL_OPERATOR,
	REDIRECTION,
	WHITESPACE,
	WORD
}	t_token_group;

typedef struct s_token
{
	char			*word;
	t_token_type	type;
	t_token_group	token_group;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_parsing_info
{
	char	metacharacters[9];
	char	*token_array[13];
}	t_parsing_info;

#endif