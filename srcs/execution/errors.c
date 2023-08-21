/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:31:37 by cschabra      #+#    #+#                 */
/*   Updated: 2023/06/26 12:42:25 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(void)
{
	// free all malloced things:
	// env, data in nodes, nodes from list, list itself, pipes, child->ids
	return ;
}

void	ft_throw_error(int errornr, char *errormessage)
{
	int	errnr;

	errnr = errornr;
	perror(errormessage);
	exit(errnr);
}
