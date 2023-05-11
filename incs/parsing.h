/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:52 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/10 19:57:55 by janmolenaar   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "structs.h"
#include "parsing_structs.h"

// test functions DELETE LATER
void		print_array(char **arr);
void		print_tokens(t_token *first_token);

void		init_struct(t_parsing_info *p_info);
t_cmd_list	*parse_line(char *line);
void		add_token_to_back(t_token **first_token, t_token *new_token);
t_token		*make_new_token(char *word, t_token_type type);

#endif
