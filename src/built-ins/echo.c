/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:14 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/13 20:48:55 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_flag(char **av, int *nl)
{
	int	i;
	int	j;
	
	*nl = 0;
	i = 1;
	while (av[i])
	{
		if (av[i][0] != '-' || av[i][1] != 'n')
			break ;
		j = 2;
		while (av[i][j] == 'n')
			j++;
		if (av[i][j] != '\0')
			break ;
		i++;
	}
	if (i > 1 && av[i] && av[i][0] == '-' && av[i][1] != 'n')
		*nl = 0;
	else if (i > 1)
		*nl = 1;
	return (i);
}

static void	print_expanded(char *arg, t_map *env, int fd)
{
	t_key	*key;
	char	*var;

	if	(!ft_is_expandable(arg))
	{
		ft_putstr_fd(arg, fd);
		return ;
	}
	else if (arg[0] == '$')
	{
		var = arg + 1;
		key = ft_get_keymap(env, var);
		if (key && key->value)
			ft_putstr_fd(key->value, fd);
	}
}

void	ft_echo(t_data *data)
{
	int	i;
	int	flag;
	
	i = 1;
	if (!data->argv[i])
	{
		ft_putchar_fd('\n', data->fdout);
		return ;
	}
	i = skip_flag(data->argv, &flag);
	while (data->argv[i])
	{
		print_expanded(data->argv[i], data->env, data->fdout);
		if (data->argv[i + 1])
			ft_putchar_fd(' ', data->fdout);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', data->fdout);
}
