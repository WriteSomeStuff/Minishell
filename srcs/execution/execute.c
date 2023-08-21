/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/11 17:02:44 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/16 17:59:13 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief execve returns -1 if it fails and sets errno, 
 * on success it ends the process
 * 
 * to do: think of function to catch errors with the right messages and
 * find the path? Or maybe this is part of parsing?
 */
void	ft_execute(t_cmd *info)
{
	// if builtin, run builtin, else run below.
	if (access(info->path, F_OK) == -1)
		ft_throw_error(errno, "access failed");
	else
	{
		if (execve(info->path, info->arg, info->env->new_env) == -1)
			ft_throw_error(errno, "execve failed");
	}
}
