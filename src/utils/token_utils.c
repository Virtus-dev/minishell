/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:57:01 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/17 13:32:08 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(char **cmd)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->str = ft_strdup(cmd);
	token->type = ft_builtin_check(cmd[0]);
	token->next = NULL;
	return (token);
}

void	ft_tokadd_back(t_token *lst, t_token *token)
{
    if (!lst)
        lst = token;
    while (lst->next)
        lst = lst->next;
    lst->next = token;
}

void	ft_freetok(t_token *token)
{
    t_token	*aux;

    while (token)
    {
        aux = token->next;
        free(token);
        token = aux;
    }
}