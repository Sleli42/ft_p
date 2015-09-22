/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:21:53 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/22 16:50:24 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

//ssize_t recv(int s, void *buf, ssize_t len, int flags);

void	read_socket(t_server *sv)
{
	int		r;
	char	buff[4096];

	ft_memset(buff, 0, ft_strlen(buff));
	while ((r = recv(sv->c_sock, buff, 4095, 0)) > 0)
	{
		buff[r] = 0;
		if (buff[0] == 0)
			send(sv->c_sock, "\0", 1, 0);
		else
		{
			if (try_builtins(buff, sv->c_sock) == 0)
			{
				if (try_exec(sv, buff) == 0)
					send(sv->c_sock, "~> ERROR\n", 10, 0);
				else
					send(sv->c_sock, "~> SUCCESS\n", 12, 0);
			}
			else
				send(sv->c_sock, "~> SUCCESS\n", 12, 0);
		}
	}
}
