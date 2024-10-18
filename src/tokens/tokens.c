/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:39:10 by fracurul          #+#    #+#             */
/*   Updated: 2024/10/18 11:11:57 by arigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_del(char c, const char *delimiter)
{
	int i;

	i = 0;
	while(delimiter[i])
	{
		if(delimiter[i] == c)
			return(TRUE);
	}
	return(FALSE);
}

int is_ddel(char *input, const char delimiter)
{
	int i;

	i = 0;
	while(input[i])
	{
		if(input[i] == delimiter && input[i + 1] == delimiter )
			return(TRUE);
	}
	return(FALSE);
}

char *ft_strtok(char *line, const char *delimiter)
{
	static char *input = NULL; //guardar token entre llamadas.
	char *token;
	int i;
	int start;

	i =
	start = 0;
	if(line != NULL) //inicializamos input con el contenido de line.
		input = line;
	if(!input) //si no existe salimos.
		return(NULL);
	while(input[start] && is_del(*input, delimiter))//saltar del iniciales en caso de que haya.
		start++;
	if(input[start] == '\0')//si hemos llegado al final no existe token, por lo tanto salimos.
	{
		input = NULL;
		return(FALSE);
	}
	i = start;
	while(input[i])//recorremos la cadena
	{
		if(!is_in_quotes(input, i) && is_del(input[i], delimiter) //si hay un del, fuera de comilla, terminamos y avanzamos
			&&	!is_ddel(input[i], '>') && !is_ddel(input[i], '<'))		
		{
			input[i] = '\0';
			token = &input[start];
			input = &input[i + 1];
			return (token);
		}
		if(!is_in_quotes(input, i) && (is_ddel(input[i], '>') //nuevo
			|| is_ddel(input[i], '<')))
		{
			input[i + 1] = '\0';
			token = &input[start + 1];
			input = &input[i + 2];
			return (token);//nuevo hasta aqui.
		}
		i++;
	}
	token = &input[start]; //si llegamos al final sin encontrar del
	input = NULL;
	return (token);
}

int count_words(char *str)
{
	int i;
	int wc;

	i = 0;
	wc = 0;
	while(str[i])
	{
		while(str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '|'))
			i++;
		if(str[i])
			wc++;
		while(str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '|'))
			i++;
	}
	return(wc);
}

char **tokenize_command(char *input)
{
	char **tokens; //doble array con los tokens
	char *token; //token simple
	const char *del = " \t|><"; //delimitadores
	int pos;

	tokens = (char **)malloc(count_words(input) * sizeof(char *));
	token = ft_strtok(input, del);
	while(token != NULL)
	{
		tokens[pos] = token;
		pos++;
		if(pos >= (count_words(input) - 1))
		{
			ft_putstr_fd("minishell: too much argumentens", 1);
			break;
		}
		token = ft_strtok(NULL, del);
	}
	tokens[pos] = NULL;
	return(tokens);
}