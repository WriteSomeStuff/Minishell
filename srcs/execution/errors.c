/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 13:31:37 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/07 16:33:21 by cheyennesch   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_export_unset(char *name, char *option)
{
	ft_putstr_fd("BabyBash: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(option, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
}

void	ft_error_exit(t_list *lst, t_init *process, char *str)
{
	ft_putstr_fd("exit\nBabyBash: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	rl_clear_history();
	ft_reset_process(lst, process);
	exit(255);
}

void	ft_error_env(int32_t errnr, char *str)
{
	char	*newstr;

	newstr = ft_strjoin(": ", str);
	errno = errnr;
	perror(newstr);
	free(newstr);
}

void	ft_throw_error(t_init *process, int32_t errnr)
{
	errno = errnr;
	perror("BabyBash");
	process->errorcode = 1;
}
