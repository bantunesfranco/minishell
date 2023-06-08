/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 09:21:09 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/08 19:39:48 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "parsing_structs.h"
# include <stdio.h>

typedef bool	(*t_is_order_valid)(t_token *, int *);

// lexer funcitons

void		lexer(char *line, t_parsing_info *p_info, t_token **first_token);
void		create_token_list(char *line, t_parsing_info *p_info, t_token **first_token);
char		*create_word(char *line, t_token_type new_token_type, t_parsing_info *p_info);
void		assign_token_groups(t_token *first_token);
void		validate_syntax(t_token	*first_token, t_parsing_info *p_info);
bool		is_single_token_valid(t_token *temp, int *open_brackets);
bool		is_parenthesis_valid(t_token *temp, int *open_brackets);
void		token_order_error(t_token *temp, int open_brackets);
bool		are_quotes_closed(char *word);
void		lex_error_function(char *word, int syntax_erorr);

#endif