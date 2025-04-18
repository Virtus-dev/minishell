/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:53:36 by arigonza          #+#    #+#             */
/*   Updated: 2025/04/17 16:04:18 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//comprobacion de señales y no abre correctamente
void	ft_write_hd(t_data *data, char *dl)
{
	int		hd;
	char	*str;

	hd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (hd == -1)
	{
		ft_putstr_fd(FILE_ERR, data->fdout);
		data->status = 1;
		return ;
	}
	ft_putstr_fd("> ", 1);
	str = get_next_line(0);
	while (ft_strcmp(str, dl))
	{
		if (!ft_strcmp(str, dl))
			break ;
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(str, hd);
		free(str);
		str = get_next_line(0);
	}
	close (hd);
	free(str);
}

void	ft_here_doc(t_data *data)
{
	char	*dl;
	int		nw_fd;

	if (!data->argv[1])
	{
		ft_putstr_fd("bash: syntax error, unexpected token\n", data->fdout);
		data->status = 1;
		return ;
	}
	dl = ft_strjoin(data->argv[1], "\n");
	ft_write_hd(data, dl);
	free(dl); //Este free ha dado un seg fault
	nw_fd = open(".tmp", O_RDONLY);
	data->fdin = nw_fd;
}
