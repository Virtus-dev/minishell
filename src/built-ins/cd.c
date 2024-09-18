/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:26:51 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/18 16:25:24 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cd(t_data *data, char *owd)
{
	t_key	*home;

	owd = getcwd(NULL, 0);
	if (!chdir(data->argv[1]) && data->argc >= 2)
		ft_update_dir(data, owd);
	else if (data->argc == 1)
	{
		if (ft_key_exist(data->env, "HOME"))
		{
			home = ft_get_keymap(data->env, "HOME");
			chdir(home->value);
			ft_update_dir(data, owd);
		}
		else
			ft_putstr_fd("bash: cd: HOME not setted yet\n", data->fdout);
	}
	chdir(data->argv[1]);
	free (owd);
}

void    ft_oldpwd(t_data *data, char *owd, char *nwd)
{
    t_key   *nkey;
    
    if (ft_strcmp(owd, nwd) != 0)
    {
        nkey = ft_new_key("OLDPWD", owd);
        ft_add_key(data->env, nkey);
    }
}

void    ft_update_dir(t_data *data, char *owd)
{
    char	*nwd;

	nwd = getcwd(NULL, 0);
	if (ft_key_exist(data->env, "PWD"))
		ft_update_map(data->env, nwd, "PWD");
	ft_oldpwd(data, owd, nwd);
	free(nwd);
}