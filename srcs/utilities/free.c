/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 14:11:39 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/07 13:02:51 by cheyennesch   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freelst(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		next = temp->next;
		ft_freescmdlst(temp->content);
		free(temp);
		temp = next;
	}
	lst = NULL;
}

void	ft_free_str_array(char **arr, char *str)
{
	int32_t	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
		arr = NULL;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

static void	ft_free_structs(t_scmd_list *temp)
{
	t_rdr	*rdr;
	t_cmd	*cmd;

	if (temp->type == RDR)
	{
		rdr = temp->data;
		if (rdr->data)
		{
			free(rdr->data);
			rdr->data = NULL;
		}
	}
	else if (temp->type == CMD)
	{
		cmd = temp->data;
		ft_free_str_array(cmd->arg, cmd->path);
	}
}

void	ft_freescmdlst(t_scmd_list *lst)
{
	t_scmd_list	*temp;
	t_scmd_list	*next;

	temp = lst;
	while (temp)
	{
		next = temp->next;
		ft_free_structs(temp);
		free(temp);
		temp = next;
	}
	lst = NULL;
}

void	ft_free_all(t_list *lst, t_env *env)
{
	ft_freelst(lst);
	ft_free_str_array(env->new_env, NULL);
	rl_clear_history();
}
