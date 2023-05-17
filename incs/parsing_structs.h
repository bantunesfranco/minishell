/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_structs.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: janmolenaar <janmolenaar@student.codam.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 19:16:12 by janmolenaar   #+#    #+#                 */
/*   Updated: 2023/05/17 08:24:18 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_STRUCTS_H
# define PARSING_STRUCTS_H

# include <stdbool.h>
# include "structs.h"

typedef enum e_token_type
{
	PIPE_PIPE,
	PIPE,
	AMPERSAND_AMPERSAND,
	OPEN_PAR,
	CLOSE_PAR,
	LESS_LESS,
	LESS,
	GREAT_GREAT,
	GREAT,
	SPACE_,
	TAB_,
	NEW_LINE,
	CHARACTERS
}	t_token_type;

typedef enum e_token_group
{
	CONTROL_OPERATOR,
	PARENTHESIS,
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
	bool	syntax_error;
	t_token	*error_token;
}			t_parsing_info;

typedef bool	(*t_is_order_valid)(t_token *, int *);
typedef void	(*t_current_state_function)(t_token *, t_cmd_list *);

#endif