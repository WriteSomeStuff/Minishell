/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:22:00 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/10 16:53:04 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/param.h>
# include <signal.h>
# include <sys/wait.h>
# include <termios.h>

typedef enum e_struct_type
{
	CMD = 0,
	RDR = 1
}	t_struct_type;

typedef enum e_rdr_type
{
	RDR_INPUT,
	RDR_OUTPUT,
	HERE_DOC,
	RDR_APPEND
}	t_rdr_type;

typedef enum e_token_type
{
	CMD_OR_FILE_TOKEN	= 1,
	RDR_TOKEN			= 2,
	PIPE_TOKEN			= 3
}	t_token_type;

typedef struct s_rdr
{
	char		*data;
	t_rdr_type	type;
	bool		expand;
}	t_rdr;

typedef struct s_env
{
	char	**new_env;
	size_t	env_len;
}	t_env;

typedef struct s_cmd
{
	char	*path;
	char	**arg;
	t_env	*env;
	bool	builtin;
}	t_cmd;

typedef struct s_scmd_list
{
	void				*data;
	t_struct_type		type;
	struct s_scmd_list	*next;
}	t_scmd_list;

typedef struct s_export
{
	char	**new_env;
	char	*arg_copy;
	size_t	arg_len;
	size_t	var_len;
	int32_t	name_len;
	char	*new_var;
}	t_export;

typedef struct s_init
{
	pid_t	*ids;
	t_cmd	*cmd;
	int32_t	status;
	int32_t	errorcode;
	size_t	i;
	size_t	nr_of_cmds;
	size_t	pipe_count;
	int32_t	**pipes;
	int32_t	fdin;
	int32_t	fdout;
	int32_t	oldout;
	int32_t	oldin;
	bool	heredoc;
}	t_init;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
}	t_token;

typedef struct s_expand_info
{
	int32_t	i;
	int32_t	j;
	int32_t	dquote_i;
	int32_t	quote_i;
	char	*old_data;
	char	*expanded_data;
}	t_expand_info;

typedef struct s_expand_length_info
{
	int32_t	i;
	int32_t	length;
	int32_t	dquote_i;
	int32_t	quote_i;
	char	*data;
}	t_expand_length_info;

// signals
void		ft_setup_interactive(t_init *process);
void		ft_setup_noninteractive(t_init *process);

// builtins
void		ft_echo_builtin(t_init *process, t_cmd *cmd);
void		ft_cd_builtin(t_init *process, t_cmd *cmd);
void		ft_pwd_builtin(t_init *process);
void		ft_exit_builtin(t_list *lst, t_init *process, t_cmd *cmd);

void		ft_free_str_array(char **arr, char *str);
void		ft_env_builtin(t_init *process, t_cmd *cmd);
bool		ft_copy_env(t_init *process, t_env *env, char **old_env);

void		ft_export_append(t_cmd *cmd, t_env *env, char *arg, int32_t j);

void		ft_add_new_var(t_cmd *cmd, t_env *env, char *arg);
void		ft_export_builtin(t_cmd *cmd);

void		ft_fill_env(t_cmd *cmd, t_env *env, t_export *exp, int32_t i);
void		ft_check_for_plus(char *arg);
int32_t		ft_find_value(char *var);
void		ft_write_export(char **sortedenv);

void		ft_unset_builtin(t_cmd *cmd);

// execution
void		ft_wait_for_last_child(t_init *process);
void		ft_create_child(t_list *lst, t_init *process);

void		ft_restore_old_fd(t_init *process);
bool		ft_store_old_fd(t_init *process);
void		ft_run_builtin(t_list *lst, t_init *process, t_cmd *cmd);
bool		ft_prep(t_list *lst, t_init *process);

void		ft_free_all(t_list *lst, t_env *env);
void		ft_error_export_unset(char *name, char *option);
void		ft_error_exit(t_list *lst, t_init *process, char *str);
void		ft_error_env(int32_t errnr, char *str);
void		ft_throw_error(t_init *process, int32_t errnr);

void		ft_reset_process(t_list *lst, t_init *process);
void		ft_execve(t_cmd *info);
void		ft_executor(t_list *lst, t_init *process);

void		ft_close_fds(t_init *process);
bool		ft_infile(t_init *process, t_rdr *rdr);
bool		ft_outfile(t_init *process, t_rdr *rdr);
bool		ft_check_for_files(t_scmd_list *lst, t_init *process);

bool		ft_heredoc(t_init *process, char *data);

bool		ft_find_path(t_list *lst);

void		ft_free_pipes(int32_t **pipes, int32_t pipe_count);
int32_t		ft_count_pipes(t_list *arglst);
bool		ft_create_pipes(t_init *process, size_t pipe_count);

// expander here
// -----------------------------------------------------------------------------

// lexer
t_token		*is_splitable(t_token *token);
size_t		join_datastr(t_list *tokens, t_list *end);
t_list		*quote_begin(t_list *tokens);
t_list		*quote_end(t_list *tokens);
size_t		join_datastr(t_list *tokens, t_list *end);
t_token		*init_token(const char *str);
t_token		*new_token(const char *data, t_token_type type);
t_list		*tokenisation(const char *user_input);

// parser here
t_list		*parse(t_env *env, const char *user_input);
size_t		count_cmdtokens(t_list **tokens);
bool		is_builtin(t_list **tokens);
char		*complete_input(char *input);

// utilities
int64_t		ft_atollong(t_list *lst, t_init *process, const char *str);

void		ft_bubble_sort(char **sortedenv, int32_t len);

t_scmd_list	*ft_lstnewscmd(void *data, t_struct_type type);
void		ft_freescmdlst(t_scmd_list *lst);
void		scmdlst_add_back(t_scmd_list **scmds, t_scmd_list *new);
void		ft_freelst(t_list *lst);

t_rdr		*ft_allocate_mem_rdr(char *data, t_rdr_type type);
t_cmd		*ft_allocate_mem_cmd(char **arg, t_env *env, bool builtin);

bool		str_equals(char *lhs, char *rhs);
bool		ft_cmpname(const char *s1, const char *s2, int32_t n);

#endif
