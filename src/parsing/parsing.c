/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:59:23 by fracurul          #+#    #+#             */
/*   Updated: 2024/10/05 22:01:56 by fracurul         ###   ########.fr       */
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
	}
	if((quote % 2 == 0) && (dquote % 2 == 0))
		return (TRUE);
	return (FALSE);
}

int is_in_quotes(char *line, int index)
{
	int i;
	int quote;
	int dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	while(i < index)//recorrer hasta la posicion donde esta nuestro caracter.
	{
		if(line[i] == '\'' && dquote == 0)
			quote = !quote;
		if(line[i] == '\"' && quote == 0)
			dquote = !dquote;
		i++;
	}
	return(quote || dquote); //devolver la diferencia entre ' y ".
}

int check_line(char *line)
{
	int len;
	int i;

	len = (int)ft_strlen(line);
	if(!check_quotes(line))
		return(FALSE);
	if(line[0] == '|' || line[0] == '>' || line[0] == '<' )
		return (FALSE);
	if(line[len - 1] == '|' || line[len - 1] == '>' || line[0] == '<')
		return (FALSE);
	while(line[i])
	{
		if(line[i] == '&' || line[i] == ';')
			return(FALSE);
		i++;
	}
	return(TRUE);
}

char *check_input(char *line)
{
	check_line(line);
	validate_metachar(line);
	
}