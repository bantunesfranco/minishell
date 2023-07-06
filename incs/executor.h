/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 12:31:23 by codespace     #+#    #+#                 */
/*   Updated: 2023/07/06 10:10:36 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <sys/wait.h>
# include "structs.h"

void		find_path(char **cmd, t_gen *gen);
void		check_access(t_gen *gen, t_cmd *cmd);
int			handle_input_redirection(t_redirect *input, t_gen *gen);
int			handle_output_redirection(t_redirect *output, t_gen *gen);
void		handle_dups(t_cmd *cmd, int *p, int pipe_rd);
int			pipe_and_fork(t_cmd *cmd, int *p);
void		close_pipes(t_cmd *cmd, int *p, int pipe_rd);
void		exec_cmd(t_gen *gen, t_cmd *cmd, int *p, int pipe_rd);
void		exec_simple_pipeline(t_gen *gen, t_pipeline *pipeline);
void		check_pipeline_for_builtins(t_cmd *first_cmd);
char		*read_here_doc(char *delimiter);
void		execute_instructions(t_gen *gen, t_pipeline *input);
int			exec_subsh(t_gen *gen, t_pipeline **pipeline, int *pipe_read);
int			exec_subsh_pipeline(t_gen *gen, t_pipeline **pipeline, \
								int *pipe_read);
int			handle_heredoc_redir(t_redirect *heredoc_node, t_gen *gen);
t_pipeline	*check_control_operators(t_gen *gen, t_pipeline *tmp);
t_pipeline	*goto_close_operator(t_pipeline *tmp);
void		is_dir(char *cmd);

#endif