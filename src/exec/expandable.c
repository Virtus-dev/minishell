/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:51:32 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/21 19:21:15 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static t_unwrap ft_unwrap_quotes(const char *str)
{
	t_unwrap	res;
	int			len;

	len = (int)ft_strlen(str);
	res.expand = 1;
	if ((str[0] == '\'' || str[0] == '"') && str[len - 1] == str[0])
	{
		res.str = ft_substr(str, 1, len - 2);
		if (str[0] == '\'')
			res.expand = 0;
	}
	else
		res.str = ft_strdup(str);
	return (res);
}*/

static void	ft_handle_quote(t_data *data, int *i, char **res)
{
	char	quote;
	char	buffer[2];
	char	*tmp;
	char	*input;

	input = data->input;
	quote = input[(*i)++];
	while (input[*i] && input[*i] != quote)
	{
		if (quote == '"' && input[*i] == '$' && input[*i + 1])
			*res = ft_expand_variable(data, i, *res);
		else
		{
			buffer[0] = input[(*i)++];
			buffer[1] = '\0';
			tmp = *res;
			*res = ft_strjoin(tmp, buffer);
			free(tmp);
		}
	}
	if (input[(*i)] == quote)
		*i = *i + 1;
}

char	*ft_expand_variable(t_data *data, int *i, char *res)
{
	char	*val;
	char	*var;
	char	*tmp;
	int		start;

	if (data->input[*i + 1] == '?')
	{
		i += 2;
		val = ft_itoa(data->status);
	}
	else
	{
		start = ++(*i);
		while (ft_isalnum(data->input[*i]) || data->input[*i] == '_')
			(*i)++;
		var = ft_substr(data->input, start, *i - start);
		val = ft_getenv(data->env, var);
		free(var);
		if (!val)
			val = ft_strdup("");
	}
	tmp = ft_strjoin(res, val);
	free(res);
	free(val);
	return (tmp);
}

char	*ft_expand(t_data *data, const char *input)
{
	char	buffer[2];
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = ft_strdup("");
	printf("INPUT A EXPANDIR: [%s]\n", data->input);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			ft_handle_quote(data, &i, &res);
		else if (input[i] == '$' && input[i + 1])
			res = ft_expand_variable(data, &i, res);
		else
		{
			buffer[0] = input[i++];
			buffer[1] = '\0';
			tmp = res;
			res = ft_strjoin(tmp, buffer);
			free(tmp);
		}
	}
	return (res);
}
