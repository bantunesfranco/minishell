/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:21:59 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/26 19:29:21 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "parsing_structs.h"
# include "structs.h"

// sig_atomic_t	g_kill_switch;

char	**env_init(char **env);
char	**ft_split_args(char *str, char sep);
char	**ft_arrdup(char **arr);

/* Builtin utils */
int		ft_envcmp(char *env, char *s2);
char	**copy_env(char **env, char *target, int size);
int		is_valid_input(char *str);

/* Builtins */
int		cd(t_gen *gen, t_cmd *cmd);
int		echo(t_gen *gen, t_cmd *cmd);
int		env(t_gen *gen, t_cmd *cmd);
int		mini_exit(t_gen *gen, t_cmd *cmd);
int		export(t_gen *gen, t_cmd *cmd);
int		export2(t_gen *gen, char *target, int add, int size);
int		pwd(t_gen *gen, t_cmd *cmd);
int		unset(t_gen *gen, t_cmd *cmd);

/* Error handling */
void	lex_error_function(char *word, int syntax_erorr);
void	built_err_msg(char *msg, char *msg2, char *msg3);
void	err_msg(char *msg, char *msg2);
void	child_err_msg(char *msg, char *msg2);
void	token_order_error(t_token *temp, int open_brackets);

void	free_parsed_structs(t_pipeline *first_pipeline);

void	setup_signal_handlers_and_terminal_non_interactive(void);
void	setup_signal_handlers_and_terminal_interactive(void);
void	heredoc_handler(int signal);
void	set_echoctl(void);
void	unset_echoctl(void);

#endif