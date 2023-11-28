/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 12:02:27 by cschabra      #+#    #+#                 */
/*   Updated: 2023/11/28 12:02:50 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_set_oldpwd(t_init *process, t_env *env, char *str, size_t i)
{
	env->new_env[i] = ft_strjoin("OLDPWD=", str);
	if (!env->new_env[i])
		return (ft_throw_error(process, ENOMEM), false);
	return (true);
}

bool	ft_set_pwd(t_init *process, t_env *env, char *buffer, size_t i)
{
	if (!getcwd(buffer, MAXPATHLEN))
		return (ft_throw_error(process, errno), false);
	env->new_env[i] = ft_strjoin("PWD=", buffer);
	if (!env->new_env[i])
		return (ft_throw_error(process, ENOMEM), false);
	return (true);
}
