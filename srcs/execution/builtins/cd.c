/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/24 16:37:53 by cschabra      #+#    #+#                 */
/*   Updated: 2023/11/24 19:13:07 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_cd3(t_init *process, char *current_path, size_t i, size_t j)
{
	while (process->env->new_env[j])
	{
		if (ft_strncmp(process->env->new_env[j], "OLDPWD=", 7) == 0)
		{
			free(process->env->new_env[j]);
			process->env->new_env[j] = ft_strjoin("OLDPWD=", \
				process->env->new_env[i] + 4);
			if (!process->env->new_env[j])
				return (ft_throw_error(process, ENOMEM), false);
			free(process->env->new_env[i]);
			process->env->new_env[i] = ft_strjoin("PWD=", current_path);
			if (!process->env->new_env[i])
				return (ft_throw_error(process, ENOMEM), false);
			return (true);
		}
		j++;
	}
	process->env->new_env[j] = ft_strjoin("OLDPWD=", \
		process->env->new_env[i] + 4);
	if (!process->env->new_env[j])
		return (ft_throw_error(process, ENOMEM), false);
	return (true);
}

static bool	ft_cd2(t_init *process, t_cmd *cmd)
{
	char	current_path[MAXPATHLEN];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (getcwd(current_path, MAXPATHLEN) == NULL)
		return (ft_throw_error(process, errno), true);
	while (cmd->env->new_env[i])
	{
		if (ft_strncmp(cmd->env->new_env[i], "PWD=", 4) == 0)
		{
			if (!ft_cd3(process, current_path, i, j))
				return (false);
			return (true);
		}
		i++;
	}
	cmd->env->new_env[i] = ft_strjoin("PWD=", current_path);
	if (!cmd->env->new_env[i])
		return (ft_throw_error(process, ENOMEM), false);
	return (true);
}

void	ft_cd_builtin(t_init *process, t_cmd *cmd, size_t i)
{
	process->errorcode = 0;
	if (!cmd->arg[1])
	{
		while (cmd->env->new_env[i])
		{
			if (ft_strncmp(cmd->env->new_env[i], "HOME=", 5) == 0)
			{
				if (chdir(cmd->env->new_env[i] + 5) == -1)
				{
					ft_throw_error(process, errno);
					return ;
				}
			}
			i++;
		}
	}
	else if (chdir(cmd->arg[1]) == -1)
	{
		ft_throw_error(process, errno);
		return ;
	}
	if (!ft_cd2(process, cmd))
		process->must_exit = true;
}
