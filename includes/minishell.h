/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:03:31 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/17 19:53:37 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "constants.h"
# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>

//Structs
typedef struct s_token
{
	char		*cmd;
	char		**cargs;
}	t_token;

typedef struct s_key
{
	char		*key;
	char		*value;
}	t_key;

typedef struct s_map
{
	t_key		**keys;
	size_t		size;
	size_t		capacity;
}				t_map;

typedef struct s_data
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

//Global
extern int	g_block;

//BUILT_INS
void	ft_echo(t_data *data);
void	ft_pwd(t_data *data);
void	ft_cd(t_data *data, char *owd);
void	ft_env(t_data *data);
void	ft_export(t_data *data, char **splited, int i);
void	ft_unset(t_data *data);
void	ft_exit(t_data *data);

//EXEC
void	ft_exec(t_data *data);

//SIGNALS
void	ft_setup_parent_signals(void);
void	ft_restore_default_signals(void);

//MAP UTILS
void	ft_map_init(t_map *map);
t_key	*ft_new_key(char *name, const char *value);
char	*ft_getenv(t_map *env, char *key);
t_key	*ft_get_keymap(t_map *map, char *key);
t_key	*ft_get_valmap(t_map *map, char *value);
void	ft_add_key(t_map *map, t_key *key);
t_map	*ft_fill_map(char **env);
int		ft_key_exist(t_map *map, char *key);
void	ft_update_map(t_map *map, char *value, char *key);
void	ft_print_map(t_data *data, t_map *map);
void	ft_mapcmp_update(t_map *map, char *values);
void	ft_free_map(t_map *map);
void	ft_remove_key(t_map *map, char *key);
void	ft_free_keys(t_key **keys);
char	*ft_getvar(t_map *map, char *key);

//STRUCT UTILS
t_data	*ft_init_data(int argc, char **env);
void	ft_map_init(t_map *map);
void	ft_load_args(t_data *data, t_token *token);

//TOKEN UTILS
t_token	*get_next_token(t_token **token, int reset);
int		ft_toklen(t_token **tokens);
void	free_tokens(t_token **tokens);
int		ft_matrix_size(char **matrix);
int		export_quoted_input(char *token);
char	*wrap_export_input(const char *input, int start, char *str);

//Echo utils
int		skip_flag(char **av, int *nl);

//UTILS
void	ft_oldpwd(t_data *data, char *owd);
void	ft_update_dir(t_data *data, char *owd);
int		ft_flag_exist(char *str);
int		ft_check_expformat(char *argv);
void	ft_free_matrix(char **str);
void	ft_free_resources(t_data *data);
int		ft_builtin_check(char *str);
int		ft_is_env_builtin(char *input);
void	ft_exec_env_builtin(t_data *data, char *input);
int		ft_nonenv_builtin(char *str);
void	ft_execpath(t_data *data);
char	*ft_find_in_path(char *cmd, t_map *env);
char	**ft_clean_redirections(char **tokens);
void	ft_clean_and_replace_args(t_data *data);

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
 * @brief Aplica redirecciones de entrada/salida
 * a partir de los argumentos del token.
 *
 * Recorre los argumentos de un comando (`t_token`) y
 * aplica redirecciones según detecte
 * los operadores `>`, `>>`, `<` o `<<`,
 * usando los argumentos siguientes como nombre de archivo o delimitador.
 *
 * @param data Estructura de datos principal con fds y entorno.
 * @param token Token que contiene los argumentos del comando actual.
 */
void	ft_start_redi(t_data *data, t_token *token);

/**
 * @brief Devuelve el tipo de redirección detectado en una cadena.
 *
 * Detecta si una cadena corresponde a un operador de redirección y
 * devuelve un valor constante:
 * S_OUT (`>`), D_OUT (`>>`), S_IN (`<`), D_IN (`<<`), o -1
 * si no es una redirección.
 *
 * @param arg Cadena a evaluar.
 * @return int Código de tipo de redirección o -1.
 */
int		ft_redir_type(const char *arg);

/**
 * @brief Aplica redirección de salida estándar (overwrite o append).
 *
 * Abre el archivo correspondiente en modo escritura, y actualiza `data->fdout`.
 * Cierra el fd anterior si era distinto de STDOUT.
 *
 * @param data Estructura principal de shell con fdout.
 * @param file Nombre del archivo destino.
 * @param type Tipo de redirección: S_OUT (`>`) o D_OUT (`>>`).
 */
void	ft_redirout(t_data *data, char *file, int type);

/**
 * @brief Aplica redirección de entrada estándar o heredoc.
 *
 * Abre el archivo para lectura o inicia un heredoc, y actualiza `data->fdin`.
 * Cierra el fd anterior si era distinto de STDIN.
 *
 * @param data Estructura principal de shell con fdin.
 * @param file Nombre del archivo fuente o delimitador.
 * @param type Tipo de redirección: S_IN (`<`) o D_IN (`<<`).
 */
void	ft_redirin(t_data *data, char *file, int type);
void	ft_here_doc(t_data *data, char *dl);

//PARSING
int		check_quotes(char *line);
int		ft_redi_ok(const char *input);
int		check_line(char *line);
int		is_in_quotes(char *line, int index);
int		check_input(char *line);
int		ft_is_all_space(char *input, t_data *data);
void	ft_check_redir(t_data *data);
int		ft_count_pipes(t_data *data);
int		ft_is_expandable(char *var);
int		ft_counterwords(const char *s, char c);
char	*ft_expand(const char *input, t_map *env);
/**
 * @brief Expande la variable $VAR que comienza en input[i]
 *
 * @param input La cadena original
 * @param i     Puntero al índice actual.
 * @param env   Mapa de entorno
 * @return char* Cadena expandida para reemplazar la variable
 */
char	*ft_expand_variable(const char *input, int *i, t_map *env, char *res);

//TOKENS
int		is_op(char c);
char	*ft_wrap_quotes(char *str, char quote);
char	**tokenizer(const char *input, int *pos);
t_token	**tokenize_command(char **tokens, int *pos);

//PIPES
void	ft_pipe_processing(t_data *data, int pipe_num);
void	ft_swapfd(t_data *data, int i, int pipe_num);
void	ft_close_fds(t_data *data);

//VALIDATIONS
int		validate_pipe(char *line, int index);
int		validate_otredir(char *line, int index);
int		validate_itredir(char *line, int index);
int		validate_metachar(char *line, int i);
#endif