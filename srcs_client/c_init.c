/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:40:32 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/15 23:57:42 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	usage(char *s)
{
	ft_putstr("Usage: ");
	if (s)
		ft_putstr(s);
	ft_putstr(" <addr> <port>\n");
	exit(-1);
}

int		create_client(char *addr, int port)
{
	struct sockaddr_in	sins;
	struct protoent		*client_p;
	int					sock;

	if ((client_p = getprotobyname("tcp")) == 0)
		client_error("GETPROTOBYNAME");
	sock = socket(PF_INET, SOCK_STREAM, client_p->p_proto);
	sins.sin_family = AF_INET;
	sins.sin_port = htons(port);
	sins.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (struct sockaddr *)&sins, sizeof(sins)) == -1)
		client_error("CONNECT");
	return (sock);
}
