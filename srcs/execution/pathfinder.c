/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pathfinder.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/01 16:57:17 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/07 13:00:36 by cheyennesch   ########   odam.nl         */
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
		if (!cmdpath)
			return (false);
		if (access(cmdpath, F_OK) == 0)
		{
			cmd->path = cmdpath;
			break ;
		}
		free(cmdpath);
		i++;
	}
	return (true);
}

static bool	ft_find_path2(t_scmd_list *tempscmd)
{
	t_cmd	*tempcmd;
	char	**path;
	int32_t	i;

	i = 0;
	tempcmd = tempscmd->data;
	if (tempcmd->builtin == false)
	{
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

bool	ft_find_path(t_list *lst)
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
				if (!ft_find_path2(tempscmd))
					return (false);
			}
			tempscmd = tempscmd->next;
		}
		temp = temp->next;
	}
	return (true);
}
