/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_mapcheck_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:08:30 by schuah            #+#    #+#             */
/*   Updated: 2022/08/06 17:22:53 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sl_bonus.h"

/* Checks the format of each file (.ber) passed as an argument */
void	sl_checkfileformat(t_gm *gm, int ac, char **av)
{
	int		i;
	int		j;
	int		wc;
	int		errno;
	char	**input;

	if (ac < 2)
		sl_fullexit("Error\nNo file input\n", 2);
	i = 0;
	errno = 0;
	while (++i < ac)
	{
		wc = ft_getwc(av[i], '.');
		input = ft_split(av[i], '.');
		if (ft_strncmp(input[wc - 1], "ber", 4) != 0 && errno == 0)
			errno = 1;
		gm->map.total_level++;
		j = -1;
		while (++j < wc)
			free(input[j]);
		free(input);
	}
	if (errno == 1)
		sl_fullexit("Error\nNo file input\n", 2);
}

/* Sets default values for special tiles */
static void	sl_setvalues(t_gm *gm, char c)
{
	if (c == 'E')
		gm->map.exit++;
	if (c == 'P')
		gm->map.start++;
	if (c == 'C')
		gm->map.n_pick++;
	if (c == 'T')
		gm->map.tprt.t_exist = 1;
	if (c == 'R')
		gm->map.tprt.r_exist = 1;
}

/* Checks the content of each map, returns 1 when
** the map does not meet the criteria of a functional map */
static int	sl_checkmapcontent(t_gm *gm, char *str, int line)
{
	int	i;

	i = -1;
	while (str[++i] != '\0' && str[i] != '\n')
	{
		if (str[i] != '1' && (line == 0 || line == -1))
			return (1);
		if (i == 0 && str[i] != '1')
			return (1);
		if (str[i] != '1' && str[i] != '0' && str[i] != 'P'
			&& str[i] != 'C' && str[i] != 'E' && str[i] != 'B'
			&& str[i] != 'T' && str[i] != 'R')
			return (1);
		sl_setvalues(gm, str[i]);
	}
	if (gm->map.x == 0)
		gm->map.x = i;
	if ((str[i] == '\n' && line == -1) || i != gm->map.x || str[i - 1] != '1')
		return (1);
	return (0);
}

/* Loops through every y line of the map to read its content.
** Exits the game if there is an error */
void	sl_runthroughmap(t_gm *gm, char *str, char *prev, int fd)
{
	int	line;

	line = 0;
	while (str != NULL)
	{
		if (sl_checkmapcontent(gm, str, line++))
		{
			free(str);
			close(fd);
			sl_fullexit("Error\nInvalid map template\n", 2);
		}
		gm->map.y++;
		str = get_next_line(fd);
		if (str == NULL && sl_checkmapcontent(gm, prev, -1))
		{
			free(prev);
			close(fd);
			sl_fullexit("Error\nInvalid map template\n", 2);
		}
		free(prev);
		prev = str;
	}
}
