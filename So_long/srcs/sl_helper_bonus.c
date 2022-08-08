/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_helper_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:34:02 by schuah            #+#    #+#             */
/*   Updated: 2022/08/06 17:16:32 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sl_bonus.h"

/* Prints all information needed for debugging */
void	sl_printply(t_gm *gm)
{
	ft_printf("----------------------------------------\n");
	ft_printf("Player Pickups: %d\n", gm->player.pickups);
	ft_printf("Player Moves: %d\n", gm->player.moves);
	ft_printf("Player X: %d\tPlayer Y: %d\n", gm->player.pos.x, gm->player.pos.y);
	ft_printf("Enemy X: %d\tEnemy Y: %d\n", gm->enemy.pos.x, gm->enemy.pos.y);
	ft_printf("Current Map: %s\n", gm->map.level_lst[gm->map.level]);
	ft_printf("Map Width: %d\tMap Height: %d\n",
		gm->map.x * PLY_MVSPD, gm->map.y * PLY_MVSPD);
	ft_printf("N_pickups: %d\n", gm->map.n_pick);
	ft_printf("----------------------------------------\n");
}

/* Prints the map layout in from the file */
void	sl_printmap(t_gm *gm)
{	
	int	x;
	int	y;

	y = -1;
	while (++y < gm->map.y)
	{
		x = -1;
		while (++x < gm->map.x)
			ft_printf("%c", gm->map.layout[y][x]);
		ft_printf("\n");
	}
}

/* Frees everything that used malloc in the gm's struct */
void	sl_freeeverything(t_gm *gm)
{
	int	y;

	y = -1;
	while (gm->map.layout[++y] != 0)
		free(gm->map.layout[y]);
	free(gm->map.layout);
	y = -1;
	while (++y < gm->map.total_level)
		free(gm->map.level_lst[y]);
	free(gm->map.level_lst);
}
