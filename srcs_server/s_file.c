/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubaujar <lubaujar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 15:29:06 by lubaujar          #+#    #+#             */
/*   Updated: 2015/09/29 22:16:46 by lubaujar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp.h"

/*
***
- sending && receiving files
- fix bugs exec

********
1.3  La requête

Dans les deux cas de transfert de fichier, il est nécessaire de connaître la taille du fichier transféré pour savoir si, lors d’un read détectant une fin de fichier (dû à la fermeture de la connexion), tout le contenu a bien été récupéré, ou si la connexion a été rompue trop tôt.

Une requête est donc de la forme :

#define REQUEST_PUT 1
#define REQUEST_GET 2
#define REQUEST_DIR 3
struct request {
    int  kind;
    char path[MAXPATH];
    int  nbbytes;        //pour PUT seulement
};
L’entier kind doit être REQUEST_PUT, REQUEST_GET ou REQUEST_DIR. La chaîne path contient le nom du fichier à écrire (put), lire (get) ou lister (dir). L’entier nbbytes contient la taille du fichier, lors d’un PUT seulement.

1.4  La réponse

Une réponse contient donc l’accusé (ack). Si la réponse est positive (ack vaut ANSWER_OK) et que la requête était un GET, nbbytes contient la taille du fichier que le serveur va envoyer. Si la réponse est négative (ANSWER_ERROR), errnum contient le code de l’erreur (valeur de la variable errno).

#define ANSWER_OK      0
#define ANSWER_UNKNOWN 1        // requête inconnue
#define ANSWER_ERROR   2        // erreur lors du traitement

struct answer {
    int  ack;
    int  nbbytes;  // pour GET seulement
    int  errnum;   // significatif ssi != 0 et ack == ANSWER_ERROR
};


***
*/

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
	int		fd;
	char	buff[MAX_SIZE];

	cmd = cmd + 4;
	if (check_file(cmd) == -1)
		display_return_and_explanation(cmd, all->sv->c_sock, 0, 'f');
	else
	{
		if ((fd = open(cmd, O_RDONLY)) == -1)
			server_error("OPEN");
		if (read(fd, buff, MAX_SIZE - 1) == -1)
			server_error("READ");
		// printf("%lu\n", sizeof(buff));
		all.
		send(all->sv->c_sock, buff, ft_strlen(buff), 0);
	}
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

