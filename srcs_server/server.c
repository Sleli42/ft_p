/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:44:50 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/14 16:21:13 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

/* ==== SERVER */
// int socket (int domain, int type, int protocol);
// int setsockopt (int s, int level, int optname, char *optval, int optlen);
// int bind (int s, struct sockaddr *name, int namelen);
	/* Fournir un nom à une socket  */
// int listen (int s, int backlog);
	/* Attendre des connexions sur une socket   */
// int accept (int s, struct sockaddr *addr, int *addrlen);
	/*Accepter une connexion sur une socket  */
// int  setsockopt(int  s, int level, int optname, const void
//      *optval, socklen_t optlen);


void	server(char *addr, int port)
{
	int					sock_s;
	struct protoent		*sp;
	struct sockaddr_in	sock_in;

	sp = getprotobyname("tcp");
	if (!sp)
		printf("[server] getprotobyname() failed!\n");
	sock_s = socket(PF_INET, SOCK_STREAM, sp->p_proto);
	if (sock_s == -1)
		printf("[server] socket() failed!\n");
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(port);
	sock_in.sin_addr.s_addr = inet_addr(addr);
	bind(sock_s, (struct sockaddr *)&sock_in, sizeof(sock_in));
	/* Prépare le socket à la réception de demande de connexions */
 	if (listen(sock_s, 3) == -1)
 		printf("[server] listen() failed!\n");
 	while (21)
 	{
 		accept(sock_s, (struct sockaddr *)&sock_in, (unsigned int *)&sock_in);
 	}
}

int		main(int ac, char **av)
{
	int		port;
	char	*addr;

	(void)ac;
	addr = ft_strdup(av[1]);
	port = ft_atoi(av[2]);
	printf("addr: %s\n", addr);
	printf("port: %d\n", port);
	server(addr, port);
	return (0);
}

// void		server(void)
// {
// 	int					val;
// 	int					ss;
// 	struct sockaddr_in	soc_in;
// 	int					len;
// 	int					f;
// 	struct sockaddr_in	from;

// 	/* socket Internet, de type stream (fiable, bi-directionnel) */
// 	ss = socket(PF_INET, SOCK_STREAM, 0);
// 	/* Force la réutilisation de l'adresse si non allouée */
// 	val = 1;
// 	setsockopt(ss, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
// 	/* Nomme le socket: socket inet, port PORT, adresse IP quelconque */
// 	soc_in.sin_family = AF_INET;
// 	soc_in.sin_addr.s_addr = htonl(INADDR_ANY);
// 	soc_in.sin_port = htons(2121); /* 2121 */
// 	bind(ss, (struct sockaddr *)&soc_in, sizeof(soc_in));
// 	/* Prépare le socket à la réception de demande de connexions */
// 	listen(ss, 5);
// 	while (21)
// 	{
// 		/* Accepte une connexion.
//          * Les paramètres `from' et `len' peuvent etre NULL. */
// 		len = sizeof(from);
// 		f = accept(ss, (struct sockaddr *)&from, (unsigned int *)&len);
// 	}
// 	return ;
// }
