/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:44:50 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/16 21:54:01 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int		main(int ac, char **av)
{
	t_server	*sv;
	int			port;

	if (ac != 2)
		usage(av[0]);
	port = atoi(av[1]);
	sv = init_server();
	sv->sock = create_server(port);
	if ((sv->c_sock = accept(sv->sock, (struct sockaddr *)&(sv->csins),
		&(sv->cslen))) == -1)
		server_error("ACCEPT");
	else
		read_socket(sv);
	return (0);
}
