/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 14:49:53 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/07 12:59:33 by cheyennesch   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_check_unset_input(char *arg)
{
	int32_t	j;

	j = 0;
	if (arg[j] && (ft_isalpha(arg[j]) || (arg[j] == '_' && arg[1])))
	{
		while (ft_isalpha(arg[j]) || ft_isdigit(arg[j]) || arg[j] == '_')
			j++;
		if (!arg[j])
			return (true);
	}
	ft_error_export_unset("unset", arg);
	return (false);
}

static void	ft_find_unset_arg(char **env, char *arg, int32_t len)
{
	char	*temp;
	int32_t	j;

	j = 0;
	while (env[j])
	{
		if (!ft_cmpname(arg, env[j], len) && env[j][len] == '=')
		{
			temp = env[j];
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			free(temp);
			temp = NULL;
			env[j] = NULL;
			break ;
		}
		j++;
	}
}

void	ft_unset_builtin(t_cmd *cmd)
{
	int32_t	i;
	size_t	len;
	char	**arg;
	char	**env;

	i = 1;
	arg = cmd->arg;
	env = cmd->env->new_env;
	if (!arg[i])
		return ;
	while (arg[i])
	{
		if (!ft_check_unset_input(arg[i]))
		{
			i++;
			continue ;
		}
		len = ft_strlen(arg[i]);
		ft_find_unset_arg(env, arg[i], len);
		i++;
	}
}
