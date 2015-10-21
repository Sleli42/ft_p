/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/13 14:45:20 by lubaujar          #+#    #+#             */
/*   Updated: 2015/10/21 13:12:25 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FTP_H
# define	FTP_H

# include "libft.h"

# include <sys/socket.h>		// socket(int domain, int type, int protocol)
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>			// stat file
# include <netinet/in.h>		// Internet Protocol family
# include <arpa/inet.h>		// definitions for internet operations
# include <netdb.h>			//definitions for network database operations
# include <unistd.h>
# include <signal.h>

# include <stdio.h>
# define		MAX_SIZE		32768
# define 		MAX_PATH		91

typedef struct stat		t_stat;

typedef struct			s_server
{
	struct sockaddr_in	csins;
	int					sock;
	int					c_sock;		/* client socket -> accept() */
	unsigned int		cslen;
}						t_server;

typedef struct			s_env
{
	char				*lowest_pwd;
	char				**dupenv;
	char				**path2exec;
}						t_env;

# define				REQUEST_PUT		1
# define				REQUEST_GET		2
# define				REQUEST_DIR		3

typedef struct			s_request
{
	int					req;
	char				*path;
	int					nbbytes;		//pour PUT seulement
}						t_request;

# define				ANSWER_OK		0
# define				ANSWER_UNKNOW	1
# define				ANSWER_ERROR	2

typedef struct			s_answer
{
	int					acc;
	int					err;
	size_t				nbbytes;		// pour GET seulement
}						t_answer;

typedef struct			s_all
{
	t_server			*sv;
	t_env				*env;
	t_request			*request;
	t_answer			*answer;
}						t_all;

typedef	struct			s_action
{
	char				*action_name;
	void				(*f)(t_all *, char *);
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
t_all		*c_init_all(void);
/*
***	c_tools.c
*/
void		read_socket_return(int sock2read);
void		write_socket(t_all *all, int sock);
void		close_and_exit(int sock);

void	init_request(t_all *all, char *buff);
/*
***	========================= server
*/
void		loop(t_all *all);
/*
*** debug.c
*/
void		display_tab(char **tab);
/*
*** s_error.c
*/
void		server_error(char *err);
/*
***	s_init.c
*/
t_all		*s_init_all(char **env);
t_env		*init_env(char **env);
t_server	*init_server(void);
void		usage(char *s);
int			create_server(int port);
/*
***	s_builtins.c
*/
int			try_builtins(t_all *all, char *cmd);
void		display_pwd(t_all *all, char *cmd);
void		goto_directory(t_all *all, char *cmd);
void		stop_connect(t_all *all, char *cmd);
/*
***	s_exec.c
*/
void		try_exec(t_all *all, char *cmd);
int			good_access(char *bin);
char		*create_path(char *path, char *bin);
int			exec_right_binary(t_all *all, char **argv_bin);
void		exec_binary(char *bin, char **argv_bin, char **env);
/*
***	s_file.c
*/
int			check_file(char *file);
void		send_file(t_all *all, char *cmd);
void		get_file(t_all *all, char *cmd);
char		get_type(mode_t mode);
/*
***	s_tools.c
*/
void		display_return_and_explanation(char *err, int sock2write, int msg, int spec);
void		read_socket(t_all *all);
void		display_header(t_all *all, char *buff);

#endif
