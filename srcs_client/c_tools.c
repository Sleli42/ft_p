/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 23:50:21 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/17 19:33:49 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	read_socket_return(int sock2read)
{
	int		r;
	char	buff[4096];

	r = 0;
	while ((r = read(sock2read, buff, 4095)) > 0)
	{
		buff[r] = '\0';
		if (ft_strlen(buff) == 0 && *buff == '\0')
			return ;
		write(1, buff, ft_strlen(buff));
		write(1, "\n", 1);
		break ;
	}
}

void	write_socket(int sock)
{
	char	*buff;

	buff = NULL;
	while (21)
	{
		write(1, "$: ", 3);
		while (get_next_line(0, &buff) > 0)
		{
			write(sock, buff, ft_strlen(buff));
			write(sock, "\n", 1);
			if (ft_strcmp(buff, "quit") == 0)
				close_and_exit(sock);
			read_socket_return(sock);
			break ;
		}
	}
}

void	close_and_exit(int sock)
{
	write(1, "quit\n", 5);
	close(sock);
	exit(1);
}
