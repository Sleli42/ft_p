/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:44:50 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/14 16:17:00 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ==== CLIENT */
// u_long htonl (u_long hostlong);
// u_short htons (u_short hostshort);
// struct hostent *gethostbyname (char *name);
// int socket (int domain, int type, int protocol);
// int connect (int s, struct sockaddr *name, int namelen);

#include "ftp.h"

void	client(char *addr, int port)
{
	int					sock_c;
	struct protoent		*sp;
	struct sockaddr_in	sins;

	sp = getprotobyname("tcp");
	if (!sp)
		printf("[client] getprotobyname() failed!\n");
	sock_c = socket(PF_INET, SOCK_STREAM, sp->p_proto);
	if (sock_c == -1)
		printf("[client] socket() failed!\n");
	/* Remplissage de la structure `sins' avec la famille de protocoles Internet,
     * le numéro IP de la machine à contacter et le numéro de port. */
	sins.sin_family = AF_INET;
	sins.sin_port = htons(port);
	sins.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock_c, (struct sockaddr *)&sins, sizeof(sins)) == -1)
		printf("connect() failed!\n");
	else
		printf("Waiting connect . . .\n");
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
	client(addr, port);
	return (0);
}


// void		client(char	*s)
// {
// 	int					sc;
// 	struct hostent		*sp;
// 	struct sockaddr_in	sins;
// /* Obtention d'information au sujet de la machine `serverhost' */
// 	sp = gethostbyname(s); /* 127.0.0.1 */
// 	if (!sp)
// 		exit(1);
// 	else
// 		printf("hostname: %s\n", sp->h_name);
// 	// int		i = 0;
// 	// while (sp->h_addr_list[i])
// 	// 	printf("%s\n", sp->h_addr_list[i++]);
// 	// exit(1);
// 	if (sp == NULL)
// 	{
// 		printf("gethostbyname: %s not found\n", s);
// 		exit(1);
// 	}
// /* Création d'un socket Internet de type stream (fiable, bi-directionnel) */
// 	sc = socket(PF_INET, SOCK_STREAM, 0);	/* PF_INET: Internet version 4 protocols */
//  SOCK_STREAM: type provides sequenced, reliable, two-way connection based byte streams.
// 	if (sc == -1)
// 	{
// 		printf("Socket failed\n");
// 		exit(1);
// 	}
// 	/* Remplissage de la structure `sins' avec la famille de protocoles Internet,
//      * le numéro IP de la machine à contacter et le numéro de port. */
// 	sins.sin_family = AF_INET; /* AF_INET Désigne une connection inter-réseaux */
// 	ft_memcpy(&sins.sin_addr, sp->h_addr_list[0], sp->h_length);
// 	sins.sin_port = htons(2121); /* 2121 */
// 	/* Tentative d'établissement de la connexion. */
// 	/* connect() : Débuter une connexion sur une socket */
// 	if (connect(sc, (struct sockaddr *)&sins, sizeof(sins)) == -1)
// 	{
// 		printf("Connect failed\n");
// 		exit(1);
// // 	}
// 	else
// 		printf("Waiting connect . . .\n");
// 	return ;
// }
