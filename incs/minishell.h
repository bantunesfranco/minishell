/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 16:21:59 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/03 09:29:24 by bruno         ########   odam.nl         */
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

/* Builtins */
int		echo(char **env, t_cmd *cmd);
int	    pwd(char **env, t_cmd *cmd);


#endif