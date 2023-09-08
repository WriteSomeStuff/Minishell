/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/31 11:14:27 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/07 17:25:03 by cheyennesch   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_env(t_cmd *cmd, t_env *env, t_export *exp, int32_t i)
{
	while (cmd->env->new_env[i])
	{
		exp->var_len = ft_strlen(cmd->env->new_env[i]);
		exp->new_env[i] = malloc((exp->var_len + 1) * sizeof(char));
		if (!exp->new_env[i])
		{
			perror("BabyBash"); // set errorcode to 1
			ft_free_str_array(exp->new_env, exp->arg_copy);
			return ;
		}
		ft_memcpy(exp->new_env[i], cmd->env->new_env[i], (exp->var_len + 1));
		i++;
	}
	exp->new_env[i] = exp->arg_copy;
	exp->new_env[i + 1] = NULL;
	ft_free_str_array(env->new_env, NULL);
	env->new_env = exp->new_env;
	env->env_len++;
	cmd->env->new_env = env->new_env;
}

void	ft_check_for_plus(char *arg)
{
	int32_t	i;

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
		return (perror("BabyBash"), NULL); // set errorcode to 1
	name[i--] = '\0';
	while (i + 1)
	{
		name[i] = var[i];
		i--;
	}
	return (name);
}

int32_t	ft_find_value(char *var)
{
	int32_t	i;
	int32_t	c;

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
	char	*name;
	int32_t	i;
	int32_t	value;

	i = 0;
	while (sortedenv[i])
	{
		name = ft_find_name(sortedenv[i]);
		if (!name)
			return ;
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
