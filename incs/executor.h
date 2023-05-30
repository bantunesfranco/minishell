/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 12:31:23 by codespace     #+#    #+#                 */
/*   Updated: 2023/05/29 14:04:59 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

char	**find_path(char **cmd, char **env);
int		check_access(t_gen *gen, t_cmd *cmd);
int		handle_input_redirection(t_redirection *input);
int		handle_output_redirection(t_redirection *output);

#endif