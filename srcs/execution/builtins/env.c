/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 11:18:44 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/14 14:23:51 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_builtin(t_init *process, t_cmd *cmd)
{
	int32_t	i;

	i = 0;
	if (str_equals("env", cmd->arg[0]))
	{
		if (cmd->arg[1])
		{
			process->errorcode = 127;
			ft_error_env(ENOENT, cmd);
			return ;
		}
		while (cmd->env->new_env[i])
		{
			if (ft_strchr(cmd->env->new_env[i], '='))
				printf("%s\n", cmd->env->new_env[i]);
			i++;
		}
	}
	process->errorcode = 0;
}

bool	ft_copy_env(t_init *process, t_env *env, char **old_env)
{
	int32_t	i;
	size_t	str_len;

	i = 0;
	env->env_len = 0;
	while (old_env[env->env_len])
		env->env_len++;
	env->new_env = malloc((env->env_len + 1) * sizeof(char *));
	if (!env->new_env)
		return (ft_throw_error(process, errno), false);
	while (old_env[i])
	{
		str_len = ft_strlen(old_env[i]);
		env->new_env[i] = malloc((str_len + 1) * sizeof(char));
		if (!env->new_env[i])
		{
			ft_free_str_array(env->new_env, NULL);
			return (ft_throw_error(process, ENOMEM), false);
		}
		ft_memmove(env->new_env[i], old_env[i], (str_len + 1));
		i++;
	}
	env->new_env[i] = NULL;
	return (true);
}
