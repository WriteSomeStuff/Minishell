/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fds.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 12:39:09 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/18 13:17:29 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_restore_output(t_childproc *child)
{
	if (dup2(child->oldout, STDOUT_FILENO) == -1 || close (child->oldout) == -1)
		perror("minishell: ");
}

void	ft_close_fds(t_childproc *child)
{
	int	i;

	i = 0;
	while (i < child->nr_of_cmds - 1)
	{
		if (close(child->pipes[i][0]) == -1 || close(child->pipes[i][1]) == -1)
			perror("minishell: ");
		i++;
	}
}

bool	ft_infile(t_childproc *child, t_rdr *rdr)
{
	child->fdin = open(rdr->data, O_RDONLY);
	if (child->fdin == -1 || dup2(child->fdin, STDIN_FILENO) == -1 || \
		close(child->fdin) == -1)
	{
		child->errorcode = errno;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		return (perror(rdr->data), false);
	}
	return (true);
}

bool	ft_outfile(t_childproc *child, t_rdr *rdr)
{
	if (rdr->type == RDR_APPEND)
		child->fdout = open(rdr->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		child->fdout = open(rdr->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (child->fdout == -1 || dup2(child->fdout, STDOUT_FILENO) == -1 || \
		close(child->fdout) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		return (perror(rdr->data), false);
	}
	return (true);
}

void	ft_check_for_files(t_childproc *child, t_scmd_list *lst)
{
	t_rdr	*rdr;

	while (lst)
	{
		if (lst->type == RDR)
		{
			rdr = lst->data;
			if (rdr->type == RDR_INPUT)
			{
				if (!ft_infile(child, rdr))
					break ;
			}
			if (rdr->type == RDR_OUTPUT || \
				rdr->type == RDR_APPEND)
				ft_outfile(child, rdr);
			if (rdr->type == HERE_DOC)
				ft_heredoc(rdr->data);
		}
		lst = lst->next;
	}
}
// edgecases and testing..
// bash checks all for existing, if not existing infile, error, dont check the rest.
// if all infiles exist, only read out of last one. if all outfiles are created or existing, only send to last one.