/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 23:50:21 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/22 23:06:08 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	read_socket_return(int sock2read)
{
	int		r;
	char	buff[4096];

	ft_memset(buff, 0, ft_strlen(buff));
	while ((r = recv(sock2read, buff, 4095, 0)) > 0)
	{
		buff[r] = 0;
		write(1, buff, ft_strlen(buff));
		if (buff[r - 3] == '`' || buff[0] == 0)
			return ;
	}
}

void	write_socket(int sock)
{
	int		r;
	char	*buff;

	buff = NULL;
	while (21)
	{
		write(1, "$: ", 3);
		while (get_next_line(0, &buff) > 0)
		{
			if ((r = send(sock, buff, 4095, 0)) < 0)
				client_error("SEND");
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
