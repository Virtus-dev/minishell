/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:37:18 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/25 14:38:09 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
