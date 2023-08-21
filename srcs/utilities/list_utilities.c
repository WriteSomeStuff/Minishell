/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_utilities.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:25:13 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/18 13:10:49 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_scmd_list	*ft_lstnewscmd(void *data, t_struct_type type)
{
	t_scmd_list	*newnode;

	newnode = malloc(sizeof(t_scmd_list));
	if (!newnode)
		return (NULL);
	newnode->data = data;
	newnode->type = type;
	newnode->next = NULL;
	return (newnode);
}

bool	ft_freelst(t_list *lst)
{
	t_list	*temp;
	t_list	*next;

	if (!lst)
		return (false);
	temp = lst;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	lst = NULL;
	return (false);
}

void	ft_freescmdlst(t_scmd_list *lst)
{
	t_scmd_list	*temp;
	t_scmd_list	*next;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	lst = NULL;
}

void	lst_free(t_list **lst)
{
	t_list	*current;
	t_list	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}
