/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 12:02:27 by cschabra      #+#    #+#                 */
/*   Updated: 2023/12/19 16:50:34 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_set_oldpwd(t_init *process, t_env *env, char *str, size_t i)
{
	char	*temp;

	temp = ft_strjoin("OLDPWD=", str);
	if (!temp)
		return (ft_throw_error(process, ENOMEM), false);
	free(env->new_env[i]);
	env->new_env[i] = temp;
	return (true);
}

bool	ft_set_pwd(t_init *process, t_env *env, char *buffer, size_t i)
{
	char	*temp;

	if (!getcwd(buffer, MAXPATHLEN))
		return (ft_throw_error(process, errno), true);
	temp = ft_strjoin("PWD=", buffer);
	if (!temp)
		return (ft_throw_error(process, ENOMEM), false);
	free(env->new_env[i]);
	env->new_env[i] = temp;
	return (true);
}
