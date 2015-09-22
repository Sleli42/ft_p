/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleli42 <sleli42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/17 21:14:36 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/22 12:30:08 by sleli42          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

int		try_exec(t_server *sv, char *cmd)
{
	char	**argv_bin;

	//close(1);
	//dup2(sv->c_sock, 1);
	printf("%s\n", cmd);
	cmd = ft_epur_str(cmd);
	argv_bin = ft_strsplit(cmd, ' ');
	write(1, "here\n", 5);
	if (exec_right_binary(sv, argv_bin) == 1)
	{
		write(1, "here\n", 5);
		//write(sv->c_sock, "~> SUCCESS", 10);
		//dup2(1, STDOUT_FILENO);
		del_array(&argv_bin);
		return (1);
	}
	return (0);
}
int		good_access(char *bin)
{
	if (access(bin, F_OK) == 0)
		if (access(bin, X_OK) == 0)
			return (1);
	return (0);
}

char	*create_path(char *path, char *bin)
{
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	tmp = ft_strjoin(tmp, bin);
	return (tmp);
}

int		exec_right_binary(t_server *sv, char **argv_bin)
{
	int		ct;
	char	*bin_tmp;

	ct = 0;
	bin_tmp = NULL;
	while (sv->path2exec[ct])
	{
		bin_tmp = create_path(sv->path2exec[ct], argv_bin[0]);
		if (good_access(bin_tmp))
		{
		//	exec_binary(bin_tmp, argv_bin, sv->dupenv);
			return (1);
		}
		ft_strdel(&bin_tmp);
		ct++;
	}
	return (0);
}