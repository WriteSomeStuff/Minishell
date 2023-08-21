/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_builtin.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 12:55:14 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/10 16:43:33 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_new_var(t_cmd *info, t_env *env, char *arg)
{
	t_export	exp;
	int			i;

	i = 0;
	ft_check_for_plus(arg);
	exp.arg_len = ft_strlen(arg);
	exp.new_env = malloc((env->env_len + 2) * sizeof(char *));
	if (!exp.new_env)
		ft_throw_error(errno, "add new env malloc failed");
	exp.arg_copy = malloc((exp.arg_len + 1) * sizeof(char));
	if (!exp.arg_copy)
	{
		i = errno;
		free(exp.new_env);
		exp.new_env = NULL;
		ft_throw_error(i, "arg copy malloc failed");
	}
	ft_memcpy(exp.arg_copy, arg, (exp.arg_len + 1));
	ft_fill_env(info, env, &exp, i);
}

static void	ft_overwrite_var(t_cmd *info, char *arg, int c)
{
	int	len;

	if (!ft_strchr(arg, '='))
		return ;
	len = ft_strlen(arg);
	free(info->env->new_env[c]);
	info->env->new_env[c] = NULL;
	info->env->new_env[c] = malloc((len + 1) * sizeof(char));
	if (!info->env->new_env[c])
		ft_throw_error(1, "overwrite var malloc failed");
	ft_memcpy(info->env->new_env[c], arg, (len + 1));
}

static bool	ft_check_export_input(t_cmd *info, t_env *env, char *arg, \
	int j)
{
	int	c;

	c = 0;
	if (arg[j] == '_' && (arg[j + 1] == '=' || arg[j + 1] == '+'))
		return (false);
	if (arg[j] && (ft_isalpha(arg[j]) || (arg[j] == '_' && arg[1])))
	{
		while (ft_isalpha(arg[j]) || ft_isdigit(arg[j]) || arg[j] == '_')
			j++;
		while (env->new_env[c])
		{
			if (!ft_cmpname(arg, env->new_env[c], j) && arg[j] != '+')
				return (ft_overwrite_var(info, arg, c), true);
			c++;
		}
		if (arg[j] == '+' && (arg[j + 1] == '='))
			return (ft_export_append(info, env, arg, j), true);
		else if (arg[j] == '=' || !arg[j])
			return (ft_add_new_var(info, env, arg), true);
	}
	return (false);
}

static void	ft_export_no_args(t_cmd *info)
{
	char	**sortedenv;
	int		len;

	len = 0;
	while (info->env->new_env[len])
		len++;
	sortedenv = malloc((len + 1) * sizeof(char *));
	if (!sortedenv)
		ft_throw_error(errno, "export malloc failed");
	ft_memcpy(sortedenv, info->env->new_env, (len + 1) * sizeof(char *));
	ft_bubble_sort(sortedenv, len);
	ft_write_export(sortedenv);
	free(sortedenv);
	sortedenv = NULL;
}

void	ft_export_builtin(t_cmd *info, t_env *env)
{
	char	**arg;
	int		i;
	int		j;

	i = 1;
	j = 0;
	arg = info->arg;
	if (!arg[i])
	{
		ft_export_no_args(info);
		return ;
	}
	while (arg[i])
	{
		if (!ft_check_export_input(info, env, arg[i], j))
			printf("minishell: export: %c%s\': not a valid identifier\n", \
				'`', arg[i]);
		i++;
	}
}
