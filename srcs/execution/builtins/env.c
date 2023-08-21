/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 11:18:44 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/10 16:49:33 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(char **new_env, char *arg_copy)
{
	int	i;

	i = 0;
	if (new_env)
	{
		while (new_env[i])
		{
			free(new_env[i]);
			new_env[i++] = NULL;
		}
		free(new_env);
		new_env = NULL;
	}
	if (arg_copy)
	{
		free(arg_copy);
		arg_copy = NULL;
	}
}

void	ft_env_builtin(t_cmd *info)
{
	int	i;

	i = 0;
	if (str_equals("env", info->arg[0]))
	{
		if (info->arg[1])
			ft_throw_error(22, "env failed");
		while (info->env->new_env[i])
		{
			if (str_contains_any(info->env->new_env[i], "="))
				printf("%s\n", info->env->new_env[i]);
			i++;
		}
	}
}

void	ft_copy_env(t_env *env, char **old_env)
{
	int	i;
	int	var_len;

	i = 0;
	env->env_len = 0;
	while (old_env[env->env_len])
		env->env_len++;
	env->new_env = malloc((env->env_len + 1) * sizeof(char *));
	if (!env->new_env)
		ft_throw_error(errno, "add new env malloc failed");
	while (old_env[i])
	{
		var_len = ft_strlen(old_env[i]);
		env->new_env[i] = malloc((var_len + 1) * sizeof(char));
		if (!env->new_env[i])
		{
			i = errno;
			ft_free_env(env->new_env, NULL);
			ft_throw_error(i, "new env while loop malloc failed");
		}
		ft_memcpy(env->new_env[i], old_env[i], (var_len + 1));
		i++;
	}
	env->new_env[i] = NULL;
}
