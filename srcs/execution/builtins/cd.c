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

static bool	ft_cd3(t_init *process, char *buffer, size_t i, size_t j)
{
	while (process->env->new_env[j])
	{
		if (ft_strncmp(process->env->new_env[j], "PWD=", 4) == 0)
			break ;
		j++;
	}
	if (!process->env->new_env[j])
	{
		if (!ft_set_pwd(process, process->env, buffer, j))
			return (false);
		return (true);
	}
	free(process->env->new_env[i]);
	if (!ft_set_oldpwd(process, process->env, process->env->new_env[j] + 4, i))
		return (false);
	free(process->env->new_env[j]);
	if (!ft_set_pwd(process, process->env, buffer, j))
		return (false);
	return (true);
}

static bool	ft_cd2(t_init *process, t_cmd *cmd)
{
	char	buffer[MAXPATHLEN];
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cmd->env->new_env[i])
	{
		if (ft_strncmp(cmd->env->new_env[i], "OLDPWD=", 7) == 0)
			break ;
		i++;
	}
	if (!cmd->env->new_env[i])
	{
		if (!ft_set_oldpwd(process, process->env, "no OLDPWD", i))
			return (false);
	}
	if (!ft_cd3(process, buffer, i, j))
		return (false);
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
