/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bfranco <bfranco@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 17:35:46 by bfranco       #+#    #+#                 */
/*   Updated: 2023/05/26 17:55:21 by bfranco       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static int	get_size(char **env)
{
	int	i;
	int	size;

	size = ft_arrlen(env);
	i = 0;
	while (env[i])
	{
		if (!ft_envcmp(env[i], "OLDWD="))
		{
			size--;
			break ;
		}
		i++;
	}
	return (size);
}

void	copy_var()


int	env_init(char **env)
{
	int		size;
	char	*new_env;

	size = get_size(env);
	new_env = ft_calloc(size + 1, sizeof(char *));
	if (!new_env)
		return (err_msg(NULL, env init), -1);
	while (env[i])
	{
		if (!ft_envcmp(env[i], "OLDWD="))
			i++;
		else
		{
			copy_var(new_env, env, i);
			i++;
		}
	}
}
