/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:45:20 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/15 22:43:14 by lubaujar         ###   ########.fr       */
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
# include <unistd.h>

# include <stdio.h>

typedef struct			s_server
{
	int					sock;
	int					c_sock;		/* client socket -> accept() */
	struct sockaddr_in	csins;
	unsigned int		cslen;
}						t_server;

typedef	struct			s_action
{
	char				*action_name;
	void				(*f)(char *);
}						t_action;
/*
*** c_error.c
*/
void	client_error(char *err);
/*
*** client.c
*/
void	usage(char *s);
int		create_client(char *addr, int port);
void	client(char *addr, int port);
/*
***	c_init.c
*/
t_client	*init_client(void);
/*
*** s_error.c
*/
void	server_error(char *err);
/*
***	server.c
*/
void	usage(char *s);
int		create_server(int port);
void	server(int port);
/*
***	s_init.c
*/
t_server	*init_server(void);
/*
***	s_builtins.c
*/
void	try_builtins(char *buff);
void	display_pwd(char *s);
void	goto_directory(char *buff);
/*
***	s_tools.c
*/
void	read_socket(int	sock);
#endif
