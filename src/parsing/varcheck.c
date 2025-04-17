/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:50:15 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/17 15:58:05 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_expandable(char *var)
{
	if (var[0] != '\'' && ft_strchr_np(var, '$'))
		return (TRUE);
	else
		return (FALSE);
}
