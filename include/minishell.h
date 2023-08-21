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

# if defined(WIN32) || defined(_WIN32) 
#  define DIR_SEPARATOR '\\'
# else 
#  define DIR_SEPARATOR '/' 
# endif 

# define ENV_VAR_DELIMITERS "\0 \t\n\r\f\v\""

typedef enum e_struct_type
{
	CMD = 0,

	RDR = 1
}	t_struct_type;

typedef enum e_redirect_type
{
	RDR_INPUT,

	RDR_OUTPUT,

	HERE_DOC,

	RDR_APPEND
}	t_redirect_type;

typedef enum e_token_type
{
	CMD_OR_FILE_TOKEN	= 1,
	OPTION_TOKEN		= 2,
	REDIRECTION_TOKEN	= 3,
	PIPE_TOKEN			= 4
}	t_token_type;

typedef struct s_rdr
{
	char			*data;
	t_redirect_type	type;
}	t_rdr;

typedef struct s_env
{
	char	**new_env;
	int		env_len;
}	t_env;

typedef struct s_cmd
{
	char	*path;
	char	**arg;
	t_env	*env;
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
	int		arg_len;
	int		var_len;
	int		name_len;
	char	*new_var;
}	t_export;

typedef struct s_childproc
{
	pid_t		*ids;
	t_cmd		*cmd;
	int			status;
	int			errorcode;
	int			i;
	int			nr_of_cmds;
	int			pipe_count;
	int			**pipes;
	int			fdin;
	int			fdout;
	int			oldout;
	t_scmd_list	*temp;
}	t_childproc;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
}	t_token;

typedef struct s_expand_info
{
	int		i;
	int		j;
	int		dquote_i;
	int		quote_i;
	char	*old_data;
	char	*expanded_data;
}	t_expand_info;

typedef struct s_expand_length_info
{
	int		i;
	int		length;
	int		dquote_i;
	int		quote_i;
	char	*data;
}	t_expand_length_info;

void			ft_test_child(t_env *env, char **argv);
// -----------------------------------------------------------------------------
void			ft_echo_builtin(t_cmd *info);
void			ft_cd_builtin(t_cmd *info);
void			ft_pwd_builtin(void);
void			ft_exit_builtin(t_cmd *info);

void			ft_free_env(char **new_env, char *arg_copy);
void			ft_env_builtin(t_cmd *info);
void			ft_copy_env(t_env *env, char **old_env);

void			ft_export_append(t_cmd *info, t_env *env, char *arg, \
	int j);

void			ft_add_new_var(t_cmd *info, t_env *env, char *arg);
void			ft_export_builtin(t_cmd *info, t_env *env);

void			ft_fill_env(t_cmd *info, t_env *env, t_export *exp, \
	int i);
void			ft_check_for_plus(char *arg);
int				ft_find_value(char *var);
void			ft_write_export(char **sortedenv);

void			ft_unset_builtin(t_cmd *info);
// -----------------------------------------------------------------------------
void			ft_create_child(t_list *lst);

bool			ft_prep(t_childproc *child, t_list *lst);

void			ft_free_all(void);
void			ft_throw_error(int errornr, char *errormessage);

void			ft_execute(t_cmd *info);

void			ft_restore_output(t_childproc *child);
void			ft_close_fds(t_childproc *child);
bool			ft_infile(t_childproc *child, t_rdr *which);
bool			ft_outfile(t_childproc *child, t_rdr *which);
void			ft_check_for_files(t_childproc *child, t_scmd_list *lst);

bool			ft_heredoc(char *data);

void			ft_free_pipes(int **pipes, int pipe_count);
int				ft_count_pipes(t_list *arglst);
int				**ft_create_pipes(int **pipes, int pipe_count);
// -----------------------------------------------------------------------------
long long int	ft_atollong(const char *str);

void			ft_bubble_sort(char **sortedenv, int len);

t_scmd_list		*ft_lstnewscmd(void *data, t_struct_type type);
bool			ft_freelst(t_list *lst);
void			ft_freescmdlst(t_scmd_list *lst);

t_rdr			*allocate_mem_redirect(t_rdr *redirect, char *data, \
	t_redirect_type type);
t_cmd			*allocate_mem_cmd_info(t_cmd *cmd, char *path, \
	char **arg, t_env *env);
// -----------------------------------------------------------------------------
int				str_array_length(char **str_array);
void			str_array_free(char **str_array);

bool			str_equals(char *lhs, char *rhs);
bool			str_contains_length(const char *str, int length, char c);
bool			str_contains_any(const char *str, const char *chars);
int				str_length_until(char *str, const char *delimiters, int delimiter_count);
bool			ft_cmpname(const char *s1, const char *s2, int n);
char			*str_head(char *str, const char *delimiters, int delimiter_count);
char			*str_join_sep(char *lhs, char *rhs, char c);
char			*str_empty(void);

t_token			*token_new(char *data, t_token_type type);
t_token			*str_to_token(char *str, t_token *previous_token);
bool 			is_quoted_token_end(t_token *token);
bool 			is_quoted_token_start(t_token *token);
void			token_free(void *token);
void			ft_put_token_lst(t_list *lst);

int				token_arr_length(t_token **tokens);

void			free_env(t_env *env);
void			lst_free(t_list **lst);

t_list			*read_tokens_from_command_line(char *command_line);

int				resolve_quote_index_at_data_index(int data_index, int quote_index);
int				resolve_environment_variable_length(char *data, int *length);
bool			do_env_variable_assignment(char *old_data, \
char 	*expanded_data, int *old_data_i, int *expanded_data_i);

bool			expand_tokens(t_list *tokens);
bool			init_expand_info(t_expand_info *info, char *old_data, int expand_data_length);
bool			expand_data_at(t_expand_info info, char c);
bool			check_env_variable_assignment(t_expand_info *info);
void			check_quote_index_at_data_index(t_expand_info *info);
void			check_dquote_index_at_data_index(t_expand_info *info);
bool			is_here_doc_argument(t_token *token, t_token *previous_token);

void			init_expand_length_info(t_expand_length_info *info, char *data);
bool			expand_length_data_at(t_expand_length_info info, char c);
void			update_quote(t_expand_length_info *info);
void			update_dquote(t_expand_length_info *info);

bool			token_arr_assert_data(t_token **token_arr, char *data[]);
bool			token_arr_assert_type(t_token **token_arr, t_token_type types[]);

#endif