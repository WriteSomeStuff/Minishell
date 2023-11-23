// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   expander_utils.c                                   :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/08/01 14:23:55 by cschabra      #+#    #+#                 */
// /*   Updated: 2023/08/24 15:21:58 by mstegema      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// //# define ENV_VAR_DELIMITERS "\0 \t\n\r\f\v\""

// int	resolve_quote_index_at_data_index(int data_index, int quote_index)
// {
// 	if (quote_index == -1)
// 		return (data_index);
// 	return (-1);
// }

// // geeft de index terug waarop de environment variabele eindigt.
// int	resolve_environment_variable_length(char *data, int *length)
// {
// 	const char	*delimiters = ENV_VAR_DELIMITERS;
// 	char		*variable_name;
// 	char		*variable_value;

// 	variable_name = str_head(data, delimiters, sizeof(ENV_VAR_DELIMITERS) - 1);
// 	if (variable_name == NULL)
// 		return (-1);
// 	variable_value = getenv(variable_name);
// 	if (variable_value == NULL)
// 		return (free(variable_name), -1);
// 	*length = ft_strlen(variable_value);
// 	free(variable_name);
// 	return (str_length_until(data, delimiters, sizeof(ENV_VAR_DELIMITERS) - 1));
// }

// static char	*get_env_variable_value(char *env_variable_name)
// {
// 	char	*variable_value;

// 	variable_value = getenv(env_variable_name);
// 	if (variable_value == NULL)
// 		variable_value = str_empty();
// 	else
// 		variable_value = ft_strdup(variable_value);
// 	return (variable_value);
// }

// // geeft de index terug waarop de environment variabele eindigt.
// bool	do_env_variable_assignment(char *old_data, \
// char *expanded_data, int *old_data_i, int *expanded_data_i)
// {
// 	const char	*delimiters = ENV_VAR_DELIMITERS;
// 	char		*variable_name;
// 	char		*variable_value;
// 	int			i;

// 	variable_name = str_head(old_data, delimiters, \
// 	sizeof(ENV_VAR_DELIMITERS) - 1);
// 	if (variable_name == NULL)
// 		return (false);
// 	variable_value = get_env_variable_value(variable_name);
// 	i = 0;
// 	while (variable_value[i] != '\0')
// 	{
// 		expanded_data[i] = variable_value[i];
// 		i++;
// 	}
// 	*old_data_i = *old_data_i + str_length_until(old_data, delimiters, \
// 	sizeof(ENV_VAR_DELIMITERS) - 1);
// 	*expanded_data_i = *expanded_data_i + i;
// 	free(variable_name);
// 	free(variable_value);
// 	return (true);
// }

// bool	is_here_doc_argument(t_token *token, t_token *previous_token)
// {
// 	if (previous_token == NULL)
// 		return (false);
// 	if (token->type != CMD_TOKEN)
// 		return (false);
// 	if (previous_token->type != RDR_TOKEN)
// 		return (false);
// 	return (str_equals(previous_token->data, "<<"));
// }
