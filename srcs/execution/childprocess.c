/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   childprocess.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 13:32:13 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/16 17:55:31 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_store_output(t_childproc *child)
{
	child->oldout = dup(STDOUT_FILENO);
	if (child->oldout == -1)
	{
		ft_putstr_fd("minishell: old fd dup failed.", STDERR_FILENO);
		return (false);
	}
	return (true);
}

static void	ft_wait_for_last_child(t_childproc *child)
{
	ft_close_fds(child);
	waitpid(child->ids[child->nr_of_cmds - 1], &child->status, 0);
	if (WIFEXITED(child->status))
		child->errorcode = WEXITSTATUS(child->status); // this must be exit value
	else
		child->errorcode = -1; // is this needed?
	free(child->ids);
	child->ids = NULL;
	ft_free_pipes(child->pipes, child->pipe_count);
}

static void	ft_child_process(t_childproc *child)
{
	if ((child->i == 0 && child->nr_of_cmds > 1) || \
		(child->i != (child->nr_of_cmds - 1)))
	{
		if (dup2(child->pipes[child->i][1], STDOUT_FILENO) == -1)
			ft_throw_error(errno, "minishell: "); // free all and exit
	}
	if (child->i != 0)
	{
		if (dup2(child->pipes[child->i - 1][0], STDIN_FILENO) == -1)
			ft_throw_error(errno, "minishell: "); // free all and exit
	}
	ft_close_fds(child);
	ft_execute(child->cmd);
}

static void	ft_find_cmd(t_childproc *child, t_scmd_list *lst)
{
	while (lst)
	{
		if (lst->type == CMD)
		{
			child->cmd = lst->data;
			break ;
		}
		lst = lst->next;
	}
	if (!lst)
	{
		child->cmd = NULL;
	}
}

void	ft_create_child(t_list *lst)
{
	t_childproc	child;

	if (!ft_prep(&child, lst) || !ft_store_output(&child))
		return ;
	while (lst)
	{
		ft_find_cmd(&child, lst->content);
		ft_check_for_files(&child, lst->content); // make sure this checks if all infiles exist & make all outfiles, write to last one only.
		if (child.cmd && !child.errorcode)
		{
			child.ids[child.i] = fork();
			if (child.ids[child.i] == -1)
			{
				perror("minishell: ");
				break ;
			}
			if (child.ids[child.i] == 0)
				ft_child_process(&child);
			child.i++;
		}
		lst = lst->next;
	}
	if (child.oldout != -1)
		ft_restore_output(&child);
	ft_wait_for_last_child(&child);
}
