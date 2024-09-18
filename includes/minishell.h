/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:31 by arigonza          #+#    #+#             */
/*   Updated: 2024/09/18 16:08:19 by arigonza         ###   ########.fr       */
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
#include <signal.h>

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
    size_t      capacity;
}   t_map;

typedef struct	s_data
{
    char        *input;
    char        **argv;
    t_token		*token;
	t_map		*env;
    int         argc;
    pid_t       child;
    int         fdin;
    int         fdout;
} t_data;

// BUILT_INS
void    ft_echo(char *msg, t_data *data);
void	ft_pwd(t_data *data);
void	ft_cd(t_data *data, char *owd);

// MAP UTILS
void    ft_map_init(t_map *map);
t_key	*ft_new_key(char *name, char *value);
t_key	*ft_get_keymap(t_map *map, char *key);
t_key	*ft_get_valmap(t_map *map, char *value);
void	ft_add_key(t_map *map, t_key *key);
t_map	*ft_fill_map(char **env);
int	    ft_key_exist(t_map *map, char *key);
void	ft_update_map(t_map *map, char *value, char *key);

// STRUCT UTILS
t_data	*ft_init_data(int argc, char **argv, char **env);

// UTILS
void    ft_oldpwd(t_data *data, char *owd, char *nwd);
void    ft_update_dir(t_data *data, char *owd);

#endif
