/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 14:11:39 by cschabra      #+#    #+#                 */
/*   Updated: 2023/11/09 23:03:34 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(rdr);
	}
	else if (temp->type == CMD)
	{
		cmd = temp->data;
		ft_free_str_array(cmd->arg, cmd->path);
		free(cmd);
	}
}

void	freescmdlst(t_scmd_list **lst)
{
	t_scmd_list	*temp;
	t_scmd_list	*next;

	temp = *lst;
	while (temp)
	{
		next = temp->next;
		ft_free_structs(temp);
		free(temp);
		temp = next;
	}
	*lst = NULL;
}

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
		freescmdlst((void *)&temp->content);
		free(temp);
		temp = next;
	}
	lst = NULL;
}

void	free_tokenlst(t_list *tokens)
{
	t_list	*temp;
	t_list	*next;
	t_token	*token;

	if (!tokens)
		return ;
	temp = tokens;
	while (temp)
	{
		next = temp->next;
		token = temp->content;
		if (token)
			free(token);
		free(temp);
		temp = next;
	}
	tokens = NULL;
}
