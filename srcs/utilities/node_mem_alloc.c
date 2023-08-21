/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   node_mem_alloc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/18 15:29:21 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/10 16:45:58 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_rdr	*allocate_mem_redirect(t_rdr *redirect, char *data, \
	t_redirect_type type)
{
	redirect = (t_rdr *)malloc(sizeof(t_rdr));
	if (!redirect)
		return (NULL);
	redirect->type = type;
	redirect->data = data;
	return (redirect);
}

t_cmd	*allocate_mem_cmd_info(t_cmd *exec, char *path, \
	char **arg, t_env *env)
{
	exec = (t_cmd *)malloc(sizeof(t_cmd));
	if (!exec)
		return (NULL);
	exec->path = path;
	exec->arg = arg;
	exec->env = env;
	return (exec);
}
