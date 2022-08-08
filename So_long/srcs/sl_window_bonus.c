/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_window_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:30:58 by schuah            #+#    #+#             */
/*   Updated: 2022/08/06 17:16:55 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sl_bonus.h"

/* Starts the next level */
static int	sl_nextlevel(t_gm *gm)
{
	mlx_destroy_window(gm->mlx, gm->window.ref);
	gm->mlx = mlx_init();
	sl_getmap(gm);
	sl_newwindow(gm, (gm->map.x * PLY_MVSPD),
		(gm->map.y * PLY_MVSPD), "so_long");
	sl_defaultplayer(gm);
	sl_defaultmap(gm);
	sl_putimage(gm);
	sl_hooks(gm);
	mlx_loop(gm->mlx);
	return (0);
}

/* Creates a new window with the size scaling based on the map */
void	sl_newwindow(t_gm *gm, int height, int width, char *name)
{
	gm->window.ref = mlx_new_window(gm->mlx, height, width, name);
	gm->window.frame = 0;
	gm->window.size.x = height;
	gm->window.size.y = width;
}

/* Will be called when the level is complete.
** Loads the next level if there is one or do a full exit */
int	sl_exit(t_gm *gm)
{
	gm->map.level++;
	if (gm->map.level == gm->map.total_level)
		sl_fullexit("Thanks for playing!\n", 1);
	else if (sl_nextlevel(gm))
		sl_fullexit("Thanks for playing!\n", 1);
	return (0);
}

void	sl_objectanim(t_gm *gm)
{
	if (gm->window.frame == FPS)
	{
		if (gm->map.tprt.t_exist)
			gm->map.tprt.tel_pos.y += 1;
		if (gm->map.tprt.r_exist)
			gm->map.tprt.rec_pos.y += 1;
	}
	else if (gm->window.frame >= FPS * 2)
	{
		if (gm->map.tprt.t_exist)
			gm->map.tprt.tel_pos.y -= 1;
		if (gm->map.tprt.r_exist)
			gm->map.tprt.rec_pos.y -= 1;
	}
	if (gm->map.tprt.t_exist)
		mlx_put_image_to_window(gm->mlx, gm->window.ref,
			gm->map.tprt.rec_img.ref, gm->map.tprt.rec_pos.x,
			gm->map.tprt.rec_pos.y);
	if (gm->map.tprt.r_exist)
		mlx_put_image_to_window(gm->mlx, gm->window.ref,
			gm->map.tprt.tel_img.ref, gm->map.tprt.tel_pos.x,
			gm->map.tprt.tel_pos.y);
}

/* Displays everything from above onto the window */
void	sl_putimage(t_gm *gm)
{
	sl_displaymap(gm);
	mlx_put_image_to_window(gm->mlx, gm->window.ref,
		gm->player.image.ref, gm->player.pos.x, gm->player.pos.y);
	if (gm->enemy.alive == 1)
		mlx_put_image_to_window(gm->mlx, gm->window.ref,
			gm->enemy.image.ref, gm->enemy.pos.x, gm->enemy.pos.y);
}
