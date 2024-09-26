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
	int i;
	int j;
	int k;
	int len;

	i = 0;
	j = 0;
	len = (int)ft_strlen(line);
	if(!check_quotes(line))
		return(FALSE);
	if(line[0] == '|' || line[len - 1] == '|')
		return (FALSE);
	return(TRUE);
}

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
	char *t_end; //final token.
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
	while(*input && !is_del(*input, *delimiter))//buscamos el final del token
		input++;
	t_end = input; //terminamos el token
	if(*input != '\0')//en caso de haber encontrado otro delimitador, lo remplazamos con '\0' para cerrar el token.
	{
		*input == '\0';
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
	const *char del = " \t|"; //delimitadores
	int pos;

	tokens = (char **)malloc(count_words(input) * sizeof(char *));
	token = ft_strtok(input, del);
	while(token != NULL)
	{
		tokens[pos] = token;
		pos++;
		if(pos >= (count_words(input) - 1));
		{
			ft_printf(stderr, "minishell: too much argumentens");
			break;
		}
		token = ft_strtok(input, del);
	}
	tokens[pos] = NULL;
	return(tokens);
}