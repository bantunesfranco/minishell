/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/22 12:31:23 by codespace     #+#    #+#                 */
/*   Updated: 2023/05/30 12:25:14 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structs.h"

char	**find_path(char **cmd, char **env);
int		check_access(t_gen *gen, t_cmd *cmd);
int		handle_input_redirection(t_redirect *input);
int		handle_output_redirection(t_redirect *output);

#endif