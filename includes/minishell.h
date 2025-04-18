/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:31 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/17 17:42:51 by fracurul         ###   ########.fr       */
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

//Structs
typedef struct	s_token
{
	char		*cmd;
	char		**cargs;
}	t_token;

typedef struct	s_key
{
	char		*key;
	char		*value;
}	t_key;

typedef struct	s_map
{
	t_key		**keys;
	size_t		size;
	size_t		capacity;
}				t_map;

typedef struct	s_data
{
	char		*input;
	char		**argv;
	t_token		**tokens;
	int			lvl;
	t_map		*env;
	t_map		*exp;
	int			argc;
	pid_t		child;
	int			fdin;
	int			fdout;
	int			status;
}				t_data;

//BUILT_INS
void	ft_echo(t_data *data);
void	ft_pwd(t_data *data);
void	ft_cd(t_data *data, char *owd);
void	ft_env(t_data *data);
void	ft_export(t_data *data);
void	ft_unset(t_data *data);
void	ft_exit(t_data *data);

//EXEC
void	ft_exec(t_data *data);

//SIGNALS
void	ft_handler(int sig);
void	ft_child_handler(int sig);
void	ft_signal(void);
int		ft_set_signal(void);
void	ft_ignore_signals(void);

//MAP UTILS
void	ft_map_init(t_map *map);
t_key	*ft_new_key(char *name, const char *value);
t_key	*ft_get_keymap(t_map *map, char *key);
t_key	*ft_get_valmap(t_map *map, char *value);
void	ft_add_key(t_map *map, t_key *key);
t_map	*ft_fill_map(char **env);
int		ft_key_exist(t_map *map, char *key);
void	ft_update_map(t_map *map, char *value, char *key);
void	ft_print_map(t_data *data, t_map *map);
void	ft_mapcmp_update(t_map *map, char *values);
void	ft_free_map(t_map *map);
void	ft_free_keys(t_key** keys);
void	ft_remove_key(t_map *map, char *key);
char	*ft_getvar(t_map *map, char *key);

//STRUCT UTILS
t_data	*ft_init_data(int argc, char **env);
void	ft_map_init(t_map *map);
t_token	*get_next_token(t_token **token, int reset);
void	ft_load_args(t_data *data, t_token *token);

//TOKEN UTILS
int		ft_toklen(t_token **tokens);
void	free_tokens(t_token **tokens);
int		ft_matrix_size(char **matrix);

//UTILS
//void	ft_oldpwd(t_data *data, char *owd, char *nwd);
void	ft_oldpwd(t_data *data, char *owd);
void	ft_update_dir(t_data *data, char *owd);
int		ft_flag_exist(char *str);
int		ft_check_expformat(char *argv);
void	ft_free_matrix(char **str);
void	ft_free_resources(t_data *data);
int		ft_builtin_check(char *str);
void	ft_execpath(t_data* data);
char	*ft_find_in_path(char *cmd, t_map *env);
char    **ft_clean_redirections(char **tokens);
void    ft_clean_and_replace_args(t_data *data);

/**
 * @brief Executes from path, looking on our ENV.
 *
 * @param data
 */
void	ft_runexec(t_data *data);
/**
 * @brief Takes from our map format and reconverts it into a format
 * we can use to execute it.
 *
 * @param map
 * @return char**
 */
char	**ft_revert_env(t_map *map);

void	ft_exec_built(t_data *data, char *input);

/**
 * @brief Returns the exact position of a rediretion on a string.
 *
 * @param argv The string to search from.
 * @return (int)Redirection position.
 */
int 	ft_redir_pos(char **argv);

/**
 * @brief Returns what type of IN redirection is,
 * simple or double.('<' or '<<')
 *
 * @param str
 * @return int
 */
int		ft_redin_type(char *str);

/**
 * @brief Returns what type of OUT redirection is,
 * simple or double.('<' or '<<')
 *
 * @param str
 * @return int
 */
int		ft_rediout_type(char *str);

/**
 * @brief Implements OUTPUT redirections such as '>' and '>>'.access
 * redirects the output to a file descriptor, creating or opening
 *  the especified file. While '>' overwrite, '>>' appends.
 *
 * @param data
 * @param redir
 * @param redir_type
 */
void	ft_redirout(t_data *data, char *redir, int redir_type);
void	ft_redirin(t_data *data, char *redir, int redir_type);
void	ft_start_redi(t_data *data);
int		ft_is_din(char *str);
int		ft_is_sin(char *str);
int		ft_is_dout(char *str);
int		ft_is_sout(char *str);
void	ft_write_hd(t_data *data, char *dl);
void	ft_here_doc(t_data *data);

//PARSING
int		check_quotes(char *line);
int	    ft_redi_ok(const char *input);
int		check_line(char *line);
int		is_in_quotes(char *line, int index);
int		check_input(char *line);
int		ft_is_all_space(char *input, t_data *data);
void	ft_check_redir(t_data *data);
int		ft_count_pipes(t_data *data);
int		ft_is_expandable(char *var);

//TOKENS
int		is_op(char c);
char	**tokenizer(const char *input);
t_token	**tokenize_command(char **tokens);

//PIPES
void	ft_pipe_processing(t_data *data, int pipe_num);
void	ft_swapfd(t_data *data, int i, int pipe_num);
void	ft_close_fds(t_data *data);

//VALIDATIONS
int		validate_pipe(char *line , int index);
int		validate_otredir(char *line , int index);
int		validate_itredir(char *line , int index);
int		validate_metachar(char *line, int i);
#endif