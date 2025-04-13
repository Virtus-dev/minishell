/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:50:15 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/13 13:45:04 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_expandable(char *var)
{
	//printf("%c\n", var[0]);
	if (var[0] != '\'' && ft_strchr_np(var, '$'))
		return (TRUE);
	else
		return (FALSE);
}