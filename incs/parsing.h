/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:52 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/06/08 19:40:08 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structs.h"
# include "parsing_structs.h"
# include <stdio.h>

typedef t_token	*(*t_current_state_function)(t_token *, t_pipeline *, t_token **);

// test functions DELETE LATER
void		print_array(char **arr);
void		print_tokens(t_token *first_token);
void		free_cmds(t_pipeline *first_pipeline);
void		print_redirects(t_pipeline *first_pipeline);
void		print_commands(t_pipeline *first_command);

t_pipeline	*parse_line(char *line, t_gen *gen);
void		init_struct(t_parsing_info *p_info);
void		parser(t_parsing_info *p_info, t_token **first_token, t_pipeline **first_pipeline);

// functions used for the token list

void		add_new_token_to_back(t_token **first_token, t_token *new_token);
t_token		*make_new_token(char *word, t_token_type type);
void		free_token_list(t_token *first_token);
void		remove_token(t_token **first_token, t_token *node_to_delete);
void		remove_tokens(t_token *temp, t_token **first_token);

// functions used for the pipeline list

t_pipeline	*make_new_pipeline(t_control_operator type);
void		add_pipeline_back(t_pipeline **head, t_pipeline *new_pipeline);

// functions used for redirect lists

t_redirect	*make_new_redirect_node(char *name, t_redirect_type type, int fd);
void		add_redirect_back(t_redirect **head, t_redirect *new_redirect);

// functions used for redirect lists

t_cmd		*make_new_simple_cmd(void);
void		add_simple_cmd_back(t_cmd **head, t_cmd *new_simple_cmd);

// functions for subshells

t_subshell	*make_new_subshell_struct(t_control_operator type);

// states

t_token		*end_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token);
t_token		*redirection_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token);
t_token		*control_operator_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token);
t_token		*parenthesis_state(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token);

t_cmd		*find_curr_cmd(t_pipeline *curr_pipeline);
t_pipeline	*find_curr_pipeline(t_pipeline *curr_pipeline);
void		close_simple_cmd(t_token *temp, t_pipeline *curr_pipeline, t_token **first_token);
char		**create_cmd_array(t_token *temp, t_token *first_token);
void		malloc_failure();
size_t		skip_quotes(char *line, size_t i);

#endif