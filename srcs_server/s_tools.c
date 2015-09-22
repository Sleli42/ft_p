/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleli42 <sleli42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:21:53 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/22 03:22:32 by sleli42          ###   ########.fr       */
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
		try_builtins(buff, sv->c_sock);

	}
	// if ((r = recv(sv->c_sock, buff, 4095, 0)) < 0)
	// 	server_error("RECV");
	// write(1, buff, ft_strlen(buff));
	// if (r > 0)
	// 	try_builtins(buff, sv->c_sock);
	// free(buff);
}
