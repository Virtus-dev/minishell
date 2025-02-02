/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:01:25 by fracurul          #+#    #+#             */
/*   Updated: 2025/02/02 12:07:22 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int validate_pipe(char *line , int index)
{
	if(index == 0 || line[index + 1] == '\0')
		return(FALSE);
	else
		return(TRUE);
}

int validate_otredir(char *line , int index)
{
	if(line[index + 1] == '>') //validar >>
	{
		if(index == 0 || line[index + 2] == '\0' || line[index + 2] == '|')
			return(FALSE);
		else
			return(TRUE);
	}
	else //validar >
	{
		if(index == 0 || line[index + 1] == '\0' || line[index + 1] == '|')
			return(FALSE);
		else
			return(TRUE);	
	}
}

int validate_itredir(char *line , int index)
{
	if(line[index + 1] == '<') //validar <<
	{
		if(index == 0 || line[index + 2] == '\0' || line[index + 2] == '|')
			return(FALSE);
		else
			return(TRUE);
	}
	else //validar <
	{
		if(index == 0 || line[index + 1] == '\0' || line[index + 1] == '|')
			return(FALSE);
		else
			return(TRUE);	
	}	
}

int validate_metachar(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] == '|' && !is_in_quotes(line, i))
		{
			if(!validate_pipe(line, i))
				return(FALSE);	
		}
		else if(line[i] == '>' && !is_in_quotes(line, i))
		{
			if(!validate_otredir(line, i))
				return(FALSE);
			if(line[i + 1] == '>')
				i++;
		}
		else if(line[i] == '<' && !is_in_quotes(line, i))
		{
			if(validate_itredir(line, i))
				return(FALSE);
			if(line[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (TRUE);
}
