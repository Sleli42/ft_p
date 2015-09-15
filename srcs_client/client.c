/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
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

int		main(int ac, char **av)
{
	int	port;
	int	sock;
	char	*buff;

	if (ac != 3)
		usage(av[1]);
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	while (get_next_line(0, &buff) > 0)
		write(sock, buff, ft_strlen(buff));
	close(sock);
	return (0);
}
