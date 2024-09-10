/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:09:50 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/10 16:39:52 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft/includes/libft.h"

void	ft_chdir(t_data *data, char *owd)
{
	char	*nwd;
	
	nwd = getcwd(nwd, NULL);

}

void	ft_cd(char* path)
{
	if (chdir(path) != 0) {
		perror("cd");
	}
}
void	ft__pwd(t_data *data)
{
	char cwd;

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