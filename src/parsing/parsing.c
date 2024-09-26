/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-26 13:59:23 by fracurul          #+#    #+#             */
/*   Updated: 2024-09-26 13:59:23 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(char *line)
{
	int quote;
	int dquote;

	quote = 0;
	dquote = 0;

	while(*line)
	{
		if(*line == '\'' && (dquote % 2 == 0))
			quote++;
		if(*line == '\"' && (quote % 2 == 0))
			dquote++;
		line++;
	}
	if((quote % 2 == 0) && (dquote % 2 == 0))
		return (TRUE);
	return (FALSE);
}

int check_line(char *line)
{
	int len;

	len = (int)ft_strlen(line);
	if(!check_quotes(line))
		return(FALSE);
	if(line[0] == '|' || line[len - 1] == '|')
		return (FALSE);
	return(TRUE);
}
