/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 14:51:40 by jmolenaa      #+#    #+#                 */
/*   Updated: 2023/07/05 19:01:05 by jmolenaa      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

char	*compare_with_env(char *var_name, t_gen *gen)
{
	int	i;

	i = 0;
	if (*var_name == '?')
		return (ft_itoa(gen->status));
	while (*(gen->env + i))
	{
		if (!ft_envcmp(var_name, *(gen->env + i)))
			return (ft_strdup(*(gen->env + i) + ft_strlen(var_name)));
		i++;
	}
	return (ft_strdup(""));
}

char	*get_var_name(char *word, int len)
{
	char	*temp;
	char	*var_name;

	temp = ft_substr(word, 0, len);
	if (temp == NULL)
		err_msg(NULL, "expander");
	var_name = ft_strjoin(temp, "=");
	if (var_name == NULL)
		err_msg(NULL, "expander");
	free(temp);
	return (var_name);
}

char	*expand_str(char *var_value, char **word, int start_var, int end_var)
{
	char	*new_str;
	char	*temp;

	new_str = ft_substr(*word, 0, start_var - 1);
	if (new_str == NULL)
		err_msg(NULL, "expander");
	temp = ft_strjoin_free(new_str, var_value);
	if (temp == NULL)
		err_msg(NULL, "expander");
	new_str = ft_strjoin(temp, *word + end_var);
	if (new_str == NULL)
		err_msg(NULL, "expander");
	free(temp);
	free(*word);
	return (new_str);
}

size_t	expand_variable(char **word, size_t start_var, t_gen *gen)
{
	size_t	end_var;
	char	*var_value;
	char	*var_name;
	size_t	return_value;

	end_var = find_end_of_var(*word, start_var);
	if (end_var == start_var)
		return (start_var);
	var_name = get_var_name(*word + start_var, end_var - start_var);
	var_value = compare_with_env(var_name, gen);
	return_value = start_var + ft_strlen(var_value) - 1;
	free(var_name);
	*word = expand_str(var_value, word, start_var, end_var);
	return (return_value);
}

char	*expand_env(char *word, t_gen *gen, int heredoc, t_quote_mark **head)
{
	size_t	i;
	int		double_quoted;

	i = 0;
	double_quoted = 0;
	while (*(word + i) != '\0')
	{
		if (*(word + i) == '$')
		{
			i = expand_variable(&word, i + 1, gen);
			continue ;
		}
		if (*(word + i) == '\'' && heredoc == 0 && double_quoted == 0)
			i = handle_quotes(word, i, head);
		if (*(word + i) == '"' && heredoc == 0)
		{
			i = handle_quotes(word, i, head);
			double_quoted = (double_quoted + 1) % 2;
		}
		i++;
	}
	return (word);
}
