/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_expander_tokens.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/01 14:26:26 by cschabra      #+#    #+#                 */
/*   Updated: 2023/08/01 14:26:29 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// parameters in format: {command_line},{expected_data}

// testen: "hoallo"hoi
// testen: hoallo""hoi
// testen: hoallo'""'hoi
// testen: hoallo'"'"''"hoi
// testen: $USER
// testen: '$USER'
// testen: "$USER"
// testen: "hallo $USER"
// testen "hallo $onzin"

// static char *ls_params[] = {
// 	(char *) "\"hoallo\"hoi,hoallohoi",
// 	(char *) "hoallo\"\"hoi,hoallohoi",
// 	(char *) "hoallo'""'hoi,hoallo""hoi",
// 	(char *) "hoallo\'\"\'\"\'\'\"hoi,hoallo\"\'\'hoi",
// 	(char *) "$USER,getenv(USER)",
// 	(char *) "\'$USER\',$USER",
// 	(char *) "\"$USER\",getenv(USER)",
// 	(char *) "\"hallo $USER\",hallo getenv(USER)",
// 	(char *) "\"hallo $onzin\", hallo "
// };