/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 11:14:27 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/10 16:46:43 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_env(t_cmd *info, t_env *env, t_export *exp, int i)
{
	while (info->env->new_env[i])
	{
		exp->var_len = ft_strlen(info->env->new_env[i]);
		exp->new_env[i] = malloc((exp->var_len + 1) * sizeof(char));
		if (!exp->new_env[i])
		{
			i = errno;
			ft_free_env(exp->new_env, exp->arg_copy);
			ft_throw_error(i, "new env while loop malloc failed");
		}
		ft_memcpy(exp->new_env[i], info->env->new_env[i], (exp->var_len + 1));
		i++;
	}
	exp->new_env[i] = exp->arg_copy;
	exp->new_env[i + 1] = NULL;
	ft_free_env(env->new_env, NULL);
	env->new_env = exp->new_env;
	env->env_len++;
	info->env->new_env = env->new_env;
}

void	ft_check_for_plus(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+')
		{
			while (arg[i])
			{
				arg[i] = arg[i + 1];
				i++;
			}
			return ;
		}
		i++;
	}
}

static char	*ft_find_name(char *var)
{
	int		i;
	char	*name;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		return (NULL);
	name[i--] = '\0';
	while (i + 1)
	{
		name[i] = var[i];
		i--;
	}
	return (name);
}

int	ft_find_value(char *var)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (-1);
	return (i + 1);
}

void	ft_write_export(char **sortedenv)
{
	int		i;
	char	*name;
	int		value;

	i = 0;
	while (sortedenv[i])
	{
		name = ft_find_name(sortedenv[i]);
		if (!name)
			ft_throw_error(1, "find name in write export failed");
		value = ft_find_value(sortedenv[i]);
		if (value == -1)
			printf("declare -x %s\n", name);
		else
			printf("declare -x %s=\"%s\"\n", name, &sortedenv[i][value]);
		free(name);
		name = NULL;
		i++;
	}
}
