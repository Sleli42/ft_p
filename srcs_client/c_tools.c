/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 23:50:21 by lubaujar          #+#    #+#             */
/*   Updated: 2015/10/26 14:53:14 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

void	read_socket_return(int sock2read)
{
	int		r;
	char	buff[MAX_SIZE];

	ft_memset(buff, 0, ft_strlen(buff));
	while ((r = recv(sock2read, buff, MAX_SIZE - 1, 0)) > 0)
	{
		buff[r] = 0;
		write(1, buff, ft_strlen(buff));
		if (buff[0] == '~' || buff[0] == 0 || buff[0] == '\n')
			return ;
	}
}

void	write_socket(t_all *all, int sock)
{
	int		r;
	char	*buff;

	buff = NULL;
	(void)all;
	while (21)
	{
		write(1, "$: ", 3);
		while (get_next_line(0, &buff) > 0)
		{
			//init_request(all, buff);
			if ((r = send(sock, buff, MAX_SIZE - 1, 0)) < 0)
				client_error("SEND");
			if (ft_strcmp(buff, "quit") == 0)
				close_and_exit(sock);
			read_socket_return(sock);
			break ;
		}
		//close_and_exit(sock);
	}
}

void	close_and_exit(int sock)
{
	write(1, "quit\n", 5);
	close(sock);
	exit(1);
}

int		check_file(char *file)
{
	t_stat	buff;

	if (lstat(file, &buff) == -1)
		return (-1);
	else
	{
		if (get_type(buff.st_mode) == '-')
			return (1);
	}
	return (0);
}

char	get_type(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISBLK(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('f');
	return (0);
}
