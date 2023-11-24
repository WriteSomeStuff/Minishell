/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 11:14:27 by cschabra      #+#    #+#                 */
/*   Updated: 2023/11/24 15:45:43 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_env(t_init *process, t_cmd *cmd, t_export *exp, size_t i)
{
	while (cmd->env->new_env[i])
	{
		exp->var_len = ft_strlen(cmd->env->new_env[i]);
		exp->new_env[i] = malloc((exp->var_len + 1) * sizeof(char));
		if (!exp->new_env[i])
		{
			ft_throw_error(process, errno);
			ft_free_str_array(exp->new_env, exp->arg_copy);
			process->must_exit = true;
			return ;
		}
		ft_memcpy(exp->new_env[i], cmd->env->new_env[i], (exp->var_len + 1));
		i++;
	}
	exp->new_env[i] = exp->arg_copy;
	exp->new_env[i + 1] = NULL;
	ft_free_str_array(cmd->env->new_env, NULL);
	cmd->env->new_env = exp->new_env;
	cmd->env->env_len++;
}

void	ft_check_for_plus(char *arg)
{
	size_t	i;

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
	int32_t	i;
	char	*name;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		return (perror("BabyBash"), NULL);
	name[i--] = '\0';
	while (i + 1)
	{
		name[i] = var[i];
		i--;
	}
	return (name);
}

size_t	ft_find_value(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (-1);
	return (i + 1);
}

bool	ft_write_export(char **sortedenv)
{
	char	*name;
	int32_t	i;
	int32_t	value;

	i = 0;
	while (sortedenv[i])
	{
		name = ft_find_name(sortedenv[i]);
		if (!name)
			return (false);
		value = ft_find_value(sortedenv[i]);
		if (value == -1)
			printf("declare -x %s\n", name);
		else
			printf("declare -x %s=\"%s\"\n", name, &sortedenv[i][value]);
		free(name);
		name = NULL;
		i++;
	}
	return (true);
}
