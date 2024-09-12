/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:14 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/12 19:35:12 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_echo(char* msg, t_data *data)
{
	ft_putstr_fd(msg, data->fdout);
	ft_putchar_fd('\n', data->fdout);
}

void	ft_cd(t_data *data)
{
	t_key	*home;
	
	if (chdir(data->argv[1]) != 0)
		perror(CD_ERR);
	else if (data->argc == 1)
	{
		home = ft_get_keymap(data->env, "HOME");	
	}
}

void	ft_pwd(t_data *data)
{
	char *cwd;

    cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror(PWD_ERR);
    else
    {
		ft_putstr_fd(cwd, data->fdout);
		ft_putchar_fd('\n', data->fdout);
	}
	free(cwd);
}