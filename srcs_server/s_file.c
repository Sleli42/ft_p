/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 15:29:06 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/29 10:49:51 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

// int
//      stat(const char *restrict path, struct stat *restrict buf);

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

void	send_file(t_all *all, char *cmd)
{
	//int		fd;
	char	*buff;

	buff = NULL;
	cmd = cmd + 4;
	if (check_file(cmd) == -1)
		display_return_and_explanation(cmd, all->sv->c_sock, 0, 'f');
	else

		//if ((fd = open(cmd, O_RDONLY)) == -1);
			//error_server("OPEN");
	/*send(all->sv->c_sock, pwd, ft_strlen(pwd), 0);*/
}

void	get_file(t_all *all, char *cmd)
{
	printf("get_file()\n");
	printf("get_file() CMD: %s\n", cmd);
	printf("get_file() low pwd: %s\n", all->env->lowest_pwd);
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

