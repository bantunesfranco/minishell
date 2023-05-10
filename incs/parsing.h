/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:52 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/05/10 16:17:38 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "structs.h"

// test functions DELETE LATER
void	print_array(char **arr);
void	print_tokens(t_token *first_token);

t_cmd_list	*parse_line(char *line);

#endif
