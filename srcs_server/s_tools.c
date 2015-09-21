/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:21:53 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/21 20:56:13 by lubaujar         ###   ########.fr       */
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
		write(1, buff, ft_strlen(buff));
		if (try_builtins(buff, sv->c_sock) == 0)
			send(sv->c_sock, "ERROR\n", 7, 0);
		else
			send(sv->c_sock, "SUCCESS\n", 9, 0);
	}
	// if ((r = recv(sv->c_sock, buff, 4095, 0)) < 0)
	// 	server_error("RECV");
	// write(1, buff, ft_strlen(buff));
	// if (r > 0)
	// 	try_builtins(buff, sv->c_sock);
	// free(buff);
}
