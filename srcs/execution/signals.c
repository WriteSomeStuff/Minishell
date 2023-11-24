/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/25 14:20:13 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/07 16:18:25 by cschabra   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_interactive_handler(int32_t signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ft_noninteractive_handler(int32_t signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	if (signum == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", STDIN_FILENO);
}

bool	ft_setup_noninteractive(t_init *process)
{
	struct termios		term;

	if (tcgetattr(0, &term) == -1)
	{
		ft_throw_error(process, errno);
		return (false);
	}
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(0, 0, &term) == -1 || \
		signal(SIGINT, ft_noninteractive_handler) == SIG_ERR || \
		signal(SIGQUIT, ft_noninteractive_handler) == SIG_ERR)
	{
		ft_throw_error(process, errno);
		return (false);
	}
	if (g_signal == SIGINT)
	{
		process->errorcode = 130;
		g_signal = 0;
	}
	return (true);
}

bool	ft_setup_interactive(t_init *process)
{
	struct termios		term;

	if (tcgetattr(0, &term) == -1)
	{
		ft_throw_error(process, errno);
		return (false);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &term) == -1 || \
		signal(SIGINT, ft_interactive_handler) == SIG_ERR || \
		signal(SIGQUIT, ft_interactive_handler) == SIG_ERR)
	{
		ft_throw_error(process, errno);
		return (false);
	}
	return (true);
}
