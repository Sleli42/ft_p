/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 22:40:14 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/22 22:55:28 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

t_all		*init_all(char **env)
{
	t_all	*new;

	if (!(new = (t_all *)malloc(sizeof(t_all))))
		return (NULL);
	else
	{
		new->sv = init_server();
		new->env = init_env(env);
	}
	return (new);
}

t_server	*init_server(void)
{
	t_server	*new;

	if (!(new = (t_server *)malloc(sizeof(t_server))))
		return (NULL);
	else
	{
		new->sock = 0;
		new->c_sock = 0;
		new->cslen = 0;
	}
	return (new);
}

t_env		*init_env(char **env)
{
	t_env	*new;
	char	*buff;

	buff = NULL;
	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	else
	{
		new->lowest_pwd = getcwd(buff, 42);
		new->dupenv = env;
		new->path2exec = ft_strsplit(env[0] + 5, ':');
	}
	return (new);
}

void		usage(char *s)
{
	ft_putstr("Usage: ");
	ft_putstr(s);
	ft_putstr(" <port>\n");
	exit(-1);
}

int			create_server(int port)
{
	struct sockaddr_in	sins;
	struct protoent		*serv_p;
	int					sock;

	if ((serv_p = getprotobyname("tcp")) == 0)
		server_error("GETPROTOBYNAME");
	sock = socket(PF_INET, SOCK_STREAM, serv_p->p_proto);
	sins.sin_family = AF_INET;
	sins.sin_port = htons(port);
	sins.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr *)&sins, sizeof(sins)) == -1)
		server_error("BIND");
	listen(sock, 42);
	return (sock);
}
