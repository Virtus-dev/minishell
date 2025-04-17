/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:12:31 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/17 00:01:57 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if the parameter passed by is or is not a built-in.
 * 
 * @param data Struct with all the main information. 
 * @param str The supossed built-in we are going to check.
 * @return Returns the kind of built-in.
 */
int	ft_builtin_check(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "ECHO"))
		return (ECHO);
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "CD"))
		return (CD);
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "PWD"))
		return (PWD);
	if (!ft_strcmp(str, "export") || !ft_strcmp(str, "EXPORT"))
		return (EXP);
	if (!ft_strcmp(str, "unset") || !ft_strcmp(str, "UNSET"))
		return (UNST);
	if (!ft_strcmp(str, "env") || !ft_strcmp(str, "ENV"))
		return (ENV);
	if (!ft_strcmp(str, "exit") || !ft_strcmp(str, "EXIT"))
		return (EXIT);
	if (!ft_strcmp(str, "./minishell"))
		return (DEF);
	return (FALSE);
}

void    ft_exec_built(t_data *data, char *input)
{
    int builtin;

    builtin = ft_builtin_check(input);
	if (builtin == CD)
		ft_cd(data, NULL);
	else if (builtin == ECHO)
		ft_echo(data);
	else if (builtin == ENV)
		ft_env(data);
	else if (builtin == EXP)
		ft_export(data);
	else if (builtin == EXIT)
		ft_exit(data);
	else if (builtin == PWD)
		ft_pwd(data);
	else if (builtin == UNST)
		ft_unset(data);
}
