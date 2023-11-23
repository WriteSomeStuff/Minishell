/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pathfinder.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 16:57:17 by cschabra      #+#    #+#                 */
/*   Updated: 2023/11/08 18:20:07 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_try_paths(char **path, t_cmd *cmd)
{
	int32_t	i;
	char	*cmdpath;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			return (false);
		cmdpath = ft_strjoin(temp, cmd->arg[0]);
		free(temp);
		temp = NULL;
		if (!cmdpath)
			return (false);
		if (access(cmdpath, F_OK) == 0)
		{
			cmd->path = cmdpath;
			break ;
		}
		free(cmdpath);
		cmdpath = NULL;
		i++;
	}
	return (true);
}

static bool	ft_is_path(t_init *process, t_cmd *cmd)
{
	char	*arg_copy;
	int		len;

	len = ft_strlen(cmd->arg[0]) + 1;
	if (cmd->arg[0][0] == '/' || cmd->arg[0][0] == '.')
	{
		arg_copy = malloc(sizeof(char) * len);
		if (!arg_copy)
		{
			process->must_exit = true;
			return (false);
		}
		ft_memmove(arg_copy, cmd->arg[0], len);
		cmd->path = arg_copy;
		return (true);
	}
	return (false);
}

static bool	ft_find_path2(t_init *process, t_scmd_list *tempscmd)
{
	t_cmd	*tempcmd;
	char	**path;
	int32_t	i;

	i = 0;
	tempcmd = tempscmd->data;
	if (tempcmd->builtin == false)
	{
		if (ft_is_path(process, tempcmd))
			return (true);
		while (tempcmd->env->new_env[i])
		{
			if (ft_strncmp(tempcmd->env->new_env[i], "PATH=", 5) == 0)
			{
				path = ft_split(tempcmd->env->new_env[i] + 5, ':');
				if (!path)
					return (false);
			}
			i++;
		}
		if (!ft_try_paths(path, tempcmd))
			return (ft_free_str_array(path, NULL), false);
		return (ft_free_str_array(path, NULL), true);
	}
	return (true);
}

bool	ft_find_path(t_list *lst, t_init *process)
{
	t_list		*temp;
	t_scmd_list	*tempscmd;

	temp = lst;
	while (temp)
	{
		tempscmd = temp->content;
		while (tempscmd)
		{
			if (tempscmd->type == CMD)
			{
				if (!ft_find_path2(process, tempscmd) || process->must_exit)
					return (ft_throw_error(process, ENOMEM), false);
			}
			tempscmd = tempscmd->next;
		}
		temp = temp->next;
	}
	return (true);
}
