/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:52 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/15 11:41:35 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structs.h"
# include "parsing_structs.h"
# include <stdio.h>

// test functions DELETE LATER
void		print_array(char **arr);
void		print_tokens(t_token *first_token);

t_cmd_list	*parse_line(char *line);
void		init_struct(t_parsing_info *p_info);

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

// functions used for the token list

void		add_new_token_to_back(t_token **first_token, t_token *new_token);
t_token		*make_new_token(char *word, t_token_type type);
void		lex_error_function(char *word, int syntax_erorr);
size_t		skip_quotes(char *line, size_t i);

#endif