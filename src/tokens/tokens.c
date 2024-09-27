/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-26 15:39:10 by fracurul          #+#    #+#             */
/*   Updated: 2024-09-26 15:39:10 by fracurul         ###   ########.fr       */
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

char *ft_strtok(char *line, const char *delimiter)
{
	static char *input = NULL; //guardar token entre llamadas.
	char *t_start; //comienzo token.
	int i;

	i = 1;
	if(line != NULL) //inicializamos input con el contenido de line.
		input = line;
	if(!input) //si no existe salimos.
		return(NULL);
	while(*input && is_del(*input, delimiter))//saltar del iniciales en caso de que haya.
		input++;
	if(*input == '\0')//si hemos llegado al final no existe token, por lo tanto salimos.
	{
		input = NULL;
		return(FALSE);
	}
	t_start = input; //si existe, inicializamos el token,
	while(*input && !is_del(*input, delimiter))//buscamos el final del token
	{
		t_start[i++] = *input;
		input++;
	}
	if(*input != '\0')//en caso de haber encontrado otro delimitador, lo remplazamos con '\0' para cerrar el token.
	{
		*input = '\0';
		input++; //avanzar al siguiente caracter
	}
	return(t_start); //retornar token
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
	const char *del = " \t|"; //delimitadores
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
		token = ft_strtok(input, del);
	}
	tokens[pos] = NULL;
	return(tokens);
}