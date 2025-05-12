/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:14 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/12 15:13:16 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_var(t_data *data, char *var, int fd)
{
	t_key	*key;

	if (ft_strcmp(var, "?") == 0)
		ft_putnbr_fd(data->status, fd);
	else
	{
		key = ft_get_keymap(data->env, var);
		if (key && key->value)
			ft_putstr_fd(key->value, fd);
	}
}

static int	ft_var_handler(t_data *data, const char *arg, int i, int fd)
{
	int		start;
	char	*var;

	if (!arg[i])
		return (i);
	if (arg[i] == '?')
	{
		ft_print_var(data, "?", fd);
		return (i + 1);
	}
	else if (ft_isalpha(arg[i]) || arg[i] == '_')
	{
		start = i;
		while (ft_isalnum(arg[i]) || arg[i] == '_')
			i++;
		var = ft_substr(arg, start, i - start);
		ft_print_var(data, var, fd);
		free(var);
		return (i);
	}
	else
	{
		ft_putchar_fd('$', fd);
		return (i);
	}
}

static void	ft_quoted_handler(t_data *data, char *arg, int *i, int fd)
{
	char	quote;

	quote = arg[(*i)++];
	while (arg[*i])
	{
		if (arg[*i] == quote)
		{
			(*i)++;
			break ;
		}
		if (quote == '"' && arg[*i] == '$')
			*i = ft_var_handler(data, arg, *i + 1, fd);
		else
			ft_putchar_fd(arg[(*i)++], fd);
	}
}

static void	print_expanded(char *arg, t_data *data, int fd)
{
	int		i;

	if (!arg)
		return ;
	i = 0;
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '"'))
			ft_quoted_handler(data, arg, &i, fd);
		if (arg[i] == '$')
			i = ft_var_handler(data, arg, i + 1, fd);
		else if (arg[i])
			ft_putchar_fd(arg[i++], fd);
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
		print_expanded(data->argv[i], data, data->fdout);
		if (data->argv[i + 1])
			ft_putchar_fd(' ', data->fdout);
		i++;
	}
	if (!flag)
		ft_putchar_fd('\n', data->fdout);
	data->status = 0;
}
