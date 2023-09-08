/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtint32_test.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/04 14:48:42 by cschabra      #+#    #+#                 */
/*   Updated: 2023/09/04 14:30:45 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

// to test exit i have to return the exit function..
void	ft_test_exit(t_env *env)
{
	t_cmd	*cmd;
	char	**arg;
	int32_t		j;

	j = 0;
	arg = ft_split("exit 9223372036854775806", ' ');
	cmd = NULL;
	cmd = ft_allocate_mem_cmd(arg, env, true);
	ft_exit_builtin(cmd);
	while (arg[j])
		free(arg[j++]);
	free(arg);
	free(cmd);
}

void	ft_test_echo(t_env *env)
{
	t_cmd	*cmd;
	char	**arg;
	int32_t		i;

	i = 0;
	arg = ft_split("echo -n -n blep -n -n -n", ' ');
	cmd = NULL;
	cmd = ft_allocate_mem_cmd(arg, env, true);
	ft_echo_builtin(cmd);
	while (arg[i])
		free(arg[i++]);
	free(arg);
	free(cmd);
}

void	ft_test_cd(t_env *env)
{
	t_cmd	*cmd;
	char	**arg;
	int32_t		i;

	i = 0;
	arg = ft_split("cd ../Minishell/srcs", ' ');
	cmd = NULL;
	cmd = ft_allocate_mem_cmd(arg, env, true);
	ft_cd_builtin(cmd);
	while (arg[i])
		free(arg[i++]);
	free(arg);
	free(cmd);
}

void	ft_test_pwd(void)
{
	ft_pwd_builtin();
}

void	ft_test_env(t_env *env)
{
	t_cmd	*cmd;
	char	**arg;
	int32_t		i;

	i = 0;
	arg = ft_split("env", ' ');
	cmd = NULL;
	cmd = ft_allocate_mem_cmd(arg, env, true);
	ft_env_builtin(cmd);
	while (arg[i])
		free(arg[i++]);
	free(arg);
	free(cmd);
}

void	ft_test_export(t_env *env)
{
	t_cmd	*cmd;
	char	**arg;
	t_cmd	*cmd2;
	char	**arg2;
	int32_t		i;

	i = 0;
	cmd = NULL;
	arg = ft_split("export _+= _= _ __=ok _s0_=kek _s0=ok s0_=ok TERM USER+= here=replaceme here=ok this=a b c noexist+=ok b=ok test=ap/pen+dhere test+=sumfin = 2test=sumfin", ' ');
	cmd = ft_allocate_mem_cmd(arg, env, true);
	ft_export_builtin(cmd);
	while (arg[i])
		free(arg[i++]);
	free(arg);
	arg2 = ft_split("export", ' ');
	cmd2 = NULL;
	cmd2 = ft_allocate_mem_cmd(arg2, env, true);
	ft_export_builtin(cmd2);
	i = 0;
	while (arg2[i])
		free(arg2[i++]);
	free(arg2);
	free(cmd2);
	arg = ft_split("env", ' ');
	cmd->arg = arg;
	ft_env_builtin(cmd);
	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
	free(cmd);
}

void	ft_test_unset(t_env *env)
{
	t_cmd	*cmd;
	char	**arg;
	t_cmd	*cmd2;
	char	**arg2;
	int32_t		i;

	i = 0;
	cmd = NULL;
	arg = ft_split("unset _ __ _0test PATH TERM 1test HOME thismust.error=something test=error test+=error", ' ');
	cmd = ft_allocate_mem_cmd(arg, env, true);
	ft_unset_builtin(cmd);
	while (arg[i])
		free(arg[i++]);
	free(arg);
	arg2 = ft_split("env", ' ');
	cmd2 = NULL;
	cmd2 = ft_allocate_mem_cmd(arg2, env, true);
	ft_env_builtin(cmd2);
	i = 0;
	while (arg2[i])
		free(arg2[i++]);
	free(arg2);
	free(cmd);
	free(cmd2);
}

// static void	ft_leaks(void)
// {
// 	system("leaks -q minishell_test");
// }

// int32_t	main(int32_t argc, char **argv, char **envp)
// {
// 	// char	buffer[MAXPATHLEN];
// 	t_env	env;
// 	int32_t		i;

// 	atexit(ft_leaks);
// 	argc = 0;
// 	argv = 0;
// 	i = 0;
// 	ft_copy_env(&env, envp);
// 	// while (env.new_env[i])
// 	// 	printf("%s\n", env.new_env[i++]);
// 	// puts("-----------------------------------------------------");
// 	// ft_test_env(&env);
// 	// ft_test_export(&env);
// 	// ft_test_unset(&env);
// 	// ft_test_exit(&env);
// 	// ft_test_echo(&env);

// 	// if (getcwd(buffer, MAXPATHLEN) == NULL)
// 	// 	ft_throw_error(errno, "pwd failed");
// 	// ft_putendl_fd(buffer, STDOUT_FILENO);
// 	// ft_test_cd(&env);
// 	// if (getcwd(buffer, MAXPATHLEN) == NULL)
// 	// 	ft_throw_error(errno, "pwd failed");
// 	// ft_putendl_fd(buffer, STDOUT_FILENO);

// 	// ft_test_pwd();
// 	ft_free_str_array(env.new_env, NULL);
// 	// while (1);
// }
