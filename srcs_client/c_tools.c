/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 23:50:21 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/16 22:25:03 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	read_return(int sock2read)
{
	int		r;
	char	buff[4096];

	while ((r = read(sock2read, buff, 4095)) > 0)
	{
		buff[r] = 0;
		if (buff)
		{
			write(1, buff, ft_strlen(buff));
			write(1, "\n", 1);
			return ;
		}
		//break ;
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
			read_return(sock);
			if (ft_strcmp(buff, "quit") == 0)
				close_and_exit(sock);
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
