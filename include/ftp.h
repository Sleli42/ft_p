/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:45:20 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/16 00:38:40 by lubaujar         ###   ########.fr       */
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
	char				cmd[1021];
}						t_server;

typedef	struct			s_action
{
	char				*action_name;
	void				(*f)(t_server *);
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
void		try_builtins(t_server *sv);
void		display_pwd(t_server *sv);
void		goto_directory(t_server *sv);
void		stop_connect(t_server *sv);
/*
***	s_tools.c
*/
void		read_socket(t_server *sv);
#endif
