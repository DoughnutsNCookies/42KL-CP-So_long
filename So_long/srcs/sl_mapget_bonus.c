/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_mapget_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:28:56 by schuah            #+#    #+#             */
/*   Updated: 2022/08/06 17:16:23 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sl_bonus.h"

/* Checks whether the map file exists
** and fulfils the criteria of being a functional map */
static void	sl_checkmapformat(t_gm *gm, char *map)
{
	int		fd;
	int		line;
	char	*str;
	char	*prev;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		sl_fullexit("Error\nCannot open file\n", 2);
	str = get_next_line(fd);
	prev = str;
	line = 0;
	sl_runthroughmap(gm, str, prev, fd);
	if (gm->map.start <= 0 || gm->map.exit <= 0 || gm->map.n_pick <= 0)
		sl_fullexit("Error\nCannot open file\n", 2);
	close(fd);
}

/* Sets each respective map data into the gm according to the map */
static void	sl_setmap(t_gm *gm, char *map)
{
	int		fd;
	int		x;
	int		y;
	char	*str;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		sl_fullexit("Error\nCannot open file\n", 2);
	str = get_next_line(fd);
	gm->map.layout = malloc(sizeof(char *) * gm->map.y + 1);
	y = 0;
	while (str != NULL)
	{
		x = -1;
		gm->map.layout[y] = malloc(sizeof(char) * gm->map.x + 1);
		while (str[++x] != '\0' && str[x] != '\n')
			gm->map.layout[y][x] = str[x];
		gm->map.layout[y][x] = '\0';
		y++;
		free(str);
		str = get_next_line(fd);
	}
}

/* Gets and stores all the file path and name and stores them into the gm */
void	sl_getfiles(t_gm *gm, char **av)
{
	int	i;

	i = -1;
	gm->map.level_lst = malloc(sizeof(char *) * (gm->map.total_level + 1));
	while (++i < gm->map.total_level)
		gm->map.level_lst[i] = ft_strdup(av[i + 1]);
	gm->map.level_lst[i] = 0;
}

/* Get every information needed to store into the gm */
void	sl_getmap(t_gm *gm)
{
	gm->map.exit = 0;
	gm->map.start = 0;
	gm->map.n_pick = 0;
	gm->map.x = 0;
	gm->map.y = 0;
	sl_checkmapformat(gm, gm->map.level_lst[gm->map.level]);
	sl_setmap(gm, gm->map.level_lst[gm->map.level]);
}
