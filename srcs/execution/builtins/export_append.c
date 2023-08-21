/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_append.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/12 18:11:54 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/10 16:43:33 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_append_to_var(t_cmd *info, t_export *exp, char *arg, int j)
{
	int	add_from_pos;

	add_from_pos = ft_find_value(arg);
	exp->arg_len = ft_strlen(info->env->new_env[j]);
	exp->var_len = exp->arg_len + ft_strlen(&arg[add_from_pos]);
	exp->new_var = ft_strjoin(info->env->new_env[j], \
		&arg[exp->name_len + 2]);
	free(info->env->new_env[j]);
	info->env->new_env[j] = NULL;
	info->env->new_env[j] = exp->new_var;
}

void	ft_export_append(t_cmd *info, t_env *env, char *arg, int j)
{
	t_export	exp;

	exp.name_len = j;
	j = 0;
	while (env->new_env[j])
	{
		if (!ft_cmpname(env->new_env[j], arg, exp.name_len))
		{
			ft_append_to_var(info, &exp, arg, j);
			return ;
		}
		j++;
	}
	ft_add_new_var(info, env, arg);
}
