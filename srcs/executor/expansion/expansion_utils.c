/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmolenaa <jmolenaa@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/05 18:59:44 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 19:00:46 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	find_end_of_var(char *word, size_t start_var)
{
	if (*(word + start_var) == '?')
		return (start_var + 1);
	while (ft_isalnum(*(word + start_var)) || *(word + start_var) == '_')
		start_var++;
	return (start_var);
}
