/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/14 23:12:20 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/15 00:05:21 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//server
// htons: host to network short
# include <sys/socket.h>		// socket(int domain, int type, int protocol)
# include <sys/types.h>
# include <netinet/in.h>		// Internet Protocol family
# include <arpa/inet.h>		// definitions for internet operations
# include <netdb.h>			//definitions for network database operations
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

void	usage(char *s)
{
	printf("Usage: %s <port>\n", s);
	exit(-1);
}

int		create_server(int port)
{
	struct sockaddr_in	sins;
	struct protoent		*serv_p;
	int					sock;

	serv_p = getprotobyname("tcp");
	if (serv_p == 0)
		printf("getprotobyname() failed!\n");
	sock = socket(PF_INET, SOCK_STREAM, serv_p->p_proto);
	sins.sin_family = AF_INET;
	sins.sin_port = htons(port);
	sins.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr *)&sins, sizeof(sins)) == -1)
	{
		printf("bind() failed!\n");
		exit(2);
	}
	listen(sock, 42);
	return (sock);
}

int		main(int ac, char **av)
{
	int	port;
	int	sock;
	int	client_s;
	unsigned int		cslen;
	struct sockaddr_in	csins;
	char				buff[1021];
	int					r;

	if (ac != 2)
		usage(av[0]);
	port = atoi(av[1]);
	sock = create_server(port);
	client_s = accept(sock, (struct sockaddr *)&csins, &cslen);
	while ((r = read(client_s, buff, 1020)) > 0)
	{
		buff[r] = '\0';
		printf("received %d bytes: %s\n", r, buff);
	}
	close(client_s);
	close(sock);
	return (0);
}

//client

void	usage(char *s)
{
	printf("Usage: %s <addr> <port>\n", s);
	exit(-1);
}

int		create_client(char *addr, int port)
{
	struct sockaddr_in	sins;
	struct protoent		*client_p;
	int					sock;

	client_p = getprotobyname("tcp");
	if (client_p == 0)
		printf("getprotobyname() failed!\n");
	sock = socket(PF_INET, SOCK_STREAM, client_p->p_proto);
	sins.sin_family = AF_INET;
	sins.sin_port = htons(port);
	sins.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (struct sockaddr *)&sins, sizeof(sins)) == -1)
	{
		printf("connect() failed!\n");
		exit(2);
	}
	return (sock);
}

int		main(int ac, char **av)
{
	int	port;
	int	sock;

	if (ac != 3)
		usage(av[1]);
	port = atoi(av[2]);
	sock = create_client(av[1], port);
	write(sock, "Hello\n", 7);
	close(sock);
	return (0);
}

