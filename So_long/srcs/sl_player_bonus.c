/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_player_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:26:22 by schuah            #+#    #+#             */
/*   Updated: 2022/08/06 17:25:01 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sl_bonus.h"

/* Sets the default values of both the player and the enemy */
void	sl_defaultplayer(t_gm *gm)
{
	gm->player.alive = 0;
	gm->player.pickups = 0;
	gm->player.moves = 0;
	gm->player.image.ref = mlx_xpm_file_to_image(gm->mlx, "sprites/p.xpm",
			&gm->player.image.size.x, &gm->player.image.size.y);
	gm->enemy.alive = 0;
	gm->enemy.pos.x = 0;
	gm->enemy.pos.y = 0;
	gm->enemy.image.ref = mlx_xpm_file_to_image(gm->mlx, "sprites/b.xpm",
			&gm->enemy.image.size.x, &gm->enemy.image.size.y);
}

/* Plays the player animation every FPS frames */
void	sl_playeranim(t_gm *gm)
{
	if (gm->window.frame == FPS)
		gm->player.pos.y += 1;
	else if (gm->window.frame >= FPS * 2)
	{
		if (gm->player.pos.y % PLY_MVSPD == 1)
			gm->player.pos.y -= 1;
		else if (gm->player.pos.y % PLY_MVSPD == PLY_MVSPD - 1)
			gm->player.pos.y += 1;
	}
	mlx_put_image_to_window(gm->mlx, gm->window.ref,
		gm->player.image.ref, gm->player.pos.x, gm->player.pos.y);
}

/* Moves the enemy depending on the keycode pressed. 
** Also Checks whether the move is possible (ie. Wall) */
void	sl_movement(t_gm *gm, int keycode)
{
	if (keycode == KEY_W && (gm->map.layout[(gm->player.pos.y / PLY_MVSPD) - 1]
			[gm->player.pos.x / PLY_MVSPD] != '1'))
	{
		gm->player.pos.y -= PLY_MVSPD;
		gm->player.moves++;
	}
	if (keycode == KEY_A && (gm->map.layout[(gm->player.pos.y / PLY_MVSPD)]
			[(gm->player.pos.x / PLY_MVSPD) - 1] != '1'))
	{
		gm->player.pos.x -= PLY_MVSPD;
		gm->player.moves++;
	}
	if (keycode == KEY_S && (gm->map.layout[(gm->player.pos.y / PLY_MVSPD) + 1]
			[gm->player.pos.x / PLY_MVSPD] != '1'))
	{
		gm->player.pos.y += PLY_MVSPD;
		gm->player.moves++;
	}
	if (keycode == KEY_D && (gm->map.layout[(gm->player.pos.y / PLY_MVSPD)]
			[(gm->player.pos.x / PLY_MVSPD) + 1] != '1'))
	{
		gm->player.pos.x += PLY_MVSPD;
		gm->player.moves++;
	}
}

/* Check whether the player wins (exiting) or loses (touching the enemy) */
void	sl_checkwinlose(t_gm *gm)
{
	if (gm->map.layout[gm->player.pos.y / PLY_MVSPD][gm->player.pos.x
		/ PLY_MVSPD] == 'E' && gm->player.pickups == gm->map.n_pick)
	{
		ft_printf("PLAYER WINS!!!\n");
		sl_exit(gm);
	}
	if (gm->enemy.pos.x == gm->player.pos.x
		&& gm->enemy.pos.y == gm->player.pos.y)
	{
		ft_printf("ENEMY WINS!!!\n");
		sl_exit(gm);
	}
}

/* Checks whether a collectible had been picked up, the door is opened,
** the player reached the door or touched the enemy */
void	sl_mapevents(t_gm *gm)
{
	sl_checkwinlose(gm);
	if (gm->map.layout[gm->player.pos.y / PLY_MVSPD][gm->player.pos.x
		/ PLY_MVSPD] == 'C')
	{
		gm->map.layout[gm->player.pos.y / PLY_MVSPD][gm->player.pos.x
			/ PLY_MVSPD] = '0';
		gm->player.pickups++;
	}
	if (gm->map.layout[gm->player.pos.y / PLY_MVSPD][gm->player.pos.x
		/ PLY_MVSPD] == 'T')
	{
		gm->player.pos.x = gm->map.tprt.rec_pos.x;
		gm->player.pos.y = gm->map.tprt.rec_pos.y;
		gm->map.layout[gm->map.tprt.tel_pos.y
			/ PLY_MVSPD][gm->map.tprt.tel_pos.x / PLY_MVSPD] = 'R';
		gm->map.layout[gm->map.tprt.rec_pos.y
			/ PLY_MVSPD][gm->map.tprt.rec_pos.x / PLY_MVSPD] = 'T';
	}
	sl_printply(gm);
}
