// /* ************************************************************************** */
// /*							                                                  */
// /*                                                        ::::::::            */
// /*   expander.c                                         :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: mstegema <mstegema@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/08/30 12:08:20 by mstegema      #+#    #+#                 */
// /*   Updated: 2023/09/06 15:39:23 by mstegema      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// //find environment variable
// //check lenght & malloc data pointer to it
// //temp = current token->data
// //token->data is pointer to new data
// //free temp
// //return

// // example string: "hello $USER"

// //not finished
// char	*find_end(char *str)
// {
// 	char	*end;
// 	size_t	i;
// 	size_t	len;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '$')
// 		{
// 			while (str[i] != '\0')
// 			{
// 				if (str[i] == ' ')
// 					break ;
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// 	len = ft_strlen(str);
// 	end = ft_substr(str, i, len);
// 	return (end);
// }

// char	*find_begin(char *str)
// {
// 	char	*beginning;
// 	size_t	i;

// 	i = 0;
// 	while (str[i] != '$')
// 		i++;
// 	beginning = ft_substr(str, 0, i);
// 	return (beginning);
// }

// size_t	expand_data(char *str)
// {
// 	char	*new_data;
// 	char	*beginning;
// 	char	*middle;
// 	char	*end;

// 	beginning = find_begin(str);
// }

// size_t	replace_token(t_token *token)
// {
// 	char	*new_data;
// 	char	*temp;

// 	new_data = expand_data(token->data);
// 	temp = token->data;
// 	token->data = new_data;
// 	free(temp);
// 	return (0);
// }

// bool	expand_check(t_token *token, size_t start)
// {
// 	bool	expand;
// 	size_t	i;
// 	size_t	count;

// 	expand = false;
// 	i = 0;
// 	count = 0;
// 	while (token->data[i] != '\0' || i < start)
// 	{
// 		if (token->data[i] == '\'')
// 			count++;
// 		i++;
// 	}
// 	if (count % 2 != 0)
// 		expand = true;
// 	return (expand);
// }

// t_list	expand(t_list *tokens)
// {
// 	t_token	*token;
// 	size_t	i;

// 	while (tokens != NULL)
// 	{
// 		i = 0;
// 		token = tokens->content;
// 		while (token->data[i] != '\0')
// 		{
// 			if (token->data[i] == '$')
// 			{
// 				if (expand_check(token, i) == true)
// 					replace_token(token);
// 			}
// 			i++;
// 		}
// 		tokens = tokens->next;
// 	}
// }
