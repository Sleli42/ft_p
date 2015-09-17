/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:40:14 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/16 22:39:12 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

t_server	*init_server(void)
{
	t_server	*new;

	if (!(new = (t_server *)malloc(sizeof(t_server))))
		return (NULL);
	else
	{
		new->sock = 0;
		new->c_sock = 0;
		new->cslen = 0;
	}
	return (new);
}

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