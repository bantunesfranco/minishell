/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:21:59 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/09 14:27:03 by bfranco       ########   odam.nl         */
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

/* Builtin utils */
int		ft_envcmp(char *env, char *s2);
int		is_valid_input(char *str);

/* Builtins */
int		echo(t_gen *gen, t_cmd *cmd);
int		pwd(t_gen *gen, t_cmd *cmd);
int		cd(t_gen *gen, t_cmd *cmd);
int		env(t_gen *gen, t_cmd *cmd);
int		export(t_gen *gen, t_cmd *cmd);
int		export2(t_gen *gen, char *target, int add, int size);
int		unset(t_gen *gen, t_cmd *cmd);

#endif