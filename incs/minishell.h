/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:21:59 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/09 10:41:05 by bruno         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// # include <readline/readline.h>
# include "libft.h"
# include "structs.h"

char	**ft_split_args(char *str, char sep);
char	**ft_arrdup(char **arr);
int		ft_envcmp(char *env, char *s2);

/* Builtins */
int		echo(t_gen *gen, t_cmd *cmd);
int		pwd(t_gen *gen, t_cmd *cmd);
int		cd(t_gen *gen, t_cmd *cmd);
int		env(t_gen *gen, t_cmd *cmd);
int		export(t_gen *gen, t_cmd *cmd);
int		unset(t_gen *gen, t_cmd *cmd);

#endif