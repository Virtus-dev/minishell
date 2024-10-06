/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:01:25 by fracurul          #+#    #+#             */
/*   Updated: 2024/10/05 22:12:09 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ""

int validate_pipe(char *line , int index)
{
	if(index == 0 || is_in_quotes(line, index) || line[index + 1] == '\0')
		return(FALSE);
	else
		return(TRUE)
}

int validate_otredir(char *line , int index)
{
	if(line[index + 1] == '>') //validar >>
	{
		if(index == 0 || is_in_quotes(line, index) || line[index + 2] == '\0' 
			|| line[index + 2] == '|')
			return(FALSE);
		else
			return(TRUE);
	}
	else //validar >
	{
		if(index == 0 || is_in_quotes(line, index) || line[index + 1] == '\0' 
			|| line[index + 1] == '|')
			return(FALSE);
		else
			return(TRUE);	
	}
}

int validate_itredir(char *line , int index)
{
	if(line[index + 1] == '<') //validar <<
	{
		if(index == 0 || is_in_quotes(line, index) || line[index + 2] == '\0' 
			|| line[index + 2] == '|')
			return(FALSE);
		else
			return(TRUE);
	}
	else //validar <
	{
		if(index == 0 || is_in_quotes(line, index) || line[index + 1] == '\0' 
			|| line[index + 1] == '|')
			return(FALSE);
		else
			return(TRUE);	
	}	
}

void validate_metachar(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if(line[i] == '|')
			validate_pipe(line, i);
		else if(line[i] == '>')
		{
			validate_otredir(line, i)
			if(line[i + 1] == '>')
				i++;
		}
		else if(line[i] == '<')
		{
			validate_itredir(line, i);
			if(line[i + 1] == '<')
				i++;
		}
		i++;
	}
}