/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:45:20 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/14 17:01:46 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FTP_H
# define	FTP_H

# include "libft.h"

# include <sys/socket.h>		// socket(int domain, int type, int protocol)
# include <sys/types.h>
# include <netinet/in.h>		// Internet Protocol family
# include <arpa/inet.h>		// definitions for internet operations
# include <netdb.h>			//definitions for network database operations

# include <stdio.h>
# include <string.h>
/* ==== REQUEST */
# define REQUEST_PUT 	1
# define REQUEST_GET 	2
# define REQUEST_DIR 	3

struct request
{
	int		req;
	int		nbbytes;	/* pour req_put only */
	char	*path;
};
/* ===== ANSWER */
# define ANSWER_OK		0
# define ANSWER_UNKNOW	1
# define ANSWER_ERROR	2

struct answer
{
	int		ans;
	int		nbbytes;	/* pour get only */
	int		errnum;
};
/* ==== SOCKET */
// struct sockaddr_in {
//         short   sin_family;       /* la famille de protocole 		*/
//         u_short sin_port;         /* numéro de port 					*/
//         struct  in_addr sin_addr; /* adresse IP de la machine 		*/
//         char    sin_zero[8];      /* remplissage pour faire 16 octets*/
// };
// struct in_addr {
//     unsigned long s_addr;  		// load with inet_aton()
// };
// struct sockaddr {
// 	u_short sa_family;
// 	char	sa_data[14];
// };
// struct protoent {
//     char  *p_name;    /* Nom officiel du protocole */
//     char **p_aliases; /* Liste d'alias             */
//     int    p_proto;   /* Numéro du protocole       */
// };
//int accept(int sockfd, struct sockaddr *adresse, socklen_t *longueur);
/*
*** client.c
*/
void	client(char *addr, int port);
/*
***	server.c
*/
void	server(int port);

#endif
