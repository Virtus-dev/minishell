/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:51:32 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/13 11:28:46 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(const char *input, t_map *env)
{
	char	*res;
	char	*tmp;
	int		i;
	char	buf[2];

	res = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] && ft_isalpha(input[i + 1]))
		{
			res = ft_expand_variable(input, &i, env, res);
			continue ;
		}
		buf[0] = input[i];
		buf[1] = '\0';
		tmp = res;
		res = ft_strjoin(tmp, buf);
		free(tmp);
		i++;
	}
	return (res);
}

char	*ft_expand_variable(const char *input, int *i, t_map *env, char *res)
{
	int		start;
	char	*var;
	char	*val;
	char	*tmp;

	start = *i + 1;
	*i = start;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	var = ft_substr(input, start, *i - start);
	val = ft_getenv(env, var);
	free(var);
	if (!val)
		val = ft_strdup("");
	tmp = ft_strjoin(res, val);
	free(res);
	res = tmp;
	free(val);
	return (res);
}

char	*ft_getenv(t_map *env, char *key)
{
	t_key *found;

	found = ft_get_keymap(env, key);
	if (!found || !found->value)
		return (NULL);
	return ft_strdup(found->value);
}
