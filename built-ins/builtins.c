/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:14 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/10 23:58:40 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_echo(char* msg)
{
	printf("%s\n", msg);
}

void	ft_cd(char* path)
{
	if (chdir(path) != 0)
		perror(CD_ERR);
}

void	ft_pwd()
{
	char *cwd;

    cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror(PWD_ERR);
    else
    {
		printf(cwd);
		printf("\n");
	}
	free(cwd);
}