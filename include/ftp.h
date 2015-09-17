/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:45:20 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/17 18:43:18 by lubaujar         ###   ########.fr       */
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
	struct sockaddr_in	csins;
	int					sock;
	int					c_sock;		/* client socket -> accept() */
	unsigned int		cslen;
}						t_server;

typedef	struct			s_action
{
	char				*action_name;
	void				(*f)(char *, int);
}						t_action;

/*
*** ========================= client
*/

/*
*** c_error.c
*/
void		client_error(char *err);
/*
***	c_init.c
*/
void		usage(char *s);
int			create_client(char *addr, int port);
/*
***	c_tools.c
*/
void		read_socket_return(int sock2read);
void		write_socket(int sock);
void		close_and_exit(int sock);
/*
***	========================= server
*/

/*
*** s_error.c
*/
void		server_error(char *err);
/*
***	s_init.c
*/
t_server	*init_server(void);
void		usage(char *s);
int			create_server(int port);
/*
***	s_builtins.c
*/
int			try_builtins(char *cmd, int c_sock);
void		display_pwd(char *cmd, int c_sock);
void		goto_directory(char *cmd, int c_sock);
void		stop_connect(char *cmd, int c_sock);
/*
***	s_tools.c
*/
void		read_socket(t_server *sv);
#endif
