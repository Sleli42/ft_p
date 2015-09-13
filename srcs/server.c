/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:44:50 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/13 18:41:32 by lubaujar         ###   ########.fr       */
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


void		server(void)
{
	int					val;
	int					ss;
	struct sockaddr_in	soc_in;
	int					len;
	int					f;
	struct sockaddr_in	from;

	/* socket Internet, de type stream (fiable, bi-directionnel) */
	ss = socket(PF_INET, SOCK_STREAM, 0);
	/* Force la réutilisation de l'adresse si non allouée */
	val = 1;
	setsockopt(ss, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	/* Nomme le socket: socket inet, port PORT, adresse IP quelconque */
	soc_in.sin_family = AF_INET;
	soc_in.sin_addr.s_addr = htonl(INADDR_ANY);
	soc_in.sin_port = htons(2121); /* 2121 */
	bind(ss, (struct sockaddr *)&soc_in, sizeof(soc_in));
	/* Prépare le socket à la réception de demande de connexions */
	listen(ss, 5);
	while (21)
	{
		/* Accepte une connexion.
         * Les paramètres `from' et `len' peuvent etre NULL. */
		len = sizeof(from);
		f = accept(ss, (struct sockaddr *)&from, (unsigned int *)&len);
	}
	return ;
}
