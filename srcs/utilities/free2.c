/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/18 12:21:06 by mstegema      #+#    #+#                 */
/*   Updated: 2023/12/18 15:33:15 by mstegema      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freestructs_nodata(t_scmd_list *temp)
{
	t_cmd	*tempcmd;

	tempcmd = temp->data;
	if (temp->type == CMD)
		free(tempcmd->arg);
	free(temp->data);
	temp->data = NULL;
}

void	freescmdlst_nodata(t_scmd_list **lst)
{
	t_scmd_list	*temp;
	t_scmd_list	*next;

	temp = *lst;
	while (temp)
	{
		next = temp->next;
		if (temp->data)
			freestructs_nodata(temp);
		free(temp);
		temp = next;
	}
	*lst = NULL;
}

void	freelst_nodata(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		next = temp->next;
		freescmdlst_nodata((void *)&temp->content);
		free(temp);
		temp = next;
	}
	lst = NULL;
}
