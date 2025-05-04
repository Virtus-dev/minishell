/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arigonza <arigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:53:36 by arigonza          #+#    #+#             */
/*   Updated: 2025/05/03 13:18:48 by arigonza         ###   ########.fr       */
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
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (!str)
			break ;
		if(ft_strncmp(str, dl, ft_strlen(dl)))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, hd);
		free(str);
	}
	close (hd);
}

void	ft_here_doc(t_data *data, char *dl)
{
	int		nw_fd;

	if (!dl)
	{
		ft_putstr_fd("bash: syntax error, unexpected token\n", data->fdout);
		data->status = 1;
		return ;
	}
	ft_write_hd(data, dl);
	nw_fd = open(".tmp", O_RDONLY);
	data->fdin = nw_fd;
	unlink(".tmp");
}
