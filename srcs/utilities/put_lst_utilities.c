/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_lst_utilities.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:25:23 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/18 13:59:55 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_command_lst(t_list *lst)
{
	t_list	*current;
	t_cmd	*cmd;
	int		count;

	current = lst;
	count = 0;
	while (current != NULL)
	{
		count++;
		cmd = (t_cmd *)current->content;
		printf("cmd %d\n", count);
		current = current->next;
	}
}

void	ft_put_token_lst(t_list *lst)
{
	t_list	*current;
	t_token	*token;
	int		count;

	current = lst;
	count = 0;
	while (current != NULL)
	{
		count++;
		token = (t_token *)current->content;
		current = current->next;
	}
}
