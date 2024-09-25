/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:10:38 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/25 15:52:40 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_check(char *str)
{
	if (!ft_strcmp(str, "echo") || ft_strcmp(str, "ECHO"))
		return (ECHO);
	if (!ft_strcmp(str, "cd") || ft_strcmp(str, "CD"))
		return (CD);
	if (!ft_strcmp(str, "export") || ft_strcmp(str, "EXPORT"))
		return (EXP);
	if (!ft_strcmp(str, "unset") || ft_strcmp(str, "UNSET"))
		return (UNST);
	if (!ft_strcmp(str, "env") || ft_strcmp(str, "ENV"))
		return (ENV);
	if (!ft_strcmp(str, "exit") || ft_strcmp(str, "EXIT"))
		return (EXIT);
	if (!ft_strcmp(str, "./minishell"))
		return (DEF);
	return (FALSE);
}