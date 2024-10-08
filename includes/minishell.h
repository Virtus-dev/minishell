/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:31 by arigonza          #+#    #+#             */
/*   Updated: 2024/10/08 08:57:25 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "constants.h"
#include "../libft/includes/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

// Structs
typedef struct	s_token
{
    char			*str;
    int				type;
    struct s_token	*prev;
    struct s_token	*next;
}	t_token;

typedef struct	s_key
{
	char		*key;
	char		*value;
}	t_key;

typedef struct  s_map
{
    t_key		**keys;
	size_t		size;
    size_t		capacity;
}				t_map;

typedef struct	s_data
{
    char		*input;
    char		**argv;
    t_token		*token;
    int			lvl;
	t_map		*env;
    t_map		*exp;
    int			argc;
    pid_t		child;
    int			fdin;
    int			fdout;
	int			status;
}				t_data;

// BUILT_INS
void	ft_echo(t_data *data);
void	ft_pwd(t_data *data);
void	ft_cd(t_data *data, char *owd);
void	ft_env(t_data *data);
void	ft_export(t_data *data);
void    ft_exit(t_data *data);

// MAP UTILS
void	ft_map_init(t_map *map);
t_key	*ft_new_key(char *name, char *value);
t_key	*ft_get_keymap(t_map *map, char *key);
t_key	*ft_get_valmap(t_map *map, char *value);
void	ft_add_key(t_map *map, t_key *key);
t_map	*ft_fill_map(char **env);
int		ft_key_exist(t_map *map, char *key);
void	ft_update_map(t_map *map, char *value, char *key);
void	ft_print_map(t_data *data, t_map *map);
void	ft_mapcmp_update(t_map *map, char *values);
void	ft_free_map(t_map *map);

// STRUCT UTILS
t_data	*ft_init_data(int argc, char **input, char **env);
void	ft_map_init(t_map *map);

// UTILS
void	ft_oldpwd(t_data *data, char *owd, char *nwd);
void	ft_update_dir(t_data *data, char *owd);
int		ft_flag_exist(char *str);
int	    ft_check_expformat(char *argv);
void	ft_free_matrix(char **str);
void	ft_free_resources(t_data *data);
int		ft_builtin_check(char *str);
void	ft_execpath(t_data* data);
void	ft_runexec(t_data *data);

// PARSING
int check_quotes(char *line);
int check_line(char *line);
int is_in_quotes(char *line, int index);
int check_input(char *line);

//TOKENS
int is_del(char c, const char *delimiter);
char *ft_strtok(char *line, const char *delimiter);
int count_words(char *str);
char **tokenize_command(char *input);
//VALIDATIONS  
int validate_pipe(char *line , int index);
int validate_otredir(char *line , int index);
int validate_itredir(char *line , int index);
int validate_metachar(char *line);
#endif
