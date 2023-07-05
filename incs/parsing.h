/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/20 12:01:52 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 13:28:10 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structs.h"
# include "parsing_structs.h"
# include <stdlib.h>

typedef t_token	*(*t_current_state_function)(t_token *, t_pipeline *, t_token **);

t_pipeline	*parse_line(char *line, t_gen *gen);
void		init_struct(t_par_info *p_info);
void		parser(t_token **head, t_pipeline **first_pipeline);
int			read_all_heredocs(t_token *head, t_token *error_token);
void		child_heredoc(char *delimiter, int p[2]);

// functions used for the token list

void		add_new_token_to_back(t_token **head, t_token *new_token);
t_token		*make_new_token(char *word, t_token_type type);
void		free_token_list(t_token *head);
void		remove_token(t_token **head, t_token *node_to_delete);
void		remove_tokens(t_token *temp, t_token **head);

// functions used for the pipeline list

t_pipeline	*make_new_pipeline(t_control_operator type);
t_pipeline	*find_last_pipeline(t_pipeline *first_pipeline);

// functions used for redirect lists

t_redirect	*make_new_redirect_node(char *name, t_redirect_type type, int fd);
void		add_redirect_back(t_redirect **head, t_redirect *new_redirect);

// functions used for redirect lists

t_cmd		*make_new_simple_cmd(void);
void		add_simple_cmd_back(t_cmd **head, t_cmd *new_simple_cmd);
t_cmd		*find_last_cmd(t_pipeline *cur_pipe);

// functions for subshells

t_subshell	*make_new_subshell_struct(t_control_operator type);

// states

t_token		*end_state(t_token *temp, t_pipeline *cur_pipe, t_token **head);
t_token		*red_st(t_token *temp, t_pipeline *cur_pipe, t_token **head);
t_token		*ctrl_op_st(t_token *temp, t_pipeline *cur_pipe, t_token **head);
t_token		*par_st(t_token *temp, t_pipeline *cur_pipe, t_token **head);
void		open_par_st(t_token *temp, t_pipeline *cur_pipe, t_token **head);

void		close_cmd(t_token *temp, t_pipeline *cur_pipe, t_token **head);
char		**create_cmd_array(t_token *temp, t_token *head);
size_t		skip_quotes(char *line, size_t i);

#endif