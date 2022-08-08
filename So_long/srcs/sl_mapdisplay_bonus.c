/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_mapdisplay_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:38:05 by schuah            #+#    #+#             */
/*   Updated: 2022/08/06 17:24:12 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sl_bonus.h"

/* Sets the default sprite images for each different objects in the map
** Also sets the initial existance (0) of the teleporters */
void	sl_defaultmap(t_gm *gm)
{
	gm->map.pickup_img.ref = mlx_xpm_file_to_image(gm->mlx, "sprites/c.xpm",
			&gm->map.pickup_img.size.x, &gm->map.pickup_img.size.y);
	gm->map.wall_img.ref = mlx_xpm_file_to_image(gm->mlx, "sprites/1.xpm",
			&gm->map.wall_img.size.x, &gm->map.wall_img.size.y);
	gm->map.exit_img.ref = mlx_xpm_file_to_image(gm->mlx, "sprites/e.xpm",
			&gm->map.exit_img.size.x, &gm->map.exit_img.size.y);
	gm->map.spc_img.ref = mlx_xpm_file_to_image(gm->mlx, "sprites/0.xpm",
			&gm->map.spc_img.size.x, &gm->map.spc_img.size.y);
	gm->map.eblock_img.ref = mlx_xpm_file_to_image(gm->mlx, "sprites/x.xpm",
			&gm->map.eblock_img.size.x, &gm->map.eblock_img.size.y);
	gm->map.tprt.tel_img.ref = mlx_xpm_file_to_image(gm->mlx, "sprites/t.xpm",
			&gm->map.tprt.tel_img.size.x, &gm->map.tprt.tel_img.size.y);
	gm->map.tprt.rec_img.ref = mlx_xpm_file_to_image(gm->mlx, "sprites/r.xpm",
			&gm->map.tprt.rec_img.size.x, &gm->map.tprt.rec_img.size.y);
	gm->map.tprt.t_exist = 0;
	gm->map.tprt.r_exist = 0;
}

/* Displays the number of moves in the top left corner of the window */
static void	sl_displaysteps(t_gm *gm)
{
	char	*str;
	char	*temp;
	char	*nbr;

	nbr = ft_itoa(gm->player.moves);
	str = ft_strjoin("Steps: ", nbr);
	mlx_string_put(gm->mlx, gm->window.ref, STEPS_X, STEPS_Y, BLACK, str);
	free(nbr);
	free(str);
	nbr = ft_itoa(gm->player.pickups);
	str = ft_strjoin("Collected: ", nbr);
	free(nbr);
	temp = str;
	str = ft_strjoin(str, "/");
	free(temp);
	nbr = ft_itoa(gm->map.n_pick);
	temp = str;
	str = ft_strjoin(str, nbr);
	free(nbr);
	free(temp);
	free(str);
	mlx_string_put(gm->mlx, gm->window.ref, STEPS_X, STEPS_Y
		+ PAD_Y, BLACK, str);
}

/* Displays the sprites according to the map.
** Also sets the initial position of the player and the enemy */
static void	sl_displayall(t_gm *gm, int x, int y, char pos)
{
	if (gm->map.layout[y][x] == 'E')
	{
		mlx_put_image_to_window(gm->mlx, gm->window.ref,
			gm->map.exit_img.ref, (x * PLY_MVSPD), (y * PLY_MVSPD));
		if (gm->player.pickups < gm->map.n_pick)
			mlx_put_image_to_window(gm->mlx, gm->window.ref,
				gm->map.eblock_img.ref, (x * PLY_MVSPD), (y * PLY_MVSPD));
	}
	if (pos == 'P' && gm->player.alive == 0)
	{
		gm->player.pos.x = x * PLY_MVSPD;
		gm->player.pos.y = y * PLY_MVSPD;
		gm->player.alive = 1;
	}
	else if (pos == 'B' && gm->enemy.alive == 0)
	{
		gm->enemy.pos.x = x * PLY_MVSPD;
		gm->enemy.pos.y = y * PLY_MVSPD;
		gm->enemy.alive = 1;
	}
}

/* Displays the teleporters and set their positions into the gm */
static void	sl_displayteleport(t_gm *gm, int x, int y, char pos)
{
	if (pos == 'T')
	{
		mlx_put_image_to_window(gm->mlx, gm->window.ref,
			gm->map.tprt.tel_img.ref, (x * PLY_MVSPD), (y * PLY_MVSPD));
		gm->map.tprt.tel_pos.x = x * PLY_MVSPD;
		gm->map.tprt.tel_pos.y = y * PLY_MVSPD;
	}
	if (pos == 'R')
	{
		mlx_put_image_to_window(gm->mlx, gm->window.ref,
			gm->map.tprt.rec_img.ref, (x * PLY_MVSPD), (y * PLY_MVSPD));
		gm->map.tprt.rec_pos.x = x * PLY_MVSPD;
		gm->map.tprt.rec_pos.y = y * PLY_MVSPD;
	}
}

/* Displays the entire map and its sprites onto the window */
void	sl_displaymap(t_gm *gm)
{
	int	x;
	int	y;

	y = -1;
	while (++y < gm->map.y)
	{
		x = -1;
		while (gm->map.layout[y][++x] != 0)
		{
			mlx_put_image_to_window(gm->mlx, gm->window.ref,
				gm->map.spc_img.ref, (x * PLY_MVSPD), (y * PLY_MVSPD));
			if (gm->map.layout[y][x] == '1')
				mlx_put_image_to_window(gm->mlx, gm->window.ref,
					gm->map.wall_img.ref, (x * PLY_MVSPD), (y * PLY_MVSPD));
			if (gm->map.layout[y][x] == 'C')
				mlx_put_image_to_window(gm->mlx, gm->window.ref,
					gm->map.pickup_img.ref, (x * PLY_MVSPD), (y * PLY_MVSPD));
			sl_displayteleport(gm, x, y, gm->map.layout[y][x]);
			sl_displayall(gm, x, y, gm->map.layout[y][x]);
		}
	}
	sl_displaysteps(gm);
}
