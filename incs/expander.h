/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 14:05:12 by bfranco       #+#    #+#                 */
/*   Updated: 2023/06/01 16:46:38 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "structs.h"

// typedef enum e_qt
// {
// 	NONE,
// 	SINGLE,
// 	DOUBLE
// }			t_qt;

void	expand_environment_vars(char *word, t_gen *gen);

#endif