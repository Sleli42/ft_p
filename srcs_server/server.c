/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:44:50 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/15 22:43:16 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	usage(char *s)
{
	ft_putstr("Usage: ");
	ft_putstr(s);
	ft_putstr(" <port>\n");
	exit(-1);
}

int		create_server(int port)
{
	struct sockaddr_in	sins;
	struct protoent		*serv_p;
	int					sock;

	if ((serv_p = getprotobyname("tcp")) == 0)
		server_error("GETPROTOBYNAME");
	sock = socket(PF_INET, SOCK_STREAM, serv_p->p_proto);
	sins.sin_family = AF_INET;
	sins.sin_port = htons(port);
	sins.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr *)&sins, sizeof(sins)) == -1)
		server_error("BIND");
	listen(sock, 42);
	return (sock);
}

int		main(int ac, char **av)
{
	t_client	*s_all;
	int			port;

	if (ac != 2)
		usage(av[0]);
	port = atoi(av[1]);
	s_all = init_server();
	sock = create_server(port);
	if ((client_s = accept(sock, (struct sockaddr *)&csins, &cslen)) == -1)
		server_error("ACCEPT");
	else
		read_socket(client_s);
	close(client_s);
	close(sock);
	return (0);
}
