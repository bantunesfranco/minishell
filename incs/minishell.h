/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:21:59 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/30 10:17:08 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include "libft.h"
# include "parsing_structs.h"
# include "structs.h"

char	**ft_split_args(char *str, char sep);
char	**ft_arrdup(char **arr);

// error functions

void	lex_error_function(char *word, int syntax_erorr);
void	built_err_msg(char *msg, char *msg2, char *msg3);
void	err_msg(char *msg, char *msg2);
void	token_order_error(t_token *temp, int open_brackets);

void	free_parsed_structs(t_pipeline *first_pipeline);

#endif